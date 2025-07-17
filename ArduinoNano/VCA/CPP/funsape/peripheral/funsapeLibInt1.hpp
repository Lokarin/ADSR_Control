//!
//! \file           funsapeLibInt1.hpp
//! \brief          External Interrupt INT1 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        External Interrupt INT1 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_INT1_HPP
#define __FUNSAPE_LIB_INT1_HPP                  2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_INT1_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_INT1_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

#if defined(_FUNSAPE_PLATFORM_AVR)

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Peripherals
//! \brief          Microcontroller peripherals.
//! \{
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Peripherals/Int1"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Int1
//! \brief          External Interrupt 1 (INT1) controller module.
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

//!
//! \brief          INT1 interrupt callback function.
//! \details        This function is called when the INT1 interrupt is treated.
//!                     It is a weak function that can be overwritten by user
//!                     code.
//!
void int1InterruptCallback();

// =============================================================================
// Int1 Class
// =============================================================================

//!
//! \brief          Int1 class.
//! \details        This class manages the External Interrupt 1 (INT1)
//!                     peripheral.
//! \warning        An instance of this class is already defined as a global
//!                     object. Therefore, there is not necessary, neither
//!                     recommended to create another object of this class.
//!
class Int1
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     /////////////////     INT1 Trigger Sense     /////////////////     //
    //!
    //! \brief      Sense Trigger enumeration.
    //! \details    Sense Trigger events associated with INT1.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class SenseMode : uint8_t {
        LOW_LEVEL           = 0,    //!< Trigger interrupt continuously while pin is in logic low level.
        BOTH_EDGES          = 1,    //!< Trigger interrupt at both edges.
        FALLING_EDGE        = 2,    //!< Trigger interrupt at falling edge.
        RISING_EDGE         = 3,    //!< Trigger interrupt at rising edge.
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Int1 class constructor.
    //! \details    Creates an Int1 object. The object is loaded with the
    //!                 default register values (SenseMode::LOW_LEVEL). The
    //!                 object still must be initialized before use.
    //! \see        init(SenseMode senseMode_p).
    //!
    Int1(
            void
    );

    //!
    //! \brief      Int1 class destructor.
    //! \details    Destroys an Int1 object.
    //!
    ~Int1(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     INITIALIZATION    ////////////////////     //

    //!
    //! \brief      Initializes the INT1 module.
    //! \details    Initializes the INT1 module. The function also configures
    //!                 the sensibility mode for trigger the interrupt. The
    //!                 default parameter is SenseMode::LOW_LEVEL.
    //! \param      senseMode_p         Trigger sense mode.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t init(
            SenseMode senseMode_p
    );

    //!
    //!
    //! \brief      Configures the trigger sense mode.
    //! \details    Configures the sensibility mode for trigger the interrupt.
    //! \param      senseMode_p         Trigger sense mode.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setSenseMode(
            SenseMode senseMode_p
    );

    //     /////////////////     CONTROL AND STATUS    //////////////////     //

    //!
    //! \brief      Returns the last error.
    //! \details    Returns the last error.
    //! \return     Error               Error status of the last operation.
    //!
    Error           getLastError(
            void
    );

    //     //////////////////////    INTERRUPT     //////////////////////     //

    //!
    //! \brief      Activates interrupt.
    //! \details    Activates interrupt. If an interrupt request is pending, an
    //!                 interrupt will be triggered when activated. In most
    //!                 applications, it is recommended to ignore an old
    //!                 interrupt request prior to activate the interrupt. This
    //!                 can be done by calling \ref clearInterruptRequest()
    //!                 function imediatelly before activating the interrupt.
    //!
    void inlined activateInterrupt(
            void
    );

    //!
    //! \brief      Clears interrupt flag.
    //! \details    Clears the interrupt flag, dismissing any pending interrupt
    //!                 request.
    //!
    void inlined clearInterruptRequest(
            void
    );

    //!
    //! \brief      Deactivates interrupt.
    //! \details    Deactivates interrupt. This function does not clears any
    //!                 pending interrupt request.
    //!
    void inlined deactivateInterrupt(
            void
    );

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
private:
    bool_t          _isInitialized      : 1;
    SenseMode       _senseMode;
    Error           _lastError;
}; // class Int1

// =============================================================================
// Inlined class functions
// =============================================================================

//!
//! \cond
//!

void inlined Int1::activateInterrupt(void)
{
    setBit(EIMSK, INT1);
    return;
}

void inlined Int1::clearInterruptRequest(void)
{
    setBit(EIFR, INTF1);
    return;
}

void inlined Int1::deactivateInterrupt(void)
{
    clrBit(EIMSK, INT1);
    return;
}

//!
//! \endcond
//!

// =============================================================================
// External global variables
// =============================================================================

//!
//! \brief          Int1 peripheral handler object.
//! \details        Int1 peripheral handler object.
//! \warning        Use this object to handle the peripheral. DO NOT create
//!                     another instance of the class, since this could lead to
//!                     information mismatch between instances and the
//!                     peripheral registers.
//!
extern Int1 int1;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/Int1"
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

#endif // defined(_FUNSAPE_PLATFORM_AVR)

#endif  // __FUNSAPE_LIB_INT1_HPP

// =============================================================================
// END OF FILE
// =============================================================================
