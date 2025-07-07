//!
//! \file           funsapeLibTimer2.cpp
//! \brief          TIMER2 peripheral control for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        TIMER2 peripheral control for the FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibTimer2.hpp"
#if !defined(__FUNSAPE_LIB_TIMER2_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_TIMER2_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

#if defined(_FUNSAPE_PLATFORM_AVR)

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define DEBUG_TIMER2                    0x1FFF

cuint8_t constOutputModeAOffset         = COM2A0;   //!< Output A bit position offset
cuint8_t constOutputModeAMask           = 0x03;     //!< Output A bit mask
cuint8_t constOutputModeBOffset         = COM2B0;   //!< Output B bit position offset
cuint8_t constOutputModeBMask           = 0x03;     //!< Output B bit mask
cuint8_t constModeOffsetPart1           = WGM20;    //!< Operation mode part 1 bit position offset
cuint8_t constModeMaskPart1             = 0x03;     //!< Operation mode part 1 bit mask
cuint8_t constModeOffsetPart2           = WGM22;    //!< Operation mode part 2 bit position offset
cuint8_t constModeMaskPart2             = 0x01;     //!< Operation mode part 2 bit mask
cuint8_t constClockSourceOffset         = CS20;     //!< Clock source bit position offset
cuint8_t constClockSourceMask           = 0x07;     //!< Clock source bit mask

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

Timer2 timer2;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Timer2::Timer2()
{
    // Mark passage for debugging purpose
    debugMark("Timer2::Timer2(void)", DEBUG_TIMER2);

    // Reset data members
    this->_clockSource                  = ClockSource::DISABLED;
    this->_mode                         = Mode::NORMAL;
    this->_isInitialized                = false;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER2);
    return;
}

Timer2::~Timer2()
{
    // Returns successfully
    debugMessage(Error::NONE, DEBUG_TIMER2);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONFIGURATION     ////////////////////     //
bool_t Timer2::init(Mode mode_p, ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark("Timer2::init(Mode, ClockSource)", DEBUG_TIMER2);

    // Local variables
    uint8_t auxTccr2A = TCCR2A;
    uint8_t auxTccr2B = TCCR2B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr2A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr2B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr2A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr2B, (aux8 >> 2), constModeOffsetPart2);
    // Configure clock source
    clrMaskOffset(auxTccr2B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr2B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR2A          = auxTccr2A;
    TCCR2B          = auxTccr2B;

    // Update class members
    this->_mode             = mode_p;
    this->_clockSource      = clockSource_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER2);
    return true;
}

bool_t Timer2::setMode(Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark("Timer2::setMode(Mode)", DEBUG_TIMER2);

    // Local variables
    uint8_t auxTccr2A = TCCR2A;
    uint8_t auxTccr2B = TCCR2B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr2A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr2B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr2A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr2B, (aux8 >> 2), constModeOffsetPart2);

    // Update registers
    TCCR2A          = auxTccr2A;
    TCCR2B          = auxTccr2B;

    // Update class members
    this->_mode             = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER2);
    return true;
}

bool_t Timer2::setClockSource(ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark("Timer2::setClockSource(ClockSource)", DEBUG_TIMER2);

    // Local variables
    uint8_t auxTccr2B = TCCR2B;

    // Configure clock source
    clrMaskOffset(auxTccr2B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr2B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR2B          = auxTccr2B;

    // Update class members
    this->_clockSource      = clockSource_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER2);
    return true;
}

bool_t Timer2::setOutputMode(OutputMode compA_p, OutputMode compB_p)
{
    // Mark passage for debugging purpose
    debugMark("Timer2::setOutputMode(OutputMode, OutputMode)", DEBUG_TIMER2);

    // Local variables
    uint8_t auxTccr2A = TCCR2A;

    // Configure outputs
    clrMaskOffset(auxTccr2A, constOutputModeAMask, constOutputModeAOffset);
    setMaskOffset(auxTccr2A, ((uint8_t)compA_p), constOutputModeAOffset);
    clrMaskOffset(auxTccr2A, constOutputModeBMask, constOutputModeBOffset);
    setMaskOffset(auxTccr2A, ((uint8_t)compB_p), constOutputModeBOffset);

    // Update registers
    TCCR2A          = auxTccr2A;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER2);
    return true;
}

//     /////////////     MASTER CONTROL AND STATUS     //////////////     //
Error Timer2::getLastError(void)
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

weakened void timer2CompareACallback(void)
{
    return;
}

weakened void timer2CompareBCallback(void)
{
    return;
}

weakened void timer2OverflowCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

//!
//! \brief          TIMER2 Compare A Match interrupt service routine
//! \details        TIMER2 Compare A Match interrupt service routine.
//!
ISR(TIMER2_COMPA_vect)
{
    timer2CompareACallback();
}

//!
//! \brief          TIMER2 Compare B Match interrupt service routine
//! \details        TIMER2 Compare B Match interrupt service routine.
//!
ISR(TIMER2_COMPB_vect)
{
    timer2CompareBCallback();
}

//!
//! \brief          TIMER2 Overflow interrupt service routine
//! \details        TIMER2 Overflow interrupt service routine.
//!
ISR(TIMER2_OVF_vect)
{
    timer2OverflowCallback();
}

#endif // defined(_FUNSAPE_PLATFORM_AVR)

// =============================================================================
// END OF FILE
// =============================================================================
