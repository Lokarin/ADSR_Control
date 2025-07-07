//!
//! \file           funsapeLibGpioBus.hpp
//! \brief          GPIO bus peripheral control for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-09
//! \version        24.05
//! \copyright      license
//! \details        GPIO bus peripheral control for the FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_GPIO_BUS_HPP
#define __FUNSAPE_LIB_GPIO_BUS_HPP              2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_GPIO_BUS_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_GPIO_BUS_HPP
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
// Doxygen: Start subgroup "Peripherals/GpioBus"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     GpioBus
//! \brief          General Purpose Intput/Output (GPIO) bus controller module.
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
// GpioBus Class
// =============================================================================

//!
//! \brief          GpioBus class.
//! \details        This class manages the General Purpose Input-Output (GPIO)
//!                     peripheral in bus mode.
//! \warning        This class is not instantiated by default. The user may
//!                     create as many instances as necessary.
//!
class GpioBus
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
        P7                              = 7,
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

    GpioBus(
            void
    );
    ~GpioBus(
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
            ioRegAddress_t gpioPortAddress_p,
            PinIndex gpioPinIndex_p,
            cuint8_t gpioBusSize_p
    );

    //     /////////////////    PIN RELATED METHODS     /////////////////     //
    inlined void clr(void) {
        // Clear pin
        clrMask(*(this->_regOut), (uint8_t)this->_pinMask);

        // Returns
        return;
    }

    inlined void clr(uint8_t bitIndex_p) {
        // Clear pin
        clrBit(*(this->_regOut), (bitIndex_p + (uint8_t)this->_pinIndex));

        // Returns
        return;
    }

    inlined void cpl(void) {
        // Toggle pin
        cplMask(*(this->_regOut), (uint8_t)this->_pinMask);

        // Returns
        return;
    }

    inlined void cpl(uint8_t bitIndex_p) {
        // Clear pin
        cplBit(*(this->_regOut), (bitIndex_p + (uint8_t)this->_pinIndex));

        // Returns
        return;
    }

    inlined void set(void) {
        // Set pin
        setMask(*(this->_regOut), (uint8_t)this->_pinMask);

        // Returns
        return;
    }

    inlined void set(uint8_t bitIndex_p) {
        // Clear pin
        setBit(*(this->_regOut), (bitIndex_p + (uint8_t)this->_pinIndex));

        // Returns
        return;
    }

    inlined void low(void) {
        this->clr();

        return;
    }

    inlined void low(uint8_t bitIndex_p) {
        this->clr(bitIndex_p);

        return;
    }

    inlined void high(void) {
        this->set();

        return;
    }

    inlined void high(uint8_t bitIndex_p) {
        this->set(bitIndex_p);

        return;
    }

    inlined void toggle(void) {
        this->cpl();

        return;
    }

    inlined void toggle(uint8_t bitIndex_p) {
        this->cpl(bitIndex_p);

        return;
    }

    inlined uint8_t read(void) {
        return (uint8_t)((*(this->_regIn) & (uint8_t)this->_pinMask) >> (uint8_t)this->_pinIndex);
    }

    bool_t write(
            uint8_t data_p
    );

    bool_t setMode(
            Mode mode_p
    );

    uint8_t getBusSize(
            void
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
    bool_t          _isInitialized              : 1;
    Error           _lastError;
    Mode            _mode;
    PinIndex        _pinIndex;
    uint8_t         _busSize                    : 4;
}; // class GpioBus

// =============================================================================
// Inlined class functions
// =============================================================================

// NONE

// =============================================================================
// External global variables
// =============================================================================

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/GpioBus"
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

#endif  // __FUNSAPE_LIB_GPIO_BUS_HPP

// =============================================================================
// END OF FILE - funsapeLibGpioBus.hpp
// =============================================================================
