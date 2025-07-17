//!
//! \file           funsapeLibTimer1.hpp
//! \brief          TIMER1 peripheral control for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        TIMER1 peripheral control for the FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_TIMER1_HPP
#define __FUNSAPE_LIB_TIMER1_HPP                            2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#    error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_TIMER1_HPP
#    error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_TIMER1_HPP
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
// Doxygen: Start subgroup "Peripherals/Timer1"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Timer1
//! \brief          Timer/Counter 1 (TIMER1) controller module.
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
//! \brief          TIMER1 compare A match interrupt callback function.
//! \details        This function is called when the TIMER1 compare A match
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer1CompareACallback(void);

//!
//! \brief          TIMER1 compare B match interrupt callback function.
//! \details        This function is called when the TIMER1 compare B match
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer1CompareBCallback(void);

//!
//! \brief          TIMER1 Input Capture interrupt callback function.
//! \details        This function is called when the TIMER1 input capture
//!                     interrupt is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer1InputCaptureCallback(void);

//!
//! \brief          TIMER1 overflow interrupt callback function.
//! \details        This function is called when the TIMER1 overflow interrupt
//!                     is treated. It is a weak function that can be
//!                     overwritten by user code.
//!
void timer1OverflowCallback(void);

// =============================================================================
// Timer1 Class
// =============================================================================

