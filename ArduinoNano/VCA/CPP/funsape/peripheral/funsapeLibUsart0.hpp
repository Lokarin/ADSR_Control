//!
//! \file           funsapeLibUsart0.hpp
//! \brief          UART/USART communication peripheral control for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        UART/USART communication peripheral control for the FunSAPE AVR8 Library
//! \todo           USART and USART in SPI mode
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_USART0_HPP
#define __FUNSAPE_LIB_USART0_HPP                2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_USART0_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_USART0_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

#include "../util/funsapeLibSystemStatus.hpp"
#if !defined(__FUNSAPE_LIB_SYSTEM_STATUS_HPP)
#   error "Header file (funsapeLibSystemStatus.hpp) is corrupted!"
#elif __FUNSAPE_LIB_SYSTEM_STATUS_HPP != __FUNSAPE_LIB_USART0_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibSystemStatus.hpp)!"
#endif

#if defined(_FUNSAPE_PLATFORM_AVR)

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Peripherals
//! \brief          Microcontroller peripherals.
//! \{
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Peripherals/Usart0"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Usart0
//! \brief          Universal Synchronous/Asynchronous Receiver/Transmitter 0
//!                     (USART0) controller module.
//! \{
//!

// =============================================================================
// External global variables
// =============================================================================

//!
//! \cond
//!

extern FILE usartStream;

//!
//! \endcond
//!

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

// NONE

// =============================================================================
// New data types
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

//!
//! \brief          USART Reception Complete interrupt callback function.
//! \details        This function is called when the USART Reception Complete
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void usartReceptionCompleteCallback(void);

//!
//! \brief          USART Transmission Buffer Empty interrupt callback function.
//! \details        This function is called when the USART Transmission Buffer
//!                     Empty interrupt is treated. It is a weak function that
//!                     can be overwritten by user code.
//!
void usartTransmissionBufferEmptyCallback(void);

//!
//! \brief          USART Transmission Complete interrupt callback function.
//! \details        This function is called when the USART Transmission Complete
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void usartTransmissionCompleteCallback(void);

// =============================================================================
// Usart Class
// =============================================================================

