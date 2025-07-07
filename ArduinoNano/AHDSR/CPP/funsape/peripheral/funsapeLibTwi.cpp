//!
//! \file           funsapeLibTwi.cpp
//! \brief          TWI peripheral control for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        TWI peripheral control for the FunSAPE AVR8 Library
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibTwi.hpp"
#if !defined(__FUNSAPE_LIB_TWI_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_TWI_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

#include <avr/interrupt.h>

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint32_t   constTwiBitRateMax          = 400'000;
cuint32_t   constTwiBitRateMin          = 1'000;
cuint8_t    constTwiBufferSizeMax       = 100;
cuint8_t    constTwiBufferSizeMin       = 10;
cuint16_t   constTwiDefaultTimeout      = 20;

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

Twi twi;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Twi::Twi(void)
{
    // Reset data members
    this->_bufferData                   = nullptr;
    this->_bufferIndex                  = 0;
    this->_bufferLength                 = 0;
    this->_bufferMaxSize                = 0;
    this->_devAddress                   = 0;
    this->_devAddressSet                = false;
    this->_initialized                  = false;
    this->_lastTransOk                  = false;
    this->_state                        = State::NO_STATE;
    this->_timeout                      = constTwiDefaultTimeout;
    this->_twiError                     = 0;
    this->_useLongAddress               = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    return;
}

Twi::~Twi(void)
{
    // Returns successfully
    return;
}

// =============================================================================
// Class public methods - Inhirited methods
// =============================================================================

