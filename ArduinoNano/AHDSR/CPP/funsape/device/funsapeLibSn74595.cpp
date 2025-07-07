//!
//! \file           funsapeLibSn74595.cpp
//! \brief          SN74595 Serial Shift Register module interface for the
//!                     FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-07-10
//! \version        24.07
//! \copyright      license
//! \details        SN74595 Serial Shift Register controller for the FunSAPE
//!                     AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibSn74595.hpp"
#if !defined(__FUNSAPE_LIB_SN74595_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_SN74595_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

// NONE

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Global variables
// =============================================================================

// NONE

// =============================================================================
// Static functions declarations
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Sn74595::Sn74595(void)
{
    // Mark passage for debugging purpose
    debugMark("Sn74595::Sn74595(void)", Debug::CodeIndex::SN74595_MODULE);

    // Resets data members
    this->_clear                        = nullptr;
    this->_dataIn                       = nullptr;
    this->_dataOrderMsbFirst            = false;
    this->_isInitialized                = false;
    this->_isPortsSet                   = false;
    this->_outputEnable                 = nullptr;
    this->_shift                        = nullptr;
    this->_store                        = nullptr;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::SN74595_MODULE);
    return;
}

Sn74595::~Sn74595(void)
{
    // Mark passage for debugging purpose
    debugMark("Sn74595::~Sn74595(void)", Debug::CodeIndex::SN74595_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::SN74595_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error Sn74595::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t Sn74595::init(const DataOrder dataOrder_p)
{
    // Mark passage for debugging purpose
    debugMark("Sn74595::init(const DataOrder)", Debug::CodeIndex::SN74595_MODULE);

    // CHECK FOR ERROR - ports not set
    if(!this->_isPortsSet) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_NOT_SET;
        debugMessage(Error::GPIO_PORT_NOT_SET, Debug::CodeIndex::SN74595_MODULE);
        return false;
    }

    // Configure clear pin
    if(isPointerValid(this->_clear)) {
        this->_clear->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
        this->_clear->low();
    }

    // Configure output enable pin
    if(isPointerValid(this->_outputEnable)) {
        this->_outputEnable->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
        this->_outputEnable->high();
    }

    // Configure data in pin
    this->_dataIn->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    this->_dataIn->low();

    // Configure shift clock pin
    this->_shift->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    this->_shift->low();

    // Configure store clock pin
    this->_store->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    this->_store->low();

    // Updates data members
    this->_dataOrderMsbFirst            = (bool_t)dataOrder_p;
    this->_isInitialized                = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::SN74595_MODULE);
    return true;
}

bool_t Sn74595::setPort(const GpioPin *dataInPin_p, const GpioPin *shiftClockPin_p, const GpioPin *storeClockPin_p,
        const GpioPin *outputEnablePin_p, const GpioPin *masterResetPin_p)
{
    // Mark passage for debugging purpose
    debugMark("Sn74595::setPort(const GpioPin *, const GpioPin *, const GpioPin *, const GpioPin *, const GpioPin *)",
            Debug::CodeIndex::SN74595_MODULE);

    // Resets data members
    this->_clear                        = nullptr;
    this->_dataIn                       = nullptr;
    this->_isInitialized                = false;
    this->_isPortsSet                   = false;
    this->_outputEnable                 = nullptr;
    this->_shift                        = nullptr;
    this->_store                        = nullptr;

    // CHECK FOR ERROR - ports not set
    if((!isPointerValid(dataInPin_p)) || (!isPointerValid(shiftClockPin_p)) || (!isPointerValid(storeClockPin_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::SN74595_MODULE);
        return false;
    }

    // Resets data members
    this->_clear                        = (GpioPin *)masterResetPin_p;
    this->_dataIn                       = (GpioPin *)dataInPin_p;
    this->_isInitialized                = false;
    this->_isPortsSet                   = true;
    this->_outputEnable                 = (GpioPin *)outputEnablePin_p;
    this->_shift                        = (GpioPin *)shiftClockPin_p;
    this->_store                        = (GpioPin *)storeClockPin_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::SN74595_MODULE);
    return true;
}

bool_t Sn74595::disableOutputs(void)
{
    // CHECKS FOR ERRORS - not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::SN74595_MODULE);
        return false;
    }
    // CHECKS FOR ERRORS - pin not set
    if(!isPointerValid(this->_outputEnable)) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_NOT_SET;
        debugMessage(Error::GPIO_PORT_NOT_SET, Debug::CodeIndex::SN74595_MODULE);
        return false;
    }

    // Disables outputs
    this->_outputEnable->high();

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::SN74595_MODULE);
    return true;
}

bool_t Sn74595::enableOutputs(void)
{
    // CHECKS FOR ERRORS - not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::SN74595_MODULE);
        return false;
    }
    // CHECKS FOR ERRORS - pin not set
    if(!isPointerValid(this->_outputEnable)) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_NOT_SET;
        debugMessage(Error::GPIO_PORT_NOT_SET, Debug::CodeIndex::SN74595_MODULE);
        return false;
    }

    // Enables outputs
    this->_outputEnable->low();

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::SN74595_MODULE);
    return true;
}

bool_t Sn74595::clearData(void)
{
    // CHECKS FOR ERRORS - not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::SN74595_MODULE);
        return false;
    }
    // CHECKS FOR ERRORS - pin not set
    if(!isPointerValid(this->_clear)) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_NOT_SET;
        debugMessage(Error::GPIO_PORT_NOT_SET, Debug::CodeIndex::SN74595_MODULE);
        return false;
    }

    // Clears data
    this->_clear->high();
    this->_clear->low();

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::SN74595_MODULE);
    return true;
}

bool_t Sn74595::sendByte(cuint8_t data_p)
{
    // CHECKS FOR ERRORS - not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::SN74595_MODULE);
        return false;
    }

    // Transfers data
    if(this->_dataOrderMsbFirst) {
        for(uint8_t i = 0; i < 8; i++) {
            if(isBitSet(data_p, (7 - i))) {
                this->_dataIn->high();
            } else {
                this->_dataIn->low();
            }
            this->_shift->high();
            this->_shift->low();
        }
    } else {
        for(uint8_t i = 0; i < 8; i++) {
            if(isBitSet(data_p, i)) {
                this->_dataIn->high();
            } else {
                this->_dataIn->low();
            }
            this->_shift->high();
            this->_shift->low();
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::SN74595_MODULE);
    return true;
}

bool_t Sn74595::store(void)
{
    // CHECKS FOR ERRORS - not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::SN74595_MODULE);
        return false;
    }

    // Stores data
    this->_store->high();
    this->_store->low();

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::SN74595_MODULE);
    return true;
}


// =============================================================================
// Class own methods - Private
// =============================================================================

// NONE

// =============================================================================
// Class own methods - Protected
// =============================================================================

// NONE

// =============================================================================
// END OF FILE - funsapeLibSn74595.cpp
// =============================================================================
