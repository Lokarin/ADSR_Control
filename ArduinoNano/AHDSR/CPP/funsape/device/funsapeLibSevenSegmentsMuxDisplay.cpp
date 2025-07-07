//!
//! \file           funsapeLibSevenSegmentsMuxDisplay.cpp
//! \brief          Seven Segments Multiplexed Display module interface for the
//!                     FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-07-10
//! \version        24.07
//! \copyright      license
//! \details        Seven segments multiplexed display controller with support
//!                     to variable number of digits (2 to 8). The library
//!                     supports both common anode and common cathode displays,
//!                     decimal point, and the special characters defined in
//!                     sevenSegmentsDisplay.hpp
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibSevenSegmentsMuxDisplay.hpp"
#if !defined(__FUNSAPE_LIB_SEVEN_SEGMENTS_MUX_DISPLAY_HPP)
#   error "Header file is corrupted!"
#elif __FUNSAPE_LIB_SEVEN_SEGMENTS_MUX_DISPLAY_HPP != 2407
#   error "Version mismatch between source and header files!"
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
// File exclusive - Global variables
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

SevenSegmentsMuxDisplay::SevenSegmentsMuxDisplay(void)
{
    // Mark passage for debugging purpose
    debugMark("SevenSegmentsMuxDisplay::SevenSegmentsMuxDisplay(void)",
            Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);

    // Reset data members
    this->_controlGpioBus               = nullptr;
    this->_dataGpioBus                  = nullptr;
    this->_digitMax                     = 0;
    this->_digitIndex                   = 0;
    for(uint8_t i = 0; i < 8; i++) {
        this->_digitValue[i]            = (uint8_t)SevenSegmentsCode::OFF;
        this->_digitPoint[i]            = false;
    }
    this->_displayType                  =  SevenSegmentsDisplayType::COMMON_ANODE;
    this->_isInitialized                = false;
    this->_isPortsSet                   = false;
    this->_controlActiveLevel           = LogicLevel::HIGH;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);
    return;
}

SevenSegmentsMuxDisplay::~SevenSegmentsMuxDisplay(void)
{
    // Mark passage for debugging purpose
    debugMark("SevenSegmentsMuxDisplay::~SevenSegmentsMuxDisplay(void)",
            Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

bool_t SevenSegmentsMuxDisplay::init(Digits numberOfDigits_p, SevenSegmentsDisplayType displayType_p)
{
    // Mark passage for debugging purpose
    debugMark("SevenSegmentsMuxDisplay::init(SevenSegmentsMuxDisplay::Digits, SevenSegmentsDisplayType)",
            Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);

    // Resets data members
    this->_digitMax             = 0;
    this->_digitIndex           = 0;
    this->_isInitialized        = false;

    // Check for errors
    if(!this->_isPortsSet) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_NOT_SET;
        debugMessage(Error::GPIO_PORT_NOT_SET, Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);
        return false;
    }
    if(((uint8_t)numberOfDigits_p < 2) || ((uint8_t)numberOfDigits_p > 8)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_VALUE_INVALID;
        debugMessage(Error::ARGUMENT_VALUE_INVALID, Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);
        return false;
    }
    if(this->_controlGpioBus->getBusSize() != (uint8_t)numberOfDigits_p) {
        // Returns error
        this->_lastError = Error::GPIO_BUS_SIZE_INVALID;
        debugMessage(Error::GPIO_BUS_SIZE_INVALID, Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);
        return false;
    }

    // I/O initialization
    if(this->_displayType == SevenSegmentsDisplayType::COMMON_ANODE) {
        this->_dataGpioBus->set();
    } else {
        this->_dataGpioBus->clr();
    }
    this->_dataGpioBus->setMode(GpioBus::Mode::OUTPUT_PUSH_PULL);
    if(this->_controlActiveLevel == LogicLevel::HIGH) {
        this->_controlGpioBus->clr();
    } else {
        this->_controlGpioBus->set();
    }
    this->_controlGpioBus->setMode(GpioBus::Mode::OUTPUT_PUSH_PULL);

    // Updates data members
    this->_displayType                  = displayType_p;
    this->_digitMax                     = (uint8_t)numberOfDigits_p - 1;
    this->_isInitialized                = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);
    return true;
}

