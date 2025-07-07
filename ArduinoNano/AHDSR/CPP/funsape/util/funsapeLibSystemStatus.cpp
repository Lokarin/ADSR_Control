//!
//! \file           funsapeLibSystemStatus.cpp
//! \brief          System function support to Funsape AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        This file provides support to system-wide features for all
//!                     modules of the Funsape AVR8 Library
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibSystemStatus.hpp"
#if !defined(__FUNSAPE_LIB_SYSTEM_STATUS_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_SYSTEM_STATUS_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

#if defined(_FUNSAPE_PLATFORM_AVR)

#include <util/atomic.h>

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

SystemStatus systemStatus;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

SystemStatus::SystemStatus(uint32_t mainClock_p)
{
    // Reset data members
    this->_initialized                  = false;
    this->_cpuClockValue                = 0;
    this->_sourceClockValue             = 0;
    this->_clockPrescaler               = ClockPrescaler::PRESCALER_1;
    this->_stopwatchMark                = 0;
    this->_stopwatchValue               = 0;
    this->_stopwatchHalted              = false;

    // Checks for errors
    if(mainClock_p == 0) {
        this->_lastError                = Error::CLOCK_SPEED_TOO_LOW;
        return;
    }

    // Updates data members
    this->_sourceClockValue             = mainClock_p;
    this->_cpuClockValue                = this->_sourceClockValue;
    this->_initialized                  = true;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return;
}

SystemStatus::~SystemStatus(void)
{
    // Returns successfully
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

bool_t SystemStatus::getCpuClock(uint32_t *cpuClockValue_p)
{
    // Checks for errors
    if(!isPointerValid(cpuClockValue_p)) {
        // Returns error
        this->_lastError                = Error::ARGUMENT_POINTER_NULL;
        return false;
    }
    // Updates value
    *cpuClockValue_p                    = this->_cpuClockValue;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return true;
}

uint32_t SystemStatus::getElapsedTime(bool_t setNewMark_p)
{
    // Local variables
    uint32_t start = this->_stopwatchMark;
    uint32_t current = this->_stopwatchValue;
    uint32_t elapsed = 0;

    // Checks for errors
    if(!this->_initialized) {
        // Returns error
        this->_lastError                = Error::NOT_INITIALIZED;
        return false;
    }

    // Evaluate time elapsed between marks
    elapsed = (current > start) ? (current - start) : (((0xFFFFFFFF - start)  + current) + 1);

    // Sets new stopwatch mark
    if(setNewMark_p) {
        this->_stopwatchMark            = current;
    }

    // Returns value
    return elapsed;
}

Error SystemStatus::getLastError(void)
{
    // Returns value
    return this->_lastError;
}

bool_t SystemStatus::setClockPrescaler(ClockPrescaler prescaler_p)
{
    // Local variables
    uint8_t aux8 = 0;
    uint16_t aux16 = 0;

    // Decodes prescaler
    switch(prescaler_p) {
    case ClockPrescaler::PRESCALER_1:
        aux8 = 0;
        aux16 = 1;
        break;
    case ClockPrescaler::PRESCALER_2:
        aux8 = 1;
        aux16 = 2;
        break;
    case ClockPrescaler::PRESCALER_4:
        aux8 = 2;
        aux16 = 4;
        break;
    case ClockPrescaler::PRESCALER_8:
        aux8 = 3;
        aux16 = 8;
        break;
    case ClockPrescaler::PRESCALER_32:
        aux8 = 4;
        aux16 = 32;
        break;
    case ClockPrescaler::PRESCALER_64:
        aux8 = 5;
        aux16 = 64;
        break;
    case ClockPrescaler::PRESCALER_128:
        aux8 = 6;
        aux16 = 128;
        break;
    case ClockPrescaler::PRESCALER_256:
        aux8 = 7;
        aux16 = 256;
        break;
    default:
        this->_lastError                = Error::CLOCK_PRESCALER_NOT_SUPPORTED;
        return false;
    }

    // Changes system clock prescaler
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        CLKPR = 0b10000000;
        CLKPR = aux8;
    }

    // Verifies if the change was successful
    doNop();
    if((CLKPR & 0x7F) != aux8) {
        this->_lastError                = Error::CLOCK_PRESCALER_CHANGE_FAILED;
        return false;
    }

    // Update member data
    this->_clockPrescaler               = prescaler_p;
    this->_cpuClockValue                = this->_sourceClockValue / aux16;

    // Return successfully
    this->_lastError                    = Error::NONE;
    return true;
}

// =============================================================================
// Class private methods
// =============================================================================

// NONE

// =============================================================================
// Class public methods
// =============================================================================

// NONE

#endif // defined(_FUNSAPE_PLATFORM_AVR)
