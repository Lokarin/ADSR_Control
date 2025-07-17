//!
//! \file           funsapeLibTm1637.cpp
//! \brief          TM1637 Display module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-07-10
//! \version        24.07
//! \copyright      license
//! \details        TM1637 Display module interface for the FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Dependencies
// =============================================================================

#include "funsapeLibTm1637.hpp"
#ifndef __FUNSAPE_LIB_TM1637_HPP
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_TM1637_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t clockPeriod = 10;
cuint8_t segments[16] = {
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111,
    0b01110111,
    0b01111100,
    0b00111001,
    0b01011110,
    0b01111001,
    0b01110001
};

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

Tm1637::Tm1637(void)
{
    // Mark passage for debugging purpose
    debugMark("Tm1637::Tm1637()", Debug::CodeIndex::TM1637_MODULE);

    // Resets data members
    this->_clkPin                       = nullptr;
    this->_contrastLevel                = Contrast::PERCENT_62_5;
    this->_dioPin                       = nullptr;
    this->_initialized                  = false;
    this->_showDisplay                  = false;
    this->_useAutoIncrementMode         = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return;
}

Tm1637::Tm1637(const GpioPin *dioPin_p, const GpioPin *clkPin_p)
{
    // Mark passage for debugging purpose
    debugMark("Tm1637::Tm1637(const GpioPin *, const GpioPin *)", Debug::CodeIndex::TM1637_MODULE);

    // Resets data members
    this->_clkPin                       = nullptr;
    this->_contrastLevel                = Contrast::PERCENT_62_5;
    this->_dioPin                       = nullptr;
    this->_initialized                  = false;
    this->_showDisplay                  = false;
    this->_useAutoIncrementMode         = true;

    // Check function arguments for errors
    if((!isPointerValid(dioPin_p)) || (!isPointerValid(clkPin_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::TM1637_MODULE);
        return;
    }

    // Update data members
    this->_clkPin                       = (GpioPin *)clkPin_p;
    this->_dioPin                       = (GpioPin *)dioPin_p;
    this->_initialized                  = true;

    // Config GPIO
    this->_clkPin->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    this->_clkPin->set();
    this->_dioPin->setMode(GpioPin::Mode::INPUT_FLOATING);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return;
}

// TODO: Implement destructor function
Tm1637::~Tm1637(void)
{
    // Mark passage for debugging purpose
    debugMark("Tm1637::~Tm1637(void)", Debug::CodeIndex::TM1637_MODULE);

    // Returns successfully
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error Tm1637::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t Tm1637::init(const GpioPin *dioPin_p, const GpioPin *clkPin_p)
{
    // Mark passage for debugging purpose
    debugMark("Tm1637::init(const GpioPin *, const GpioPin *)", Debug::CodeIndex::TM1637_MODULE);

    // Resets data members
    this->_clkPin                       = nullptr;
    this->_contrastLevel                = Contrast::PERCENT_62_5;
    this->_dioPin                       = nullptr;
    this->_initialized                  = false;
    this->_showDisplay                  = false;
    this->_useAutoIncrementMode         = true;

    // Check function arguments for errors
    if((!isPointerValid(dioPin_p)) || (!isPointerValid(clkPin_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }

    // Update data members
    this->_clkPin                       = (GpioPin *)clkPin_p;
    this->_dioPin                       = (GpioPin *)dioPin_p;
    this->_initialized                  = true;

    // Config GPIO
    this->_clkPin->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    this->_clkPin->set();
    this->_dioPin->setMode(GpioPin::Mode::INPUT_FLOATING);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return true;
}

bool_t Tm1637::setAddressingMode(cbool_t useAutoIncrementMode_p)
{
    // Mark passage for debugging purpose
    debugMark("Tm1637::setAddressingMode(cbool_t)", Debug::CodeIndex::TM1637_MODULE);

    // Update data members
    this->_useAutoIncrementMode         = useAutoIncrementMode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return true;
}

//     /////////////////////    DISPLAY CONTROL     /////////////////////     //

bool_t Tm1637::setDisplayContrast(const Contrast contrastLevel_p)
{
    // Mark passage for debugging purpose
    debugMark("Tm1637::setDisplayContrast(const Contrast)", Debug::CodeIndex::TM1637_MODULE);

    // Local variables
    uint8_t data = 0;

    // CHECK FOR ERROR - peripheral not initialized
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }

    // Prepare command
    data = (uint8_t)Command::DISPLAY_CONTROL;
    setMaskOffset(data,
            ((uint8_t)(this->_showDisplay) & (uint8_t)(BitMask::DISPLAY_CONTROL_SHOW)),
            (uint8_t)(BitPos::DISPLAY_CONTROL_SHOW));
    setMaskOffset(data,
            ((uint8_t)(contrastLevel_p) & (uint8_t)(BitMask::DISPLAY_CONTROL_CONTRAST)),
            (uint8_t)(BitPos::DISPLAY_CONTROL_CONTRAST));

    // Send command
    this->_sendStart();
    this->_writeByte(data);
    if(!this->_readAck()) {
        // Returns error
        this->_lastError = Error::COMMUNICATION_FAILED;
        debugMessage(Error::COMMUNICATION_FAILED, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }
    this->_sendStop();

    // Update data members
    this->_contrastLevel                = contrastLevel_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return true;
}

bool_t Tm1637::showDisplay(cbool_t showDisplay_p)
{
    // Mark passage for debugging purpose
    debugMark("Tm1637::showDisplay(cbool_t)", Debug::CodeIndex::TM1637_MODULE);

    // Local variables
    uint8_t data = 0;

    // CHECK FOR ERROR - peripheral not initialized
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }

    // Prepare command
    data = (uint8_t)Command::DISPLAY_CONTROL;
    setMaskOffset(data,
            ((uint8_t)(showDisplay_p) & (uint8_t)(BitMask::DISPLAY_CONTROL_SHOW)),
            (uint8_t)(BitPos::DISPLAY_CONTROL_SHOW));
    setMaskOffset(data,
            ((uint8_t)(this->_contrastLevel) & (uint8_t)(BitMask::DISPLAY_CONTROL_CONTRAST)),
            (uint8_t)(BitPos::DISPLAY_CONTROL_CONTRAST));

    // Send command
    this->_sendStart();
    this->_writeByte(data);
    if(!this->_readAck()) {
        // Returns error
        this->_lastError = Error::COMMUNICATION_FAILED;
        debugMessage(Error::COMMUNICATION_FAILED, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }
    this->_sendStop();

    // Update data members
    this->_showDisplay                  = showDisplay_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return true;
}

bool_t Tm1637::writeDisplayData(cuint16_t displayValue_p, cuint8_t base_p)
{
    // Mark passage for debugging purpose
    debugMark("Tm1637::writeDisplayData(cuint16_t, cuint8_t)", Debug::CodeIndex::TM1637_MODULE);

    // Local variables
    uint8_t auxSegments[4] = {0, 0, 0, 0};
    uint8_t aux8 = 0;
    uint16_t aux16 = displayValue_p;
    cuint8_t displayIndex = 0;

    // CHECK FOR ERROR - peripheral not initialized
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }
    // CHECK FOR ERROR - base
    if((base_p < 2) || (base_p > 16)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_VALUE_INVALID;
        debugMessage(Error::ARGUMENT_VALUE_INVALID, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }

    // Extract digits
    for(uint8_t i = 0; i < 4; i++) {
        aux8 = (aux16 % base_p);
        aux16 /= (uint16_t)base_p;
        auxSegments[i] = segments[aux8];
    }

    // Prepare command
    aux8 = (uint8_t)Command::DISPLAY_ADDRESS;
    setMaskOffset(aux8,
            ((uint8_t)(displayIndex) & (uint8_t)(BitMask::DISPLAY_ADDRESS)),
            (uint8_t)(BitPos::DISPLAY_ADDRESS));

    // Writing data to display
    this->_sendStart();
    this->_writeByte(aux8);
    this->_readAck();
    for(uint8_t i = 0; i < 4; i++) {
        this->_writeByte(auxSegments[3 - i]);
        this->_readAck();
    }
    this->_sendStop();

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return true;
}

bool_t Tm1637::writeDisplayData(cuint8_t segments_p, cuint8_t index_p, cbool_t showDot_p)
{
    // Mark passage for debugging purpose
    debugMark("Tm1637::writeDisplayData(cuint8_t, cuint8_t, cbool_t)", Debug::CodeIndex::TM1637_MODULE);

    // Local variables
    uint8_t aux8 = 0;
    uint8_t auxSegments = segments_p;

    // CHECK FOR ERROR - peripheral not initialized
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }
    // CHECK FOR ERROR - base
    if((index_p > 4) || (index_p == 0)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_VALUE_INVALID;
        debugMessage(Error::ARGUMENT_VALUE_INVALID, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }

    // Prepare command
    aux8 = (uint8_t)Command::DISPLAY_ADDRESS;
    setMaskOffset(aux8,
            ((uint8_t)(index_p - 1) & (uint8_t)(BitMask::DISPLAY_ADDRESS)),
            (uint8_t)(BitPos::DISPLAY_ADDRESS));

    // Check dot
    if(showDot_p) {
        auxSegments |= 0x80;
    }

    // Writing data to display
    this->_sendStart();
    this->_writeByte(aux8);
    this->_readAck();
    this->_writeByte(auxSegments);
    this->_readAck();
    this->_sendStop();

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return true;
}

//     /////////////////////     KEYPAD CONTROL     /////////////////////     //

bool_t Tm1637::readKeypadData(uint8_t *keyPressed_p)
{
    // FIXME: Implement this function
    return true;
}

// =============================================================================
// Class own methods - Private
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

bool_t Tm1637::_isInitialized(void)
{
    // Mark passage for debugging purpose
    debugMark("Tm1637::_isInitialized(void)", Debug::CodeIndex::TM1637_MODULE);

    // Checks if device is initialized
    if(!this->_initialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::TM1637_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::TM1637_MODULE);
    return true;
}

//     /////////////////     COMMUNICATION PROTOCOL     /////////////////     //

void Tm1637::_sendStart(void)
{
    // Pull lines up
    this->_clkPin->set();
    this->_dioPin->setMode(GpioPin::Mode::INPUT_FLOATING);
    delayUs(clockPeriod);

    // Send start condition
    this->_dioPin->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    delayUs(clockPeriod / 2);
    this->_clkPin->clr();

    return;
}

void Tm1637::_sendStop(void)
{
    // Assuring the DIO line is driven LOW
    this->_dioPin->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    // Send stop condition
    delayUs(clockPeriod / 2);
    this->_clkPin->set();
    delayUs(clockPeriod / 2);
    this->_dioPin->setMode(GpioPin::Mode::INPUT_FLOATING);
    delayUs(clockPeriod);

    return;
}

void Tm1637::_writeByte(cuint8_t byteToWrite_p)
{
    for(uint8_t i = 0; i < 8; i++) {
        if(isBitSet(byteToWrite_p, i)) {
            this->_dioPin->setMode(GpioPin::Mode::INPUT_FLOATING);
        } else {
            this->_dioPin->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
        }
        delayUs(clockPeriod / 2);
        this->_clkPin->set();
        delayUs(clockPeriod / 2);
        this->_clkPin->clr();
    }

    return;
}

void Tm1637::_readByte(uint8_t *byteRead_p)
{
    // FIXME: Implement this function
    return;
}

bool_t Tm1637::_readAck(void)
{
    // Releases DIO line
    this->_dioPin->setMode(GpioPin::Mode::INPUT_FLOATING);
    // Reads ACK bit
    delayUs(clockPeriod / 2);
    this->_clkPin->set();
    this->_dioPin->read();
    delayUs(clockPeriod / 2);
    this->_clkPin->clr();

    return true;
}

// =============================================================================
// Class own methods - Protected
// =============================================================================

// NONE

// =============================================================================
// END OF FILE
// =============================================================================
