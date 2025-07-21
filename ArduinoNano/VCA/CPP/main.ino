// =============================================================================
// Project:         Potentia VCA Module Firmware
// File:            main.ino
// Author:          Gabriel Garcia; Henrique Amaral Onuki
// Created:         2025-07-09
// Modified:        2025-07-18
// Version:         4.0
// Description:     Comunicação SPI mestre com renderização gráfica no OLED.
//                      Recebe comandos do escravo (ADC ou waveform) e exibe dados
//                      graficamente em tempo real.
// Purpose:         Multiplexar as fontes de áudio amplificadas pelo VCA, controlar
//                      um gerador de ondas como fonte interna de áudio, bem como
//                      receber dados do AHDSR para mostrar o envelope no display,
//                      ou recever dados para alterar seu próprio funcionamento.
// =============================================================================


// =============================================================================
// DEPENDENCIES
// =============================================================================

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>


// =============================================================================
// CONSTANT DEFINITIONS
// =============================================================================

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C

#define ADC_COMMAND_BYTE        0b11000011
#define WAVEFORM_COMMAND_BYTE   0b00111100

#define SLAVE_READY_WAIT_TICKS  3
#define FINALIZE_WAIT_TICKS     5


// =============================================================================
// ENUMERATIONS
// =============================================================================

enum SPIState {
    SPI_IDLE,
    SPI_WAIT_SLAVE_READY,
    SPI_RECEIVING_COMMAND,
    SPI_RECEIVING_ADC_DATA,
    SPI_RECEIVING_WAVEFORM_MODE,
    SPI_RECEIVING_WAVEFORM_FREQ_HIGH,
    SPI_RECEIVING_WAVEFORM_FREQ_LOW,
    SPI_WAIT_NEXT_DATA,
    SPI_FINALIZING
};


// =============================================================================
// STATIC FUNCTION DECLARATIONS
// =============================================================================

// NONE


// =============================================================================
// GLOBAL VARIABLES
// =============================================================================

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte NUM_COLS = SCREEN_WIDTH;
volatile byte yBuf[NUM_COLS] = {0};
const byte hScale = 6;

volatile uint8_t receivedByte = 0;
volatile SPIState spiState = SPI_IDLE;
volatile bool dataReadyDetected = false;
volatile bool drawGraph = false;
volatile byte graphValue = 0;
volatile uint8_t currentCommand = 0;
volatile uint8_t waveformBytesReceived = 0;
volatile uint8_t muxLoop = 0;

volatile uint8_t waveformMode = 0;
volatile uint8_t waveformFreqHigh = 0;
volatile uint8_t waveformFreqLow = 0;
volatile bool waveformDataReady = false;

volatile uint16_t stateTimer = 0;
volatile bool timerTick = false;

volatile bool lastPCINT8State = false;
volatile bool lastPCINT0State = false;


//=============================================================================
// FUNCTION PROTOTYPES
//=============================================================================

bool slaveHasData();
void initSPI();
void initButton();
void initPinData();
void initTimer2();
void startSPIProcess();
void finalizeSPICommunication();
void requestNextByte(SPIState nextState);
void processSPIStateMachine();
void processWaveformData();
const char* getWaveformName(uint8_t mode);


// =============================================================================
// Function: slaveHasData
// Description: Verifica se o escravo tem dados disponíveis via PC0.
// =============================================================================

bool slaveHasData() {
    return (PINC & (1 << PC0)) != 0;
}


// =============================================================================
// Function: initSPI
// Description: Inicializa SPI em modo mestre com interrupção habilitada.
// =============================================================================

void initSPI() {
    DDRB |= (1 << PB2) | (1 << PB3) | (1 << PB5);
    DDRB &= ~(1 << PB4);
    PORTB |= (1 << PB2);

    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1)
         | (1 << SPIE) | (1 << CPOL) | (1 << CPHA);
}


// =============================================================================
// Function: initButton
// Description: Inicializa entrada de botão (INT0) e os pinos do mux.
// =============================================================================

void initButton() {
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);

    EICRA |= (1 << ISC01);
    EIMSK |= (1 << INT0);

    DDRD  |= (1 << PD7) | (1 << PD6) | (1 << PD5);
    PORTD |= (1 << PD7) | (1 << PD6) | (1 << PD5);
}


// =============================================================================
// Function: initPinData
// Description: Configura o PC0 como entrada com interrupção por mudança.
// =============================================================================

void initPinData() {
    DDRC &= ~(1 << PC0);
    PORTC &= ~(1 << PC0);

    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << PCINT8);

    lastPCINT8State = (PINC & (1 << PC0)) != 0;
}

