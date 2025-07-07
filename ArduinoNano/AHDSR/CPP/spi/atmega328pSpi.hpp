#ifndef SPI_HPP
#define SPI_HPP

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Biblioteca para controle do periférico SPI no ATmega328P.
 * 
 * Fornece inicialização e operação do SPI tanto no modo mestre quanto escravo,
 * com suporte a diferentes modos de clock (CPOL/CPHA) e taxa de transmissão.
 */
namespace Spi {

    /**
     * @brief Define o modo de operação do SPI.
     */
    enum class Mode {
        MASTER, /**< Controla a comunicação SPI (gera clock). */
        SLAVE   /**< Responde à comunicação iniciada por um mestre. */
    };

    /**
     * @brief Define a taxa de clock do SPI com base no clock do sistema.
     */
    enum class ClockRate {
        FOSC_4,   /**< f_osc / 4   */
        FOSC_16,  /**< f_osc / 16  */
        FOSC_64,  /**< f_osc / 64  */
        FOSC_128  /**< f_osc / 128 */
    };

    /**
     * @brief Define o modo de operação dos sinais de clock (CPOL e CPHA).
     */
    enum class DataMode {
        MODE_0, /**< CPOL = 0, CPHA = 0 */
        MODE_1, /**< CPOL = 0, CPHA = 1 */
        MODE_2, /**< CPOL = 1, CPHA = 0 */
        MODE_3  /**< CPOL = 1, CPHA = 1 */
    };

    /**
     * @brief Inicializa o periférico SPI.
     * 
     * @param mode Modo de operação: mestre ou escravo.
     * @param rate Taxa de clock SPI.
     * @param dataMode Modo CPOL/CPHA da comunicação SPI.
     */
    void init(Mode mode, ClockRate rate, DataMode dataMode);

    /**
     * @brief Envia um byte pelo barramento SPI.
     * 
     * Se o SPI estiver ocupado, a função não realiza o envio.
     * Use `isBusy()` para verificar quando estiver pronto novamente.
     * 
     * @param data Byte a ser enviado.
     */
    void sendByte(uint8_t data);

    /**
     * @brief Retorna o último byte recebido via SPI.
     * 
     * No modo mestre, este valor é recebido logo após uma transmissão.
     * No modo escravo, é preenchido automaticamente na interrupção.
     * 
     * @return Último byte recebido.
     */
    uint8_t getLastReceived();

    /**
     * @brief Indica se o SPI está ocupado transmitindo dados.
     * 
     * @return true se ocupado, false se pronto para nova transmissão.
     */
    bool isBusy();

    /**
     * @brief Função de callback chamada automaticamente na interrupção SPI.
     * 
     * Pode ser sobrescrita pelo usuário para reagir à chegada de novos dados.
     * 
     * @param received Byte recebido no momento da interrupção SPI.
     */
    void spiCallbackInterrupt(uint8_t received); // Implementação fraca (weak)

    /**
     * @brief Ativa a interrupção SPI.
     */
    void activateSpiCallbackInterrupt();

    /**
     * @brief Desativa a interrupção SPI.
     */
    void disableSpiCallbackInterrupt();

} // namespace Spi

#endif // SPI_HPP

