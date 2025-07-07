//!
//! \file           funsapeLibTimer0.hpp
//! \brief          TIMER0 peripheral control for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        TIMER0 peripheral control for the FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_TIMER0_HPP
#define __FUNSAPE_LIB_TIMER0_HPP                2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_TIMER0_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_TIMER0_HPP
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
// Doxygen: Start subgroup "Peripherals/Timer0"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Timer0
//! \brief          Timer/Counter 0 (TIMER0) controller module.
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
//! \brief          TIMER0 compare A match interrupt callback function.
//! \details        This function is called when the TIMER0 compare A match
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer0CompareACallback();

//!
//! \brief          TIMER0 compare B match interrupt callback function.
//! \details        This function is called when the TIMER0 compare B match
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer0CompareBCallback();

//!
//! \brief          TIMER0 overflow interrupt callback function.
//! \details        This function is called when the TIMER0 overflow interrupt
//!                     is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer0OverflowCallback();

// =============================================================================
// Timer0 Class
// =============================================================================

//!
//! \brief          Timer0 class.
//! \details        This class manages the Timer/Counter 0 (TIMER0)
//!                     peripheral.
//! \warning        An instance of this class is already defined as a global
//!                     object. Therefore, there is not necessary, neither
//!                     recommended to create another object of this class.
//!
class Timer0
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     ////////////////     TIMER0 Clock Source     /////////////////     //
    //!
    //! \brief      Clock source enumeration.
    //! \details    Clock prescaler options associated with TIMER0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class ClockSource : uint8_t {
        DISABLED                    = 0,    //!< Disables clock, timer is off.
        PRESCALER_1                 = 1,    //!< Disables prescaler, timer clock frequency will be equal to CPU clock.
        PRESCALER_8                 = 2,    //!< Timer clock frequency will be CPU clock divided by 8.
        PRESCALER_64                = 3,    //!< Timer clock frequency will be CPU clock divided by 64.
        PRESCALER_256               = 4,    //!< Timer clock frequency will be CPU clock divided by 256.
        PRESCALER_1024              = 5,    //!< Timer clock frequency will be CPU clock divided by 1024.
        T0_FALLING_EDGE             = 6,    //!< Timer clock will be based on the falling edge of a signal placed on T0 pin.
        T0_RISING_EDGE              = 7     //!< Timer clock will be based on the rising edge of a signal placed on T0 pin.
    };

    //     ////////////////////     TIMER0 Mode     /////////////////////     //
    //!
    //! \brief      Operation Mode enumeration.
    //! \details    Operation Mode options associated with TIMER0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class Mode : uint8_t {
        NORMAL                          = 0,    //!< Normal mode (direction = UP / TOP = 0xFF / UPDATE OCR0x = immediate / TOV Flag = 0xFF).
        PWM_PHASE_CORRECTED_MAX         = 1,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = 0xFF / UPDATE OCR0x = 0xFF / TOV Flag = 0x00).
        CTC_OCRA                        = 2,    //!< CTC mode (direction = UP / TOP = OCR0A / UPDATE OCR0x = immediate / TOV Flag = 0xFF).
        PWM_FAST_MAX                    = 3,    //!< PWM mode fast (direction = UP / TOP = 0xFF / UPDATE OCR0x = 0x00 / TOV Flag = 0xFF).
        // RESERVED                     = 4,
        PWM_PHASE_CORRECTED_OCRA        = 5,    //!< PWM mode fast (direction = UP / TOP = OCR0A / UPDATE OCR0x = 0x00 / TOV Flag = 0xFF).
        // RESERVED                     = 6,
        PWM_FAST_OCRA                   = 7,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = OCR0A / UPDATE OCR0x = OCR0A / TOV Flag = 0x00).
    };

    //     /////////////////     TIMER0 Output Mode    //////////////////     //
    //!
    //! \brief      Output Mode enumeration.
    //! \details    Output Mode options associated with TIMER0.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class OutputMode : uint8_t {
        NORMAL                          = 0,    //!< OC0x disabled. Normal port operation.
        TOGGLE_ON_COMPARE               = 1,    //!< OC0x will toggle on OCR0x compare match.
        CLEAR_ON_COMPARE                = 2,    //!< OC0x will clear on OCR0x compare match.
        SET_ON_COMPARE                  = 3,    //!< OC0x will set on OCR0x compare match.
        NON_INVERTING_MODE              = 2,    //!< OC0x will produce a non-inverted PWM signal.
        INVERTING_MODE                  = 3,    //!< OC0x will produce a inverted PWM signal.
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Timer0 class constructor.
    //! \details    Creates a Timer0 object. The object is loaded with the
    //!                 default register values (ClockSource::DISABLED and
    //!                 Mode::NORMAL). The object still must be initialized
    //!                 before use.
    //! \see        init(Mode mode_p, ClockSource clockSource_p).
    //!
    Timer0(
            void
    );

    //!
    //! \brief      Timer0 class destructor.
    //! \details    Destroys a Timer0 object.
    //!
    ~Timer0(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     INITIALIZATION    ////////////////////     //
    //!
    //! \brief      Initializes the TIMER0 module.
    //! \details    Initializes the TIMER0 module.
    //! \param[in]  mode_p              Operation mode.
    //! \param[in]  clockSource_p       Clock source and prescaler.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t init(
            const Mode mode_p,
            const ClockSource clockSource_p
    );

    //!
    //! \brief      Configures the clock source and the clock prescaler.
    //! \details    Configures the clock source and the clock prescaler.
    //! \param      clockSource_p       Clock source and prescaler.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setClockSource(
            ClockSource clockSource_p
    );

    //!
    //! \brief      Configures the operation mode.
    //! \details    Configures the operation mode.
    //! \param      mode_p              Operation mode.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setMode(
            Mode mode_p
    );

    //!
    //! \brief      Configures the desired behavior of OCR0x pins during compare match.
    //! \details    Configures the desired behavior of OCR0x pins during compare match.
    //! \param      compA_p             Behavior of OCR0A pin during a compare A match.
    //! \param      compB_p             Behavior of OCR0B pin during a compare B match.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setOutputMode(
            OutputMode compA_p,
            OutputMode compB_p
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

    //     /////////////////////     COMPARE A     //////////////////////     //
    //!
    //! \brief      Activates Compare A Match interrupt.
    //! \details    Activates Compare A Match interrupt. If an interrupt request
    //!                 is pending, an interrupt will be triggered when
    //!                 activated. In most applications, it is recommended to
    //!                 ignore an old interrupt request prior to activate the
    //!                 interrupt. This can be done by calling \ref
    //!                 clearCompareAInterruptRequest() function imediatelly
    //!                 before activating the interrupt.
    //!
    void inlined activateCompareAInterrupt(
            void
    );

    //!
    //! \brief      Clears Compare A Match interrupt flag
    //! \details    Clears Compare A Match interrupt flag, dismissing any
    //!                 pending interrupt request.
    //!
    void inlined clearCompareAInterruptRequest(
            void
    );

    //!
    //! \brief      Deactivates Compare A Match interrupt.
    //! \details    Deactivates Compare A Match interrupt. This function does
    //!                 not clears any pending interrupt request.
    //!
    void inlined deactivateCompareAInterrupt(
            void
    );

    //!
    //! \brief      Forces a Compare A Match condition on output pin.
    //! \details    Forces a Compare A Match condition on output pin. No
    //!                 interrupt will be generated.
    //!
    void inlined forceCompareA(
            void
    );

    //!
    //! \brief      Gets Compare A Match value.
    //! \details    Gets Compare A Match value.
    //!
    uint8_t inlined getCompareAValue(
            void
    );

    //!
    //! \brief      Sets Compare A Match value.
    //! \details    Sets Compare A Match value.
    //!
    void inlined setCompareAValue(
            uint8_t value_p
    );

    //     /////////////////////     COMPARE B     //////////////////////     //
    //!
    //! \brief      Activates Compare B Match interrupt.
    //! \details    Activates Compare B Match interrupt. If an interrupt request
    //!                 is pending, an interrupt will be triggered when
    //!                 activated. In most applications, it is recommended to
    //!                 ignore an old interrupt request prior to activate the
    //!                 interrupt. This can be done by calling \ref
    //!                 clearCompareBInterruptRequest() function imediatelly
    //!                 before activating the interrupt.
    //!
    void inlined activateCompareBInterrupt(
            void
    );

    //!
    //! \brief      Clears Compare B Match interrupt flag.
    //! \details    Clears Compare B Match interrupt flag, dismissing any
    //!                 pending interrupt request.
    //!
    void inlined clearCompareBInterruptRequest(
            void
    );

    //!
    //! \brief      Deactivates Compare B Match interrupt.
    //! \details    Deactivates Compare B Match interrupt. This function does
    //!                 not clears any pending interrupt request.
    //!
    void inlined deactivateCompareBInterrupt(
            void
    );

    //!
    //! \brief      Forces a Compare B Match condition on output pin.
    //! \details    Forces a Compare B Match condition on output pin. No
    //!                 interrupt will be generated.
    //!
    void inlined forceCompareB(
            void
    );

    //!
    //! \brief      Gets Compare B Match value.
    //! \details    Gets Compare B Match value.
    //!
    uint8_t inlined getCompareBValue(
            void
    );

    //!
    //! \brief      Sets Compare B Match value.
    //! \details    Sets Compare B Match value.
    //!
    void inlined setCompareBValue(
            uint8_t value_p
    );

    //     //////////////////////     OVERFLOW    ///////////////////////     //
    //!
    //! \brief      Activates Overflow interrupt.
    //! \details    Activates Overflow interrupt. If an interrupt request
    //!                 is pending, an interrupt will be triggered when
    //!                 activated. In most applications, it is recommended to
    //!                 ignore an old interrupt request prior to activate the
    //!                 interrupt. This can be done by calling \ref
    //!                 clearOverflowInterruptRequest() function imediatelly
    //!                 before activating the interrupt.
    //!
    void inlined activateOverflowInterrupt(
            void
    );

    //!
    //! \brief      Clears Overflow interrupt flag.
    //! \details    Clears Overflow interrupt flag, dismissing any pending
    //!                 interrupt request.
    //!
    void inlined clearOverflowInterruptRequest(
            void
    );

    //!
    //! \brief      Deactivates Overflow Match interrupt.
    //! \details    Deactivates Overflow Match interrupt. This function does
    //!                 not clears any pending interrupt request.
    //!
    void inlined deactivateOverflowInterrupt(
            void
    );

    //!
    //! \brief      Gets counter value.
    //! \details    Gets counter value.
    //!
    uint8_t inlined getCounterValue(
            void
    );

    //!
    //! \brief      Sets counter value.
    //! \details    Sets counter value.
    //!
    void inlined setCounterValue(
            uint8_t value_p
    );

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
private:
    bool_t          _isInitialized      : 1;
    ClockSource     _clockSource;
    Mode            _mode;
    Error           _lastError;
}; // class Timer0

