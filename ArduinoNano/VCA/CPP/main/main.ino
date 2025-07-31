/**
 * =============================================================================
 * Project:         Potentia VCA Module Firmware
 * File:            main.ino
 * Author:          Gabriel Garcia; Henrique Amaral Onuki
 * Created:         2025-07-09
 * Modified:        2025-07-31
 * Version:         7.0 (Traduzido e Reorganizado por GitHub Copilot)
 * Description:     Master SPI communication with OLED graphic rendering.
 *                  Receives commands from slave (ADC or waveform) and displays
 *                  data graphically in real time.
 * Purpose:         Multiplex amplified audio sources through VCA, control
 *                  internal wave generator, receive AHDSR envelope data for
 *                  display, and handle configuration changes.
 * =============================================================================
 */

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MD_AD9833.h>
#include <Wire.h>

// =============================================================================
// HARDWARE CONFIGURATION
// =============================================================================
namespace Config {
    // Display
    constexpr uint8_t SCREEN_WIDTH = 128;
    constexpr uint8_t SCREEN_HEIGHT = 64;
    constexpr uint8_t OLED_RESET = -1;
    constexpr uint8_t OLED_ADDRESS = 0x3C;
    
    // SPI Commands
    constexpr uint8_t ADC_COMMAND = 0b11000011;
    constexpr uint8_t WAVEFORM_COMMAND = 0b00111100;
    
    // Timing
    constexpr uint16_t SLAVE_READY_WAIT_MS = 3;
    constexpr uint16_t FINALIZE_WAIT_MS = 5;
    constexpr uint16_t SPLASH_DELAY_MS = 3000;
    constexpr uint16_t INIT_DELAY_MS = 1400;
    
    // Pins
    constexpr uint8_t FSYNC_PIN = 9;
    constexpr uint8_t DATA_READY_PIN = A0;    // PC0
    constexpr uint8_t EXT_DETECT_PIN = 8;     // PB0
    constexpr uint8_t BUTTON_PIN = 2;         // PD2
    
    // MUX Control Pins
    constexpr uint8_t MUX_PIN_A = 5;  // PD5
    constexpr uint8_t MUX_PIN_B = 6;  // PD6
    constexpr uint8_t MUX_PIN_C = 7;  // PD7
    
    // Graph settings
    constexpr uint8_t GRAPH_COLS = SCREEN_WIDTH;
    constexpr uint8_t GRAPH_H_SCALE = 6;
    constexpr uint8_t GRAPH_TOP_LINE = 16;
}

// =============================================================================
// ENUMERATIONS & STRUCTURES
// =============================================================================
enum class SPIState : uint8_t {
    IDLE,
    WAIT_SLAVE_READY,
    RECEIVING_COMMAND,
    RECEIVING_ADC_DATA,
    RECEIVING_WAVEFORM_MODE,
    RECEIVING_WAVEFORM_FREQ_HIGH,
    RECEIVING_WAVEFORM_FREQ_LOW,
    WAIT_NEXT_DATA,
    FINALIZING
};

enum class VCAMode : uint8_t {
    SINGLE,
    POTENTIA
};

enum class AudioSource : uint8_t {
    EXT = 0,
    NOISE = 1,
    INT = 2
};

enum class WaveformType : uint8_t {
    SQUARE = 0,
    TRIANGLE = 1,
    SINE = 2,
    NOISE = 3
};

struct WaveformData {
    WaveformType type = WaveformType::SQUARE;
    uint16_t frequency = 1000;
    bool ready = false;
};

// =============================================================================
// GLOBAL OBJECTS & VARIABLES
// =============================================================================
Adafruit_SSD1306 display(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, &Wire, Config::OLED_RESET);
MD_AD9833 waveGenerator(Config::FSYNC_PIN);

// State variables
volatile SPIState spiState = SPIState::IDLE;
volatile VCAMode operatingMode = VCAMode::SINGLE;
volatile AudioSource currentAudioSource = AudioSource::EXT;

