// =============================================================================
// Project:         Potentia AHDSR Module Firmware
// File:            main.cpp
// Author:          Gabriel Garcia; Henrique Amaral Onuki
// Created:         2025-06-25
// Modified:        2025-07-07
// Version:         11.0
// Notes:           Firmware do módulo AHDSR do Projeto Potentia. Desenvolvido
//                      com a biblioteca FunSAPE para plataforma AVR (ATmega328P).
//                      Este módulo realiza controle digital de envelope utilizando
//                      um par de potenciômetros digitais (DS1803) via I2C, leitura
//                      analógica contínua (ADC), comunicação SPI com outro módulo
//                      (VCA), e recebe comandos seriais via USART.
// Purpose:         Controlar a forma do envelope de volume de sinais de áudio com
//                      base em triggers internos ou externos, além de receber comandos
//                      do aplicativo de controle para ajuste dinâmico de parâmetros.
//                      O sistema utiliza timers, interrupções e uma máquina de estados
//                      para orquestrar a operação em tempo real.
// =============================================================================

// =============================================================================
// PRECOMPILER CONSTANT DEFINITIONS
// =============================================================================

#define F_CPU 16000000UL

// =============================================================================
// DEPENDENCIES
// =============================================================================

#include "funsape/funsapeLibGlobalDefines.hpp"
#include "funsape/peripheral/funsapeLibAdc.hpp"
#include "funsape/peripheral/funsapeLibTimer0.hpp"
#include "funsape/peripheral/funsapeLibTimer1.hpp"
#include "funsape/peripheral/funsapeLibInt1.hpp"
#include "funsape/peripheral/funsapeLibInt0.hpp"
#include "funsape/peripheral/funsapeLibPcint2.hpp"
#include "funsape/peripheral/funsapeLibUsart0.hpp"
#include "funsape/peripheral/funsapeLibTwi.hpp"
#include "spi/atmega328pSpi.hpp"

// =============================================================================
// CONSTANT DEFINITIONS
// =============================================================================

#define TRIGGER_SECTION           0x00
#define TRIGGER_AUTO              0x00
#define TRIGGER_MANUAL_AND_OFF    0x01
#define TRIGGER_MANUAL_AND_ON     0x03
#define SLA0_W                    0b01010000
#define SLA1_W                    0b01010010
#define WR_POT_0                  0b10101001
#define ADC_CMD_BYTE              0b11000011
#define WAVE_FORM_CMD_BYTE        0b00111100

//=============================================================================
// ENUMERATIONS
//=============================================================================

enum {
    LOAD_ADC_VALUE,
    ADC_VALUE_LOADED,
    SPI_ADC_END,
    LOAD_WAVE_FORM_MODE,
    WF_MODE_LOADED,
    LOAD_WAVE_FORM_FREQ_HIGH,
    WF_FREQ_HIGH_LOADED,
    LOAD_WAVE_FORM_FREQ_LOW,
    WF_FREQ_LOW_LOADED,
    SPI_WAVE_FORM_END
} typedef SpiState;

// =============================================================================
// NEW DATA TYPES
// =============================================================================

typedef union {
    struct {
        bool_t newUsartData     : 1;        // Bit 0
        bool_t spiBusy          : 1;        // Bit 1
        bool_t newAdcData       : 1;        // Bit 2
        bool_t newWaveFormData  : 1;        // Bit 3
        uint8_t unused          : 4;        // Bits 4-7 (future flags)
    };
    volatile uint8_t allFlags;              // Access all bits as uint8_t
} BooleanFlags_t;

typedef struct {
    volatile BooleanFlags_t boolFlags;      // Boolean flags
    volatile SpiState spiState;             // SPI machine state
} SystemFlags;

// =============================================================================
// STATIC FUNCTION DECLARATIONS
// =============================================================================

// NONE

//=============================================================================
// GLOBAL VARIABLES
//=============================================================================

SystemFlags systemFlags = {
    .boolFlags = {.allFlags = 0},
    .spiState = SPI_ADC_END,
};

