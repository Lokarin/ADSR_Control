//!
//! \file           funsapeLibStepper.hpp
//! \brief          Stepper motor module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-07-10
//! \version        24.07
//! \copyright      license
//! \details        Stepper motor module interface for the FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard
// =============================================================================

#ifndef __FUNSAPE_LIB_STEPPER_HPP
#define __FUNSAPE_LIB_STEPPER_HPP                       2407

// =============================================================================
// Dependencies
// =============================================================================

// -----------------------------------------------------------------------------
// Global definitions file -----------------------------------------------------

#include "../funsapeLibGlobalDefines.hpp"
#ifndef __FUNSAPE_LIB_GLOBAL_DEFINES_HPP
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_STEPPER_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

// -----------------------------------------------------------------------------
// Header files - FunSAPE Library header files ---------------------------------

#include "../util/funsapeLibDebug.hpp"
#ifndef __FUNSAPE_LIB_DEBUG_HPP
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_STEPPER_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

#include "../peripheral/funsapeLibGpioPin.hpp"
#ifndef __FUNSAPE_LIB_GPIO_PIN_HPP
#   error "Header file (funsapeLibGpioPin.hpp) is corrupted!"
#elif __FUNSAPE_LIB_GPIO_PIN_HPP != __FUNSAPE_LIB_STEPPER_HPP
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
// Stepper - Class declaration
// =============================================================================

class Stepper
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    enum class Mode : uint8_t {
        FULL_STEP_ONE_PHASE             = 0,
        FULL_STEP_TWO_PHASE             = 1,
        HALF_STEP                       = 2,
    };

private:
    typedef uint8_t step_t;

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    Stepper(
            void
    );
    // TODO: Implement destructor function
    ~Stepper(
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
            const GpioPin *coilA_p,
            const GpioPin *coilB_p,
            const GpioPin *coilC_p,
            const GpioPin *coilD_p
    );
    bool_t setMode(
            const Mode mode_p
    );
    bool_t move(
            const Rotation direction_p
    );

private:
    void _doStep(
            const step_t step_p
    );

    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------

public:

    // NONE

private:
    //     ////////////////    PERIPHERAL BUS HANDLER     ////////////////     //
    GpioPin *_coilA;
    GpioPin *_coilB;
    GpioPin *_coilC;
    GpioPin *_coilD;

    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    bool_t          _initialized                : 1;
    step_t          _step                       : 3;
    Error           _lastError;
    Mode            _mode;
}; // class Stepper

// =============================================================================
// Stepper - Class overloading operators
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
// Stepper - Class inline function definitions
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

#endif // __FUNSAPE_LIB_STEPPER_HPP

// =============================================================================
// END OF FILE
// =============================================================================
