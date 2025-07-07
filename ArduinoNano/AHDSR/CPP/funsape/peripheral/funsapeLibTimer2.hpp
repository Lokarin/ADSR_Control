//!
//! \file           funsapeLibTimer2.hpp
//! \brief          TIMER2 peripheral control for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        TIMER2 peripheral control for the FunSAPE AVR8 Library
//! \todo           ASSR and GTCCR2 registers
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_TIMER2_HPP
#define __FUNSAPE_LIB_TIMER2_HPP                2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_TIMER2_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_TIMER2_HPP
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
// Doxygen: Start subgroup "Peripherals/Timer2"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Timer2
//! \brief          Timer/Counter 2 (TIMER2) controller module.
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
//! \brief          TIMER2 compare A match interrupt callback function.
//! \details        This function is called when the TIMER2 compare A match
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer2CompareACallback();

//!
//! \brief          TIMER2 compare B match interrupt callback function.
//! \details        This function is called when the TIMER2 compare B match
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer2CompareBCallback();

//!
//! \brief          TIMER2 overflow interrupt callback function.
//! \details        This function is called when the TIMER2 overflow interrupt
//!                     is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer2OverflowCallback();

// =============================================================================
// Timer2 Class
// =============================================================================

//!
//! \brief          Timer2 class.
//! \details        This class manages the Timer/Counter 2 (TIMER2)
//!                     peripheral.
//! \warning        An instance of this class is already defined as a global
//!                     object. Therefore, there is not necessary, neither
//!                     recommended to create another object of this class.
//!
class Timer2
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     ////////////////     TIMER2 Clock Source     /////////////////     //
    //!
    //! \brief      Clock source enumeration.
    //! \details    Clock prescaler options associated with TIMER2.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class ClockSource : uint8_t {
        DISABLED                        = 0,    //!< Disables clock, timer is off.
        PRESCALER_1                     = 1,    //!< Disables prescaler, timer clock frequency will be equal to CPU clock.
        PRESCALER_8                     = 2,    //!< Timer clock frequency will be CPU clock divided by 8.
        PRESCALER_32                    = 3,    //!< Timer clock frequency will be CPU clock divided by 32.
        PRESCALER_64                    = 4,    //!< Timer clock frequency will be CPU clock divided by 64.
        PRESCALER_128                   = 5,    //!< Timer clock frequency will be CPU clock divided by 128.
        PRESCALER_256                   = 6,    //!< Timer clock frequency will be CPU clock divided by 256.
        PRESCALER_1024                  = 7     //!< Timer clock frequency will be CPU clock divided by 1024.
    };

    //     ////////////////////     TIMER2 Mode     /////////////////////     //
    //!
    //! \brief      Operation Mode enumeration.
    //! \details    Operation Mode options associated with TIMER2.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class Mode : uint8_t {
        NORMAL                          = 0,    //!< Normal mode (direction = UP / TOP = 0xFF / UPDATE OCR2x = immediate / TOV Flag = 0xFF).
        PWM_PHASE_CORRECTED_MAX         = 1,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = 0xFF / UPDATE OCR2x = 0xFF / TOV Flag = 0x00).
        CTC_OCRA                        = 2,    //!< CTC mode (direction = UP / TOP = OCR2A / UPDATE OCR2x = immediate / TOV Flag = 0xFF).
        PWM_FAST_MAX                    = 3,    //!< PWM mode fast (direction = UP / TOP = 0xFF / UPDATE OCR2x = 0x00 / TOV Flag = 0xFF).
        // RESERVED                     = 4,
        PWM_PHASE_CORRECTED_OCRA        = 5,    //!< PWM mode fast (direction = UP / TOP = OCR2A / UPDATE OCR2x = 0x00 / TOV Flag = 0xFF).
        // RESERVED                     = 6,
        PWM_FAST_OCRA                   = 7,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = OCR2A / UPDATE OCR2x = OCR2A / TOV Flag = 0x00).
    };

    //     /////////////////     TIMER2 Output Mode    //////////////////     //
    //!
    //! \brief      Output Mode enumeration.
    //! \details    Output Mode options associated with TIMER2.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class OutputMode : uint8_t {
        NORMAL                          = 0,    //!< OC2x disabled. Normal port operation.
        TOGGLE_ON_COMPARE               = 1,    //!< OC2x will toggle on OCR2x compare match.
        CLEAR_ON_COMPARE                = 2,    //!< OC2x will clear on OCR2x compare match.
        SET_ON_COMPARE                  = 3,    //!< OC2x will set on OCR2x compare match.
        NON_INVERTING_MODE              = 2,    //!< OC2x will produce a non-inverted PWM signal.
        INVERTING_MODE                  = 3,    //!< OC2x will produce a inverted PWM signal.
    };

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:
    //!
    //! \brief      Timer2 class constructor.
    //! \details    Creates a Timer2 object. The object is loaded with the
    //!                 default register values (ClockSource::DISABLED and
    //!                 Mode::NORMAL). The object still must be initialized
    //!                 before use.
    //! \see        init(Mode mode_p, ClockSource clockSource_p).
    //!
    Timer2(
            void
    );

    //!
    //! \brief      Timer2 class destructor.
    //! \details    Destroys a Timer2 object.
    //!
    ~Timer2(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     INITIALIZATION    ////////////////////     //
    //!
    //! \brief      Initializes the TIMER2 module.
    //! \details    Initializes the TIMER2 module.
    //! \param      mode_p              Operation mode.
    //! \param      clockSource_p       Clock source and prescaler.
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
    //! \brief      Configures the desired behavior of OCR2x pins during compare match.
    //! \details    Configures the desired behavior of OCR2x pins during compare match.
    //! \param      compA_p             Behavior of OCR2A pin during a compare A match.
    //! \param      compB_p             Behavior of OCR2B pin during a compare B match.
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
}; // class Timer2

