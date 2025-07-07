//!
//! \file           funsapeLibSn74595.hpp
//! \brief          SN74595 Serial Shift Register module interface for the
//!                     FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-07-10
//! \version        24.07
//! \copyright      license
//! \details        SN74595 Serial Shift Register controller for the FunSAPE
//!                     AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_SN74595_HPP
#define __FUNSAPE_LIB_SN74595_HPP                       2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_SN74595_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_SN74595_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

#include "../peripheral/funsapeLibGpioPin.hpp"
#ifndef __FUNSAPE_LIB_GPIO_PIN_HPP
#   error "Header file (funsapeLibGpioPin.hpp) is corrupted!"
#elif __FUNSAPE_LIB_GPIO_PIN_HPP != __FUNSAPE_LIB_SN74595_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibGpioPin.hpp)!"
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Devices"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Devices
//! \brief          External devices.
//! \{
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Devices/Sn74595"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Sn74595
//! \brief          SN74595 Serial Shift Register controller module.
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
// Sn74595 Class
// =============================================================================

//!
//! \brief          Sn74595 class.
//! \details        This class manages cascaded SN74595 shift registers.
//! \warning        This class is not instantiated by default. The user may
//!                     create as many instances as necessary.
//!
class Sn74595
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    enum class DataOrder : bool_t {
        LSB_FIRST   = false,
        MSB_FIRST   = true
    };

    // NONE


    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    Sn74595(
            void
    );
    ~Sn74595(
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
            const DataOrder dataOrder_p         = DataOrder::LSB_FIRST
    );
    bool_t setPort(
            const GpioPin *dataInPin_p,
            const GpioPin *shiftClockPin_p,
            const GpioPin *storeClockPin_p,
            const GpioPin *outputEnablePin_p    = nullptr,
            const GpioPin *masterResetPin_p     = nullptr
    );
    bool_t enableOutputs(
            void
    );
    bool_t disableOutputs(
            void
    );
    bool_t clearData(
            void
    );
    bool_t sendByte(
            cuint8_t data_p
    );
    bool_t store(
            void
    );

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
private:

    //     /////////////////    CONTROL AND STATUS     //////////////////     //
    bool_t          _isPortsSet                 : 1;
    bool_t          _isInitialized              : 1;
    bool_t          _dataOrderMsbFirst          : 1;
    Error           _lastError;

    //     ////////////////    PERIPHERAL BUS HANDLER     ////////////////     //
    GpioPin         *_dataIn;
    GpioPin         *_shift;
    GpioPin         *_store;
    GpioPin         *_outputEnable;
    GpioPin         *_clear;
}; // class Sn74595

// =============================================================================
// Inlined class functions
// =============================================================================

// NONE

// =============================================================================
// External global variables
// =============================================================================

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Devices/Sn74595"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End main group "Devices"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __FUNSAPE_LIB_SN74595_HPP

// =============================================================================
// END OF FILE - funsapeLibSn74595.hpp
// =============================================================================