//!
//! \brief          Timer1 class.
//! \details        This class manages the Timer/Counter 1 (TIMER1)
//!                     peripheral.
//! \warning        An instance of this class is already defined as a global
//!                     object. Therefore, there is not necessary, neither
//!                     recommended to create another object of this class.
//!
class Timer1
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     ////////////////     TIMER1 Clock Source     /////////////////     //
    //!
    //! \brief      Clock source enumeration.
    //! \details    Clock prescaler options associated with TIMER1.
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
        T1_FALLING_EDGE             = 6,    //!< Timer clock will be based on the falling edge of a signal placed on T1 pin.
        T1_RISING_EDGE              = 7     //!< Timer clock will be based on the rising edge of a signal placed on T1 pin.
    };

    //     ////////////////////     TIMER1 Mode     /////////////////////     //
    //!
    //! \brief      Operation Mode enumeration.
    //! \details    Operation Mode options associated with TIMER1.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class Mode : uint8_t {
        NORMAL                          = 0,    //!< Normal mode (direction = UP / TOP = 0x00FF / UPDATE OCR1x = immediate / TOV Flag = 0xFFFF).
        PWM_PHASE_CORRECTED_8_BITS      = 1,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = 0x00FF / UPDATE OCR1x = 0x00FF / TOV Flag = 0x0000).
        PWM_PHASE_CORRECTED_9_BITS      = 2,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = 0x01FF / UPDATE OCR1x = 0x01FF / TOV Flag = 0x0000).
        PWM_PHASE_CORRECTED_10_BITS     = 3,    //!< PWM mode with phase correction (direction = DOWN then UP / TOP = 0x03FF / UPDATE OCR1x = 0x03FF / TOV Flag = 0x0000).
        CTC_OCRA                        = 4,    //!< CTC mode (direction = UP / TOP = OCR1A / UPDATE OCR1x = immediate / TOV Flag = 0xFFFF).
        PWM_FAST_8_BITS                 = 5,    //!< PWM mode fast (direction = UP / TOP = 0x00FF / UPDATE OCR1x = 0x0000 / TOV Flag = 0x00FF).
        PWM_FAST_9_BITS                 = 6,    //!< PWM mode fast (direction = UP / TOP = 0x01FF / UPDATE OCR1x = 0x0000 / TOV Flag = 0x01FF).
        PWM_FAST_10_BITS                = 7,    //!< PWM mode fast (direction = UP / TOP = 0x03FF / UPDATE OCR1x = 0x0000 / TOV Flag = 0x03FF).
        PWM_PHASE_FREQ_CORRECTED_ICR    = 8,    //!< PWM mode with phase and frequency correction (direction = UP then DOWN / TOP = ICR1 / UPDATE OCR1x = 0x0000 / TOV Flag = 0x0000).
        PWM_PHASE_FREQ_CORRECTED_OCRA   = 9,    //!< PWM mode with phase and frequency correction (direction = UP then DOWN / TOP = OCR1A / UPDATE OCR1x = 0x0000 / TOV Flag = 0x0000).
        PWM_PHASE_CORRECTED_ICR         = 10,   //!< PWM mode with phase correction (direction = DOWN then UP / TOP = ICR1 / UPDATE OCR1x = ICR1 / TOV Flag = 0x0000).
        PWM_PHASE_CORRECTED_OCRA        = 11,   //!< PWM mode with phase correction (direction = DOWN then UP / TOP = OCR1A / UPDATE OCR1x = OCR1A / TOV Flag = 0x0000).
        CTC_ICR                         = 12,    //!< CTC mode (direction = UP / TOP = ICR1A / UPDATE OCR1x = immediate / TOV Flag = 0xFFFF).
        // RESERVED                     = 13,
        PWM_FAST_ICR                    = 14,   //!< PWM mode fast (direction = UP / TOP = ICR1 / UPDATE OCR1x = 0x0000 / TOV Flag = 0xFFFF).
        PWM_FAST_OCRA                   = 15    //!< PWM mode fast (direction = UP / TOP = OCR1A / UPDATE OCR1x = 0x0000 / TOV Flag = 0xFFFF).
    };

    //     /////////////////     TIMER1 Output Mode    //////////////////     //
    //!
    //! \brief      Output Mode enumeration.
    //! \details    Output Mode options associated with TIMER1.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class OutputMode : uint8_t {
        NORMAL                          = 0,    //!< OC1x disabled. Normal port operation.
        TOGGLE_ON_COMPARE               = 1,    //!< OC1x will toggle on OCR1x compare match.
        CLEAR_ON_COMPARE                = 2,    //!< OC1x will clear on OCR1x compare match.
        SET_ON_COMPARE                  = 3,    //!< OC1x will set on OCR1x compare match.
        NON_INVERTING_MODE              = 2,    //!< OC1x will produce a non-inverted PWM signal.
        INVERTING_MODE                  = 3,    //!< OC1x will produce a inverted PWM signal.
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Timer1 class constructor.
    //! \details    Creates a Timer1 object. The object is loaded with the
    //!                 default register values (ClockSource::DISABLED and
    //!                 Mode::NORMAL). The object still must be initialized
    //!                 before use.
    //! \see        init(Mode mode_p, ClockSource clockSource_p).
    //!
    Timer1(
            void
    );

    //!
    //! \brief      Timer1 class destructor.
    //! \details    Destroys a Timer1 object.
    //!
    ~Timer1(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     INITIALIZATION    ////////////////////     //
    //!
    //! \brief      Initializes the TIMER1 module.
    //! \details    Initializes the TIMER1 module.
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
            const ClockSource clockSource_p
    );

    //!
    //! \brief      Configures the input capture mode.
    //! \details    Configures the input capture mode.
    //! \param      edgeSelection_p     edge of the input capture signal.
    //! \param      noiseCanceler_p     state of the noise canceler circuit.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setInputCaptureMode(
            const Edge edgeSelection_p,
            cbool_t noiseCanceler_p
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
            const Mode mode_p
    );

    //!
    //! \brief      Configures the desired behavior of OCR1x pins during compare match.
    //! \details    Configures the desired behavior of OCR1x pins during compare match.
    //! \param      compA_p             Behavior of OCR1A pin during a compare A match.
    //! \param      compB_p             Behavior of OCR1B pin during a compare B match.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setOutputMode(
            const OutputMode compA_p,
            const OutputMode compB_p
    );

    //     /////////////////     CONTROL AND STATUS    //////////////////     //
    //!
    //! \brief      Returns the last error.
    //! \details    Returns the last error.
    //! \return     Error               Error status of the last operation.
    //!
    Error getLastError(
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
    uint16_t inlined getCompareAValue(
            void
    );

    //!
    //! \brief      Sets Compare A Match value.
    //! \details    Sets Compare A Match value.
    //!
    void inlined setCompareAValue(
            cuint16_t value_p
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
    uint16_t inlined getCompareBValue(
            void
    );

    //!
    //! \brief      Sets Compare B Match value.
    //! \details    Sets Compare B Match value.
    //!
    void inlined setCompareBValue(
            cuint16_t value_p
    );

    //     ///////////////////     INPUT CAPTURE     ////////////////////     //
    //!
    //! \brief      Activates Input Capture interrupt.
    //! \details    Activates Input Capture interrupt. If an interrupt request
    //!                 is pending, an interrupt will be triggered when
    //!                 activated. In most applications, it is recommended to
    //!                 ignore an old interrupt request prior to activate the
    //!                 interrupt. This can be done by calling \ref
    //!                 clearInputCaptureInterruptRequest() function imediatelly
    //!                 before activating the interrupt.
    //!
    void inlined activateInputCaptureInterrupt(
            void
    );

    //!
    //! \brief      Clears Input Capture interrupt flag.
    //! \details    Clears Input Capture interrupt flag, dismissing any
    //!                 pending interrupt request.
    //!
    void inlined clearInputCaptureInterruptRequest(
            void
    );

    //!
    //! \brief      Deactivates Input Capture interrupt.
    //! \details    Deactivates Input Capture interrupt. This function does
    //!                 not clears any pending interrupt request.
    //!
    void inlined deactivateInputCaptureInterrupt(
            void
    );

    //!
    //! \brief      Gets Input Capture value.
    //! \details    Gets Input Capture value.
    //!
    uint16_t inlined getInputCaptureValue(
            void
    );

    //!
    //! \brief      Sets Input Capture value.
    //! \details    Sets Input Capture value.
    //!
    void inlined setInputCaptureValue(
            cuint16_t value_p
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
    uint16_t inlined getCounterValue(
            void
    );

    //!
    //! \brief      Sets counter value.
    //! \details    Sets counter value.
    //!
    void inlined setCounterValue(
            cuint16_t value_p
    );

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
private:
    bool_t          _isInitialized      : 1;
    ClockSource     _clockSource;
    Mode            _mode;
    Error           _lastError;
}; // class Timer1

// =============================================================================
// Inlined class functions
// =============================================================================

//!
//! \cond
//!

//     ///////////////////////     COMPARE A     ////////////////////////     //
void inlined Timer1::activateCompareAInterrupt(void)
{
    setBit(TIMSK1, OCIE1A);
    return;
}

void inlined Timer1::clearCompareAInterruptRequest(void)
{
    setBit(TIFR1, OCF1A);
    return;
}

void inlined Timer1::deactivateCompareAInterrupt(void)
{
    clrBit(TIMSK1, OCIE1A);
    return;
}

void inlined Timer1::forceCompareA(void)
{
    setBit(TCCR1C, FOC1A);
    return;
}

uint16_t inlined Timer1::getCompareAValue(void)
{
    uint16_t aux16 = 0;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        aux16 = OCR1A;
    }
    return aux16;
}

void inlined Timer1::setCompareAValue(cuint16_t value_p)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        OCR1A = value_p;
    }
    return;
}

