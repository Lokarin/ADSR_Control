// =============================================================================
// Project:         Potentia VCA Module Firmware
// File:            main.ino
// Author:          Gabriel Garcia; Henrique Amaral Onuki
// Created:         2025-07-09
// Modified:        2025-07-18
// Version:         6.0
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
#include <MD_AD9833.h>
#include <Wire.h>


// =============================================================================
// CONSTANT DEFINITIONS
// =============================================================================

#define SCREEN_WIDTH            128
#define SCREEN_HEIGHT           64
#define OLED_RESET              -1
#define OLED_ADDRESS            0x3C

#define ADC_COMMAND_BYTE        0b11000011
#define WAVEFORM_COMMAND_BYTE   0b00111100

#define SLAVE_READY_WAIT_TICKS  3
#define FINALIZE_WAIT_TICKS     5

#define FSYNC_PIN               9


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

enum VCAMode {
  SINGLE_MODE,
  POTENTIA_MODE
};


// =============================================================================
// STATIC FUNCTION DECLARATIONS
// =============================================================================

// NONE


// =============================================================================
// GLOBAL VARIABLES
// =============================================================================

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MD_AD9833 gen(FSYNC_PIN);

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
uint16_t freq = (waveformFreqHigh << 8) | waveformFreqLow;
volatile bool waveformDataReady = false;

volatile uint16_t stateTimer = 0;
volatile bool timerTick = false;
volatile bool blinkOn = false;

volatile bool lastPCINT8State = false;
volatile bool lastPCINT0State = false;

volatile VCAMode pairing = SINGLE_MODE;


//=============================================================================
// FUNCTION PROTOTYPES
//=============================================================================

bool slaveHasData();
void initSPI();
void initButton();
void initPinData();
void initExtDetect();
void initTimer1();
void initTimer2();
void initWaveForm();
void startSPIProcess();
void finalizeSPICommunication();
void requestNextByte(SPIState nextState);
void processSPIStateMachine();
void processWaveformData();
const char* getWaveformName(uint8_t mode);
VCAMode checkPairing();
void drawDownArrow(uint8_t x, uint8_t y);


// =============================================================================
// Function: slaveHasData
// Description: Verifica se o escravo tem dados disponíveis via PC0.
// =============================================================================

bool slaveHasData() {
  return (PINC & (1 << PC0)) == 0;
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
  PORTD |= (1 << PD7) | (1 << PD6);
}


// =============================================================================
// Function: initPinData
// Description: Configura o PC0 como entrada com interrupção por mudança.
// =============================================================================

void initPinData() {
  DDRC &= ~(1 << PC0);
  PORTC |= (1 << PC0);

  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PCINT8);

  lastPCINT8State = (PINC & (1 << PC0)) != 0;
}

// =============================================================================
// Function: initExtDetect
// Description: Configura o PB0 como entrada com interrupção por mudança.
// =============================================================================

void initExtDetect() {
  // Configure PB0 (D8) como entrada com pull-up
  DDRB &= ~(1 << PB0);   // Entrada
  PORTB |= (1 << PB0);   // Pull-up interno

  // Ativa interrupção por mudança de pino no grupo PCIE0 (PORTB)
  PCICR |= (1 << PCIE0);

  // Habilita interrupção especificamente no pino PCINT0 (PB0)
  PCMSK0 |= (1 << PCINT0);

  // Leitura inicial do estado do pino
  lastPCINT0State = (PINB & (1 << PB0)) != 0;
}

// =============================================================================
// Function: initTimer1
// Description: Inicializa Timer1 
// =============================================================================

