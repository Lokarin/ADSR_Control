//!
//! \file           funsapeLibPcint1.cpp
//! \brief          External Interrupt PCINT1 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        External Interrupt PCINT1 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibPcint1.hpp"
#if !defined(__FUNSAPE_LIB_PCINT1_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_PCINT1_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

#if defined(_FUNSAPE_PLATFORM_AVR)

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define DEBUG_PCINT1                    0x2BFF

cuint8_t constInterruptPinOffset        = PCINT8;   //!< Interrupt pin offset
cuint8_t constInterruptPinsMask         = 0x7F;     //!< Interrupt pins bit mask

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

Pcint1 pcint1;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Pcint1::Pcint1()
{
    // Mark passage for debugging purpose
    debugMark("Pcint1::Pcint1(void)", DEBUG_PCINT1);

    // Reset data members
    this->_enabledPins                  = (Pcint1::Pin)0;
    this->_isInitialized                = false;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    debugMessage(Error::NONE, DEBUG_PCINT1);
    return;
}

Pcint1::~Pcint1()
{
    // Returns successfully
    debugMessage(Error::NONE, DEBUG_PCINT1);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONFIGURATION     ////////////////////     //
bool_t Pcint1::init(Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark("Pcint1::init(Pin)", DEBUG_PCINT1);

    // Local variables
    uint8_t auxPcmsk1 = PCMSK1;

    // Configure mode
    clrMaskOffset(auxPcmsk1, constInterruptPinsMask, constInterruptPinOffset);
    setMaskOffset(auxPcmsk1, ((uint8_t)enablePins_p), constInterruptPinOffset);

    // Update registers
    PCMSK1          = auxPcmsk1;

    // Update class members
    this->_enabledPins      = enablePins_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_PCINT1);
    return true;
}

bool_t Pcint1::enablePins(Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark("Pcint1::enablePins(Pin)", DEBUG_PCINT1);

    // Local variables
    uint8_t auxPcmsk1 = PCMSK1;
    uint8_t aux8 = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk1, constInterruptPinsMask, constInterruptPinOffset);
    setMask(aux8, (uint8_t)enablePins_p);
    setMaskOffset(auxPcmsk1, aux8, constInterruptPinOffset);

    // Update registers
    PCMSK1          = auxPcmsk1;

    // Update class members
    this->_enabledPins      = (Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_PCINT1);
    return true;
}

bool_t Pcint1::disablePins(Pin disablePins_p)
{
    // Mark passage for debugging purpose
    debugMark("Pcint1::disablePins(Pin)", DEBUG_PCINT1);

    // Local variables
    uint8_t auxPcmsk1 = PCMSK1;
    uint8_t aux8 = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk1, constInterruptPinsMask, constInterruptPinOffset);
    clrMask(aux8, (uint8_t)disablePins_p);
    setMaskOffset(auxPcmsk1, aux8, constInterruptPinOffset);

    // Update registers
    PCMSK1          = auxPcmsk1;

    // Update class members
    this->_enabledPins      = (Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_PCINT1);
    return true;
}

//     /////////////     MASTER CONTROL AND STATUS     //////////////     //
Error Pcint1::getLastError(void)
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

weakened void pcint1InterruptCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

//!
//! \brief          PCINT1 interrupt service routine
//! \details        PCINT1 interrupt service routine.
//!
ISR(PCINT1_vect)
{
    pcint1InterruptCallback();
}

#endif // defined(_FUNSAPE_PLATFORM_AVR)

// =============================================================================
// END OF FILE
// =============================================================================