// =============================================================================
// Inlined class functions
// =============================================================================

//!
//! \cond
//!

//     ///////////////////////     COMPARE A     ////////////////////////     //
void inlined Timer2::activateCompareAInterrupt(void)
{
    setBit(TIMSK2, OCIE2A);
    return;
}

void inlined Timer2::clearCompareAInterruptRequest(void)
{
    setBit(TIFR2, OCF2A);
    return;
}

void inlined Timer2::deactivateCompareAInterrupt(void)
{
    clrBit(TIMSK2, OCIE2A);
    return;
}

void inlined Timer2::forceCompareA(void)
{
    setBit(TCCR2B, FOC2A);
    return;
}

uint8_t inlined Timer2::getCompareAValue(void)
{
    return OCR2A;
}

void inlined Timer2::setCompareAValue(uint8_t value_p)
{
    OCR2A = value_p;
    return;
}

//     ///////////////////////     COMPARE B     ////////////////////////     //

void inlined Timer2::activateCompareBInterrupt(void)
{
    setBit(TIMSK2, OCIE2B);
    return;
}

void inlined Timer2::clearCompareBInterruptRequest(void)
{
    setBit(TIFR2, OCF2B);
    return;
}

void inlined Timer2::deactivateCompareBInterrupt(void)
{
    clrBit(TIMSK2, OCIE2B);
    return;
}

void inlined Timer2::forceCompareB(void)
{
    setBit(TCCR2B, FOC2B);
    return;
}

uint8_t inlined Timer2::getCompareBValue(void)
{
    return OCR2B;
}

void inlined Timer2::setCompareBValue(uint8_t value_p)
{
    OCR2B = value_p;
    return;
}

//     ////////////////////////     OVERFLOW    /////////////////////////     //

void inlined Timer2::activateOverflowInterrupt(void)
{
    setBit(TIMSK2, TOIE2);
    return;
}

void inlined Timer2::clearOverflowInterruptRequest(void)
{
    setBit(TIFR2, TOV2);
    return;
}

void inlined Timer2::deactivateOverflowInterrupt(void)
{
    clrBit(TIMSK2, TOIE2);
    return;
}

uint8_t inlined Timer2::getCounterValue(void)
{
    return TCNT2;
}

void inlined Timer2::setCounterValue(uint8_t value_p)
{
    TCNT2 = value_p;
    return;
}

// TODO: ASSR register
// TODO: GTCCR2 register

//!
//! \endcond
//!

// =============================================================================
// External global variables
// =============================================================================

//!
//! \brief          Timer2 peripheral handler object.
//! \details        Timer2 peripheral handler object.
//! \warning        Use this object to handle the peripheral. DO NOT create
//!                     another instance of the class, since this could lead to
//!                     information mismatch between instances and the
//!                     peripheral registers.
//!
extern Timer2 timer2;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/Timer2"
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

#endif  // __FUNSAPE_LIB_TIMER2_HPP

// =============================================================================
// END OF FILE
// =============================================================================
