//!
//! \file           funsapeLibGpioBus.cpp
//! \brief          GPIO bus peripheral control for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-09
//! \version        24.05
//! \copyright      license
//! \details        GPIO bus peripheral control for the FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibGpioBus.hpp"
#if !defined(__FUNSAPE_LIB_GPIO_BUS_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_GPIO_BUS_HPP != 2407
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

GpioBus::GpioBus(void)
{
    // Mark passage for debugging purpose
    debugMark("GpioBus::GpioBus(void)", Debug::CodeIndex::GPIO_BUS_MODULE);

    // Resets data members
    this->_regDir                       = nullptr;
    this->_regOut                       = nullptr;
    this->_regIn                        = nullptr;
    this->_pinMask                      = (PinMask)0;
    this->_pinIndex                     = PinIndex::P0;
    this->_isInitialized                = false;
    this->_mode                         = Mode::INPUT_FLOATING;
    this->_busSize                      = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_BUS_MODULE);
    return;
}

GpioBus::~GpioBus(void)
{
    // Mark passage for debugging purpose
    debugMark("GpioBus::~GpioBus(void)", Debug::CodeIndex::GPIO_BUS_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_BUS_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error GpioBus::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t GpioBus::init(ioRegAddress_t gpioPortAddress_p, PinIndex gpioPinIndex_p, cuint8_t gpioBusSize_p)
{
    // Mark passage for debugging purpose
    debugMark("GpioBus::init(ioRegAddress_t, PinIndex, cuint8_t)", Debug::CodeIndex::GPIO_BUS_MODULE);

    // CHECK FOR ERROR - port address invalid
    if(!isPointerValid(gpioPortAddress_p)) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_INVALID;
        debugMessage(Error::GPIO_PORT_INVALID, Debug::CodeIndex::GPIO_BUS_MODULE);
        return false;
    }
    // CHECK FOR ERROR - bus size invalid
    if(((uint8_t)gpioPinIndex_p + gpioBusSize_p) > 16) {
        // Returns error
        this->_lastError = Error::GPIO_PIN_INDEX_INVALID;
        debugMessage(Error::ARGUMENT_VALUE_INVALID, Debug::CodeIndex::GPIO_BUS_MODULE);
        return false;
    }
    // CHECK FOR ERROR - bus out of boundaries
    if((gpioBusSize_p == 0) || (gpioBusSize_p > 16)) {
        // Returns error
        this->_lastError = Error::GPIO_PIN_OUT_OF_BOUNDARIES;
        debugMessage(Error::GPIO_PIN_OUT_OF_BOUNDARIES, Debug::CodeIndex::GPIO_BUS_MODULE);
        return false;
    }

    // Local variables
    uint8_t auxPinMask = (((1 << gpioBusSize_p) - 1) << (uint8_t)gpioPinIndex_p);

    // Update data members
    this->_regDir                       = getGpioDdrAddress(gpioPortAddress_p);
    this->_regOut                       = getGpioPortAddress(gpioPortAddress_p);
    this->_regIn                        = getGpioPinAddress(gpioPortAddress_p);
    this->_pinMask                      = (PinMask)auxPinMask;
    this->_pinIndex                     = gpioPinIndex_p;
    this->_isInitialized                = true;
    this->_busSize                      = gpioBusSize_p;

    // Configure pins as input floating
    clrMask(*(this->_regDir), (uint8_t)this->_pinMask);
    clrMask(*(this->_regOut), (uint8_t)this->_pinMask);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_BUS_MODULE);
    return true;
}

//     ///////////////////    PIN RELATED METHODS     ///////////////////     //

bool_t GpioBus::setMode(Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark("GpioBus::setMode(Mode)", Debug::CodeIndex::GPIO_BUS_MODULE);

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::GPIO_BUS_MODULE);
        return false;
    }

    // Nothing to do!
    if(this->_mode == mode_p) {
        // Returns successfully
        this->_lastError = Error::NONE;
        debugMessage(Error::NONE, Debug::CodeIndex::GPIO_BUS_MODULE);
        return true;
    }

    // Configure pin
    switch(mode_p) {
    case Mode::INPUT_FLOATING:
        clrMask(*(this->_regDir), (uint8_t)this->_pinMask);
        clrMask(*(this->_regOut), (uint8_t)this->_pinMask);
        break;
    case Mode::INPUT_PULLED_UP:
        clrMask(*(this->_regDir), (uint8_t)this->_pinMask);
        setMask(*(this->_regOut), (uint8_t)this->_pinMask);
        break;
    case Mode::OUTPUT_PUSH_PULL:
        setMask(*(this->_regDir), (uint8_t)this->_pinMask);
        break;
    }

    // Update data members
    this->_mode = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_BUS_MODULE);
    return true;
}

bool_t GpioBus::write(uint8_t data_p)
{
    // Local variables
    uint8_t aux8 = 0;

    // CHECKS FOR ERRORS - not initialized
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::GPIO_BUS_MODULE);
        return false;
    }

    aux8 = *(this->_regOut);
    clrMask(aux8, (uint8_t)(this->_pinMask));
    aux8 |= ((data_p << (uint8_t)this->_pinIndex) & (uint8_t)(this->_pinMask));
    *(this->_regOut) = aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_BUS_MODULE);
    return true;
}

uint8_t GpioBus::getBusSize(void)
{
    if(!this->_isInitialized) {
        // Returns 0
        return 0;
    }

    // Returns value
    return this->_busSize;
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
// END OF FILE - funsapeLibGpioBus.cpp
// =============================================================================
