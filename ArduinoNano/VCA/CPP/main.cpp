#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET   -1
#define OLED_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------- parâmetros do "osciloscópio" ----------
const byte NUM_COLS = SCREEN_WIDTH;
volatile byte yBuf[NUM_COLS] = {0};
const byte hScale = 6;

// Protocolo de comunicação
#define ADC_COMMAND_BYTE     0b11000011  // Comando ADC
#define WAVEFORM_COMMAND_BYTE 0b00111100  // Comando Waveform

// Estados da máquina SPI - NOMES CORRIGIDOS
enum SPIState {
  SPI_IDLE,
  SPI_WAIT_SLAVE_READY,
  SPI_RECEIVING_COMMAND,         // Recebendo o byte de comando (1º byte)
  SPI_RECEIVING_ADC_DATA,        // Recebendo dado ADC (2º byte para ADC)
  SPI_RECEIVING_WAVEFORM_MODE,   // Recebendo mode (2º byte para Waveform)
  SPI_RECEIVING_WAVEFORM_FREQ_HIGH,  // Recebendo freq high (3º byte para Waveform)
  SPI_RECEIVING_WAVEFORM_FREQ_LOW,   // Recebendo freq low (4º byte para Waveform)
  SPI_WAIT_NEXT_DATA,            // Aguardando próximo dado ficar disponível
  SPI_FINALIZING
};

// Variáveis globais
volatile uint8_t receivedByte = 0;
volatile SPIState spiState = SPI_IDLE;
volatile bool dataReadyDetected = false;
volatile bool drawGraph = false;
volatile byte graphValue = 0;
volatile uint8_t currentCommand = 0;
volatile uint8_t waveformBytesReceived = 0;

// Variáveis para armazenar dados do waveform
volatile uint8_t waveformMode = 0;
volatile uint8_t waveformFreqHigh = 0;
volatile uint8_t waveformFreqLow = 0;
volatile bool waveformDataReady = false;

// Contadores para máquina de estados temporal (baseados em Timer2)
volatile uint16_t stateTimer = 0;
volatile bool timerTick = false;

// Constantes de timing (em ticks de ~1ms)
#define SLAVE_READY_WAIT_TICKS  3    // ~3ms para slave se preparar
#define FINALIZE_WAIT_TICKS     5    // ~5ms após finalizar

// Função para verificar se slave tem dados disponíveis
bool slaveHasData() {
    return (PIND & (1 << PD3)) != 0;
}

// SPI initialization as master
void initSPI()
{
    // SS (PB2), MOSI (PB3), SCK (PB5) como saídas e MISO (PB4) como entrada
    DDRB |= (1 << PB2) | (1 << PB3) | (1 << PB5);
    DDRB &= ~(1 << PB4);  // MISO como entrada

    // SS inicialmente em HIGH (slave não selecionado)
    PORTB |= (1 << PB2);

    // SPI enable, Master mode, SCK frequency = fosc/64 = 250kHz, interrupt enable
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (0 << SPR0) | (1 << SPIE) | (1 << CPOL) | (1 << CPHA);
}

// Pin data configuration - usando interrupt
void initPinData()
{
    // PD3 como entrada para detectar dados disponíveis
    DDRD &= ~(1 << PD3);
    PORTD &= ~(1 << PD3);  // Sem pull-up interno

    // Configurar INT1 para detectar rising edge (LOW->HIGH)
    EICRA |= (1 << ISC11) | (1 << ISC10);  // Rising edge
    EIMSK |= (1 << INT1);   // Habilita INT1
}

// Timer2 para base de tempo (substitui delays)
void initTimer2()
{
    // Timer2 em modo CTC para tick a cada ~1ms
    TCCR2A = (1 << WGM21);
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);  // Prescaler 1024
    OCR2A = 15;  // ~1ms @ 16MHz
    TIMSK2 |= (1 << OCIE2A);  // Enable compare match interrupt
}