void initTimer1() {
  // Configure o Timer1 para modo CTC (Clear Timer on Compare Match)
  TCCR1A = 0;                           // Modo normal
  TCCR1B = (1 << WGM12);                // CTC
  TCCR1B |= (1 << CS12) | (1 << CS10);  // Prescaler 1024

  OCR1A = 6250 - 1;

  TIMSK1 |= (1 << OCIE1A);
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
// Function: initWaveForm
// Description: Inicializa o AD9833.
// =============================================================================

void initWaveForm() {
  gen.begin();
  gen.reset(true);
  gen.setFrequency(MD_AD9833::CHAN_0, 1000);
  gen.setMode(MD_AD9833::MODE_TRIANGLE);
  gen.reset(false);
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

void processWaveformData() {
  if (waveformDataReady) {
    freq = (waveformFreqHigh << 8) | waveformFreqLow;

    // Entra no Modo 2      
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1)
         | (1 << SPIE) | (1 << CPOL);

    // Mux Desativado
    PORTD |= (1 << PD7) | (1 << PD6) | (1 << PD5);

    switch (waveformMode) {
      case 0:
        // Setar áudio interno provindo do AD9833 e como Quadrada
        gen.setMode(MD_AD9833::MODE_SQUARE1);
        PORTD &= ~(1 << PD6); muxLoop = 2;
      break;
      case 1:
        // Setar áudio interno provindo do AD9833 e como Triangular
        gen.setMode(MD_AD9833::MODE_TRIANGLE);
        PORTD &= ~(1 << PD6); muxLoop = 2;
      break;
      case 2:
        // Setar áudio interno provindo do AD9833 e como Senoidal
        gen.setMode(MD_AD9833::MODE_SINE);
        PORTD &= ~(1 << PD6); muxLoop = 2;
      break;
      case 3: // Setar áudio interno como ruido
        PORTD &= ~(1 << PD7); muxLoop = 1;
      break;
    }

    // Seta a frequencia
    gen.setFrequency(MD_AD9833::CHAN_0, freq);

    // Volta para Mode 3
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1)
         | (1 << SPIE) | (1 << CPOL) | (1 << CPHA);

    // Disponivel para nova wave data
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
// Function: checkPairing
// Description: Checa a conexão entre o VCA e o AHDSR.
// =============================================================================

VCAMode checkPairing() {
  if ((PINC & (1 << PC0)) == 0) {
    dataReadyDetected = true;
    return POTENTIA_MODE;
  } else {
    return SINGLE_MODE;
  }
}

// =============================================================================
// Function: drawDownArrow
// Description: Desenha um triangulo que pisca.
// =============================================================================

void drawDownArrow(uint8_t x, uint8_t y) {
  if (blinkOn) {
    display.fillTriangle(x - 7, y, x + 7, y, x, y + 8, SSD1306_WHITE);
  }
}


// =============================================================================
// SETUP FUNCION
// =============================================================================

void setup() {
  initWaveForm();
  initSPI();
  initPinData();
  initExtDetect();
  initButton();
  initTimer1();
  initTimer2();

  delay(1400);

  pairing = checkPairing();

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();
  display.display();

  // Splash screen
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  if (pairing == POTENTIA_MODE) {
    display.setCursor(5, 0);
    display.println(F("-POTENTIA-"));

    uint8_t x0 = 0;              // Início
    uint8_t y0 = SCREEN_HEIGHT - 1;
    
    uint8_t x1 = 20;             // Fim do ataque
    uint8_t y1 = 20;
    
    uint8_t x2 = 30;             // Fim do hold
    uint8_t y2 = y1;
    
    uint8_t x3 = 45;             // Fim do decay
    uint8_t y3 = 32;
    
    uint8_t x4 = 80;             // Fim do sustain
    uint8_t y4 = y3;
    
    uint8_t x5 = 110;            // Fim do release
    uint8_t y5 = SCREEN_HEIGHT - 1;
    
    // Desenha os segmentos
    display.drawLine(x0, y0, x1, y1, SSD1306_WHITE); // Attack
    display.drawLine(x1, y1, x2, y2, SSD1306_WHITE); // Hold
    display.drawLine(x2, y2, x3, y3, SSD1306_WHITE); // Decay
    display.drawLine(x3, y3, x4, y4, SSD1306_WHITE); // Sustain
    display.drawLine(x4, y4, x5, y5, SSD1306_WHITE); // Release

  } else {
    display.setCursor(10, 0);
    display.println(F("---VCA---"));
    for (uint8_t i = 0; i < SCREEN_WIDTH; i += 4) {
        float angle = (float)i / SCREEN_WIDTH * 2 * PI * 3; // 3 ciclos de onda na largura da tela
        uint8_t h = 28 + (int)(10 * sin(angle)); // altura varia entre 8 e 28 (18 ± 10)
        display.drawFastVLine(i, SCREEN_HEIGHT - h, h, SSD1306_WHITE);
    }
  }

  display.display();
  delay(3000);

  pairing = checkPairing();

  sei();  // Habilita interrupções globais
}


// =============================================================================
// MAIN LOOP
// =============================================================================

void loop() {
  processWaveformData();

  if (pairing == SINGLE_MODE) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);

    uint8_t y = 16; 

    // EXT alinhado à esquerda
    display.setCursor(0, y);
    display.print(F("EXT"));

    // INT centralizado
    uint8_t intWidth = 3 * 12;  // 3 letras x 12px
    uint8_t xInt = (SCREEN_WIDTH - intWidth) / 2;  // centro da tela
    display.setCursor(xInt, y);
    display.print(F("INT"));

    // NOI alinhado à direita
    uint8_t noiWidth = 3 * 12;
    uint8_t xNoi = SCREEN_WIDTH - noiWidth;  // tela vai de 0 a 127
    display.setCursor(xNoi, y);
    display.print(F("NOI"));

    uint8_t dotX = 0;
    switch (muxLoop) {
        case 0: // EXT (ESQUERDA)
          dotX = 36 / 2;  // início do EXT + metade
          break;

        case 1: // NOI (DIREITA)
          dotX = 110;  // início da NOI + metade da palavra
          break;

        case 2: // INT (MEIO)
          dotX = 64;  // início do INT + metade
          break;

        default:
          return;  // valor inválido
    }

    drawDownArrow(dotX, 3);

    display.setTextSize(1);
    display.setCursor(11,55);
    display.print("(Selecionar Audio)");

    display.display();
  }

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
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      
      const char* waveformName = getWaveformName(waveformMode);
      freq = (waveformFreqHigh << 8) | waveformFreqLow;
      
      display.print("WF: ");
      display.print(waveformName);
      display.setCursor(0, 8);
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
  bool current = (PINB & (1 << PB0)) != 0;
  if (!lastPCINT0State && current) {
    PORTD |= (1 << PD7) | (1 << PD6) | (1 << PD5);
    PORTD &= ~(1 << PD5); muxLoop = 0;
  }
  lastPCINT0State = current;
}

// PCINT1 Interrupt
ISR(PCINT1_vect) {
  bool current = (PINC & (1 << PC0)) != 0;
  if (lastPCINT8State && !current) {
    dataReadyDetected = true;
  }
  lastPCINT8State = current;
}


// Timer1 Compare A Interrupt
ISR(TIMER1_COMPA_vect) {
  blinkOn = !blinkOn;
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