//!
//! \brief          Usart0 class.
//! \details        This class manages the Universal Synchronous/Asynchronous
//!                     Receiver/Transmitter 0 (USART0) peripheral.
//! \warning        An instance of this class is already defined as a global
//!                     object. Therefore, there is not necessary, neither
//!                     recommended to create another object of this class.
//!
class Usart0
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     ///////////////     USART0 Operation Mode     ////////////////     //
    //!
    //! \brief      USART0 Operation Mode enumeration.
    //! \details    Operation mode associated with the USART0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class Mode : uint8_t {
        ASYNCHRONOUS                            = 0,    //!< Peripheral in UART without double speed mode.
        ASYNCHRONOUS_DOUBLE_SPEED               = 1,    //!< Peripheral in UART with double speed mode.
        SYNCHRONOUS_TX_RISING_RX_FALLING        = 2,    //!< Peripheral in USART mode on falling edge.
        SYNCHRONOUS_TX_FALLING_RX_RISING        = 3,    //!< Peripheral in USART mode on rising edge.
        MASTER_SPI_MODE_0                       = 4,    //!< Peripheral in master SPI mode 0.
        MASTER_SPI_MODE_1                       = 5,    //!< Peripheral in master SPI mode 1.
        MASTER_SPI_MODE_2                       = 6,    //!< Peripheral in master SPI mode 2.
        MASTER_SPI_MODE_3                       = 7,    //!< Peripheral in master SPI mode 3.
    };

    //     ///////////////    USART0 Reception Error     ////////////////     //
    //!
    //! \brief      USART0 Reception Error enumeration.
    //! \details    Reception error associated with the USART0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class ReceptionError : uint8_t {
        NONE                            = 0,            //!< No reception errors occurred.
        FRAME_ERROR                     = (1 << 0),     //!< Frame format invalid.
        PARITY_ERROR                    = (1 << 1),     //!< Parity check failed.
        DATA_OVERRUN_ERROR              = (1 << 2),     //!< Data lost.
        ALL                             = (1 << 0) | (1 << 1) | (1 << 2) //!< All errors
    };

    // friend inlined ReceptionError operator|(ReceptionError a, ReceptionError b);
    // friend inlined ReceptionError &operator|=(ReceptionError &a, ReceptionError b);
    // friend inlined ReceptionError operator&(ReceptionError a, ReceptionError b);
    // friend inlined ReceptionError &operator&=(ReceptionError &a, ReceptionError b);
    // friend inlined ReceptionError operator~(ReceptionError a);

    //     /////////////////    USART0 Parity Mode     //////////////////     //
    //!
    //! \brief      USART0 Parity Mode enumeration.
    //! \details    Parity mode associated with the USART0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class ParityMode : uint8_t {
        NONE                            = 0,    //!< No parity.
        ODD                             = 1,    //!< Odd parity.
        EVEN                            = 2     //!< Even parity.
    };

    //     //////////////////     USART0 StopBits     ///////////////////     //
    //!
    //! \brief      USART0 StopBits enumeration.
    //! \details    Number of stop bits associated with the USART0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class StopBits : uint8_t {
        SINGLE                          = 0,    //!< One stop bit.
        DOUBLE                          = 1     //|< Two stop bits.
    };

    //     //////////////////     USART0 DataSize     ///////////////////     //
    //!
    //! \brief      USART0 DataSize enumeration.
    //! \details    Data size associated with the USART0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class DataSize : uint8_t {
        DATA_5_BITS                     = 0,    //!< 5 data bits.
        DATA_6_BITS                     = 1,    //!< 6 data bits.
        DATA_7_BITS                     = 2,    //!< 7 data bits.
        DATA_8_BITS                     = 3,    //!< 8 data bits.
        DATA_9_BITS                     = 7,    //!< 9 data bits.
    };

    //     /////////////////    USART0 FrameFormat     //////////////////     //
    //!
    //! \brief      USART0 FrameFormat enumeration.
    //! \details    Frame format mode associated with the USART0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class FrameFormat : uint8_t {
        //                      = 0bDDDDPPSS
        // DDDD -> Number of data bits (5-8)
        // PP   -> Parity (NONE / ODD / EVEN)
        // SS   -> Number of stop bits (1-2)
        FRAME_FORMAT_8_N_1        = 0b10000001,    //!< 8 data bits / Parity NONE / 1 stop bit.
        FRAME_FORMAT_8_O_1        = 0b10000101,    //!< 8 data bits / Parity ODD / 1 stop bit.
        FRAME_FORMAT_8_E_1        = 0b10001001,    //!< 8 data bits / Parity EVEN / 1 stop bit.
        FRAME_FORMAT_8_N_2        = 0b10000010,    //!< 8 data bits / Parity NONE / 2 stop bit.
        FRAME_FORMAT_8_O_2        = 0b10000110,    //!< 8 data bits / Parity ODD / 2 stop bit.
        FRAME_FORMAT_8_E_2        = 0b10001010,    //!< 8 data bits / Parity EVEN / 2 stop bit.
        FRAME_FORMAT_9_N_1        = 0b10010001,    //!< 9 data bits / Parity NONE / 1 stop bit.
        FRAME_FORMAT_9_O_1        = 0b10010101,    //!< 9 data bits / Parity ODD / 1 stop bit.
        FRAME_FORMAT_9_E_1        = 0b10011001,    //!< 9 data bits / Parity EVEN / 1 stop bit.
        FRAME_FORMAT_9_N_2        = 0b10010010,    //!< 9 data bits / Parity NONE / 2 stop bit.
        FRAME_FORMAT_9_O_2        = 0b10010110,    //!< 9 data bits / Parity ODD / 2 stop bit.
        FRAME_FORMAT_9_E_2        = 0b10011010,    //!< 9 data bits / Parity EVEN / 2 stop bit.
        FRAME_FORMAT_5_N_1        = 0b01010001,    //!< 5 data bits / Parity NONE / 1 stop bit.
        FRAME_FORMAT_5_O_1        = 0b01010101,    //!< 5 data bits / Parity ODD / 1 stop bit.
        FRAME_FORMAT_5_E_1        = 0b01011001,    //!< 5 data bits / Parity EVEN / 1 stop bit.
        FRAME_FORMAT_5_N_2        = 0b01010010,    //!< 5 data bits / Parity NONE / 2 stop bit.
        FRAME_FORMAT_5_O_2        = 0b01010110,    //!< 5 data bits / Parity ODD / 2 stop bit.
        FRAME_FORMAT_5_E_2        = 0b01011010,    //!< 5 data bits / Parity EVEN / 2 stop bit.
        FRAME_FORMAT_6_N_1        = 0b01100001,    //!< 7 data bits / Parity NONE / 1 stop bit.
        FRAME_FORMAT_6_O_1        = 0b01100101,    //!< 7 data bits / Parity ODD / 1 stop bit.
        FRAME_FORMAT_6_E_1        = 0b01101001,    //!< 7 data bits / Parity EVEN / 1 stop bit.
        FRAME_FORMAT_6_N_2        = 0b01100010,    //!< 7 data bits / Parity NONE / 2 stop bit.
        FRAME_FORMAT_6_O_2        = 0b01100110,    //!< 7 data bits / Parity ODD / 2 stop bit.
        FRAME_FORMAT_6_E_2        = 0b01101010,    //!< 7 data bits / Parity EVEN / 2 stop bit.
        FRAME_FORMAT_7_N_1        = 0b01110001,    //!< 7 data bits / Parity NONE / 1 stop bit.
        FRAME_FORMAT_7_O_1        = 0b01110101,    //!< 7 data bits / Parity ODD / 1 stop bit.
        FRAME_FORMAT_7_E_1        = 0b01111001,    //!< 7 data bits / Parity EVEN / 1 stop bit.
        FRAME_FORMAT_7_N_2        = 0b01110010,    //!< 7 data bits / Parity NONE / 2 stop bit.
        FRAME_FORMAT_7_O_2        = 0b01110110,    //!< 7 data bits / Parity ODD / 2 stop bit.
        FRAME_FORMAT_7_E_2        = 0b01111010,    //!< 7 data bits / Parity EVEN / 2 stop bit.
    };

    //     //////////////////    USART0 Baud Rate     ///////////////////     //
    //!
    //! \brief      USART0 Baud Rate enumeration.
    //! \details    Baud rate speed associated with the USART0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class BaudRate : uint32_t {
        BAUD_RATE_600                   = 600UL,        //!< Baud rate = 600 bps.
        BAUD_RATE_1200                  = 1200UL,       //!< Baud rate = 1,200 bps.
        BAUD_RATE_1800                  = 1800UL,       //!< Baud rate = 1,800 bps.
        BAUD_RATE_2400                  = 2400UL,       //!< Baud rate = 2,400 bps.
        BAUD_RATE_4800                  = 4800UL,       //!< Baud rate = 4,800 bps.
        BAUD_RATE_9600                  = 9600UL,       //!< Baud rate = 9,600 bps.
        BAUD_RATE_14400                 = 14400UL,      //!< Baud rate = 14,400 bps.
        BAUD_RATE_19200                 = 19200UL,      //!< Baud rate = 19,200 bps.
        BAUD_RATE_28800                 = 28800UL,      //!< Baud rate = 28,800 bps.
        BAUD_RATE_38400                 = 38400UL,      //!< Baud rate = 38,400 bps.
        BAUD_RATE_56000                 = 56000UL,      //!< Baud rate = 56,000 bps.
        BAUD_RATE_57600                 = 57600UL,      //!< Baud rate = 57,600 bps.
        BAUD_RATE_115200                = 115200UL,     //!< Baud rate = 115,200 bps.
        BAUD_RATE_128000                = 128000UL,     //!< Baud rate = 128,000 bps.
        BAUD_RATE_230400                = 230400UL,     //!< Baud rate = 230,400 bps.
        BAUD_RATE_256000                = 256000UL      //!< Baud rate = 256,000 bps.
    };
    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:
    //!
    //! \brief      Usart0 class constructor.
    //! \details    Creates an Usart0 object. The object is loaded with the
    //!                 default register values (BaudRate::BAUD_RATE_9600,
    //!                 Mode::ASYNCHRONOUS and FrameFormat::FRAME_FORMAT_8_N_1).
    //!                 The object still must be initialized before use.
    //! \see        init(void).
    //!
    Usart0(
            BaudRate baudRate_p = BaudRate::BAUD_RATE_9600,
            Mode mode_p = Mode::ASYNCHRONOUS,
            FrameFormat format = FrameFormat::FRAME_FORMAT_8_N_1
    );

    //!
    //! \brief      Usart0 class destructor.
    //! \details    Destroys an Usart0 object.
    //!
    ~Usart0(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     CONFIGURATION     ////////////////////     //

    //!
    //! \brief      Initializes the USART0 module
    //! \details    Initializes the USART0 module.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t init(
            void
    );

    //!
    //! \brief      Disables the USART receiver.
    //! \details    Disables the USART receiver.
    //!
    void inlined disableReceiver(
            void
    );

    //!
    //! \brief      Disables the USART transmitter.
    //! \details    Disables the USART transmitter.
    //!
    void inlined disableTransmitter(
            void
    );

    //!
    //! \brief      Enables the USART receiver.
    //! \details    Enables the USART receiver.
    //!
    void inlined enableReceiver(
            void
    );

    //!
    //! \brief      Enables the USART transmitter.
    //! \details    Enables the USART transmitter.
    //!
    void inlined enableTransmitter(
            void
    );

    //!
    //! \brief      Sets data size.
    //! \details    Sets data size.
    //! \param[in]  dataSize_p      Data size.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setDataSize(
            const DataSize dataSize_p
    );

    //!
    //! \brief      Sets operation mode.
    //! \details    Sets operation mode.
    //! \param[in]  operationMode_p     Operation mode.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setMode(
            const Mode operationMode_p
    );

    //!
    //! \brief      Sets number of stop bits.
    //! \details    Sets number of stop bits.
    //! \param[in]  stopBits_p          Number of stop bits.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setStopBits(
            const StopBits stopBits_p
    );

    //!
    //! \brief      Sets the parity mode.
    //! \details    Sets the parity mode.
    //! \param[in]  parityMode_p        Parity mode.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setParityMode(
            const ParityMode parityMode_p
    );

    //!
    //! \brief      Sets the communication baud rate.
    //! \details    Sets the communication baud rate.
    //! \param[in]  baudRate_p          Communication baud rate.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setBaudRate(
            const BaudRate baudRate_p
    );

    //!
    //! \brief      Sets the Frame format.
    //! \details    Sets the Frame format.
    //! \param[in]  frameFormat_p       Frame format.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setFrameFormat(
            const FrameFormat frameFormat_p
    );

    //     ///////////////////////     STATUS    ////////////////////////     //

    //!
    //! \brief      Verifies the reception status.
    //! \details    Verifies the reception status.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t inlined isReceptionComplete(void);

    //!
    //! \brief      Verifies the transmission buffer status.
    //! \details    Verifies the transmission buffer status.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t inlined isTransmissionBufferEmpty(void);

    //!
    //! \brief      Verifies the transmission status.
    //! \details    Verifies the transmission status.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t inlined isTransmissionComplete(void);

    //!
    //! \brief      Gets the errors of the last reception.
    //! \details    Gets the errors of the last reception.
    //! \param[out] errorCode_p         Pointer to store the reception error code.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t getReceptionErrors(
            ReceptionError *errorCode_p
    );

    //     /////////////////////     INTERRUPTS    //////////////////////     //

    //!
    //! \brief      Activates the Reception Complete interrupt.
    //! \details    Activates the Reception Complete interrupt.
    //!
    void inlined activateReceptionCompleteInterrupt(void);

    //!
    //! \brief      Activates the Transmission Buffer Empty interrupt.
    //! \details    Activates the Transmission Buffer Empty interrupt.
    //!
    void inlined activateTransmissionBufferEmptyInterrupt(void);

    //!
    //! \brief      Activates the Transmission Complete interrupt.
    //! \details    Activates the Transmission Complete interrupt.
    //!
    void inlined activateTransmissionCompleteInterrupt(void);

    //!
    //! \brief      Deactivates the Reception Complete interrupt.
    //! \details    Deactivates the Reception Complete interrupt
    //!
    void inlined deactivateReceptionCompleteInterrupt(void);

    //!
    //! \brief      Deactivates the Transmission Buffer Empty interrupt.
    //! \details    Deactivates the Transmission Buffer Empty interrupt.
    //!
    void inlined deactivateTransmissionBufferEmptyInterrupt(void);

    //!
    //! \brief      Deactivates the Transmission Complete interrupt.
    //! \details    Deactivates the Transmission Complete interrupt.
    //!
    void inlined deactivateTransmissionCompleteInterrupt(void);

    //!
    //! \brief      Redirects the standard I/O streams.
    //! \details    Redirects the standard I/O streams.
    //!
    void inlined stdio(void);

    // UCSRA    U2X0
    // UCSRA    MPCM0

    //!
    //! \brief      Sends a frame through the transmitter.
    //! \details    Sends a frame through the transmitter.
    //! \param[out] data_p         Data to be transmitted.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t sendData(cuint16_t data_p);

    //!
    //! \brief      Gets the received data.
    //! \details    Gets the received data.
    //! \param[out] data_p              Pointer to store the received data.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t receiveData(uint16_t *data_p);

    //!
    //! \brief      Flushes the reception buffer.
    //! \details    Flushes the reception buffer.
    //!
    void flushReceptionBuffer(void);

    //!
    //! \brief      Receives data via standard data stream.
    //! \details    Receives data via standard data stream.
    //! \param[out] stream_p            Pointer to data stream.
    //! \return     char                Character received.
    //!
    char receiveDataStd(FILE *stream_p);

    //!
    //! \brief      Sends data via standard data stream.
    //! \details    Sends data via standard data stream.
    //! \param[in]  data_p              Data to be transmitted.
    //! \param[out] stream_p            Pointer to data stream.
    //! \return     int16_t             Always returns 0.
    //!
    int16_t sendDataStd(char data_p, FILE *stream_p);

    //     /////////////////     CONTROL AND STATUS    //////////////////     //
    //!
    //! \brief      Returns the last error.
    //! \details    Returns the last error.
    //! \return     Error               Error status of the last operation.
    //!
    Error           getLastError(
            void
    );