volatile uint16_t adcValue;
volatile uint8_t triggerMode = 1;
volatile uint8_t attackByte;
volatile uint8_t decayAndReleaseByte;
volatile uint8_t holdByte;
volatile uint8_t sustainByte;
volatile uint8_t waveFormMode;
volatile uint8_t waveFormFreqHigh;
volatile uint8_t waveFormFreqLow;
volatile uint8_t timer1FreqHigh;
volatile uint8_t timer1FreqLow;

//=============================================================================
// FUNCTION PROTOTYPES
//=============================================================================

void jackDetectorInput();
void updateDigipots();
void setTriggerAuto();
void setTriggerManualOn();
void setTriggerManualOff();
void setTrigger(uint8_t triggerMod);
void checkPairing();

//=============================================================================
// TRIGGER FUNCTIONS
//=============================================================================

// Change between EXTERNAL or INTERNAL Trigger
void jackDetectorInput()
{
    if(bit_is_set(PIND, PD4)) {              // EXTERNAL
        timer1.setClockSource(
                Timer1::ClockSource::DISABLED
        );
        timer1.setOutputMode(
                Timer1::OutputMode::NORMAL,
                Timer1::OutputMode::NORMAL
        );
        int1.activateInterrupt();
    } else {                                // INTERNAL
        setTrigger(triggerMode);
        int1.deactivateInterrupt();
    }
}

// Set Trigger Function
void setTrigger(uint8_t triggerMode)
{
    if(bit_is_clear(PIND, PD4)) {
        switch(triggerMode) {
        case TRIGGER_AUTO:
            setTriggerAuto();
            break;
        case TRIGGER_MANUAL_AND_ON:
            setTriggerManualOn();
            break;
        case TRIGGER_MANUAL_AND_OFF:
            setTriggerManualOff();
            break;
        }
    }
}

// Configure Trigger in AUTO mode
void setTriggerAuto()
{
    timer1.setOutputMode(
            Timer1::OutputMode::TOGGLE_ON_COMPARE,
            Timer1::OutputMode::NORMAL
    );
    timer1.setClockSource(
            Timer1::ClockSource::PRESCALER_256
    );
    timer1.setCounterValue(0);
}

// Set Trigger PIN in HIGH
void setTriggerManualOn()
{
    timer1.setOutputMode(
            Timer1::OutputMode::NORMAL,
            Timer1::OutputMode::NORMAL
    );
    setBit(PORTB, PB1);
}

// Set Trigger PIN in LOW
void setTriggerManualOff()
{
    timer1.setOutputMode(
            Timer1::OutputMode::NORMAL,
            Timer1::OutputMode::NORMAL
    );
    clrBit(PORTB, PB1);
}

//=============================================================================
// DIGIPOT FUNCTIONS
//=============================================================================

// Configure DS1803 via I2C
void updateDigipots()
{
    // First DS1803
    twi.setDevice(SLA0_W >> 1, false);  // 0x50 >> 1 = 0x28
    uint8_t payload0[] = { attackByte, decayAndReleaseByte };
    twi.writeReg(WR_POT_0, payload0, 2);

    // Second DS1803
    twi.setDevice(SLA1_W >> 1, false);  // 0x52 >> 1 = 0x29
    uint8_t payload1[] = { holdByte, sustainByte };
    twi.writeReg(WR_POT_0, payload1, 2);
}

//=============================================================================
// PAIRING FUNCTIONS
//=============================================================================

void checkPairing()
{
    if(bit_is_set(PIND, PD2)) {
        timer0.setClockSource(
                Timer0::ClockSource::DISABLED
        );
    } else {
        timer0.setClockSource(
                Timer0::ClockSource::PRESCALER_1024
        );
        timer0.setCounterValue(0);
    }
}

//=============================================================================
// MAIN FUNCTION
//=============================================================================

