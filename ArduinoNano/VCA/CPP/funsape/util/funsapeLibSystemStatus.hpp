//!
//! \file           funsapeLibSystemStatus.hpp
//! \brief          System function support to Funsape AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        This file provides support to system-wide features for all
//!                     modules of the Funsape AVR8 Library
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_SYSTEM_STATUS_HPP
#define __FUNSAPE_LIB_SYSTEM_STATUS_HPP         2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_SYSTEM_STATUS_HPP
#   error "Version mismatch between file header and global definitions file!"
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
// Doxygen: Start subgroup "Peripherals/System_Status"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     System_Status
//! \brief          System Status and Control controller module.
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
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// SystemStatus Class
// =============================================================================

//!
//! \brief          SystemStatus class.
//! \details        This class manages the System Status and Controls the System
//!                     Clock.
//! \warning        An instance of this class is already defined as a global
//!                     object. Therefore, there is not necessary, neither
//!                     recommended to create another object of this class.
//!
class SystemStatus
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:
    //     ///////////////    SYSTEM CLOCK PRESCALER    /////////////////     //
    //!
    //! \brief      System Clock prescaler enumeration.
    //! \details    Clock prescaler options associated with MCU System.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead of
    //!                 the VALUE.
    //!
    enum class ClockPrescaler {
        PRESCALER_1                     = 0,    //!< Prescaler off. System clock is not divided.
        PRESCALER_2                     = 1,    //!< I/O clock frequency will be System Clock divided by 2.
        PRESCALER_4                     = 2,    //!< I/O clock frequency will be System Clock divided by 4.
        PRESCALER_8                     = 3,    //!< I/O clock frequency will be System Clock divided by 8.
        PRESCALER_32                    = 4,    //!< I/O clock frequency will be System Clock divided by 32.
        PRESCALER_64                    = 5,    //!< I/O clock frequency will be System Clock divided by 64.
        PRESCALER_128                   = 6,    //!< I/O clock frequency will be System Clock divided by 128.
        PRESCALER_256                   = 7,    //!< I/O clock frequency will be System Clock divided by 256.
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      SystemStatus class constructor.
    //! \details    Creates a SystemStatus object. The object is loaded with the
    //!                 default configuration values (clock = F_CPU,
    //!                 ClockPrescaler::PRESCALER_1). The object starts
    //!                 initialized and is ready to use.
    //! \param[in]  mainClock_p         Value of the system main clock.
    //!
    SystemStatus(
            uint32_t mainClock_p = F_CPU
    );

    //!
    //! \brief      SystemStatus class destructor.
    //! \details    Destroys a SystemStatus object.
    //!
    ~SystemStatus(
            void
    );

    // -------------------------------------------------------------------------
    // Operator overloading ----------------------------------------------------
public:
    // NONE

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - Inherited methods ---------------------------------------------
public:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - Class own methods ---------------------------------------------
public:
    //     /////////////     SYSTEM CLOCK AND PRESCALER     /////////////     //
    //!
    //! \brief          Returns CPU clock.
    //! \details        Returns the value of the main CPU clock.]
    //! \param[out]     cpuClockValue_p Pointer to store the clock value.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t getCpuClock(
            uint32_t *cpuClockValue_p
    );

    //!
    //! \brief          Set system clock prescaler.
    //! \details        Set system clock prescaler.
    //! \param[in]      prescaler_p             Value of the system clock prescaler.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setClockPrescaler(
            ClockPrescaler prescaler_p
    );

    //     //////////////////////    STOPWATCH     //////////////////////     //
    //!
    //! \brief          Returns the elapsed time between marks.
    //! \details        Returns the elapsed time between marks.
    //! \param          setNewMark_p    Erase old time mark.
    //! \return         uint32_t        Elapsed time between marks.
    //!
    inlined uint32_t getElapsedTime(
            bool_t setNewMark_p = true
    );

    //!
    //! \brief          Gets the value of the stopwatch counter.
    //! \details        Gets the value of the stopwatch counter.
    //! \param[out]     stopwatchValue_p    Pointer to store the clock value.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    inlined bool_t getStopwatchValue(
            uint32_t *stopwatchValue_p
    );

    //!
    //! \brief          Increments the stopwatch counter.
    //! \details        Increments the stopwatch counter.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    inlined bool_t incrementStopwatch(
            void
    );

    //!
    //! \brief          Resets the stopwatch counter.
    //! \details        Resets the stopwatch counter.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    inlined bool_t resetStopwatch(
            void
    );

    //!
    //! \brief          Sets a time marker at the stopwatch.
    //! \details        Sets a time marker at the stopwatch.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    inlined bool_t setStopwatchMark(
            void
    );

    //!
    //! \brief          Starts the stopwatch counter.
    //! \details        Starts the stopwatch counter.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    inlined bool_t startStopwatch(
            void
    );

    //!
    //! \brief          Stops the stopwatch counter.
    //! \details        Stops the stopwatch counter.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    inlined bool_t stopStopwatch(
            void
    );


    //     ////////////////////     CHECK STATUS     ////////////////////     //
    //!
    //! \brief      Returns the last error.
    //! \details    Returns the last error.
    //! \return     Error               Error status of the last operation.
    //!
    Error getLastError(
            void
    );