bool_t Twi::readReg(cuint8_t reg_p, uint8_t *buffData_p, cuint16_t buffSize_p)
{
    // Local variables
    bool_t auxBool                      = false;

    // Checks for errors - Device address not set
    if(!this->_devAddressSet) {
        // Returns error
        this->_lastError = Error::COMMUNICATION_NO_DEVICE_SELECTED;
        return false;
    }

    // Sends data
    if(this->_useLongAddress) {
        // FIXME - implement support to 10-bit address
        // Returns error
        this->_lastError = Error::NOT_IMPLEMENTED;
        return false;
    } else {
        auxBool = this->sendData((uint8_t)this->_devAddress, Operation::READ, reg_p, buffData_p, buffSize_p);
    }

    // Error - Communication error
    if(!auxBool) {
        // Returns error
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Twi::writeReg(cuint8_t reg_p, cuint8_t *buffData_p, cuint16_t buffSize_p)
{
    // Local variables
    bool_t auxBool                      = false;

    // Checks for errors - Device address not set
    if(!this->_devAddressSet) {
        // Returns error
        this->_lastError = Error::COMMUNICATION_NO_DEVICE_SELECTED;
        return false;
    }

    // Sends data
    if(this->_useLongAddress) {
        // FIXME - implement support to 10-bit address
        // Returns error
        this->_lastError = Error::NOT_IMPLEMENTED;
        return false;
    } else {
        auxBool = this->sendData((uint8_t)this->_devAddress, Operation::WRITE, reg_p, (uint8_t *)buffData_p, buffSize_p);
    }

    // Error - Communication error
    if(!auxBool) {
        // Returns error
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Twi::setDevice(cuint16_t address_p, cbool_t useLongAddress_p)
{
    // Update data members
    this->_devAddress                   = address_p;
    this->_useLongAddress               = useLongAddress_p;
    this->_devAddressSet                = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Twi::sendData(uint8_t devAddress_p, Operation readWrite_p, uint8_t reg_p, uint8_t *msg_p, uint8_t msgSize_p)
{
    // Check for errors - NOT Initialized
    if(!this->_initialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        return false;
    }
    // Check for errors - Message pointer
    if((msgSize_p > 0) && (msg_p == nullptr)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        return false;
    }

    // Wait last transmission ends
    if(!this->_waitWhileIsBusy()) {
        // Returns error
        return false;
    }

    // Prepare to send data
    if(readWrite_p == Operation::WRITE) {       // Write operation
        this->_bufferData[0] = (devAddress_p << 1) | (uint8_t)(Operation::WRITE);
        this->_bufferData[1] = reg_p;
        for(uint8_t i = 0; i < msgSize_p; i++) {
            this->_bufferData[i + 2] = msg_p[i];
        }
        this->_bufferLength = msgSize_p + 2;
        this->_startTransmission();
    } else {                            // Read operation
        // Set pointer first
        this->_bufferData[0] = (devAddress_p << 1) | (uint8_t)(Operation::WRITE);
        this->_bufferData[1] = reg_p;
        this->_bufferLength = 2;
        this->_startTransmission();
        // Wait last transmission ends
        if(!this->_waitWhileIsBusy()) {
            // Returns error
            return false;
        }
        // Read data
        this->_bufferData[0] = (devAddress_p << 1) | (uint8_t)(Operation::READ);
        this->_bufferLength = msgSize_p + 1;
        this->_startTransmission();
        if(!this->_waitWhileIsBusy()) {
            // Returns error
            return false;
        }
        // Gets data from reception buffer
        if(!this->_readFromBuffer(msg_p, msgSize_p)) {
            // Returns error
            return false;
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

Bus::BusType Twi::getBusType(void)
{
    // Returns bus type
    return Bus::BusType::TWI;
}

// =============================================================================
// Class public methods - Own methods
// =============================================================================

bool_t Twi::init(cuint32_t clockSpeed_p, cuint8_t bufferSize_p)
{
    // Local variables
    uint32_t aux32                      = 0;
    // uint16_t aux16 = 0;
    uint8_t aux8                        = 0;

    // Disables TWI and reset all registers
    clrBit(TWCR, TWEN);
    TWCR = 0x00;
    TWSR = 0x00;
    TWBR = 0;
    TWAR = 0;
    TWAMR = 0;

    // Check for errors - Clock speed
    if(clockSpeed_p < constTwiBitRateMin) {
        // Returns error
        this->_lastError = Error::CLOCK_SPEED_TOO_LOW;
        return false;
    } else if(clockSpeed_p > constTwiBitRateMax) {
        // Returns error
        this->_lastError = Error::CLOCK_SPEED_TOO_HIGH;
        return false;
    }
    // Check for errors - Buffer size
    if(bufferSize_p < constTwiBufferSizeMin) {
        // Returns error
        this->_lastError = Error::BUFFER_SIZE_TOO_SMALL;
        return false;
    } else if(bufferSize_p > constTwiBufferSizeMax) {
        // Returns error
        this->_lastError = Error::BUFFER_SIZE_TOO_LARGE;
        return false;
    }

    // Allocates memory (Free first if already allocated)
    if(isPointerValid(this->_bufferData)) {
        free(this->_bufferData);
        this->_bufferData = nullptr;
    }
    this->_bufferData = (uint8_t *)calloc((bufferSize_p + 2), sizeof(uint8_t));
    if(!isPointerValid(this->_bufferData)) {
        // Returns error
        this->_lastError = Error::MEMORY_ALLOCATION;
        return false;
    }
    this->_bufferMaxSize = bufferSize_p + 2;
    this->_bufferIndex = 0;
    this->_bufferLength = 0;

    // Evaluate BIT RATE and PRESCALER
    systemStatus.getCpuClock(&aux32);
    aux32 /= clockSpeed_p;
    // aux16 = (uint16_t)aux32;
    aux32 -= 16;
    aux32 /= 2;
    if(aux32 <= 255) {                  // Prescaler 1
        aux8 = (uint8_t)aux32;
    } else if(aux32 <= 1020) {          // Prescaler 4
        aux8 = (uint8_t)(aux32 / 4);
        TWSR |= (1 << TWPS0);
    } else if(aux32 <= 4080) {          // Prescaler 16
        aux8 = (uint8_t)(aux32 / 16);
        TWSR |= (2 << TWPS0);
    } else if(aux32 <= 16320) {         // Prescaler 64
        aux8 = (uint8_t)(aux32 / 64);
        TWSR |= (3 << TWPS0);
    }

    // Update TWI registers
    TWBR                                = aux8;
    TWDR                                = 0xFF;         // Release SDA
    setBit(TWCR, TWEN);                 // Activate TWI interface
    this->_initialized                  = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Twi::setTimeout(cuint16_t timeout_p)
{
    // Updates data members
    this->_timeout = timeout_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

Error Twi::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

// =============================================================================
// Class private methods
// =============================================================================

bool_t Twi::_waitWhileIsBusy(void)
{
    // Local variables
    uint32_t stopwatchMark;
    uint32_t stopwatchDeadline;

    // Evaluates stopwatch deadline
    if(this->_timeout == 0) {
        stopwatchDeadline = 0xFFFFFFFF;
    } else {
        stopwatchDeadline = 0;
        systemStatus.getStopwatchValue(&stopwatchDeadline);
        stopwatchDeadline += this->_timeout;
    }

    // Wait until TWI is ready for next transmission
    do {
        stopwatchMark = 0;
        systemStatus.getStopwatchValue(&stopwatchMark);
        if(stopwatchMark > stopwatchDeadline) {
            // Returns error
            this->_lastError = Error::COMMUNICATION_TIMEOUT;
            return false;
        }
    } while(isBitSet(TWCR, TWIE));

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Twi::_startTransmission(void)
{
    this->_lastTransOk = false;
    this->_state = State::NO_STATE;
    TWCR = 0 |
            (1 << TWEN) |
            (1 << TWIE) |
            (1 << TWINT) |
            (1 << TWSTA);

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

bool_t Twi::_readFromBuffer(uint8_t *msg_p, cuint8_t msgSize_p)
{
    // Check for errors
    if(!this->_lastTransOk) {
        // Returns error
        this->_lastError = Error::COMMUNICATION_FAILED;
        return false;
    }
    for(uint8_t i = 0; i < msgSize_p; i++) {
        msg_p[i] = this->_bufferData[i + 1];
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    return true;
}

// =============================================================================
// Class protected methods
// =============================================================================

// NONE

// =============================================================================
// General public functions definitions
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

void Twi::interruptHandler(void)
{
    static uint8_t twiBufferPointer;

    State twiState = (Twi::State)(TWSR & 0xFC);

    switch(twiState) {
    case Twi::State::START:             // START has been transmitted
    case Twi::State::REP_START:         // Repeated START has been transmitted
        twiBufferPointer = 0;           // Set buffer pointer to the TWI Address location
    case Twi::State::MTX_ADR_ACK:       // SLA+W has been transmitted and ACK received
    case Twi::State::MTX_DATA_ACK:      // Data byte has been transmitted and ACK received
        if(twiBufferPointer < this->_bufferLength) {
            TWDR = this->_bufferData[twiBufferPointer++];
            TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT);
        } else {                        // Send STOP after last byte
            this->_lastTransOk = true;  // Set status bits to completed successfully
            TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTO);
        }
        break;
    case Twi::State::MRX_DATA_ACK:      // Data byte has been received and ACK transmitted
        this->_bufferData[twiBufferPointer++] = TWDR;
    case Twi::State::MRX_ADR_ACK:       // SLA+R has been transmitted and ACK received
        if(twiBufferPointer < (this->_bufferLength - 1)) {  // Detect the last byte to NACK it
            TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT) | (1 << TWEA);
        } else {                        // Send NACK after next reception
            TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT);
        }
        break;
    case Twi::State::MRX_DATA_NACK:     // Data byte has been received and NACK transmitted
        this->_bufferData[twiBufferPointer] = TWDR;
        this->_lastTransOk = true;      // Set status bits to completed successfully
        TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTO);
        break;
    case Twi::State::ARB_LOST:          // Arbitration lost
        TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT) | (1 << TWSTA);
        break;
    case Twi::State::MTX_ADR_NACK:      // SLA+W has been transmitted and NACK received
    case Twi::State::MRX_ADR_NACK:      // SLA+R has been transmitted and NACK received
    case Twi::State::MTX_DATA_NACK:     // Data byte has been transmitted and NACK received
    case Twi::State::BUS_ERROR:         // Bus error due to an illegal START or STOP condition
    default:
        this->_twiError = TWSR;         // Store TWSR and automatically sets clears noErrors bit
        TWCR = (1 << TWEN);             // Reset TWI Interface
        break;
    }
}

// =============================================================================
// Interrupt handlers
// =============================================================================

ISR(TWI_vect)
{
    twi.interruptHandler();
}

// =============================================================================
// END OF FILE
// =============================================================================