// =============================================================================
// Function: initExtDetect
// Description: Configura o PB0 como entrada com interrupção por mudança.
// =============================================================================

void initExtDetect() {
    DDRB &= ~(1 << PB0);
    PORTB |= ~(1 << PB0); 

    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << PCINT0);

    lastPCINT0State = (PINB & (1 << PB0)) != 0;
}


// =============================================================================
// Function: initTimer2
// Description: Inicializa Timer2 para gerar ticks de ~1ms.
// =============================================================================

void initTimer2() {
    TCCR2A = (1 << WGM21);
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
    OCR2A = 15;
    TIMSK2 |= (1 << OCIE2A);
}


// =============================================================================
// Function: startSPIProcess
// Description: Inicia comunicação SPI.
// =============================================================================

void startSPIProcess() {
    if (spiState == SPI_IDLE) {
        spiState = SPI_WAIT_SLAVE_READY;
        stateTimer = 0;
        PORTB &= ~(1 << PB2);
    }
}


// =============================================================================
// Function: finalizeSPICommunication
// Description: Finaliza comunicação SPI.
// =============================================================================

void finalizeSPICommunication() {
    PORTB |= (1 << PB2);
    spiState = SPI_FINALIZING;
    stateTimer = 0;
}


// =============================================================================
// Function: requestNextByte
// Description: Solicita próximo byte ao escravo, se disponível.
// =============================================================================

void requestNextByte(SPIState nextState) {
    if (slaveHasData()) {
        SPDR = 0x00;
        spiState = nextState;
    } else {
        spiState = SPI_WAIT_NEXT_DATA;
        stateTimer = 0;
    }
}


// =============================================================================
// Function: processSPIStateMachine
// Description: Máquina de estados baseada em tempo (~1ms).
// =============================================================================

void processSPIStateMachine() {
    if (!timerTick) return;
    timerTick = false;

    switch (spiState) {
        case SPI_WAIT_SLAVE_READY:
            if (stateTimer >= SLAVE_READY_WAIT_TICKS && slaveHasData()) {
                spiState = SPI_RECEIVING_COMMAND;
                stateTimer = 0;
                SPDR = 0x00;
            }
            break;

        case SPI_WAIT_NEXT_DATA:
            if (slaveHasData()) {
                SPDR = 0x00;
                stateTimer = 0;

                if (currentCommand == ADC_COMMAND_BYTE) {
                    spiState = SPI_RECEIVING_ADC_DATA;
                } else if (currentCommand == WAVEFORM_COMMAND_BYTE) {
                    if (waveformBytesReceived == 1)
                        spiState = SPI_RECEIVING_WAVEFORM_FREQ_HIGH;
                    else if (waveformBytesReceived == 2)
                        spiState = SPI_RECEIVING_WAVEFORM_FREQ_LOW;
                    else
                        spiState = SPI_RECEIVING_WAVEFORM_MODE;
                }
            }
            break;

        case SPI_FINALIZING:
            if (stateTimer >= FINALIZE_WAIT_TICKS) {
                spiState = SPI_IDLE;
                stateTimer = 0;
            }
            break;

        default:
            break;
    }
}


// =============================================================================
// Function: processWaveformData
// Description: Processar os dados de configuração do áudio interno.
// =============================================================================

//TODO
void processWaveformData() {
    if (waveformDataReady) {
        PORTD |= (1 << PD7) | (1 << PD6) | (1 << PD5);
        switch (waveformMode) {
          case 0:
            //TODO: Setar áudio interno provindo do AD9833 e como Quadrada
            PORTD &= ~(1 << PD6); muxLoop = 2;
          break;
          case 1:
            //TODO: Setar áudio interno provindo do AD9833 e como Triangular
            PORTD &= ~(1 << PD6); muxLoop = 2;
          break;
          case 2:
            //TODO: Setar áudio interno provindo do AD9833 e como Senoidal
            PORTD &= ~(1 << PD6); muxLoop = 2;
          break;
          case 3: // Setar áudio interno como ruido
            PORTD &= ~(1 << PD7); muxLoop = 1;
          break;
        }

        waveformDataReady = false;
    }
}


// =============================================================================
// Function: getWaveformName
// Description: Associa os números ao tipo de áudio interno.
// =============================================================================

const char* getWaveformName(uint8_t mode) {
    switch (mode) {
        case 0: return "Quadrada";
        case 1: return "Triangular";
        case 2: return "Senoidal";
        case 3: return "Ruido";
        default: return "Unknown";
    }
}


// =============================================================================
// SETUP FUNCION
// =============================================================================

