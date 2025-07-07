/*
 * Project:  Digipot Control
 * File:     main.cpp
 * Author:   Gabriel Garcia; Henrique Onuki
 * Created:  2025-04-19
 * Modified: 2025-07-07
 * Version:  8.0
 * Notes:    Controle de Digipots. Fcpu = 16 MHz.
 */

#define F_CPU 16000000UL

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

// Definitions
#define TRIGGER_SECTION           0x00
#define TRIGGER_AUTO              0x00
#define TRIGGER_MANUAL_AND_OFF    0x01
#define TRIGGER_MANUAL_AND_ON     0x03
#define SLA0_W                    0b01010000
#define SLA1_W                    0b01010010
#define WR_POT_0                  0b10101001
#define ADC_CMD_BYTE              0b11000011
#define WAVE_FORM_CMD_BYTE        0b00111100

// Global Variables
volatile bool_t newUsartData = false;

volatile bool_t spiBusy = false;
volatile bool_t newAdcData = false;
volatile bool_t newWaveFormData = false;
volatile uint16_t adcValue = 0;

volatile uint8_t attackByte = 2;
volatile uint8_t decayAndReleaseByte = 4;
volatile uint8_t holdByte = 8;
volatile uint8_t sustainByte = 16;

volatile uint8_t triggerByte = 1;
volatile uint8_t timer1FreqByteHigh = 0;
volatile uint8_t timer1FreqByteLow = 0;

enum {
    SPI_ADC,
    SEND_ADC_BYTE,
    SPI_ADC_END,
    SPI_WAVE_FORM,
    SEND_WAVE_FORM_BYTE,
    SPI_WAVE_FORM_END
} typedef SpiState;

SpiState spiState;

// Function Prototypes
void jackDetectorInput();
void updateDigipots();
void setTriggerAuto();
void setTriggerManualOn();
void setTriggerManualOff();
void setTrigger(uint8_t triggerMod);

// Change between EXTERNAL or INTERNAL Trigger
void jackDetectorInput()
{
    if(bit_is_set(PIND, PD4)) {       // EXTERNAL
        timer1.setClockSource(Timer1::ClockSource::DISABLED);
        timer1.setOutputMode(Timer1::OutputMode::NORMAL, Timer1::OutputMode::NORMAL);
        int1.activateInterrupt();
    } else {                            // INTERNAL
        setTrigger(triggerByte);
        int1.deactivateInterrupt();
    }
}

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

void checkPairing()
{
    if(bit_is_set(PIND, PD2)) {
        timer0.setClockSource(Timer0::ClockSource::DISABLED);
    } else {
        timer0.setClockSource(Timer0::ClockSource::PRESCALER_1024);
        timer0.setCounterValue(0);
    }
}

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
        if(newUsartData && !spiBusy) {
            newUsartData = false;
            timer1.setCompareAValue((timer1FreqByteHigh << 8) | timer1FreqByteLow);
            updateDigipots();

            SPDR = WAVE_FORM_CMD_BYTE;
            //spiBusy = true;
            spiState = SPI_WAVE_FORM;
            setBit(PORTC, PC1);

        } else if(newAdcData && !spiBusy) {

            SPDR = ADC_CMD_BYTE;
            spiBusy = true;
            spiState = SPI_ADC;
            setBit(PORTC, PC1);
        }

        switch(spiState) {

        case SEND_WAVE_FORM_BYTE:
            spiState = SPI_WAVE_FORM_END;
            setBit(PORTC, PC1);
            break;

        case SEND_ADC_BYTE:
            spiState = SPI_ADC_END;
            setBit(PORTC, PC1);
            break;

        default:
            break;
        }
    }

    return 0;
}

// ADC Conversion Interrupt
void adcConversionCompleteCallback(void)
{
    adcValue = ADCH;
    timer0.clearCompareAInterruptRequest();
    newAdcData = true;
}

// SPI Interrupt
void Spi::spiCallbackInterrupt(uint8_t received)
{
    uint8_t status = SPSR;
    uint8_t cleanSPDR = SPDR;
    (void)status;
    (void)cleanSPDR;

    clrBit(PORTC, PC1);

    switch(spiState) {
    case SPI_WAVE_FORM:
        SPDR = 0;
        spiState = SEND_WAVE_FORM_BYTE;
        break;

    case SPI_WAVE_FORM_END:
        timer0.setClockSource(Timer0::ClockSource::PRESCALER_1024);
        timer0.setCounterValue(0);
        newWaveFormData = false;
        spiBusy = false;
        break;

    case SPI_ADC:
        SPDR = adcValue;
        spiState = SEND_ADC_BYTE;
        break;

    case SPI_ADC_END:
        newAdcData = false;
        spiBusy = false;
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
            triggerByte = buffer[1];
            setTrigger(triggerByte);
        } else {
            attackByte = buffer[1];
            holdByte = buffer[2];
            sustainByte = buffer[3];
            decayAndReleaseByte = buffer[4];
            timer1FreqByteHigh = buffer[5];
            timer1FreqByteLow = buffer[6];

            newUsartData = true;
            timer0.setClockSource(Timer0::ClockSource::DISABLED);
        }
        byteIndex = 0;
    }
}