private:
    char _receiveDataStd(FILE *stream_p);
    void _clearDataOverrunError(void);
    void _clearFrameError(void);
    void _clearParityError(void);

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
private:
    //     ////////////////     RECEPTION ERROR FLAGS    ////////////////     //
    bool_t  _isDataOverrunError                         : 1;
    bool_t  _isFrameError                               : 1;
    bool_t  _isParityError                              : 1;

    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    bool_t  _isInitialized                              : 1;
    bool_t  _isReceiverEnabled                          : 1;
    bool_t  _isReceptionCompleteInterruptEnabled        : 1;
    bool_t  _isTransmissionBufferEmptyInterruptEnabled  : 1;
    bool_t  _isTransmissionCompleteInterruptEnabled     : 1;
    bool_t  _isTransmitterEnabled                       : 1;
    Error   _lastError;

    //     ////////////////////     CONFIGURATION    ////////////////////     //
    DataSize        _dataSize;
    Mode            _mode;
    BaudRate        _baudRate;
    ParityMode      _parityMode;
    StopBits        _stopBits;
}; // class Usart0

// =============================================================================
// Class inlined functions
// =============================================================================

//!
//! \cond
//!

void inlined Usart0::disableReceiver(void)
{
    clrBit(UCSR0B, RXEN0);
    return;
}

