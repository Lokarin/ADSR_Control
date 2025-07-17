//!
//! \file           funsapeLibTm1637.hpp
//! \brief          TM1637 Display module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-07-10
//! \version        24.07
//! \copyright      license
//! \details        TM1637 Display module interface for the FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard
// =============================================================================

#ifndef __FUNSAPE_LIB_TM1637_HPP
#define __FUNSAPE_LIB_TM1637_HPP                        2407

// =============================================================================
// Dependencies
// =============================================================================

// -----------------------------------------------------------------------------
// Global definitions file -----------------------------------------------------

#include "../funsapeLibGlobalDefines.hpp"
#ifndef __FUNSAPE_LIB_GLOBAL_DEFINES_HPP
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_TM1637_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

// -----------------------------------------------------------------------------
// Header files - FunSAPE Library header files ---------------------------------

#include "../util/funsapeLibDebug.hpp"
#ifndef __FUNSAPE_LIB_DEBUG_HPP
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_TM1637_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

#include "../peripheral/funsapeLibGpioPin.hpp"
#ifndef __FUNSAPE_LIB_GPIO_PIN_HPP
#   error "Header file (funsapeLibGpioPin.hpp) is corrupted!"
#elif __FUNSAPE_LIB_GPIO_PIN_HPP != __FUNSAPE_LIB_TM1637_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibGpioPin.hpp)!"
#endif

// =============================================================================
// Platform verification
// =============================================================================

// NONE

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

// NONE

// =============================================================================
// Macro-function definitions
// *INDENT-OFF*
// =============================================================================

// NONE

// *INDENT-ON*

// =============================================================================
// New data types
// =============================================================================

// NONE

// =============================================================================
// Extern global variables
// =============================================================================

// NONE

// =============================================================================
// Tm1637 - Class declaration
// =============================================================================

class Tm1637
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    enum class Contrast : uint8_t {
        PERCENT_6_25                    = 0,
        PERCENT_13                      = 1,
        PERCENT_26                      = 2,
        PERCENT_62_5                    = 3,
        PERCENT_68_75                   = 4,
        PERCENT_75                      = 5,
        PERCENT_81_25                   = 6,
        PERCENT_87_5                    = 7,
    };

private:
    //     //////////////////////     COMMANDS     //////////////////////     //
    enum class Command : uint8_t {
        DATA_SETTING                    = 0x40,
        DISPLAY_ADDRESS                 = 0xC0,
        DISPLAY_CONTROL                 = 0x80,
    };
    //     ////////////////////    BIT POSITIONS     ////////////////////     //
    enum class BitPos : uint8_t {

        // Command setting
        DATA_SETTING_MODE_READ          = 1,
        DATA_SETTING_FIXED_ADDRESS      = 2,
        DATA_SETTING_TEST_MODE          = 3,

        // Display address
        DISPLAY_ADDRESS                 = 0,

        // Display control
        DISPLAY_CONTROL_CONTRAST        = 0,
        DISPLAY_CONTROL_SHOW            = 3,
    };
    //     //////////////////////     BIT MASK     //////////////////////     //
    enum class BitMask : uint8_t {

        // Command setting
        DATA_SETTING_MODE_READ          = 0x01,
        DATA_SETTING_FIXED_ADDRESS      = 0x01,
        DATA_SETTING_TEST_MODE          = 0x01,

        // Display address
        DISPLAY_ADDRESS                 = 0x07,

        // Display control
        DISPLAY_CONTROL_CONTRAST        = 0x07,
        DISPLAY_CONTROL_SHOW            = 0x01,
    };

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Operators overloading ---------------------------------------------------

public:
    // NONE

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    Tm1637(
            void
    );
    Tm1637(
            const GpioPin *dioPin_p,
            const GpioPin *clkPin_p
    );
    // TODO: Implement destructor function
    ~Tm1637(
            void
    );

    // -------------------------------------------------------------------------
    // Methods - Class own methods ---------------------------------------------

public:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    Error getLastError(
            void
    );
    bool_t init(
            const GpioPin *dioPin_p,
            const GpioPin *clkPin_p
    );
    bool_t setAddressingMode(
            cbool_t useAutoIncrementMode_p
    );

    //     ///////////////////    DISPLAY CONTROL     ///////////////////     //
    bool_t setDisplayContrast(
            const Contrast contrastLevel_p
    );
    bool_t showDisplay(
            cbool_t showDisplay_p
    );
    bool_t writeDisplayData(
            cuint16_t displayValue_p,
            cuint8_t base_p = 10
    );
    bool_t writeDisplayData(
            cuint8_t segments_p,
            cuint8_t index_p,
            cbool_t showDot_p
    );

    //     ///////////////////     KEYPAD CONTROL     ///////////////////     //
    bool_t readKeypadData(
            uint8_t *keyPressed_p
    );

private:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    bool_t _isInitialized(
            void
    );

    //     ///////////////     COMMUNICATION PROTOCOL     ///////////////     //
    void _sendStart(
            void
    );
    void _sendStop(
            void
    );
    void _writeByte(
            cuint8_t byteToWrite_p
    );
    void _readByte(
            uint8_t *byteRead_p
    );
    bool_t _readAck(
            void
    );

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------

public:
    // NONE

private:
    //     ////////////////    PERIPHERAL BUS HANDLER     ////////////////     //
    GpioPin        *_clkPin;
    GpioPin        *_dioPin;

    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    bool_t          _initialized                : 1;
    Error           _lastError;
    bool_t          _useAutoIncrementMode       : 1;

    //     ///////////////////    DISPLAY CONTROL     ///////////////////     //
    Contrast        _contrastLevel;
    bool_t          _showDisplay;
}; // class Tm1637

// =============================================================================
// Tm1637 - Class overloading operators
// =============================================================================

// NONE

// =============================================================================
// Global variables
// =============================================================================

// -----------------------------------------------------------------------------
// Externally defined global variables -----------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Internally defined global variables -----------------------------------------

// NONE

// =============================================================================
// Tm1637 - Class inline function definitions
// =============================================================================

// NONE

// =============================================================================
// General public functions declarations
// =============================================================================

// NONE

// =============================================================================
// General inline functions definitions
// =============================================================================

// NONE

// =============================================================================
// External default objects
// =============================================================================

// NONE

#endif // __FUNSAPE_LIB_TM1637_HPP

// =============================================================================
// END OF FILE
// =============================================================================