// Função para iniciar processo de comunicação SPI
void startSPIProcess()
{
    if (spiState == SPI_IDLE) {
        spiState = SPI_WAIT_SLAVE_READY;
        stateTimer = 0;
        
        // Pull SS low imediatamente
        PORTB &= ~(1 << PB2);
    }
}

// Função para finalizar comunicação SPI
void finalizeSPICommunication()
{
    // Pull SS high
    PORTB |= (1 << PB2);
    
    spiState = SPI_FINALIZING;
    stateTimer = 0;
}

// Função para solicitar próximo byte
void requestNextByte(SPIState nextState)
{
    if (slaveHasData()) {
        SPDR = 0x00;  // Envia byte dummy para receber próximo
        spiState = nextState;  // Vai direto para o próximo estado
    } else {
        // Slave não tem dados ainda - aguarda no estado SPI_WAIT_NEXT_DATA
        spiState = SPI_WAIT_NEXT_DATA;
        stateTimer = 0;
    }
}

// ISR para mudanças no pino de dados disponíveis
ISR(INT1_vect)
{
    // Detecta apenas rising edge (dados disponíveis)
    if (PIND & (1 << PD3)) {
        dataReadyDetected = true;
    }
}

// ISR Timer2 - base de tempo para máquina de estados
ISR(TIMER2_COMPA_vect)
{
    timerTick = true;
    stateTimer++;
}

// ISR SPI - Máquina de estados CORRIGIDA
ISR(SPI_STC_vect)
{
    receivedByte = SPDR;
    
    switch (spiState) {
        case SPI_RECEIVING_COMMAND:
            // 1º byte: comando (ADC ou WAVEFORM)
            if (receivedByte == ADC_COMMAND_BYTE) {
                currentCommand = receivedByte;
                requestNextByte(SPI_RECEIVING_ADC_DATA);
            } else if (receivedByte == WAVEFORM_COMMAND_BYTE) {
                currentCommand = receivedByte;
                requestNextByte(SPI_RECEIVING_WAVEFORM_MODE);
            }
            break;
            
        case SPI_RECEIVING_ADC_DATA:
            // 2º byte: dado ADC
            graphValue = receivedByte;
            drawGraph = true;
            finalizeSPICommunication();
            break;
            
        case SPI_RECEIVING_WAVEFORM_MODE:
            // 2º byte: modo do waveform
            waveformMode = receivedByte;
            waveformBytesReceived = 1;
            requestNextByte(SPI_RECEIVING_WAVEFORM_FREQ_HIGH);
            break;
            
        case SPI_RECEIVING_WAVEFORM_FREQ_HIGH:
            // 3º byte: parte alta da frequência
            waveformBytesReceived = 2;
            waveformFreqHigh = receivedByte;
            requestNextByte(SPI_RECEIVING_WAVEFORM_FREQ_LOW);
            break;
            
        case SPI_RECEIVING_WAVEFORM_FREQ_LOW:
            // 4º byte: parte baixa da frequência
            waveformFreqLow = receivedByte;
            waveformDataReady = true;
            waveformBytesReceived = 0;
            finalizeSPICommunication();
            break;
            
        default:
            break;
    }
}