void inlined Usart0::disableTransmitter(void)
{
    clrBit(UCSR0B, TXEN0);
    return;
}

void inlined Usart0::enableReceiver(void)
{
    setBit(UCSR0B, RXEN0);
    return;
}

void inlined Usart0::enableTransmitter(void)
{
    setBit(UCSR0B, TXEN0);
    return;
}

bool_t inlined Usart0::isReceptionComplete(void)
{
    return isBitSet(UCSR0A, RXC0);
}

bool_t inlined Usart0::isTransmissionBufferEmpty(void)
{
    return isBitSet(UCSR0A, UDRE0);
}

bool_t inlined Usart0::isTransmissionComplete(void)
{
    return isBitSet(UCSR0A, TXC0);
}

void inlined Usart0::activateReceptionCompleteInterrupt(void)
{
    setBit(UCSR0B, RXCIE0);
    return;
}

void inlined Usart0::activateTransmissionBufferEmptyInterrupt(void)
{
    setBit(UCSR0B, UDRIE0);
    return;
}

void inlined Usart0::activateTransmissionCompleteInterrupt(void)
{
    setBit(UCSR0B, TXCIE0);
    return;
}

void inlined Usart0::deactivateReceptionCompleteInterrupt(void)
{
    clrBit(UCSR0B, RXCIE0);
    return;
}