bool_t SevenSegmentsMuxDisplay::setPorts(GpioBus *dataPort_p, GpioBus *controlPort_p, LogicLevel displayTurnOnLevel_p)
{
    // Mark passage for debugging purpose
    debugMark("SevenSegmentsMuxDisplay::setPorts(GpioBus *, GpioBus *, LogicLevel)",
            Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);

    // Resets data members
    this->_controlGpioBus               = nullptr;
    this->_dataGpioBus                  = nullptr;
    this->_isPortsSet                   = false;
    this->_digitIndex                   = 0;

    // Check for errors
    if(!isPointerValid(dataPort_p)) {
        // Returns error
        debugMessage(Error::GPIO_DATA_PORT_INVALID, Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);
        this->_lastError = Error::GPIO_DATA_PORT_INVALID;
        return false;
    }
    if(dataPort_p->getBusSize() != 8) {
        // Returns error
        debugMessage(Error::GPIO_BUS_SIZE_INVALID, Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);
        this->_lastError = Error::GPIO_BUS_SIZE_INVALID;
        return false;
    }
    if(!isPointerValid(controlPort_p)) {
        // Returns error
        debugMessage(Error::GPIO_CONTROL_PORT_INVALID, Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);
        this->_lastError = Error::GPIO_CONTROL_PORT_INVALID;
        return false;
    }

    // Updates data members
    this->_controlGpioBus               = controlPort_p;
    this->_dataGpioBus                  = dataPort_p;
    this->_controlActiveLevel           = displayTurnOnLevel_p;
    this->_isPortsSet                   = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);
    return true;
}

bool_t SevenSegmentsMuxDisplay::showNextDigit(void)
{
    // Mark passage for debugging purpose
    debugMark("SevenSegmentsMuxDisplay::showNextDigit(void)", Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);

    // Checks for errors
    if(!this->_isInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);
        return false;
    }

    // Turns current digit OFF
    if(this->_displayType == SevenSegmentsDisplayType::COMMON_ANODE) {
        this->_dataGpioBus->set();
    } else {
        this->_dataGpioBus->clr();
    }
    // Turns all displays off
    if(this->_controlActiveLevel == LogicLevel::HIGH) {
        this->_controlGpioBus->clr();
    } else {
        this->_controlGpioBus->set();
    }

    // Evaluates next digit
    this->_digitIndex = (this->_digitIndex == this->_digitMax) ? 0 : (this->_digitIndex + 1);

    // Send data to port
    uint8_t aux8 = convertToSevenSegments(this->_digitValue[this->_digitIndex], this->_digitPoint[this->_digitIndex],
                    this->_displayType);
    this->_dataGpioBus->write(aux8);
    // Turns digit on
    if(this->_controlActiveLevel == LogicLevel::HIGH) {
        this->_controlGpioBus->set(this->_digitIndex);
    } else {
        this->_controlGpioBus->clr(this->_digitIndex);
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);
    return true;
}

bool_t SevenSegmentsMuxDisplay::updateDigitValues(cuint8_t *digitValues_p, cbool_t *digitPoints_p)
{
    // Mark passage for debugging purpose
    debugMark("SevenSegmentsMuxDisplay::updateDigitValues(cuint8_t *, cbool_t *)",
            Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);

    // Check for errors
    if(!isPointerValid(digitValues_p)) {
        // Returns error
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        return false;
    }

    // Updates data members
    for(uint8_t i = 0; i < (this->_digitMax + 1); i++) {
        this->_digitValue[i] = digitValues_p[i];
        if(isPointerValid(digitPoints_p)) {
            this->_digitPoint[i] = digitPoints_p[i];
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::SEVEN_SEGMENTS_MUX_DISPLAY_MODULE);
    return true;
}

// =============================================================================
// Class private methods
// =============================================================================

// NONE

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

// NONE

// =============================================================================
// Interrupt handlers
// =============================================================================

// NONE

// =============================================================================
// END OF FILE
// =============================================================================