// Communication variables
volatile uint8_t receivedByte = 0;
volatile uint8_t currentCommand = 0;
volatile uint8_t waveformBytesReceived = 0;
volatile uint16_t stateTimer = 0;

// Flags
volatile bool dataReadyFlag = false;
volatile bool timerTickFlag = false;
volatile bool blinkState = false;
volatile bool drawGraphFlag = false;
volatile bool lastDataReadyState = false;
volatile bool lastExtDetectState = false;

// Graph and display data
volatile uint8_t graphBuffer[Config::GRAPH_COLS] = {0};
volatile uint8_t graphValue = 0;
WaveformData waveformData;

// =============================================================================
// HARDWARE ABSTRACTION LAYER
// =============================================================================
namespace HAL {
    inline bool isSlaveReady() {
        return (PINC & (1 << PC0)) == 0;
    }
    
    inline void setSPISlaveSelect(bool active) {
        if (active) {
            PORTB &= ~(1 << PB2);  // Active low
        } else {
            PORTB |= (1 << PB2);   // Inactive high
        }
    }
    
    inline void setMuxChannel(AudioSource source) {
        // Disable all channels first
        PORTD |= (1 << PD7) | (1 << PD6) | (1 << PD5);
        
        // Enable selected channel
        switch (source) {
            case AudioSource::EXT:
                PORTD &= ~(1 << PD5);
                break;
            case AudioSource::NOISE:
                PORTD &= ~(1 << PD7);
                break;
            case AudioSource::INT:
                PORTD &= ~(1 << PD6);
                break;
        }
    }
    
    inline void setSPIMode(bool mode3) {
        if (mode3) {
            SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | 
                   (1 << SPIE) | (1 << CPOL) | (1 << CPHA);
        } else {
            SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | 
                   (1 << SPIE) | (1 << CPOL);
        }
    }
}

// =============================================================================
// INITIALIZATION FUNCTIONS
// =============================================================================
void initSPI() {
    // Configure SPI pins
    DDRB |= (1 << PB2) | (1 << PB3) | (1 << PB5);  // SS, MOSI, SCK as outputs
    DDRB &= ~(1 << PB4);                            // MISO as input
    PORTB |= (1 << PB2);                            // SS high initially
    
    // Initialize SPI in Mode 3
    HAL::setSPIMode(true);
}

void initGPIO() {
    // Button (INT0)
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);  // Pull-up
    
    // MUX control pins
    DDRD |= (1 << PD7) | (1 << PD6) | (1 << PD5);
    PORTD |= (1 << PD7) | (1 << PD6);  // Default state
    
    // Data ready pin (PC0)
    DDRC &= ~(1 << PC0);
    PORTC |= (1 << PC0);  // Pull-up
    
    // External detect pin (PB0)
    DDRB &= ~(1 << PB0);
    PORTB |= (1 << PB0);  // Pull-up
}

void initInterrupts() {
    // External interrupt INT0 (button)
    EICRA |= (1 << ISC01);  // Falling edge
    EIMSK |= (1 << INT0);
    
    // Pin change interrupts
    PCICR |= (1 << PCIE1) | (1 << PCIE0);  // Enable PORTC and PORTB
    PCMSK1 |= (1 << PCINT8);               // PC0
    PCMSK0 |= (1 << PCINT0);               // PB0
    
    // Read initial states
    lastDataReadyState = (PINC & (1 << PC0)) != 0;
    lastExtDetectState = (PINB & (1 << PB0)) != 0;
}

void initTimers() {
    // Timer1: 100ms intervals for blinking
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);  // CTC, prescaler 1024
    OCR1A = 6249;  // ~100ms at 16MHz
    TIMSK1 |= (1 << OCIE1A);
    
    // Timer2: ~1ms intervals for state machine
    TCCR2A = (1 << WGM21);                               // CTC
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);   // Prescaler 1024
    OCR2A = 15;    // ~1ms at 16MHz
    TIMSK2 |= (1 << OCIE2A);
}

