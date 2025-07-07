/*
 * Project:  Digipot Control
 * File:     main.cpp
 * Author:   Gabriel Garcia; Henrique Onuki
 * Created:  2025-04-19
 * Modified: 2025-07-07
 * Version:  10.0
 * Notes:    Controle de Digipots. Fcpu = 16 MHz.
 */

#define F_CPU 16000000UL

//=============================================================================
// INCLUDES
//=============================================================================
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

//=============================================================================
// DEFINITIONS
//=============================================================================
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
    SPI_ADC,
    SEND_ADC_BYTE,
    SPI_ADC_END,
    SPI_WAVE_FORM,
    SEND_WAVE_FORM_BYTE,
    SPI_WAVE_FORM_END
} typedef SpiState;

//=============================================================================
// STRUCTURES
//=============================================================================
typedef union {
    struct {
        bool_t newUsartData     : 1;        // Bit 0
        bool_t spiBusy          : 1;        // Bit 1
        bool_t newAdcData       : 1;        // Bit 2
        bool_t newWaveFormData  : 1;        // Bit 3
        uint8_t unused          : 4;        // Bits 4-7 (future flags)
    };
    volatile uint8_t allFlags;              // Acess all bits as uint8_t
} BooleanFlags_t;

typedef struct {
    volatile BooleanFlags_t boolFlags;      // Boolean flags
    volatile SpiState spiState;             // SPI machine state
    volatile uint8_t triggerMode;           // Trigger mode
    volatile uint8_t timer1FreqHigh;        // Byte alto da frequência Timer1
    volatile uint8_t timer1FreqLow;         // Byte baixo da frequência Timer1
} SystemFlags;

//=============================================================================
// GLOBAL VARIABLES
//=============================================================================
SystemFlags systemFlags = {
    .boolFlags = {.allFlags = 0},          
    .spiState = SPI_ADC,
    .triggerMode = 1,
    .timer1FreqHigh = 0,
    .timer1FreqLow = 0
};

volatile uint16_t adcValue = 0;

volatile uint8_t attackByte = 2;
volatile uint8_t decayAndReleaseByte = 4;
volatile uint8_t holdByte = 8;
volatile uint8_t sustainByte = 16;

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
    if(bit_is_set(PIND, PD4)) {             // EXTERNAL
        timer1.setClockSource(Timer1::ClockSource::DISABLED);
        timer1.setOutputMode(Timer1::OutputMode::NORMAL, Timer1::OutputMode::NORMAL);
        int1.activateInterrupt();
    } else {                                // INTERNAL
        setTrigger(systemFlags.triggerMode);
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
    timer1.setOutputMode(Timer1::OutputMode::TOGGLE_ON_COMPARE, Timer1::OutputMode::NORMAL);
    timer1.setClockSource(Timer1::ClockSource::PRESCALER_256);
    timer1.setCounterValue(0);
}

// Set Trigger PIN in HIGH
void setTriggerManualOn()
{
    timer1.setOutputMode(Timer1::OutputMode::NORMAL, Timer1::OutputMode::NORMAL);
    setBit(PORTB, PB1);
}

// Set Trigger PIN in LOW
void setTriggerManualOff()
{
    timer1.setOutputMode(Timer1::OutputMode::NORMAL, Timer1::OutputMode::NORMAL);
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
        timer0.setClockSource(Timer0::ClockSource::DISABLED);
    } else {
        timer0.setClockSource(Timer0::ClockSource::PRESCALER_1024);
        timer0.setCounterValue(0);
    }
}