// Função para processar máquina de estados temporal
void processSPIStateMachine()
{
    if (timerTick) {
        timerTick = false;
    } else {
        return;
    }
    
    switch (spiState) {
        case SPI_WAIT_SLAVE_READY:
            if (stateTimer >= SLAVE_READY_WAIT_TICKS) {
                // Tempo suficiente passou, verifica se slave tem dados
                if (slaveHasData()) {
                    // Slave tem dados, inicia recepção do comando
                    spiState = SPI_RECEIVING_COMMAND;
                    stateTimer = 0;
                    SPDR = 0x00;  // Envia byte dummy para receber comando
                } else {
                    // Slave não tem dados ainda - continua aguardando
                    // Pode implementar timeout aqui se necessário
                }
            }
            break;
            
        case SPI_WAIT_NEXT_DATA:
            // Aguarda até que slave tenha próximo dado disponível
            if (slaveHasData()) {
                // Dados disponíveis, determina próximo estado baseado no comando atual
                SPDR = 0x00;  // Envia byte dummy
                stateTimer = 0;
                
                // Determina próximo estado baseado no comando e progresso
                if (currentCommand == ADC_COMMAND_BYTE) {
                    spiState = SPI_RECEIVING_ADC_DATA;
                } else if (currentCommand == WAVEFORM_COMMAND_BYTE) {
                    if (waveformBytesReceived == 1) {
                        spiState = SPI_RECEIVING_WAVEFORM_FREQ_HIGH;
                    } else if (waveformBytesReceived == 2) {
                        spiState = SPI_RECEIVING_WAVEFORM_FREQ_LOW;
                    } else {
                        spiState = SPI_RECEIVING_WAVEFORM_MODE;
                    }
                }
            }
            // Se não há dados, continua aguardando
            break;
            
        case SPI_FINALIZING:
            if (stateTimer >= FINALIZE_WAIT_TICKS) {
                // Finalização completa - volta ao estado idle
                spiState = SPI_IDLE;
                stateTimer = 0;
            }
            break;
            
        case SPI_IDLE:
        case SPI_RECEIVING_COMMAND:
        case SPI_RECEIVING_ADC_DATA:
        case SPI_RECEIVING_WAVEFORM_MODE:
        case SPI_RECEIVING_WAVEFORM_FREQ_HIGH:
        case SPI_RECEIVING_WAVEFORM_FREQ_LOW:
        default:
            // Estados que não precisam de processamento temporal
            break;
    }
}

// Função para processar dadFos do waveform recebidos
void processWaveformData()
{
    if (waveformDataReady) {
        waveformDataReady = false;
        waveformMode = 0;
        waveformFreqHigh = 0;
        waveformFreqLow = 0;
        currentCommand = 0;  // Reseta também o comando
    }
}

void setup() {
    initSPI();
    initPinData();
    initTimer2();

    // OLED
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
    display.clearDisplay();
    display.display();

    // ---------- Splash screen ----------
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("DEBUG"));

    // Desenha uma mini senoide centralizada
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        float rad = (float)x / SCREEN_WIDTH * TWO_PI;      // 0 → 2π
        int16_t y = SCREEN_HEIGHT/2 + (sin(rad) * 10);     // amplitude 10 px
        display.drawPixel(x, y, SSD1306_WHITE);
    }

    display.display();   // Envia ao OLED
    delay(1500);         // Mostra por 1,5 s
    // ---------- Fim do splash ----------

    // Habilita interrupções globais
    sei();
}

void loop() {    
    // Processa dados do waveform se disponíveis
    processWaveformData();
    
    if (drawGraph) {
        // 1) Converte a amostra ADC (0‑255) para coordenada Y na tela (0 em cima)
        byte y = map(graphValue << 2, 0, 1023, SCREEN_HEIGHT - 1, 0);

        // 2) Interpola hScale sub‑pontos entre prevY e y
        static byte prevY = SCREEN_HEIGHT / 2;   // inicia no meio

        for (byte k = 0; k < hScale; k++) {
            float t  = (float)(k + 1) / hScale;           // 0 < t ≤ 1
            byte yi  = prevY + (int)((y - prevY) * t);    // interp. linear

            // Desloca todo o buffer 1 coluna para a esquerda
            memmove(yBuf, yBuf + 1, NUM_COLS - 1);
            yBuf[NUM_COLS - 1] = yi;                      // adiciona novo ponto
        }

        prevY = y;   // salva para a próxima amostra

        // 3) Redesenha o gráfico
        display.clearDisplay();
        for (byte x = 0; x < NUM_COLS - 1; x++) {
            display.drawLine(x, yBuf[x], x + 1, yBuf[x + 1], SSD1306_WHITE);
        }
        display.display();

        drawGraph = false;   // pronto para a próxima amostra
    }

    // Processa máquina de estados temporal
    processSPIStateMachine();
    
    // Verifica se há solicitação para iniciar comunicação
    if (dataReadyDetected && spiState == SPI_IDLE) {
        dataReadyDetected = false;
        startSPIProcess();
    }
}
