//!
//! \file           funsapeLibKeypad.hpp
//! \brief          Matrix keypad module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-07-10
//! \version        24.07
//! \copyright      license
//! \details        Matrix keypad controller with support to 4x3, 4x4 and 5x3
//!                     keypads and configurable debounce time
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_KEYPAD_HPP
#define __FUNSAPE_LIB_KEYPAD_HPP                        2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////    GLOBAL DEFINITIONS FILE     /////////////////     //

#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_KEYPAD_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_KEYPAD_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

#include "../peripheral/funsapeLibGpioBus.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibGpioBus.hpp) is corrupted!"
#elif __FUNSAPE_LIB_GPIO_BUS_HPP != __FUNSAPE_LIB_KEYPAD_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibGpioBus.hpp)!"
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

#include <stdarg.h>
#include <stdlib.h>

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

#include <avr/builtins.h>

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

cuint8_t constKeypadDefaultDebounceTime         = 1;    //!< Default debounce time

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
// Classes
// =============================================================================

//!
//! \brief          Keypad class
//! \details        Keypad class with support to 4x3, 4x4 and 5x3 keypads and
//!                     configurable debounce time.
//!
class Keypad
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     /////////////////////    KEYPAD TYPE     /////////////////////     //

    //!
    //! \brief      Keypad type
    //! \details    Keypad type enumeration.
    //!
    enum class Type : uint8_t {
        KEYPAD_4X4                      = 0,
        KEYPAD_4X3                      = 1,
        KEYPAD_5X3                      = 2
    };

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Keypad class constructor
    //! \details    Creates a Keypad object.
    //!
    Keypad(
            void
    );

    //!
    //! \brief      Keypad class destructor
    //! \details    Destroys a Keypad object.
    //!
    ~Keypad(
            void
    );

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Methods - Inherited methods ---------------------------------------------
public:

    // NONE

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Methods - Class own methods ---------------------------------------------
public:

    //     ////////////////////    CONFIGURATION     ////////////////////     //

    //!
    //! \brief      Keypad initialization
    //! \details    Initializes a Keypad object
    //! \param      debounceTime_p      Debounce time in milliseconds
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t init(
            cuint8_t debounceTime_p     = constKeypadDefaultDebounceTime
    );

    //!
    //! \brief      Set ports
    //! \details    This function sets the keypad columns and lines registers
    //!                 and bit positions.
    //! \param      gpioLines_p         Pointer to GpioBus of the Keypad lines
    //! \param      gpioColumns_p       Pointer to GpioBus of the Keypad columns
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t setPorts(
            const GpioBus *gpioLines_p,
            const GpioBus *gpioColumns_p
    );

    //!
    //! \brief      Sets the keypad type and key values
    //! \details    This function sets the keypad type and keys values.
    //! \param      type_p              Keypad type
    //! \param      ...                 Array of keypad key values (uint8_t)
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t setKeyValues(
            Type type_p,
            ...
    );

    //!
    //! \brief      Reads the pressed key on the keypad.
    //! \details    This function gets the keypad status and decodes the pressed
    //!                 key.
    //! \param      keyPressedValue_p   Pointer to store the pressed key value (0xFF if no key is pressed)
    //! \return     bool_t              True on success / False on failure
    //!
    bool_t readKeyPressed(
            uint8_t *keyPressedValue_p
    );

    Error getLastError(
            void
    );


private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
public:

    // NONE

private:

    //     //////////////////     DEVICE BUS PORTS     //////////////////     //

    GpioBus                             *_gpioLines;
    GpioBus                             *_gpioColumns;

    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    bool_t                              _isPortsSet     : 1;
    bool_t                              _isKeyValuesSet : 1;
    bool_t                              _isInitialized  : 1;
    Error                               _lastError;

    //     ///////////////     HARDWARE CONFIGURATION     ///////////////     //
    Type                                _type;
    uint8_t                             _columnsMax     : 3;
    uint8_t                             _linesMax       : 3;
    uint8_t                             *_keyValue;
    bool_t                              _debounceTime   : 7;

protected:

    // NONE

}; // class Keypad

// =============================================================================
// Inlined class functions
// =============================================================================

// NONE

// =============================================================================
// External global variables
// =============================================================================

// NONE

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __FUNSAPE_LIB_KEYPAD_HPP

// =============================================================================
// END OF FILE - funsapeLibKeypad.hpp
// =============================================================================
