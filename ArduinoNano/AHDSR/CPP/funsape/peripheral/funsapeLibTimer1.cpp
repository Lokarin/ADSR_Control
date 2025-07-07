//!
//! \file           funsapeLibTimer1.cpp
//! \brief          TIMER1 peripheral control for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        TIMER1 peripheral control for the FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibTimer1.hpp"
#if !defined(__FUNSAPE_LIB_TIMER1_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_TIMER1_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

#if defined(_FUNSAPE_PLATFORM_AVR)

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define DEBUG_TIMER1                    0x3FFF

cuint8_t constOutputModeAOffset         = COM1A0;       //!< Output A bit position offset
cuint8_t constOutputModeAMask           = 0x03;         //!< Output A bit mask
cuint8_t constOutputModeBOffset         = COM1B0;       //!< Output B bit position offset
cuint8_t constOutputModeBMask           = 0x03;         //!< Output B bit mask
cuint8_t constModeOffsetPart1           = WGM10;        //!< Operation mode part 1 bit position offset
cuint8_t constModeMaskPart1             = 0x03;         //!< Operation mode part 1 bit mask
cuint8_t constModeOffsetPart2           = WGM12;        //!< Operation mode part 2 bit position offset
cuint8_t constModeMaskPart2             = 0x03;         //!< Operation mode part 2 bit mask
cuint8_t constClockSourceOffset         = CS10;         //!< Clock source bit position offset
cuint8_t constClockSourceMask           = 0x07;         //!< Clock source bit mask

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

Timer1 timer1;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Timer1::Timer1()
{
    // Mark passage for debugging purpose
    debugMark("Timer1::Timer1(void)", DEBUG_TIMER1);

    // Reset data members
    this->_clockSource                  = ClockSource::DISABLED;
    this->_mode                         = Mode::NORMAL;
    this->_isInitialized                = false;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER1);
    return;
}

Timer1::~Timer1()
{
    // Returns successfully
    debugMessage(Error::NONE, DEBUG_TIMER1);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONFIGURATION     ////////////////////     //
bool_t Timer1::init(const Mode mode_p, const ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark("Timer1::init(const Mode, const ClockSource)", DEBUG_TIMER1);

    // Local variables
    uint8_t auxTccr1A = TCCR1A;
    uint8_t auxTccr1B = TCCR1B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr1A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr1B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr1A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr1B, (aux8 >> 2), constModeOffsetPart2);
    // Configure clock source
    clrMaskOffset(auxTccr1B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr1B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR1A          = auxTccr1A;
    TCCR1B          = auxTccr1B;

    // Update class members
    this->_mode             = mode_p;
    this->_clockSource      = clockSource_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER1);
    return true;
}

bool_t Timer1::setMode(const Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark("Timer1::setMode(const Mode)", DEBUG_TIMER1);

    // Local variables
    uint8_t auxTccr1A = TCCR1A;
    uint8_t auxTccr1B = TCCR1B;
    uint8_t aux8 = 0;

    // Configure mode
    aux8 = (uint8_t)mode_p;
    clrMaskOffset(auxTccr1A, constModeMaskPart1, constModeOffsetPart1);
    clrMaskOffset(auxTccr1B, constModeMaskPart2, constModeOffsetPart2);
    setMaskOffset(auxTccr1A, (aux8 & 0x03), constModeOffsetPart1);
    setMaskOffset(auxTccr1B, (aux8 >> 2), constModeOffsetPart2);

    // Update registers
    TCCR1A          = auxTccr1A;
    TCCR1B          = auxTccr1B;

    // Update class members
    this->_mode             = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER1);
    return true;
}

bool_t Timer1::setClockSource(const ClockSource clockSource_p)
{
    // Mark passage for debugging purpose
    debugMark("Timer1::setClockSource(const ClockSource)", DEBUG_TIMER1);

    // Local variables
    uint8_t auxTccr1B = TCCR1B;

    // Configure clock source
    clrMaskOffset(auxTccr1B, constClockSourceMask, constClockSourceOffset);
    setMaskOffset(auxTccr1B, ((uint8_t)clockSource_p), constClockSourceOffset);

    // Update registers
    TCCR1B          = auxTccr1B;

    // Update class members
    this->_clockSource      = clockSource_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER1);
    return true;
}

bool_t Timer1::setOutputMode(const OutputMode compA_p, const OutputMode compB_p)
{
    // Mark passage for debugging purpose
    debugMark("Timer1::setOutputMode(const OutputMode, const OutputMode)", DEBUG_TIMER1);

    // Local variables
    uint8_t auxTccr1A = TCCR1A;

    // Configure outputs
    clrMaskOffset(auxTccr1A, constOutputModeAMask, constOutputModeAOffset);
    setMaskOffset(auxTccr1A, ((uint8_t)compA_p), constOutputModeAOffset);
    clrMaskOffset(auxTccr1A, constOutputModeBMask, constOutputModeBOffset);
    setMaskOffset(auxTccr1A, ((uint8_t)compB_p), constOutputModeBOffset);

    // Update registers
    TCCR1A          = auxTccr1A;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER1);
    return true;
}

bool_t Timer1::setInputCaptureMode(const Edge edgeSelection_p, cbool_t noiseCanceler_p)
{
    // Mark passage for debugging purpose
    debugMark("Timer1::setInputCaptureMode(const Edge, cbool_t)", DEBUG_TIMER1);

    // Local variables
    uint8_t auxTccr1B = TCCR1B;

    // Configure Input Capture
    if(noiseCanceler_p) {
        setBit(auxTccr1B, ICNC1);
    } else {
        clrBit(auxTccr1B, ICNC1);
    }
    if(edgeSelection_p == Edge::RISING) {
        setBit(auxTccr1B, ICES1);
    } else {
        clrBit(auxTccr1B, ICES1);
    }

    // Update registers
    TCCR1B          = auxTccr1B;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_TIMER1);
    return true;
}

//     /////////////     MASTER CONTROL AND STATUS     //////////////     //
Error Timer1::getLastError(void)
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

weakened void timer1CompareACallback(void)
{
    return;
}

weakened void timer1CompareBCallback(void)
{
    return;
}

weakened void timer1InputCaptureCallback(void)
{
    return;
}

weakened void timer1OverflowCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

//!
//! \brief          TIMER1 Compare B Match interrupt service routine
//! \details        TIMER1 Compare B Match interrupt service routine.
//!
ISR(TIMER1_COMPA_vect)
{
    timer1CompareACallback();
}

//!
//! \brief          TIMER1 Compare B Match interrupt service routine
//! \details        TIMER1 Compare B Match interrupt service routine.
//!
ISR(TIMER1_COMPB_vect)
{
    timer1CompareBCallback();
}

//!
//! \brief          TIMER1 Input Capture interrupt service routine
//! \details        TIMER1 Input Capture interrupt service routine.
//!
ISR(TIMER1_CAPT_vect)
{
    timer1InputCaptureCallback();
}

//!
//! \brief          TIMER1 Overflow interrupt service routine
//! \details        TIMER1 Overflow interrupt service routine.
//!
ISR(TIMER1_OVF_vect)
{
    timer1OverflowCallback();
}

#endif // defined(_FUNSAPE_PLATFORM_AVR)

// =============================================================================
// END OF FILE
// =============================================================================
