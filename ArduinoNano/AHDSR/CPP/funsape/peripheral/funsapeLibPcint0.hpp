//!
//! \file           funsapeLibPcint0.hpp
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
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_PCINT0_HPP
#define __FUNSAPE_LIB_PCINT0_HPP                2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_PCINT0_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_PCINT0_HPP
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
// Doxygen: Start subgroup "Peripherals/Pcint0"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Pcint0
//! \brief          Pin Change Interrupt 0 (PCINT0) controller module.
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
//! \brief          PCINT0 interrupt callback function.
//! \details        This function is called when the PCINT0 interrupt is
//!                     treated. It is a weak function that can be overwritten
//!                     by user code.
//!
void pcint0InterruptCallback();

// =============================================================================
// Pcint0 Class
// =============================================================================

//!
//! \brief          Pcint0 class.
//! \details        This class manages the Pin Change Interrupt 0 (PCINT0)
//!                     peripheral.
//! \warning        An instance of this class is already defined as a global
//!                     object. Therefore, there is not necessary, neither
//!                     recommended to create another object of this class.
//!
class Pcint0
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     /////////////////    PCINT0 Trigger Mode     /////////////////     //
    //!
    //! \brief      Trigger Mode Pins enumeration.
    //! \details    Trigger Mode Pins associated with PCINT0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class Pin : uint8_t {
        PIN_PCINT0          = (1 << 0), //!< Enables trigger by PCINT0 pin.
        PIN_PCINT1          = (1 << 1), //!< Enables trigger by PCINT1 pin.
        PIN_PCINT2          = (1 << 2), //!< Enables trigger by PCINT2 pin.
        PIN_PCINT3          = (1 << 3), //!< Enables trigger by PCINT3 pin.
        PIN_PCINT4          = (1 << 4), //!< Enables trigger by PCINT4 pin.
        PIN_PCINT5          = (1 << 5), //!< Enables trigger by PCINT5 pin.
        PIN_PCINT6          = (1 << 6), //!< Enables trigger by PCINT6 pin.
        PIN_PCINT7          = (1 << 7), //!< Enables trigger by PCINT7 pin.
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Pcint0 class constructor.
    //! \details    Creates a Pcint0 object. The object is loaded with the
    //!                 default register values (no pins enabled). The
    //!                 object still must be initialized before use.
    //! \see        init(Pin enablePins_p).
    //!
    Pcint0(
            void
    );

    //!
    //! \brief      Pcint0 class destructor.
    //! \details    Destroys an Pcint0 object.
    //!
    ~Pcint0(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     INITIALIZATION    ////////////////////     //
    //!
    //! \brief      Initializes the PCINT0 module.
    //! \details    Initializes the PCINT0 module. The function also enables
    //!                 the pins that trigger the interrupt. The default
    //!                 parameter has no pins enabled.
    //! \param      enablePins_p        Enable interrupt pins. Multiples pins
    //!                                     can be enabled at the same time by
    //!                                     using OR operations.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t init(
            Pin enablePins_p = (Pcint0::Pin)0
    );

    //!
    //! \brief      Enables interrupt pins.
    //! \details    Enables the pins to trigger the interrupt.
    //! \param      enablePins_p        Enable interrupt pins. Multiples pins
    //!                                     can be enabled at the same time by
    //!                                     using OR operations.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t enablePins(
            Pin enablePins_p
    );

    //!
    //! \brief      Disable the pins to trigger the interrupt.
    //! \details    Configures the trigger sense mode.
    //! \param      disablePins_p       Disable interrupt pins. Multiples pins
    //!                                     can be disabled at the same time by
    //!                                     using OR operations.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t disablePins(
            Pin disablePins_p
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
    //! \brief      Activates interrupt
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
    Pin             _enabledPins;
    Error           _lastError;
}; // class Pcint0

// =============================================================================
// Inlined class functions
// =============================================================================

//!
//! \cond
//!

//     ////////////////////////    INTERRUPT     ////////////////////////     //
void inlined Pcint0::activateInterrupt(void)
{
    setBit(PCICR, PCINT0);
    return;
}

void inlined Pcint0::clearInterruptRequest(void)
{
    setBit(PCIFR, PCIF0);
    return;
}

void inlined Pcint0::deactivateInterrupt(void)
{
    clrBit(PCICR, PCINT0);
    return;
}

//     //////////////////     OPERATOR OVERLOADING     //////////////////     //
inlined Pcint0::Pin operator|(Pcint0::Pin a, Pcint0::Pin b)
{
    return static_cast<Pcint0::Pin>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inlined Pcint0::Pin &operator|=(Pcint0::Pin &a, Pcint0::Pin b)
{
    return a = static_cast<Pcint0::Pin>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inlined Pcint0::Pin operator&(Pcint0::Pin a, Pcint0::Pin b)
{
    return static_cast<Pcint0::Pin>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

inlined Pcint0::Pin &operator&=(Pcint0::Pin &a, Pcint0::Pin b)
{
    return a = static_cast<Pcint0::Pin>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

//!
//! \endcond
//!

// =============================================================================
// External global variables
// =============================================================================

//!
//!
//! \brief          Pcint0 peripheral handler object.
//! \details        Pcint0 peripheral handler object.
//! \warning        Use this object to handle the peripheral. DO NOT create
//!                     another instance of the class, since this could lead to
//!                     information mismatch between instances and the
//!                     peripheral registers.
//!
extern Pcint0 pcint0;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/Pcint0"
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

#endif  // __FUNSAPE_LIB_PCINT0_HPP

// =============================================================================
// END OF FILE
// =============================================================================