// =============================================================================
// Inlined class functions
// =============================================================================

//!
//! \cond
//!

//     ///////////////////////     COMPARE A     ////////////////////////     //
void inlined Timer0::activateCompareAInterrupt(void)
{
    setBit(TIMSK0, OCIE0A);
    return;
}

void inlined Timer0::clearCompareAInterruptRequest(void)
{
    setBit(TIFR0, OCF0A);
    return;
}

void inlined Timer0::deactivateCompareAInterrupt(void)
{
    clrBit(TIMSK0, OCIE0A);
    return;
}

void inlined Timer0::forceCompareA(void)
{
    setBit(TCCR0B, FOC0A);
    return;
}

uint8_t inlined Timer0::getCompareAValue(void)
{
    return OCR0A;
}

void inlined Timer0::setCompareAValue(uint8_t value_p)
{
    OCR0A = value_p;
    return;
}

//     ///////////////////////     COMPARE B     ////////////////////////     //

void inlined Timer0::activateCompareBInterrupt(void)
{
    setBit(TIMSK0, OCIE0B);
    return;
}

void inlined Timer0::clearCompareBInterruptRequest(void)
{
    setBit(TIFR0, OCF0B);
    return;
}

void inlined Timer0::deactivateCompareBInterrupt(void)
{
    clrBit(TIMSK0, OCIE0B);
    return;
}