//=============================================================================
// MAIN FUNCTION
//=============================================================================
int main()
{
    // Configure PCINT20, PD4
    pcint2.enablePins(Pcint2::Pin::PIN_PCINT20);
    pcint2.clearInterruptRequest();
    pcint2.activateInterrupt();
    clrBit(DDRD, PD4);
    setBit(PORTD, PD4);

    // Configure INT0
    int0.init(Int0::SenseMode::BOTH_EDGES);
    int0.activateInterrupt();
    clrBit(DDRD, PD2);
    setBit(PORTD, PD2);

    // Configure INT1
    int1.init(Int1::SenseMode::BOTH_EDGES);

    // Configure SPI
    Spi::init(Spi::Mode::SLAVE, Spi::ClockRate::FOSC_64, Spi::DataMode::MODE_3);
    Spi::activateSpiCallbackInterrupt();

    // Configure I2C
    twi.init(100'000);

    // Configure USART
    usart0.setFrameFormat(Usart0::FrameFormat::FRAME_FORMAT_8_N_1);
    usart0.setBaudRate(Usart0::BaudRate::BAUD_RATE_9600);
    usart0.init();
    usart0.enableReceiver();
    usart0.activateReceptionCompleteInterrupt();

    // Configure ADC
    adc.init(
            Adc::Mode::AUTO_TIMER0_COMPA,
            Adc::Reference::POWER_SUPPLY,
            Adc::Prescaler::PRESCALER_128
    );
    adc.setDataAdjust(Adc::DataAdjust::LEFT);
    adc.setChannel(Adc::Channel::CHANNEL_0);
    adc.clearInterruptRequest();
    adc.activateInterrupt();
    adc.enable();

    // Configure Timer0
    timer0.setCompareAValue(155);
    timer0.setMode(Timer0::Mode::CTC_OCRA);
    timer0.clearCompareAInterruptRequest();

    // Configure Timer1
    timer1.init(Timer1::Mode::CTC_OCRA, Timer1::ClockSource::PRESCALER_256);
    timer1.setCompareAValue(10416);
    timer1.setOutputMode(Timer1::OutputMode::TOGGLE_ON_COMPARE, Timer1::OutputMode::NORMAL);
    setBit(DDRB, PB1);

    // Set PC1 (Communication PIN)
    setBit(DDRC, PC1);
    clrBit(PORTC, PC1);

    // Chack Jack Detector
    jackDetectorInput();

    // Check VCA Pairing
    checkPairing();

    // Debug
    setBit(DDRD, PD7);
    setBit(PORTD, PD7);

    // Enable Global Interrupts
    sei();

    while(true) {
        if(systemFlags.boolFlags.newUsartData && !systemFlags.boolFlags.spiBusy) {
            systemFlags.boolFlags.newUsartData = false;
            timer1.setCompareAValue((systemFlags.timer1FreqHigh << 8) | systemFlags.timer1FreqLow);
            updateDigipots();

            SPDR = WAVE_FORM_CMD_BYTE;
            //systemFlags.boolFlags.spiBusy = true;
            systemFlags.spiState = SPI_WAVE_FORM;
            setBit(PORTC, PC1);

        } else if(systemFlags.boolFlags.newAdcData && !systemFlags.boolFlags.spiBusy) {

            SPDR = ADC_CMD_BYTE;
            systemFlags.boolFlags.spiBusy = true;
            systemFlags.spiState = SPI_ADC;
            setBit(PORTC, PC1);
        }

        switch(systemFlags.spiState) {

        case SEND_WAVE_FORM_BYTE:
            systemFlags.spiState = SPI_WAVE_FORM_END;
            setBit(PORTC, PC1);
            break;

        case SEND_ADC_BYTE:
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
    adcValue = ADCH;
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
    case SPI_WAVE_FORM:
        SPDR = 0;
        systemFlags.spiState = SEND_WAVE_FORM_BYTE;
        break;

    case SPI_WAVE_FORM_END:
        timer0.setClockSource(Timer0::ClockSource::PRESCALER_1024);
        timer0.setCounterValue(0);
        systemFlags.boolFlags.newWaveFormData = false;
        systemFlags.boolFlags.spiBusy = false;
        break;

    case SPI_ADC:
        SPDR = adcValue;
        systemFlags.spiState = SEND_ADC_BYTE;
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
    cplBit(PORTD, PD7);
}

// USART Interrupt
void usartReceptionCompleteCallback()
{
    static uint8_t byteIndex = 0;
    static uint8_t buffer[7];
    static uint8_t expectedBytes = 0;

    uint8_t data = UDR0;

    if(byteIndex == 0) {
        buffer[0] = data;
        expectedBytes = (buffer[0] == TRIGGER_SECTION) ? 2 : 7;
        byteIndex = 1;
        return;
    }

    buffer[byteIndex++] = data;

    if(byteIndex == expectedBytes) {
        if(buffer[0] == TRIGGER_SECTION) {
            systemFlags.triggerMode = buffer[1];
            setTrigger(systemFlags.triggerMode);
        } else {
            attackByte = buffer[1];
            holdByte = buffer[2];
            sustainByte = buffer[3];
            decayAndReleaseByte = buffer[4];
            systemFlags.timer1FreqHigh = buffer[5];
            systemFlags.timer1FreqLow = buffer[6];

            systemFlags.boolFlags.newUsartData = true;
            timer0.setClockSource(Timer0::ClockSource::DISABLED);
        }
        byteIndex = 0;
    }
}
