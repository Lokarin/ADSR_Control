

#include "funsapeLibUsart0.hpp"

#if defined(_FUNSAPE_PLATFORM_AVR)

Usart0 *usartDefaultHandler;
Usart0 usart0;
FILE usartStream;

int usartTransmitStdWrapper(char data, FILE *stream);

Usart0::Usart0(BaudRate baudRate_p, Mode mode_p, FrameFormat format_p)
{
    if(!this->setBaudRate(baudRate_p)) {
        // Returns error
        return;
    }
    if(!this->setMode(mode_p)) {
        // Returns error
        return;
    }
    if(!this->setFrameFormat(format_p)) {
        // Returns error
        return;
    }

    fdev_setup_stream(&usartStream, usartTransmitStdWrapper, NULL, _FDEV_SETUP_WRITE);

    // Returns successfully
    this->_lastError = Error::NONE;
    return;
}

Usart0::~Usart0(void)
{
    return;
}

bool_t Usart0::init(void)
{
    // Local variables
    uint8_t ucsr0a = UCSR0A;
    uint8_t ucsr0b = UCSR0B;
    uint8_t ucsr0c = UCSR0C;
    uint64_t ubrr0 = (uint64_t)UBRR0;
    uint8_t auxPrescaler = 1;
    uint32_t aux32 = 0;

    // Clear errors
    ucsr0a &= ~((1 << FE0) | (1 << DOR0) | (1 << UPE0));

    // Configure stop bit
    switch(this->_stopBits) {
    case Usart0::StopBits::SINGLE:
        clrBit(ucsr0c, USBS0);
        break;
    case Usart0::StopBits::DOUBLE:
        setBit(ucsr0c, USBS0);
        break;
    }

    // Configure parity
    clrMaskOffset(ucsr0c, 0x03, UPM00);
    switch(this->_parityMode) {
    case Usart0::ParityMode::NONE:
        break;
    case Usart0::ParityMode::ODD:
        setMaskOffset(ucsr0c, 0x03, UPM00);
        break;
    case Usart0::ParityMode::EVEN:
        setMaskOffset(ucsr0c, 0x02, UPM00);
        break;
    }

    // Configure data bits
    clrBit(ucsr0b, UCSZ02);
    clrMaskOffset(ucsr0c, 0x03, UCSZ00);
    switch(this->_dataSize) {
    case Usart0::DataSize::DATA_5_BITS:
        break;
    case Usart0::DataSize::DATA_6_BITS:
        setMaskOffset(ucsr0c, 0x01, UCSZ00);
        break;
    case Usart0::DataSize::DATA_7_BITS:
        setMaskOffset(ucsr0c, 0x02, UCSZ00);
        break;
    case Usart0::DataSize::DATA_8_BITS:
        setMaskOffset(ucsr0c, 0x03, UCSZ00);
        break;
    case Usart0::DataSize::DATA_9_BITS:
        setBit(ucsr0b, UCSZ02);
        setMaskOffset(ucsr0c, 0x03, UCSZ00);
        break;
    }

    // Configure mode
    clrMaskOffset(ucsr0c, 0x03, UMSEL00);
    clrBit(ucsr0a, U2X0);               // Single Speed
    clrBit(ucsr0c, UCPOL0);             // Polarity
    switch(this->_mode) {
    case Usart0::Mode::ASYNCHRONOUS:
        auxPrescaler = 16;
        break;
    case Usart0::Mode::ASYNCHRONOUS_DOUBLE_SPEED:
        setBit(ucsr0a, U2X0);           // Double Speed
        auxPrescaler = 8;
        break;
    case Usart0::Mode::SYNCHRONOUS_TX_RISING_RX_FALLING:
        setMaskOffset(ucsr0c, 1, UMSEL00);      // Synchronous Mode Tx rising edge
        clrBit(ucsr0c, UCPOL0);
        auxPrescaler = 2;
        break;
    case Usart0::Mode::SYNCHRONOUS_TX_FALLING_RX_RISING:
        setMaskOffset(ucsr0c, 1, UMSEL00);      // Synchronous Mode Tx falling edge
        setBit(ucsr0c, UCPOL0);
        auxPrescaler = 2;
        break;
    case Usart0::Mode::MASTER_SPI_MODE_0:
        setMaskOffset(ucsr0c, 3, UMSEL00);      // Synchronous SPI Mode
        clrBit(ucsr0c, UCPOL0);         // Polarity
        clrBit(ucsr0c, UCPHA0);         // Phase
        auxPrescaler = 2;
        break;
    case Usart0::Mode::MASTER_SPI_MODE_1:
        setMaskOffset(ucsr0c, 3, UMSEL00);      // Synchronous SPI Mode
        clrBit(ucsr0c, UCPOL0);         // Polarity
        setBit(ucsr0c, UCPHA0);         // Phase
        auxPrescaler = 2;
        break;
    case Usart0::Mode::MASTER_SPI_MODE_2:
        setMaskOffset(ucsr0c, 3, UMSEL00);      // Synchronous SPI Mode
        setBit(ucsr0c, UCPOL0);         // Polarity
        clrBit(ucsr0c, UCPHA0);         // Phase
        auxPrescaler = 2;
        break;
    case Usart0::Mode::MASTER_SPI_MODE_3:
        setMaskOffset(ucsr0c, 3, UMSEL00);      // Synchronous SPI Mode
        setBit(ucsr0c, UCPOL0);         // Polarity
        setBit(ucsr0c, UCPHA0);         // Phase
        auxPrescaler = 2;
        break;
    }

    // Configure baud rate
    systemStatus.getCpuClock(&aux32);
    ubrr0 = (aux32 / (auxPrescaler * (uint32_t)this->_baudRate) - 1);

    // Configures USART registers
    UCSR0A = ucsr0a;
    UCSR0B = ucsr0b;
    UCSR0C = ucsr0c;
    UBRR0H = (uint8_t)(0x0F & (ubrr0 >> 8));
    UBRR0L = (uint8_t)(0xFF & ubrr0);

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Usart0::setMode(const Mode mode_p)
{
    // Resets data members
    this->_isInitialized = false;

    // Checks for errors
    switch(mode_p) {
    case Usart0::Mode::ASYNCHRONOUS:
    case Usart0::Mode::ASYNCHRONOUS_DOUBLE_SPEED:
    case Usart0::Mode::SYNCHRONOUS_TX_RISING_RX_FALLING:
    case Usart0::Mode::SYNCHRONOUS_TX_FALLING_RX_RISING:
    case Usart0::Mode::MASTER_SPI_MODE_0:
    case Usart0::Mode::MASTER_SPI_MODE_1:
    case Usart0::Mode::MASTER_SPI_MODE_2:
    case Usart0::Mode::MASTER_SPI_MODE_3:
        break;
    default:
        // Returns error
        this->_lastError = Error::MODE_NOT_SUPPORTED;
        return false;
    }

    // Updates class member
    this->_mode = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Usart0::setDataSize(const DataSize dataSize_p)
{
    // Resets data members
    this->_isInitialized = false;

    // Checks for errors
    switch(dataSize_p) {
    case Usart0::DataSize::DATA_5_BITS:
    case Usart0::DataSize::DATA_6_BITS:
    case Usart0::DataSize::DATA_7_BITS:
    case Usart0::DataSize::DATA_8_BITS:
    case Usart0::DataSize::DATA_9_BITS:
        break;
    default:
        // Returns error
        this->_lastError = Error::USART_DATA_SIZE_NOT_SUPPORTED;
        return false;
    }

    // Updates data members
    this->_dataSize = dataSize_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Usart0::setStopBits(const StopBits stopBits_p)
{
    // Resets data members
    this->_isInitialized = false;

    // Checks for errors
    switch(stopBits_p) {
    case Usart0::StopBits::SINGLE:
    case Usart0::StopBits::DOUBLE:
        break;
    default:
        // Returns error
        this->_lastError = Error::USART_STOP_BIT_NOT_SUPPORTED;
        return false;
    }

    // Updates data members
    this->_stopBits = stopBits_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Usart0::setParityMode(const ParityMode parityMode_p)
{
    // Resets data members
    this->_isInitialized = false;

    // Checks for errors
    switch(parityMode_p) {
    case Usart0::ParityMode::NONE:
    case Usart0::ParityMode::ODD:
    case Usart0::ParityMode::EVEN:
        break;
    default:
        // Returns error
        this->_lastError = Error::USART_PARITY_NOT_SUPPORTED;
        return false;
    }

    // Updates data members
    this->_parityMode = parityMode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Usart0::setBaudRate(const BaudRate baudRate_p)
{
    // Resets data members
    this->_isInitialized = false;

    // Checks for errors
    switch(baudRate_p) {
    case Usart0::BaudRate::BAUD_RATE_600:
    case Usart0::BaudRate::BAUD_RATE_1200:
    case Usart0::BaudRate::BAUD_RATE_1800:
    case Usart0::BaudRate::BAUD_RATE_2400:
    case Usart0::BaudRate::BAUD_RATE_4800:
    case Usart0::BaudRate::BAUD_RATE_9600:
    case Usart0::BaudRate::BAUD_RATE_14400:
    case Usart0::BaudRate::BAUD_RATE_19200:
    case Usart0::BaudRate::BAUD_RATE_28800:
    case Usart0::BaudRate::BAUD_RATE_38400:
    case Usart0::BaudRate::BAUD_RATE_56000:
    case Usart0::BaudRate::BAUD_RATE_57600:
    case Usart0::BaudRate::BAUD_RATE_115200:
    case Usart0::BaudRate::BAUD_RATE_128000:
    case Usart0::BaudRate::BAUD_RATE_230400:
    case Usart0::BaudRate::BAUD_RATE_256000:
        break;
    default:
        // Returns error
        this->_lastError = Error::USART_BAUD_RATE_NOT_SUPPORTED;
        return false;
    }

    // Updates data members
    this->_baudRate = baudRate_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Usart0::setFrameFormat(const FrameFormat frameFormat_p)
{
    // Local variables
    uint8_t auxFrame = 0;

    // Resets data members
    this->_isInitialized = false;

    // Checks for errors
    switch(frameFormat_p) {
    case Usart0::FrameFormat::FRAME_FORMAT_8_N_1:
    case Usart0::FrameFormat::FRAME_FORMAT_8_O_1:
    case Usart0::FrameFormat::FRAME_FORMAT_8_E_1:
    case Usart0::FrameFormat::FRAME_FORMAT_8_N_2:
    case Usart0::FrameFormat::FRAME_FORMAT_8_O_2:
    case Usart0::FrameFormat::FRAME_FORMAT_8_E_2:
    case Usart0::FrameFormat::FRAME_FORMAT_9_N_1:
    case Usart0::FrameFormat::FRAME_FORMAT_9_O_1:
    case Usart0::FrameFormat::FRAME_FORMAT_9_E_1:
    case Usart0::FrameFormat::FRAME_FORMAT_9_N_2:
    case Usart0::FrameFormat::FRAME_FORMAT_9_O_2:
    case Usart0::FrameFormat::FRAME_FORMAT_9_E_2:
    case Usart0::FrameFormat::FRAME_FORMAT_5_N_1:
    case Usart0::FrameFormat::FRAME_FORMAT_5_O_1:
    case Usart0::FrameFormat::FRAME_FORMAT_5_E_1:
    case Usart0::FrameFormat::FRAME_FORMAT_5_N_2:
    case Usart0::FrameFormat::FRAME_FORMAT_5_O_2:
    case Usart0::FrameFormat::FRAME_FORMAT_5_E_2:
    case Usart0::FrameFormat::FRAME_FORMAT_6_N_1:
    case Usart0::FrameFormat::FRAME_FORMAT_6_O_1:
    case Usart0::FrameFormat::FRAME_FORMAT_6_E_1:
    case Usart0::FrameFormat::FRAME_FORMAT_6_N_2:
    case Usart0::FrameFormat::FRAME_FORMAT_6_O_2:
    case Usart0::FrameFormat::FRAME_FORMAT_6_E_2:
    case Usart0::FrameFormat::FRAME_FORMAT_7_N_1:
    case Usart0::FrameFormat::FRAME_FORMAT_7_O_1:
    case Usart0::FrameFormat::FRAME_FORMAT_7_E_1:
    case Usart0::FrameFormat::FRAME_FORMAT_7_N_2:
    case Usart0::FrameFormat::FRAME_FORMAT_7_O_2:
    case Usart0::FrameFormat::FRAME_FORMAT_7_E_2:
        break;
    default:
        // Returns error
        this->_lastError = Error::USART_FRAME_FORMAT_NOT_SUPPORTED;
        return false;
    }

    // Decodes frame format
    auxFrame = (uint8_t)frameFormat_p;
    switch(auxFrame & 0x03) {
    case 1: this->_stopBits = StopBits::SINGLE; break;
    case 2: this->_stopBits = StopBits::DOUBLE; break;
    default:
        // Returns error
        this->_lastError = Error::UNKNOWN;
        return false;
    }
    auxFrame >>= 2;
    switch(auxFrame & 0x03) {
    case 0: this->_parityMode = ParityMode::NONE; break;
    case 1: this->_parityMode = ParityMode::ODD; break;
    case 2: this->_parityMode = ParityMode::EVEN; break;
    default:
        // Returns error
        this->_lastError = Error::UNKNOWN;
        return false;
    }
    auxFrame >>= 2;
    switch(auxFrame & 0x0F) {
    case 5: this->_dataSize = DataSize::DATA_5_BITS; break;
    case 6: this->_dataSize = DataSize::DATA_6_BITS; break;
    case 7: this->_dataSize = DataSize::DATA_7_BITS; break;
    case 8: this->_dataSize = DataSize::DATA_8_BITS; break;
    case 9: this->_dataSize = DataSize::DATA_9_BITS; break;
    default:
        // Returns error
        this->_lastError = Error::UNKNOWN;
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Usart0::getReceptionErrors(ReceptionError *errorCode_p)
{
    // Checks for errors
    if(!isPointerValid(errorCode_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        return false;
    }

    // Gets errors
    *errorCode_p = ReceptionError::NONE;
    if(this->_isDataOverrunError) {
        *errorCode_p |= Usart0::ReceptionError::DATA_OVERRUN_ERROR;
    }
    if(this->_isFrameError) {
        *errorCode_p |= Usart0::ReceptionError::FRAME_ERROR;
    }
    if(this->_isParityError) {
        *errorCode_p |= Usart0::ReceptionError::PARITY_ERROR;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

char Usart0::_receiveDataStd(FILE *stream)
{
    char auxChar = 0;

    return auxChar;
}

void Usart0::_clearDataOverrunError(void)
{
    clrBit(UCSR0A, DOR0);
    return;
}

void Usart0::_clearFrameError(void)
{
    clrBit(UCSR0A, FE0);
    return;
}

void Usart0::_clearParityError(void)
{
    clrBit(UCSR0A, UPE0);
    return;
}

bool_t Usart0::sendData(cuint16_t data_p)
{
    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        return false;
    }

    // Waits until last transmission ends
    waitUntilBitIsSet(UCSR0A, UDRE0);

    // Stores 8th bit (if data size in 9 bits)
    if(this->_dataSize == DataSize::DATA_9_BITS) {
        if(isBitSet(data_p, 8)) {
            setBit(UCSR0B, TXB80);
        } else {
            clrBit(UCSR0B, TXB80);
        }
    }
    UDR0 = (uint8_t)data_p;

    // Returns sucessfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Usart0::receiveData(uint16_t *data_p)
{
    // Local variables
    uint8_t aux8;

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        return false;
    }

    // Waits until last reception ends
    waitUntilBitIsSet(UCSR0A, RXC0);

    // Checks reception erros
    aux8 = UCSR0A;
    this->_isDataOverrunError = isBitSet(aux8, DOR0);
    this->_isFrameError = isBitSet(aux8, FE0);
    this->_isParityError = isBitSet(aux8, UPE0);

    // Stores 8th bit (if data size in 9 bits)
    *data_p = 0;
    if(this->_dataSize == DataSize::DATA_9_BITS) {
        *data_p = (isBitSet(UCSR0B, RXB80)) ? (1 << 8) : 0;
    }

    // Gets received byte
    *data_p |= UDR0;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

void Usart0::flushReceptionBuffer(void)
{
    __attribute__((unused)) uint8_t aux8;

    while(this->isReceptionComplete()) {
        aux8 = UDR0;
    }

    return;
}

char Usart0::receiveDataStd(FILE *stream_p)
{
    waitUntilBitIsSet(UCSR0A, RXC0);	// Waits until last reception ends

    return (int16_t)UDR0;
}

int16_t Usart0::sendDataStd(char data_p, FILE *stream_p)
{
    waitUntilBitIsSet(UCSR0A, UDRE0);	// Waits until last transmission ends
    UDR0 = data_p;

    return 0;
}

int usartTransmitStdWrapper(char c, FILE *f)
{
    return usartDefaultHandler->sendDataStd(c, f);
}

// =============================================================================
// Interrupt callback functions
// =============================================================================

weakened void usartReceptionCompleteCallback(void)
{
    return;
}

weakened void usartTransmissionBufferEmptyCallback(void)
{
    return;
}

weakened void usartTransmissionCompleteCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

//!
//! \brief          USART_RX interrupt service routine
//! \details        USART_RX interrupt service routine.
//!
ISR(USART_RX_vect)
{
    usartReceptionCompleteCallback();
}

//!
//! \brief          USART_TX interrupt service routine
//! \details        USART_TX interrupt service routine.
//!
ISR(USART_TX_vect)
{
    usartTransmissionCompleteCallback();
}

//!
//! \brief          USART_UDRE interrupt service routine
//! \details        USART_UDRE interrupt service routine.
//!
ISR(USART_UDRE_vect)
{
    usartTransmissionBufferEmptyCallback();
}

#endif // defined(_FUNSAPE_PLATFORM_AVR)

// =============================================================================
// END OF FILE
// =============================================================================
