//!
//! \file           funsapeLibTimer0.cpp
//! \brief          TIMER0 peripheral control for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        TIMER0 peripheral control for the FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibTimer0.hpp"
#if !defined(__FUNSAPE_LIB_TIMER0_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_TIMER0_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

#if defined(_FUNSAPE_PLATFORM_AVR)

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define DEBUG_TIMER0                    0x2FFF

cuint8_t constOutputModeAOffset         = COM0A0;   //!< Output A bit position offset
cuint8_t constOutputModeAMask           = 0x03;     //!< Output A bit mask
cuint8_t constOutputModeBOffset         = COM0B0;   //!< Output B bit position offset
cuint8_t constOutputModeBMask           = 0x03;     //!< Output B bit mask
cuint8_t constModeOffsetPart1           = WGM00;    //!< Operation mode part 1 bit position offset
cuint8_t constModeMaskPart1             = 0x03;     //!< Operation mode part 1 bit mask
cuint8_t constModeOffsetPart2           = WGM02;    //!< Operation mode part 2 bit position offset
cuint8_t constModeMaskPart2             = 0x01;     //!< Operation mode part 2 bit mask
cuint8_t constClockSourceOffset         = CS00;     //!< Clock source bit position offset
cuint8_t constClockSourceMask           = 0x07;     //!< Clock source bit mask

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

Timer0 timer0;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Timer0::Timer0()
{
    // Mark passage for debugging purpose
    debugMark("Timer0::Timer0(void)", DEBUG_TIMER0);

    // Reset data members
    this->_clockSource                  = ClockSource::DISABLED;
    this->_mode                         = Mode::NORMAL;
    this->_isInitialized                = false;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER0);
    return;
}

Timer0::~Timer0()
{
    // Returns successfully
    debugMessage(Error::NONE, DEBUG_TIMER0);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONFIGURATION     ////////////////////     //
bool_t Timer0::init(Mode mode_p, ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark("Timer0::init(Mode, ClockSource)", DEBUG_TIMER0);

    // Local variables
    uint8_t auxTccr0A = TCCR0A;
    uint8_t auxTccr0B = TCCR0B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr0A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr0B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr0A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr0B, (aux8 >> 2), constModeOffsetPart2);
    // Configure clock source
    clrMaskOffset(auxTccr0B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr0B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR0A          = auxTccr0A;
    TCCR0B          = auxTccr0B;

    // Update class members
    this->_mode             = mode_p;
    this->_clockSource      = clockSource_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER0);
    return true;
}

bool_t Timer0::setMode(Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark("Timer0::setMode(Mode)", DEBUG_TIMER0);

    // Local variables
    uint8_t auxTccr0A = TCCR0A;
    uint8_t auxTccr0B = TCCR0B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr0A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr0B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr0A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr0B, (aux8 >> 2), constModeOffsetPart2);

    // Update registers
    TCCR0A          = auxTccr0A;
    TCCR0B          = auxTccr0B;

    // Update class members
    this->_mode     = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER0);
    return true;
}

bool_t Timer0::setClockSource(ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark("Timer0::setClockSource(ClockSource)", DEBUG_TIMER0);

    // Local variables
    uint8_t auxTccr0B = TCCR0B;

    // Configure clock source
    clrMaskOffset(auxTccr0B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr0B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR0B          = auxTccr0B;

    // Update class members
    this->_clockSource      = clockSource_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER0);
    return true;
}

bool_t Timer0::setOutputMode(OutputMode compA_p, OutputMode compB_p)
{
    // Mark passage for debugging purpose
    debugMark("Timer0::setOutputMode(OutputMode, OutputMode)", DEBUG_TIMER0);

    // Local variables
    uint8_t auxTccr0A = TCCR0A;

    // Configure outputs
    clrMaskOffset(auxTccr0A, constOutputModeAMask, constOutputModeAOffset);
    setMaskOffset(auxTccr0A, ((uint8_t)compA_p), constOutputModeAOffset);
    clrMaskOffset(auxTccr0A, constOutputModeBMask, constOutputModeBOffset);
    setMaskOffset(auxTccr0A, ((uint8_t)compB_p), constOutputModeBOffset);

    // Update registers
    TCCR0A          = auxTccr0A;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER0);
    return true;
}

//     /////////////     MASTER CONTROL AND STATUS     //////////////     //
Error Timer0::getLastError(void)
{
    // Returns last error
    return this->_lastError;
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

weakened void timer0CompareACallback(void)
{
    return;
}

weakened void timer0CompareBCallback(void)
{
    return;
}

weakened void timer0OverflowCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

//!
//! \brief          TIMER0 Compare A Match interrupt service routine
//! \details        TIMER0 Compare A Match interrupt service routine.
//!
ISR(TIMER0_COMPA_vect)
{
    timer0CompareACallback();
}

//!
//! \brief          TIMER0 Compare B Match interrupt service routine
//! \details        TIMER0 Compare B Match interrupt service routine.
//!
ISR(TIMER0_COMPB_vect)
{
    timer0CompareBCallback();
}

//!
//! \brief          TIMER0 Overflow interrupt service routine
//! \details        TIMER0 Overflow interrupt service routine.
//!
ISR(TIMER0_OVF_vect)
{
    timer0OverflowCallback();
}

#endif // defined(_FUNSAPE_PLATFORM_AVR)

// =============================================================================
// END OF FILE
// =============================================================================