//     ///////////////////////     COMPARE B     ////////////////////////     //

void inlined Timer1::activateCompareBInterrupt(void)
{
    setBit(TIMSK1, OCIE1B);
    return;
}

void inlined Timer1::clearCompareBInterruptRequest(void)
{
    setBit(TIFR1, OCF1B);
    return;
}

void inlined Timer1::deactivateCompareBInterrupt(void)
{
    clrBit(TIMSK1, OCIE1B);
    return;
}

void inlined Timer1::forceCompareB(void)
{
    setBit(TCCR1C, FOC1B);
    return;
}

uint16_t inlined Timer1::getCompareBValue(void)
{
    uint16_t aux16 = 0;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        aux16 = OCR1B;
    }
    return aux16;
}

void inlined Timer1::setCompareBValue(cuint16_t value_p)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        OCR1B = value_p;
    }
    return;
}

//     /////////////////////     INPUT CAPTURE     //////////////////////     //

inlined void Timer1::activateInputCaptureInterrupt(void)
{
    setBit(TIMSK1, ICIE1);
    return;
}

inlined void Timer1::clearInputCaptureInterruptRequest(void)
{
    setBit(TIFR1, ICF1);
    return;
}

inlined void Timer1::deactivateInputCaptureInterrupt(void)
{
    clrBit(TIMSK1, ICIE1);
    return;
}

inlined uint16_t Timer1::getInputCaptureValue(void)
{
    uint16_t aux16 = 0;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        aux16 = ICR1;
    }
    return aux16;
}

inlined void Timer1::setInputCaptureValue(cuint16_t value_p)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ICR1 = value_p;
    }
    return;
}

//     ////////////////////////     OVERFLOW    /////////////////////////     //

void inlined Timer1::activateOverflowInterrupt(void)
{
    setBit(TIMSK1, TOIE1);
    return;
}

void inlined Timer1::clearOverflowInterruptRequest(void)
{
    setBit(TIFR1, TOV1);
    return;
}

void inlined Timer1::deactivateOverflowInterrupt(void)
{
    clrBit(TIMSK1, TOIE1);
    return;
}

uint16_t inlined Timer1::getCounterValue(void)
{
    uint16_t aux16 = 0;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        aux16 = TCNT1;
    }
    return aux16;
}

void inlined Timer1::setCounterValue(cuint16_t value_p)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        TCNT1 = value_p;
    }
    return;
}

//!
//! \endcond
//!

// =============================================================================
// External global variables
// =============================================================================

//!
//! \brief          Timer1 peripheral handler object.
//! \details        Timer1 peripheral handler object.
//! \warning        Use this object to handle the peripheral. DO NOT create
//!                     another instance of the class, since this could lead to
//!                     information mismatch between instances and the
//!                     peripheral registers.
//!
extern Timer1 timer1;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/Timer1"
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

#endif  // __FUNSAPE_LIB_TIMER1_HPP

// =============================================================================
// END OF FILE
// =============================================================================
