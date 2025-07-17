//!
//! \file           funsapeLibDebug.hpp
//! \brief          Debug support to Funsape AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        This file provides extended debug support to all modules of
//!                     the Funsape AVR8 Library
//! \todo           This file is just a stub. Must implement the full file.
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_DEBUG_HPP
#define __FUNSAPE_LIB_DEBUG_HPP                 2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_DEBUG_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

#if defined(_FUNSAPE_PLATFORM_AVRXXXX)

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

// NONE

// =============================================================================
// New data types
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

// NONE

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Debug Class
// =============================================================================

class Debug
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:
    Debug(
            void
    );
    ~Debug(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     CONFIGURATION     ////////////////////     //
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
private:
    // NONE
}; // class Debug

// =============================================================================
// Inlined class functions
// =============================================================================

// NONE

// =============================================================================
// External global variables
// =============================================================================

//!
//! \brief          Brief description
//! \details        Long description
//!
extern Debug debug;

// =============================================================================
// Include guard (END)
// =============================================================================

#endif // defined(_FUNSAPE_PLATFORM_AVR)

class Debug
{
public:
    enum class CodeIndex {
        GPIO_MODULE                     = 1,
        GPIO_PIN_MODULE                 = 2,
        GPIO_BUS_MODULE                 = 3,
        TM1637_MODULE                   = 4,
        SEVEN_SEGMENTS_MUX_DISPLAY_MODULE   = 5,
        SN74595_MODULE                  = 6,
        Hd44780_MODULE                  = 7,
        STEPPER_MODULE                  = 8,
        KEYPAD_MODULE                   = 9,
        DS1307_MODULE                   = 10,
    };
};

#define debugMessage(errorCode, module)         {}
#define debugMark(string, module)               {}

#endif  // __FUNSAPE_LIB_DEBUG_HPP

// =============================================================================
// END OF FILE
// =============================================================================
