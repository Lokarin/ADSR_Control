//!
//! \file           funsapeLibStepper.cpp
//! \brief          Stepper motor module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-07-10
//! \version        24.07
//! \copyright      license
//! \details        Stepper motor module interface for the FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Dependencies
// =============================================================================

#include "funsapeLibStepper.hpp"
#ifndef __FUNSAPE_LIB_STEPPER_HPP
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_STEPPER_HPP != 2407
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

Stepper::Stepper(void)
{
    // Mark passage for debugging purpose
    debugMark("Stepper::Stepper()", Debug::CodeIndex::STEPPER_MODULE);

    // Resets data members
    this->_coilA                        = nullptr;
    this->_coilB                        = nullptr;
    this->_coilC                        = nullptr;
    this->_coilD                        = nullptr;
    this->_mode                         = Mode::FULL_STEP_ONE_PHASE;
    this->_step                         = 0;
    this->_initialized                  = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::STEPPER_MODULE);
    return;
}

// TODO: Implement destructor function
Stepper::~Stepper(void)
{
    // Mark passage for debugging purpose
    debugMark("Stepper::~Stepper(void)", Debug::CodeIndex::STEPPER_MODULE);

    // Returns successfully
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error Stepper::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t Stepper::init(const GpioPin *coilA_p, const GpioPin *coilB_p, const GpioPin *coilC_p, const GpioPin *coilD_p)
{
    // Mark passage for debugging purpose
    debugMark("Stepper::init(const GpioPin *, const GpioPin *)", Debug::CodeIndex::STEPPER_MODULE);

    // Local variables
    GpioPin *auxGpioPin                 = nullptr;

    // Resets data members
    this->_coilA                        = nullptr;
    this->_coilB                        = nullptr;
    this->_coilC                        = nullptr;
    this->_coilD                        = nullptr;
    this->_mode                         = Mode::FULL_STEP_ONE_PHASE;
    this->_step                         = 0;
    this->_initialized                  = false;

    // Checks for errors
    if((!isPointerValid(coilA_p)) || (!isPointerValid(coilB_p)) || (!isPointerValid(coilC_p)) ||
            (!isPointerValid(coilD_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::STEPPER_MODULE);
        return false;
    }
    auxGpioPin = (GpioPin *)coilA_p;
    if(!(auxGpioPin->isInitialized())) {
        // Returns error
        this->_lastError = Error::GPIO_NOT_INITIALIZED;
        debugMessage(Error::GPIO_NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }
    auxGpioPin = (GpioPin *)coilB_p;
    if(!(auxGpioPin->isInitialized())) {
        // Returns error
        this->_lastError = Error::GPIO_NOT_INITIALIZED;
        debugMessage(Error::GPIO_NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }
    auxGpioPin = (GpioPin *)coilC_p;
    if(!(auxGpioPin->isInitialized())) {
        // Returns error
        this->_lastError = Error::GPIO_NOT_INITIALIZED;
        debugMessage(Error::GPIO_NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }
    auxGpioPin = (GpioPin *)coilD_p;
    if(!(auxGpioPin->isInitialized())) {
        // Returns error
        this->_lastError = Error::GPIO_NOT_INITIALIZED;
        debugMessage(Error::GPIO_NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    // Update data members
    this->_coilA                        = (GpioPin *)coilA_p;
    this->_coilB                        = (GpioPin *)coilB_p;
    this->_coilC                        = (GpioPin *)coilC_p;
    this->_coilD                        = (GpioPin *)coilD_p;
    this->_initialized                  = true;

    // Config GPIO
    this->_doStep(0);
    this->_coilA->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    this->_coilB->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    this->_coilC->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    this->_coilD->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::STEPPER_MODULE);
    return true;
}

bool_t Stepper::move(const Rotation direction_p)
{
    // Mark passage for debugging purpose
    debugMark("Stepper::move(const Rotation)", Debug::CodeIndex::STEPPER_MODULE);

    // Checks for errors
    if(!this->_initialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::STEPPER_MODULE);
        return false;
    }

    step_t auxStep = this->_step;

    if(this->_mode == Mode::HALF_STEP) {
        if(direction_p == Rotation::CLOCKWISE) {        // Increment
            auxStep = (auxStep == 7) ? 0 : (auxStep + 1);
        } else {                                        // Decrement
            auxStep = (auxStep == 0) ? 7 : (auxStep - 1);
        }
    } else if(this->_mode == Mode::FULL_STEP_ONE_PHASE) {
        auxStep /= 2;
        if(direction_p == Rotation::CLOCKWISE) {        // Increment
            auxStep = (auxStep == 3) ? 0 : (auxStep + 1);
        } else {                                        // Decrement
            auxStep = (auxStep == 0) ? 3 : (auxStep - 1);
        }
        auxStep *= 2;
    } else if(this->_mode == Mode::FULL_STEP_TWO_PHASE) {
        auxStep = (auxStep == 0) ? 7 : (auxStep - 1);
        auxStep /= 2;
        if(direction_p == Rotation::CLOCKWISE) {        // Increment
            auxStep = (auxStep == 3) ? 0 : (auxStep + 1);
        } else {                                        // Decrement
            auxStep = (auxStep == 0) ? 3 : (auxStep - 1);
        }
        auxStep *= 2;
        auxStep++;
    }

    this->_step = auxStep;
    this->_doStep(auxStep);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::STEPPER_MODULE);
    return true;
}

bool_t Stepper::setMode(const Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark("Stepper::setMode(const Mode)", Debug::CodeIndex::STEPPER_MODULE);

    // Updates data members
    this->_mode     = (Mode)mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::STEPPER_MODULE);
    return true;
}

// =============================================================================
// Class own methods - Private
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

void Stepper::_doStep(const step_t step_p)
{
    switch(step_p) {
    case 0: this->_coilA->high();   this->_coilB->low();    this->_coilC->low();    this->_coilD->low();    break;
    case 1: this->_coilA->high();   this->_coilB->high();   this->_coilC->low();    this->_coilD->low();    break;
    case 2: this->_coilA->low();    this->_coilB->high();   this->_coilC->low();    this->_coilD->low();    break;
    case 3: this->_coilA->low();    this->_coilB->high();   this->_coilC->high();   this->_coilD->low();    break;
    case 4: this->_coilA->low();    this->_coilB->low();    this->_coilC->high();   this->_coilD->low();    break;
    case 5: this->_coilA->low();    this->_coilB->low();    this->_coilC->high();   this->_coilD->high();   break;
    case 6: this->_coilA->low();    this->_coilB->low();    this->_coilC->low();    this->_coilD->high();   break;
    case 7: this->_coilA->high();   this->_coilB->low();    this->_coilC->low();    this->_coilD->high();   break;
    }

    return;
};

// =============================================================================
// Class own methods - Protected
// =============================================================================

// NONE

// =============================================================================
// END OF FILE
// =============================================================================