void initWaveGenerator() {
    waveGenerator.begin();
    waveGenerator.reset(true);
    waveGenerator.setFrequency(MD_AD9833::CHAN_0, 1000);
    waveGenerator.setMode(MD_AD9833::MODE_TRIANGLE);
    waveGenerator.reset(false);
}

// =============================================================================
// DISPLAY FUNCTIONS
// =============================================================================
void drawSplashScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    
    if (operatingMode == VCAMode::POTENTIA) {
        display.setCursor(5, 0);
        display.println(F("-POTENTIA-"));
        
        // Draw AHDSR envelope
        const uint8_t points[][2] = {
            {0, 63}, {20, 20}, {30, 20}, {45, 32}, {80, 32}, {110, 63}
        };
        
        for (uint8_t i = 0; i < 5; i++) {
            display.drawLine(points[i][0], points[i][1], 
                           points[i+1][0], points[i+1][1], SSD1306_WHITE);
        }
    } else {
        display.setCursor(10, 0);
        display.println(F("---VCA---"));
        
        // Draw sine wave
        for (uint8_t i = 0; i < Config::SCREEN_WIDTH; i += 4) {
            float angle = (float)i / Config::SCREEN_WIDTH * 2 * PI * 3;
            uint8_t h = 28 + (int)(10 * sin(angle));
            display.drawFastVLine(i, Config::SCREEN_HEIGHT - h, h, SSD1306_WHITE);
        }
    }
    
    display.display();
}

void drawDownArrow(uint8_t x, uint8_t y) {
    if (blinkState) {
        display.fillTriangle(x - 7, y, x + 7, y, x, y + 8, SSD1306_WHITE);
    }
}

void drawAudioSourceSelection() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    
    constexpr uint8_t y = 16;
    constexpr uint8_t textWidth = 36;  // 3 chars * 12px
    
    // Draw labels
    display.setCursor(0, y);
    display.print(F("EXT"));
    
    display.setCursor((Config::SCREEN_WIDTH - textWidth) / 2, y);
    display.print(F("INT"));
    
    display.setCursor(Config::SCREEN_WIDTH - textWidth, y);
    display.print(F("NOI"));
    
    // Draw selection indicator
    uint8_t arrowX = 0;
    switch (currentAudioSource) {
        case AudioSource::EXT: arrowX = 18; break;
        case AudioSource::INT: arrowX = 64; break;
        case AudioSource::NOISE: arrowX = 110; break;
    }
    
    drawDownArrow(arrowX, 3);
    
    display.setTextSize(1);
    display.setCursor(11, 55);
    display.print(F("(Selecionar Audio)"));
    display.display();
}

void updateGraphDisplay() {
    // Map ADC value to display area
    uint8_t y = map(graphValue << 2, 0, 1023, Config::SCREEN_HEIGHT - 1, Config::GRAPH_TOP_LINE);
    static uint8_t prevY = (Config::SCREEN_HEIGHT + Config::GRAPH_TOP_LINE) / 2;
    
    // Smooth interpolation
    for (uint8_t k = 0; k < Config::GRAPH_H_SCALE; k++) {
        float t = (float)(k + 1) / Config::GRAPH_H_SCALE;
        uint8_t yi = prevY + (int)((y - prevY) * t);
        memmove((void*)graphBuffer, (void*)(graphBuffer + 1), Config::GRAPH_COLS - 1);
        graphBuffer[Config::GRAPH_COLS - 1] = yi;
    }
    prevY = y;
    
    display.clearDisplay();
    
    // Display waveform info
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(F("WF: "));
    
    const char* waveNames[] = {"Quadrada", "Triangular", "Senoidal", "Ruido"};
    display.print(waveNames[static_cast<uint8_t>(waveformData.type)]);
    
    display.setCursor(0, 8);
    display.print(F("Freq: "));
    display.print(waveformData.frequency);
    display.print(F(" Hz"));
    
    // Draw graph
    for (uint8_t x = 0; x < Config::GRAPH_COLS - 1; x++) {
        display.drawLine(x, graphBuffer[x], x + 1, graphBuffer[x + 1], SSD1306_WHITE);
    }
    
    display.display();
}