// private:
//     uint32_t _elapsedTime(
//             uint32_t customMark_p
//     );

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
public:
    // NONE

private:
    //     /////////////     SYSTEM CLOCK AND PRESCALER     /////////////     //
    uint32_t        _sourceClockValue;
    ClockPrescaler  _clockPrescaler;
    uint32_t        _cpuClockValue;

    //     //////////////////////    STOPWATCH     //////////////////////     //
    bool_t          _initialized                : 1;
    vuint32_t       _stopwatchValue;
    vuint32_t       _stopwatchMark;
    bool_t          _stopwatchHalted            : 1;

    //     ////////////////////     CHECK STATUS     ////////////////////     //
    Error           _lastError;
}; // class SystemStatus

// =============================================================================
// SystemStatus - Class overloading operators
// =============================================================================

// NONE

// =============================================================================
// SystemStatus - Class inline function definitions
// =============================================================================

//!
//! \cond
//!

inlined bool_t SystemStatus::getStopwatchValue(uint32_t *stopwatchValue_p)
{
    // Checks for errors
    if(!this->_initialized) {
        // Returns error
        this->_lastError                = Error::NOT_INITIALIZED;
        return false;
    }
    if(!isPointerValid(stopwatchValue_p)) {
        // Returns error
        this->_lastError                = Error::ARGUMENT_POINTER_NULL;
        return false;
    }

    // Updates value
    *stopwatchValue_p                   = this->_stopwatchValue;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return true;
}

inlined bool_t SystemStatus::incrementStopwatch(void)
{
    // Checks for errors
    if(!this->_initialized) {
        // Returns error
        this->_lastError                = Error::NOT_INITIALIZED;
        return false;
    }

    // Increments stopwatch value
    if(!this->_stopwatchHalted) {
        this->_stopwatchValue++;
    }

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return true;
}

inlined bool_t SystemStatus::resetStopwatch(void)
{
    // Checks for errors
    if(!this->_initialized) {
        // Returns error
        this->_lastError                = Error::NOT_INITIALIZED;
        return false;
    }

    // Resets stopwatch
    this->_stopwatchValue               = 0;
    this->_stopwatchMark                = 0;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return true;
}

bool_t SystemStatus::setStopwatchMark(void)
{
    // Checks for errors
    if(!this->_initialized) {
        // Returns error
        this->_lastError                = Error::NOT_INITIALIZED;
        return false;
    }

    // Sets stopwatch mark
    this->_stopwatchMark                = this->_stopwatchValue;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return true;
}

inlined bool_t SystemStatus::stopStopwatch(void)
{
    // Checks for errors
    if(!this->_initialized) {
        // Returns error
        this->_lastError                = Error::NOT_INITIALIZED;
        return false;
    }

    // Pauses stopwatch
    this->_stopwatchHalted              = true;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return true;
}

inlined bool_t SystemStatus::startStopwatch(void)
{
    // Checks for errors
    if(!this->_initialized) {
        // Returns error
        this->_lastError                = Error::NOT_INITIALIZED;
        return false;
    }

    // Resumes stopwatch
    this->_stopwatchHalted              = false;

    // Returns successfully
    this->_lastError                    = Error::NONE;
    return true;
}

//!
//! \endcond
//!

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

//!
//! \brief          SystemStatus peripheral handler object.
//! \details        SystemStatus peripheral handler object.
//! \warning        Use this object to handle the peripheral. DO NOT create
//!                     another instance of the class, since this could lead to
//!                     information mismatch between instances and the
//!                     peripheral registers.
//!
extern SystemStatus systemStatus;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/System_Status"
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

#endif  // __FUNSAPE_LIB_SYSTEM_STATUS_HPP

// =============================================================================
// END OF FILE
// =============================================================================