void inlined Usart0::deactivateTransmissionBufferEmptyInterrupt(void)
{
    clrBit(UCSR0B, UDRIE0);
    return;
}

void inlined Usart0::deactivateTransmissionCompleteInterrupt(void)
{
    clrBit(UCSR0B, TXCIE0);
    return;
}

void inlined Usart0::stdio(void)
{
    stdin = stdout = stderr = &usartStream;
    return;
}

Usart0::ReceptionError inlined operator|(Usart0::ReceptionError a, Usart0::ReceptionError b)
{
    return static_cast<Usart0::ReceptionError>(static_cast<cuint8_t>(a) | static_cast<cuint8_t>(b));
}

Usart0::ReceptionError inlined &operator|=(Usart0::ReceptionError &a, Usart0::ReceptionError b)
{
    return a = static_cast<Usart0::ReceptionError>(static_cast<uint8_t>(a) | static_cast<cuint8_t>(b));
}

Usart0::ReceptionError inlined operator&(Usart0::ReceptionError a, Usart0::ReceptionError b)
{
    return static_cast<Usart0::ReceptionError>(static_cast<cuint8_t>(a) & static_cast<cuint8_t>(b));
}

Usart0::ReceptionError inlined &operator&=(Usart0::ReceptionError &a, Usart0::ReceptionError b)
{
    return a = static_cast<Usart0::ReceptionError>(static_cast<uint8_t>(a) & static_cast<cuint8_t>(b));
}