// =============================================================================
// SPI COMMUNICATION
// =============================================================================
void startSPICommunication() {
    if (spiState == SPIState::IDLE) {
        spiState = SPIState::WAIT_SLAVE_READY;
        stateTimer = 0;
        HAL::setSPISlaveSelect(true);
    }
}

void finalizeSPICommunication() {
    HAL::setSPISlaveSelect(false);
    spiState = SPIState::FINALIZING;
    stateTimer = 0;
}

void requestNextByte(SPIState nextState) {
    if (HAL::isSlaveReady()) {
        SPDR = 0x00;
        spiState = nextState;
    } else {
        spiState = SPIState::WAIT_NEXT_DATA;
        stateTimer = 0;
    }
}

void processSPIStateMachine() {
    if (!timerTickFlag) return;
    timerTickFlag = false;
    
    switch (spiState) {
        case SPIState::WAIT_SLAVE_READY:
            if (stateTimer >= Config::SLAVE_READY_WAIT_MS && HAL::isSlaveReady()) {
                spiState = SPIState::RECEIVING_COMMAND;
                stateTimer = 0;
                SPDR = 0x00;
            }
            break;
            
        case SPIState::WAIT_NEXT_DATA:
            if (HAL::isSlaveReady()) {
                SPDR = 0x00;
                stateTimer = 0;
                
                if (currentCommand == Config::ADC_COMMAND) {
                    spiState = SPIState::RECEIVING_ADC_DATA;
                } else if (currentCommand == Config::WAVEFORM_COMMAND) {
                    switch (waveformBytesReceived) {
                        case 1: spiState = SPIState::RECEIVING_WAVEFORM_FREQ_HIGH; break;
                        case 2: spiState = SPIState::RECEIVING_WAVEFORM_FREQ_LOW; break;
                        default: spiState = SPIState::RECEIVING_WAVEFORM_MODE; break;
                    }
                }
            }
            break;
            
        case SPIState::FINALIZING:
            if (stateTimer >= Config::FINALIZE_WAIT_MS) {
                spiState = SPIState::IDLE;
                stateTimer = 0;
            }
            break;
            
        default:
            break;
    }
}

// =============================================================================
// WAVEFORM PROCESSING
// =============================================================================
void applyWaveformConfiguration() {
    if (!waveformData.ready) return;
    
    HAL::setSPIMode(false);  // Switch to Mode 2 for AD9833
    HAL::setMuxChannel(AudioSource::INT);  // Default to internal
    
    switch (waveformData.type) {
        case WaveformType::SQUARE:
            waveGenerator.setMode(MD_AD9833::MODE_SQUARE1);
            currentAudioSource = AudioSource::INT;
            break;
            
        case WaveformType::TRIANGLE:
            waveGenerator.setMode(MD_AD9833::MODE_TRIANGLE);
            currentAudioSource = AudioSource::INT;
            break;
            
        case WaveformType::SINE:
            waveGenerator.setMode(MD_AD9833::MODE_SINE);
            currentAudioSource = AudioSource::INT;
            break;
            
        case WaveformType::NOISE:
            currentAudioSource = AudioSource::NOISE;
            break;
    }
    
    HAL::setMuxChannel(currentAudioSource);
    waveGenerator.setFrequency(MD_AD9833::CHAN_0, waveformData.frequency);
    HAL::setSPIMode(true);  // Back to Mode 3
    
    waveformData.ready = false;
}

VCAMode detectOperatingMode() {
    return HAL::isSlaveReady() ? VCAMode::POTENTIA : VCAMode::SINGLE;
}

void cycleAudioSource() {
    HAL::setMuxChannel(AudioSource::EXT);  // Reset all channels
    
    switch (currentAudioSource) {
        case AudioSource::EXT:
            currentAudioSource = AudioSource::NOISE;
            break;
        case AudioSource::NOISE:
            currentAudioSource = AudioSource::INT;
            break;
        case AudioSource::INT:
            currentAudioSource = AudioSource::EXT;
            break;
    }
    
    HAL::setMuxChannel(currentAudioSource);
}