int main()
{
    // =========================================================================
    // Variable declaration
    // =========================================================================

    // NONE

    // =========================================================================
    // PCINT2 CONFIGURATION
    // =========================================================================

    // Configure PCINT20, PD4
    pcint2.enablePins(
            Pcint2::Pin::PIN_PCINT20
    );
    pcint2.clearInterruptRequest();
    pcint2.activateInterrupt();
    clrBit(DDRD, PD4);
    setBit(PORTD, PD4);

    // =========================================================================
    // INT0 CONFIGURATION
    // =========================================================================

    int0.init(
            Int0::SenseMode::BOTH_EDGES
    );
    int0.activateInterrupt();
    clrBit(DDRD, PD2);
    setBit(PORTD, PD2);

    // =========================================================================
    // INT1 CONFIGURATION
    // =========================================================================

    int1.init(
            Int1::SenseMode::BOTH_EDGES
    );

    // =========================================================================
    // SPI CONFIGURATION
    // =========================================================================

    Spi::init(
            Spi::Mode::SLAVE,
            Spi::ClockRate::FOSC_64,
            Spi::DataMode::MODE_2
    );
    Spi::activateSpiCallbackInterrupt();

    // =========================================================================
    // I2C CONFIGURATION
    // =========================================================================

    twi.init(100'000);

    // =========================================================================
    // USART0 CONFIGURATION
    // =========================================================================

    usart0.setFrameFormat(
            Usart0::FrameFormat::FRAME_FORMAT_8_N_1
    );
    usart0.setBaudRate(
            Usart0::BaudRate::BAUD_RATE_9600
    );
    usart0.init();
    usart0.enableReceiver();
    usart0.activateReceptionCompleteInterrupt();

    // =========================================================================
    // ADC CONFIGURATION
    // =========================================================================

    adc.init(
            Adc::Mode::AUTO_TIMER0_COMPA,
            Adc::Reference::POWER_SUPPLY,
            Adc::Prescaler::PRESCALER_128
    );
    adc.setChannel(
            Adc::Channel::CHANNEL_0
    );
    adc.clearInterruptRequest();
    adc.activateInterrupt();
    adc.enable();

    // =========================================================================
    // TIMER0 CONFIGURATION
    // =========================================================================

    timer0.setCompareAValue(155);
    timer0.setMode(
            Timer0::Mode::CTC_OCRA
    );
    timer0.clearCompareAInterruptRequest();

    // =========================================================================
    // TIMER1 CONFIGURATION
    // =========================================================================

    timer1.init(
            Timer1::Mode::CTC_OCRA,
            Timer1::ClockSource::PRESCALER_256
    );
    timer1.setCompareAValue(10416);
    timer1.setOutputMode(
            Timer1::OutputMode::TOGGLE_ON_COMPARE,
            Timer1::OutputMode::NORMAL
    );
    setBit(DDRB, PB1);

    // =========================================================================
    // COMMUNICATION PIN CONFIGURATION
    // =========================================================================

    setBit(DDRC, PC1);
    clrBit(PORTC, PC1);

    // =========================================================================
    // INIT CHECKS
    // =========================================================================

    // Chack Jack Detector
    jackDetectorInput();

    // Check VCA Pairing
    checkPairing();

    // =========================================================================
    // ENABLE GLOBAL INTERRUPTS
    // =========================================================================

    sei();

    // =========================================================================
    // MAIN LOOP
    // =========================================================================

    while(true) {
        if(systemFlags.boolFlags.newUsartData && !systemFlags.boolFlags.spiBusy) {
            systemFlags.boolFlags.newUsartData = false;
            timer1.setCompareAValue((timer1FreqHigh << 8) | timer1FreqLow);
            updateDigipots();

            SPDR = WAVE_FORM_CMD_BYTE;
            //systemFlags.boolFlags.spiBusy = true;
            systemFlags.spiState = LOAD_WAVE_FORM_MODE;
            setBit(PORTC, PC1);

        } else if(systemFlags.boolFlags.newAdcData && !systemFlags.boolFlags.spiBusy) {

            SPDR = ADC_CMD_BYTE;
            systemFlags.boolFlags.spiBusy = true;
            systemFlags.spiState = LOAD_ADC_VALUE;
            setBit(PORTC, PC1);
        }

        switch(systemFlags.spiState) {

        case WF_MODE_LOADED:
            systemFlags.spiState = LOAD_WAVE_FORM_FREQ_HIGH;
            setBit(PORTC, PC1);
            break;

        case WF_FREQ_HIGH_LOADED:
            systemFlags.spiState = LOAD_WAVE_FORM_FREQ_LOW;
            setBit(PORTC, PC1);
            break;

        case WF_FREQ_LOW_LOADED:
            systemFlags.spiState = SPI_WAVE_FORM_END;
            setBit(PORTC, PC1);
            break;

        case ADC_VALUE_LOADED:
            systemFlags.spiState = SPI_ADC_END;
            setBit(PORTC, PC1);
            break;

        default:
            break;
        }
    }

    return 0;
}

//=============================================================================
// INTERRUPT HANDLERS
//=============================================================================

// ADC Conversion Interrupt
void adcConversionCompleteCallback(void)
{
    adcValue = ADC;
    timer0.clearCompareAInterruptRequest();
    systemFlags.boolFlags.newAdcData = true;
}

// SPI Interrupt
void Spi::spiCallbackInterrupt(uint8_t received)
{
    uint8_t status = SPSR;
    uint8_t cleanSPDR = SPDR;
    (void)status;
    (void)cleanSPDR;

    clrBit(PORTC, PC1);

    switch(systemFlags.spiState) {
    case LOAD_WAVE_FORM_MODE:
        SPDR = waveFormMode;
        systemFlags.spiState = WF_MODE_LOADED;
        break;

    case LOAD_WAVE_FORM_FREQ_HIGH:
        SPDR = waveFormFreqHigh;
        systemFlags.spiState = WF_FREQ_HIGH_LOADED;
        break;

    case LOAD_WAVE_FORM_FREQ_LOW:
        SPDR = waveFormFreqLow;
        systemFlags.spiState = WF_FREQ_LOW_LOADED;
        break;

    case SPI_WAVE_FORM_END:
        timer0.setClockSource(
                Timer0::ClockSource::PRESCALER_1024
        );
        timer0.setCounterValue(0);
        systemFlags.boolFlags.newWaveFormData = false;
        systemFlags.boolFlags.spiBusy = false;
        break;

    case LOAD_ADC_VALUE:
        systemFlags.spiState = ADC_VALUE_LOADED;
        SPDR = adcValue >> 2;
        break;

    case SPI_ADC_END:
        systemFlags.boolFlags.newAdcData = false;
        systemFlags.boolFlags.spiBusy = false;
        break;

    default:
        break;
    }
}

// INT0 Interrupt
void int0InterruptCallback()
{
    checkPairing();
}

// INT1 Interrupt
void int1InterruptCallback()
{
    if(PIND & (1 << PD3)) {
        // Activate trigger
        setBit(PORTB, PB1);
    } else {
        // Deactivate trigger
        clrBit(PORTB, PB1);
    }
}

// PCINT2 Interrupt
void pcint2InterruptCallback()
{
    jackDetectorInput();
}

// USART Interrupt
void usartReceptionCompleteCallback()
{
    static uint8_t byteIndex = 0;
    static uint8_t buffer[10];
    static uint8_t expectedBytes = 0;

    uint8_t data = UDR0;

    if(byteIndex == 0) {
        buffer[0] = data;
        expectedBytes = (buffer[0] == TRIGGER_SECTION) ? 2 : 10;
        byteIndex = 1;
        return;
    }

    buffer[byteIndex++] = data;

    if(byteIndex == expectedBytes) {
        if(buffer[0] == TRIGGER_SECTION) {
            triggerMode = buffer[1];
            setTrigger(triggerMode);
        } else {
            attackByte = buffer[1];
            holdByte = buffer[2];
            sustainByte = buffer[3];
            decayAndReleaseByte = buffer[4];
            waveFormMode = buffer[5];
            waveFormFreqHigh = buffer[6];
            waveFormFreqLow = buffer[7];
            timer1FreqHigh = buffer[8];
            timer1FreqLow = buffer[9];

            systemFlags.boolFlags.newUsartData = true;
            timer0.setClockSource(
                    Timer0::ClockSource::DISABLED
            );
        }
        byteIndex = 0;
    }
}

// =============================================================================
// END OF FILE
// =============================================================================
