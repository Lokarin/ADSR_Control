//!
//! \file           funsapeLibGpioPin.cpp
//! \brief          GPIO single pin peripheral control for the FunSAPE AVR8
//!                     Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-09
//! \version        24.05
//! \copyright      license
//! \details        GPIO single pin peripheral control for the FunSAPE AVR8
//!                     Library
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibGpioPin.hpp"
#if !defined(__FUNSAPE_LIB_GPIO_PIN_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_GPIO_PIN_HPP != 2407
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

GpioPin::GpioPin(void)
{
    // Mark passage for debugging purpose
    debugMark("GpioPin::GpioPin(void)", Debug::CodeIndex::GPIO_PIN_MODULE);

    // Resets data members
    this->_regDir                       = nullptr;
    this->_regOut                       = nullptr;
    this->_regIn                        = nullptr;
    this->_pinMask                      = (PinMask)0;
    this->_pinIndex                     = PinIndex::P0;
    this->_isInitialized                = false;
    this->_mode                         = Mode::INPUT_FLOATING;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_PIN_MODULE);
    return;
}

GpioPin::~GpioPin(void)
{
    // Mark passage for debugging purpose
    debugMark("GpioPin::~GpioPin(void)", Debug::CodeIndex::GPIO_PIN_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_PIN_MODULE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error GpioPin::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t GpioPin::init(ioRegAddress_t gpioPortAddress_p, PinIndex gpioPinIndex_p)
{
    // Mark passage for debugging purpose
    debugMark("GpioPin::init(ioRegAddress_t, PinIndex)", Debug::CodeIndex::GPIO_PIN_MODULE);

    // Local variables
    ioRegAddress_t auxDir = getGpioDdrAddress(gpioPortAddress_p);
    ioRegAddress_t auxOut = getGpioPortAddress(gpioPortAddress_p);

    // CHECK FOR ERROR - port address invalid
    if(!isPointerValid(gpioPortAddress_p)) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_INVALID;
        debugMessage(Error::GPIO_PORT_INVALID, Debug::CodeIndex::GPIO_PIN_MODULE);
        return false;
    }

    // Retrieve pin mode
    if(isBitSet(*auxDir, (uint8_t)gpioPinIndex_p)) {    // Output
        this->_mode = Mode::OUTPUT_PUSH_PULL;
    } else {                                            // Input
        if(isBitSet(*auxOut, (uint8_t)gpioPinIndex_p)) {    // Input pulled up
            this->_mode = Mode::INPUT_PULLED_UP;
        } else {                                            // Input floating
            this->_mode = Mode::INPUT_FLOATING;
        }
    }

    // Update data members
    this->_regDir                       = auxDir;
    this->_regOut                       = auxOut;
    this->_regIn                        = getGpioPinAddress(gpioPortAddress_p);
    this->_pinMask                      = (PinMask)(1 << (uint8_t)gpioPinIndex_p);
    this->_pinIndex                     = gpioPinIndex_p;
    this->_isInitialized                = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_PIN_MODULE);
    return true;
}

//     ///////////////////    PIN RELATED METHODS     ///////////////////     //

bool_t GpioPin::setMode(Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark("GpioPin::setMode(Mode)", Debug::CodeIndex::GPIO_PIN_MODULE);

    // Checks initialization
    if(!this->_isInitialized) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::GPIO_PIN_MODULE);
        return false;
    }

    // Nothing to do!
    if(this->_mode == mode_p) {
        // Returns successfully
        this->_lastError = Error::NONE;
        debugMessage(Error::NONE, Debug::CodeIndex::GPIO_PIN_MODULE);
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
    debugMessage(Error::NONE, Debug::CodeIndex::GPIO_PIN_MODULE);
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
// END OF FILE - funsapeLibGpioPin.cpp
// =============================================================================