void setup() {
    initSPI();
    initPinData();
    initExtDetect();
    initButton();
    initTimer2();

    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
    display.clearDisplay();
    display.display();

    // Splash screen
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(17, 0);
    display.println(F("POTENTIA"));

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        float rad = (float)x / SCREEN_WIDTH * TWO_PI;
        int16_t y = SCREEN_HEIGHT / 2 + (sin(rad) * 10);
        display.drawPixel(x, y, SSD1306_WHITE);
    }

    display.display();
    delay(5000);

    sei();  // Habilita interrupções globais
}


// =============================================================================
// MAIN LOOP
// =============================================================================

void loop() {
    processWaveformData();

    if (drawGraph) {
        // Mapear valor para a área azul (linhas 16 até 63)
        byte y = map(graphValue << 2, 0, 1023, SCREEN_HEIGHT - 1, 16);
        static byte prevY = 40; // Centro da área azul (entre 16 e 63)
    
        for (byte k = 0; k < hScale; k++) {
            float t = (float)(k + 1) / hScale;
            byte yi = prevY + (int)((y - prevY) * t);
            memmove(yBuf, yBuf + 1, NUM_COLS - 1);
            yBuf[NUM_COLS - 1] = yi;
        }
    
        prevY = y;
    
        display.clearDisplay();
    
        // Texto na parte amarela (linhas 0 a 15)
        display.setTextSize(1);  // Para caber duas linhas de informação
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        
        const char* waveformName = getWaveformName(waveformMode);
        uint16_t freq = (waveformFreqHigh << 8) | waveformFreqLow;
        
        display.print("WF: ");
        display.print(waveformName);
        display.setCursor(0, 8); // Próxima linha
        display.print("Freq: ");
        display.print(freq);
        display.print(" Hz");

    
        // Gráfico na parte azul (linhas 16 a 63)
        for (byte x = 0; x < NUM_COLS - 1; x++) {
            display.drawLine(x, yBuf[x], x + 1, yBuf[x + 1], SSD1306_WHITE);
        }
    
        display.display();
        drawGraph = false;
    }

    processSPIStateMachine();

    if (dataReadyDetected && spiState == SPI_IDLE) {
        dataReadyDetected = false;
        startSPIProcess();
    }
}


// =============================================================================
// INTERRUPT HANDLERS
// =============================================================================

// INT0 Interrupt
ISR(INT0_vect) {
    PORTD |= (1 << PD7) | (1 << PD6) | (1 << PD5);
    switch (muxLoop) {
        case 0: PORTD &= ~(1 << PD7); muxLoop++; break;
        case 1: PORTD &= ~(1 << PD6); muxLoop++; break;
        case 2: PORTD &= ~(1 << PD5); muxLoop = 0; break;
    }
}

// PCINT0 Interrupt
ISR(PCINT0_vect) {
}

// PCINT1 Interrupt
ISR(PCINT1_vect) {
    bool current = (PINC & (1 << PC0)) != 0;
    if (!lastPCINT8State && current) {
        dataReadyDetected = true;
    }
    lastPCINT8State = current;
}

// Timer2 Compare A Interrupt
ISR(TIMER2_COMPA_vect) {
    timerTick = true;
    stateTimer++;
}

// SPI Interrupt
ISR(SPI_STC_vect) {
    receivedByte = SPDR;

    switch (spiState) {
        case SPI_RECEIVING_COMMAND:
            if (receivedByte == ADC_COMMAND_BYTE) {
                currentCommand = receivedByte;
                requestNextByte(SPI_RECEIVING_ADC_DATA);
            } else if (receivedByte == WAVEFORM_COMMAND_BYTE) {
                currentCommand = receivedByte;
                requestNextByte(SPI_RECEIVING_WAVEFORM_MODE);
            }
            break;

        case SPI_RECEIVING_ADC_DATA:
            graphValue = receivedByte;
            drawGraph = true;
            finalizeSPICommunication();
            break;

        case SPI_RECEIVING_WAVEFORM_MODE:
            waveformMode = receivedByte;
            waveformBytesReceived = 1;
            requestNextByte(SPI_RECEIVING_WAVEFORM_FREQ_HIGH);
            break;

        case SPI_RECEIVING_WAVEFORM_FREQ_HIGH:
            waveformFreqHigh = receivedByte;
            waveformBytesReceived = 2;
            requestNextByte(SPI_RECEIVING_WAVEFORM_FREQ_LOW);
            break;

        case SPI_RECEIVING_WAVEFORM_FREQ_LOW:
            waveformFreqLow = receivedByte;
            waveformDataReady = true;
            waveformBytesReceived = 0;
            finalizeSPICommunication();
            break;

        default:
            break;
    }
}