void inlined Timer0::forceCompareB(void)
{
    setBit(TCCR0B, FOC0B);
    return;
}

uint8_t inlined Timer0::getCompareBValue(void)
{
    return OCR0B;
}

void inlined Timer0::setCompareBValue(uint8_t value_p)
{
    OCR0B = value_p;
    return;
}

//     ////////////////////////     OVERFLOW    /////////////////////////     //

void inlined Timer0::activateOverflowInterrupt(void)
{
    setBit(TIMSK0, TOIE0);
    return;
}

void inlined Timer0::clearOverflowInterruptRequest(void)
{
    setBit(TIFR0, TOV0);
    return;
}

void inlined Timer0::deactivateOverflowInterrupt(void)
{
    clrBit(TIMSK0, TOIE0);
    return;
}

uint8_t inlined Timer0::getCounterValue(void)
{
    return TCNT0;
}

void inlined Timer0::setCounterValue(uint8_t value_p)
{
    TCNT0 = value_p;
    return;
}

//!
//! \endcond
//!

// =============================================================================
// External global variables
// =============================================================================

//!
//! \brief          Timer0 peripheral handler object.
//! \details        Timer0 peripheral handler object.
//! \warning        Use this object to handle the peripheral. DO NOT create
//!                     another instance of the class, since this could lead to
//!                     information mismatch between instances and the
//!                     peripheral registers.
//!
extern Timer0 timer0;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/Timer0"
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

#endif  // __FUNSAPE_LIB_TIMER0_HPP

// =============================================================================
// END OF FILE
// =============================================================================