// =============================================================================
// MAIN FUNCTIONS
// =============================================================================
void setup() {
    // Initialize hardware subsystems
    initWaveGenerator();
    initSPI();
    initGPIO();
    initInterrupts();
    initTimers();
    
    delay(Config::INIT_DELAY_MS);
    
    // Detect operating mode
    operatingMode = detectOperatingMode();
    
    // Initialize display
    display.begin(SSD1306_SWITCHCAPVCC, Config::OLED_ADDRESS);
    display.clearDisplay();
    display.display();
    
    // Show splash screen
    drawSplashScreen();
    delay(Config::SPLASH_DELAY_MS);
    
    // Final mode check
    operatingMode = detectOperatingMode();
    
    sei();  // Enable global interrupts
}

void loop() {
    // Process waveform configuration updates
    applyWaveformConfiguration();
    
    // Handle display updates based on mode
    if (operatingMode == VCAMode::SINGLE) {
        drawAudioSourceSelection();
    } else if (drawGraphFlag) {
        // POTENTIA mode - show graph when data is received
        updateGraphDisplay();
        drawGraphFlag = false;
    }
    
    // Process SPI state machine
    processSPIStateMachine();
    
    // Handle incoming data
    if (dataReadyFlag && spiState == SPIState::IDLE) {
        dataReadyFlag = false;
        startSPICommunication();
    }
}

// =============================================================================
// INTERRUPT SERVICE ROUTINES
// =============================================================================
ISR(INT0_vect) {
    cycleAudioSource();
}

ISR(PCINT0_vect) {
    bool current = (PINB & (1 << PB0)) != 0;
    if (!lastExtDetectState && current) {
        currentAudioSource = AudioSource::EXT;
        HAL::setMuxChannel(currentAudioSource);
    }
    lastExtDetectState = current;
}

ISR(PCINT1_vect) {
    bool current = (PINC & (1 << PC0)) != 0;
    if (lastDataReadyState && !current) {
        dataReadyFlag = true;
    }
    lastDataReadyState = current;
}

ISR(TIMER1_COMPA_vect) {
    blinkState = !blinkState;
}

ISR(TIMER2_COMPA_vect) {
    timerTickFlag = true;
    stateTimer++;
}

ISR(SPI_STC_vect) {
    receivedByte = SPDR;
    
    switch (spiState) {
        case SPIState::RECEIVING_COMMAND:
            if (receivedByte == Config::ADC_COMMAND || 
                receivedByte == Config::WAVEFORM_COMMAND) {
                currentCommand = receivedByte;
                requestNextByte(receivedByte == Config::ADC_COMMAND ? 
                              SPIState::RECEIVING_ADC_DATA : 
                              SPIState::RECEIVING_WAVEFORM_MODE);
            }
            break;
            
        case SPIState::RECEIVING_ADC_DATA:
            graphValue = receivedByte;
            drawGraphFlag = true;
            finalizeSPICommunication();
            break;
            
        case SPIState::RECEIVING_WAVEFORM_MODE:
            waveformData.type = static_cast<WaveformType>(receivedByte);
            waveformBytesReceived = 1;
            requestNextByte(SPIState::RECEIVING_WAVEFORM_FREQ_HIGH);
            break;
            
        case SPIState::RECEIVING_WAVEFORM_FREQ_HIGH:
            waveformData.frequency = (receivedByte << 8) | (waveformData.frequency & 0xFF);
            waveformBytesReceived = 2;
            requestNextByte(SPIState::RECEIVING_WAVEFORM_FREQ_LOW);
            break;
            
        case SPIState::RECEIVING_WAVEFORM_FREQ_LOW:
            waveformData.frequency = (waveformData.frequency & 0xFF00) | receivedByte;
            waveformData.ready = true;
            waveformBytesReceived = 0;
            finalizeSPICommunication();
            break;
            
        default:
            break;
    }
}
