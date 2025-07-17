#include "atmega328pSpi.hpp"

namespace {
    // Indica se uma transmissão SPI está em andamento
    volatile bool busy = false;

    // Armazena o último byte recebido pelo SPI
    volatile uint8_t lastReceived = 0;
}

/**
 * @brief Rotina de interrupção do SPI.
 * 
 * Atualiza o status de busy, armazena o byte recebido e
 * chama o callback definido pelo usuário (se houver).
 */
ISR(SPI_STC_vect) {
    busy = false;
    lastReceived = SPDR;
    Spi::spiCallbackInterrupt(SPDR);
}

/**
 * @brief Inicializa o periférico SPI com os parâmetros especificados.
 * 
 * Configura os pinos, define o modo de operação, taxa de clock
 * e modo de dados (CPOL/CPHA).
 * 
 * @param mode Modo de operação (MASTER ou SLAVE).
 * @param rate Taxa de clock do SPI.
 * @param dataMode Modo de dados (CPOL/CPHA).
 */
void Spi::init(Mode mode, ClockRate rate, DataMode dataMode) {
    // Configuração dos pinos
    if (mode == Mode::MASTER) {
        DDRB |= (1 << PB2) | (1 << PB3) | (1 << PB5); // SS, MOSI, SCK como saída
        DDRB &= ~(1 << PB4);                         // MISO como entrada
        PORTB |= (1 << PB2);                         // SS em HIGH (evita modo slave acidental)
    } else {
        DDRB &= ~((1 << PB2) | (1 << PB3) | (1 << PB5)); // SS, MOSI, SCK como entrada
        DDRB |= (1 << PB4);                             // MISO como saída
    }

    // Habilita SPI
    SPCR = (1 << SPE);

    // Define como mestre, se aplicável
    if (mode == Mode::MASTER) SPCR |= (1 << MSTR);

    // Configuração da taxa de clock
    switch (rate) {
        case ClockRate::FOSC_4:
            break;
        case ClockRate::FOSC_16:
            SPCR |= (1 << SPR0);
            break;
        case ClockRate::FOSC_64:
            SPCR |= (1 << SPR1);
            break;
        case ClockRate::FOSC_128:
            SPCR |= (1 << SPR0) | (1 << SPR1);
            break;
    }

    // Configuração do modo CPOL/CPHA
    switch (dataMode) {
        case DataMode::MODE_0:
            SPCR &= ~(1 << CPOL);
            SPCR &= ~(1 << CPHA);
            break;
        case DataMode::MODE_1:
            SPCR &= ~(1 << CPOL);
            SPCR |=  (1 << CPHA);
            break;
        case DataMode::MODE_2:
            SPCR |=  (1 << CPOL);
            SPCR &= ~(1 << CPHA);
            break;
        case DataMode::MODE_3:
            SPCR |=  (1 << CPOL);
            SPCR |=  (1 << CPHA);
            break;
    }

    // Desativa o modo de velocidade dupla
    SPSR &= ~(1 << SPI2X);
}

/**
 * @brief Ativa a interrupção do SPI.
 */
void Spi::activateSpiCallbackInterrupt() {
    SPCR |= (1 << SPIE);
}

/**
 * @brief Desativa a interrupção do SPI.
 */
void Spi::disableSpiCallbackInterrupt() {
    SPCR &= ~(1 << SPIE);
}

/**
 * @brief Envia um byte pelo barramento SPI.
 * 
 * Se o periférico estiver ocupado, o envio é ignorado.
 * 
 * @param data Byte a ser enviado.
 */
void Spi::sendByte(uint8_t data) {
    if (!busy) {
        busy = true;
        SPDR = data;
    }
}

/**
 * @brief Retorna o último byte recebido via SPI.
 * 
 * @return Byte recebido.
 */
uint8_t Spi::getLastReceived() {
    return lastReceived;
}

/**
 * @brief Indica se o SPI está ocupado com uma transmissão.
 * 
 * @return true se ocupado, false se livre.
 */
bool Spi::isBusy() {
    return busy;
}

/**
 * @brief Função fraca chamada na interrupção SPI.
 * 
 * O usuário pode sobrescrever essa função em seu próprio código.
 * 
 * @param received Byte recebido do barramento SPI.
 */
void Spi::spiCallbackInterrupt(uint8_t) __attribute__((weak));
void Spi::spiCallbackInterrupt(uint8_t) {
    // Implementado externamente pelo usuário, se necessário
}