Usart0::ReceptionError inlined operator~(Usart0::ReceptionError a)
{
    return static_cast<Usart0::ReceptionError>(static_cast<int>(Usart0::ReceptionError::ALL) ^ static_cast<int>(a));
}

//!
//! \endcond
//!

// =============================================================================
// External global variables
// =============================================================================

//!
//! \brief          Usart0 peripheral handler object.
//! \details        Usart0 peripheral handler object.
//! \warning        Use this object to handle the peripheral. DO NOT create
//!                     another instance of the class, since this could lead to
//!                     information mismatch between instances and the
//!                     peripheral registers.
//!
extern Usart0 usart0;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/Usart0"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// =============================================================================
// Include guard (END)
// =============================================================================

#endif // defined(_FUNSAPE_PLATFORM_AVR)

#endif  // __FUNSAPE_LIB_USART0_HPP

// =============================================================================
// END OF FILE
// =============================================================================

/*

#define DEBUG_USART0                    0xFFFF

bool_t Usart0::getReceptionStatus(ReceptionError *errorCode_p)
{
    // Marks passage for debugging purpose
    debugMark("Usart0::getReceptionStatus(ReceptionError *)", DEBUG_USART0);

    // Local variables
    uint8_t aux8 = 0;

    // Checks for errors
    if(!isPointerValid(errorCode_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, DEBUG_USART0)
        return false;
    }

    // Retrieve reception error
    aux8 |= (isBitSet(UCSR0A, FE0)) ? (uint8_t)ReceptionError::FRAME_ERROR : 0;
    aux8 |= (isBitSet(UCSR0A, UPE0)) ? (uint8_t)ReceptionError::PARITY_ERROR : 0;
    aux8 |= (isBitSet(UCSR0A, DOR0)) ? (uint8_t)ReceptionError::DATA_OVERRUN_ERROR : 0;
    *errorCode_p = (ReceptionError)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_USART0);
    return true;
}
*/
