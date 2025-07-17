//!
//! \file           funsapeLibPcint0.cpp
//! \brief          External Interrupt PCINT0 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        External Interrupt PCINT0 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibPcint0.hpp"
#if !defined(__FUNSAPE_LIB_PCINT0_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_PCINT0_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

#if defined(_FUNSAPE_PLATFORM_AVR)

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define DEBUG_PCINT0                    0x2AFF

cuint8_t constInterruptPinOffset        = PCINT0;   //!< Interrupt pin offset
cuint8_t constInterruptPinsMask         = 0xFF;     //!< Interrupt pins bit mask

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

Pcint0 pcint0;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Pcint0::Pcint0()
{
    // Mark passage for debugging purpose
    debugMark("Pcint0::Pcint0(void)", DEBUG_PCINT0);

    // Reset data members
    this->_enabledPins                  = (Pcint0::Pin)0;
    this->_isInitialized                = false;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    debugMessage(Error::NONE, DEBUG_PCINT0);
    return;
}

Pcint0::~Pcint0()
{
    // Returns successfully
    debugMessage(Error::NONE, DEBUG_PCINT0);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONFIGURATION     ////////////////////     //
bool_t Pcint0::init(Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark("Pcint0::init(Pin)", DEBUG_PCINT0);

    // Local variables
    uint8_t auxPcmsk0 = PCMSK0;

    // Configure mode
    clrMaskOffset(auxPcmsk0, constInterruptPinsMask, constInterruptPinOffset);
    setMaskOffset(auxPcmsk0, ((uint8_t)enablePins_p), constInterruptPinOffset);

    // Update registers
    PCMSK0          = auxPcmsk0;

    // Update class members
    this->_enabledPins      = enablePins_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_PCINT0);
    return true;
}

bool_t Pcint0::enablePins(Pin enablePins_p)
{
    // Mark passage for debugging purpose
    debugMark("Pcint0::enablePins(Pin)", DEBUG_PCINT0);

    // Local variables
    uint8_t auxPcmsk0 = PCMSK0;
    uint8_t aux8 = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk0, constInterruptPinsMask, constInterruptPinOffset);
    setMask(aux8, (uint8_t)enablePins_p);
    setMaskOffset(auxPcmsk0, aux8, constInterruptPinOffset);

    // Update registers
    PCMSK0          = auxPcmsk0;

    // Update class members
    this->_enabledPins      = (Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_PCINT0);
    return true;
}

bool_t Pcint0::disablePins(Pin disablePins_p)
{
    // Mark passage for debugging purpose
    debugMark("Pcint0::disablePins(Pin)", DEBUG_PCINT0);

    // Local variables
    uint8_t auxPcmsk0 = PCMSK0;
    uint8_t aux8 = (uint8_t)this->_enabledPins;

    // Configure mode
    clrMaskOffset(auxPcmsk0, constInterruptPinsMask, constInterruptPinOffset);
    clrMask(aux8, (uint8_t)disablePins_p);
    setMaskOffset(auxPcmsk0, aux8, constInterruptPinOffset);

    // Update registers
    PCMSK0          = auxPcmsk0;

    // Update class members
    this->_enabledPins      = (Pin)aux8;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_PCINT0);
    return true;
}

//     /////////////     MASTER CONTROL AND STATUS     //////////////     //
Error Pcint0::getLastError(void)
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

weakened void pcint0InterruptCallback(void)
{
    return;
}

// =============================================================================
// Interrupt handlers
// =============================================================================

//!
//! \brief          PCINT0 interrupt service routine
//! \details        PCINT0 interrupt service routine.
//!
ISR(PCINT0_vect)
{
    pcint0InterruptCallback();
}

#endif // defined(_FUNSAPE_PLATFORM_AVR)

// =============================================================================
// END OF FILE
// =============================================================================
