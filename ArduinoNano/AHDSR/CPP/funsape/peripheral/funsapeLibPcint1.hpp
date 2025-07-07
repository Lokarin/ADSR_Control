//!
//! \file           funsapeLibPcint1.hpp
//! \brief          External Interrupt PCINT1 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        External Interrupt PCINT1 peripheral control for the FunSAPE
//!                     AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_PCINT1_HPP
#define __FUNSAPE_LIB_PCINT1_HPP                2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_PCINT1_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_PCINT1_HPP
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
// Doxygen: Start subgroup "Peripherals/Pcint1"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Pcint1
//! \brief          Pin Change Interrupt 1 (PCINT1) controller module.
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
//! \brief          PCINT1 interrupt callback function.
//! \details        This function is called when the PCINT1 interrupt is
//!                     treated. It is a weak function that can be overwritten
//!                     by user code.
//!
void pcint1InterruptCallback();

// =============================================================================
// Pcint1 Class
// =============================================================================

//!
//! \brief          Pcint1 class.
//! \details        This class manages the Pin Change Interrupt 1 (PCINT1)
//!                     peripheral.
//! \warning        An instance of this class is already defined as a global
//!                     object. Therefore, there is not necessary, neither
//!                     recommended to create another object of this class.
//!
class Pcint1
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     /////////////////    PCINT1 Trigger Mode     /////////////////     //
    //!
    //! \brief      Trigger Mode Pins enumeration.
    //! \details    Trigger Mode Pins associated with PCINT1.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class Pin : uint8_t {
        PIN_PCINT8          = (1 << 0), //!< Enables trigger by PCINT8 pin.
        PIN_PCINT9          = (1 << 1), //!< Enables trigger by PCINT9 pin.
        PIN_PCINT10         = (1 << 2), //!< Enables trigger by PCINT10 pin.
        PIN_PCINT11         = (1 << 3), //!< Enables trigger by PCINT11 pin.
        PIN_PCINT12         = (1 << 4), //!< Enables trigger by PCINT12 pin.
        PIN_PCINT13         = (1 << 5), //!< Enables trigger by PCINT13 pin.
        PIN_PCINT14         = (1 << 6), //!< Enables trigger by PCINT14 pin.
        // PIN_PCINT15         = (1 << 7), //!< Enables trigger by PCINT15 pin.
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Pcint1 class constructor.
    //! \details    Creates a Pcint1 object. The object is loaded with the
    //!                 default register values (no pins enabled). The
    //!                 object still must be initialized before use.
    //! \see        init(Pin enablePins_p).
    //!
    Pcint1(
            void
    );

    //!
    //! \brief      Pcint1 class destructor.
    //! \details    Destroys an Pcint1 object.
    //!
    ~Pcint1(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     INITIALIZATION    ////////////////////     //
    //!
    //! \brief      Initializes the PCINT1 module.
    //! \details    Initializes the PCINT1 module. The function also enables
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
            Pin enablePins_p
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
}; // class Pcint1

// =============================================================================
// Inlined class functions
// =============================================================================

//!
//! \cond
//!

//     ////////////////////////    INTERRUPT     ////////////////////////     //
void inlined Pcint1::activateInterrupt(void)
{
    setBit(PCICR, PCINT1);
    return;
}

void inlined Pcint1::clearInterruptRequest(void)
{
    setBit(PCIFR, PCIF1);
    return;
}

void inlined Pcint1::deactivateInterrupt(void)
{
    clrBit(PCICR, PCINT1);
    return;
}

//     //////////////////     OPERATOR OVERLOADING     //////////////////     //
inlined Pcint1::Pin operator|(Pcint1::Pin a, Pcint1::Pin b)
{
    return static_cast<Pcint1::Pin>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inlined Pcint1::Pin &operator|=(Pcint1::Pin &a, Pcint1::Pin b)
{
    return a = static_cast<Pcint1::Pin>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inlined Pcint1::Pin operator&(Pcint1::Pin a, Pcint1::Pin b)
{
    return static_cast<Pcint1::Pin>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

inlined Pcint1::Pin &operator&=(Pcint1::Pin &a, Pcint1::Pin b)
{
    return a = static_cast<Pcint1::Pin>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

//!
//! \endcond
//!

// =============================================================================
// External global variables
// =============================================================================

//!
//!
//! \brief          Pcint1 peripheral handler object.
//! \details        Pcint1 peripheral handler object.
//! \warning        Use this object to handle the peripheral. DO NOT create
//!                     another instance of the class, since this could lead to
//!                     information mismatch between instances and the
//!                     peripheral registers.
//!
extern Pcint1 pcint1;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/Pcint1"
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

#endif  // __FUNSAPE_LIB_PCINT1_HPP

// =============================================================================
// END OF FILE
// =============================================================================
