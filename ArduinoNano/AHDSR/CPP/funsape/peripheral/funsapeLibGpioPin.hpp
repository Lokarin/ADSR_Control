//!
//! \file           funsapeLibGpioPin.hpp
//! \brief          GPIO single pin peripheral control for the FunSAPE AVR8
//!                     Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-09
//! \version        24.05
//! \copyright      license
//! \details        GPIO single pin peripheral control for the FunSAPE AVR8
//!                     Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_GPIO_PIN_HPP
#define __FUNSAPE_LIB_GPIO_PIN_HPP              2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_GPIO_PIN_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_GPIO_PIN_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Peripherals
//! \brief          Microcontroller peripherals.
//! \{
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Peripherals/GpioPin"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     GpioPin
//! \brief          General Purpose Intput/Output (GPIO) pin controller module.
//! \{
//!

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
// GpioPin Class
// =============================================================================

//!
//! \brief          GpioPin class.
//! \details        This class manages the General Purpose Input-Output (GPIO)
//!                     peripheral in single pin mode.
//! \warning        This class is not instantiated by default. The user may
//!                     create as many instances as necessary.
//!
class GpioPin
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    enum class PinIndex : uint8_t {
        P0                              = 0,
        P1                              = 1,
        P2                              = 2,
        P3                              = 3,
        P4                              = 4,
        P5                              = 5,
        P6                              = 6,
        P7                              = 7
    };

    enum class PinMask : uint8_t {
        P0                              = 1 << 0,
        P1                              = 1 << 1,
        P2                              = 1 << 2,
        P3                              = 1 << 3,
        P4                              = 1 << 4,
        P5                              = 1 << 5,
        P6                              = 1 << 6,
        P7                              = 1 << 7,
    };

    enum class Mode : uint8_t {
        INPUT_FLOATING                  = 1,
        INPUT_PULLED_UP                 = 3,
        OUTPUT_PUSH_PULL                = 5,
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    GpioPin(
            void
    );
    ~GpioPin(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:

    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    Error getLastError(
            void
    );

    bool_t init(
            ioRegAddress_t gpioPort_p,
            PinIndex gpioPinIndex_p
    );

    //     /////////////////    PIN RELATED METHODS     /////////////////     //
    inlined void clr(void) {
        // Clear pin
        clrMask(*(this->_regOut), (uint8_t)this->_pinMask);

        // Returns
        return;
    }

    inlined void cpl(void) {
        // Toggle pin
        cplMask(*(this->_regOut), (uint8_t)this->_pinMask);

        // Returns
        return;
    }

    inlined void set(void) {
        // Set pin
        setMask(*(this->_regOut), (uint8_t)this->_pinMask);

        // Returns
        return;
    }

    inlined void low(void) {
        this->clr();

        return;
    }

    inlined void high(void) {
        this->set();

        return;
    }

    inlined void toggle(void) {
        this->cpl();

        return;
    }

    inlined bool_t read(void) {
        return (bool_t)(*(this->_regIn) & (uint8_t)(this->_pinMask));
    }

    bool_t setMode(
            Mode mode_p
    );

    inlined bool_t isInitialized(void) {
        return this->_isInitialized;
    }

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
private:

    //     /////////////////    CONTROL AND STATUS     //////////////////     //
    ioRegAddress_t  _regDir;
    ioRegAddress_t  _regOut;
    ioRegAddress_t  _regIn;
    PinMask         _pinMask;
    PinIndex        _pinIndex;
    bool_t          _isInitialized              : 1;
    Error           _lastError;
    Mode            _mode;
}; // class GpioPin

// =============================================================================
// Inlined class functions
// =============================================================================

// NONE

// =============================================================================
// External global variables
// =============================================================================

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/GpioPin"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __FUNSAPE_LIB_GPIO_PIN_HPP

// =============================================================================
// END OF FILE - funsapeLibGpioPin.hpp
// =============================================================================
