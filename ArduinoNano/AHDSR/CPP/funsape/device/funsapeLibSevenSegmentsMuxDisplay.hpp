//!
//! \file           funsapeLibSevenSegmentsMuxDisplay.hpp
//! \brief          Seven Segments Multiplexed Display module interface for the
//!                     FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-07-10
//! \version        24.07
//! \copyright      license
//! \details        Seven segments multiplexed display controller with support
//!                     to variable number of digits (2 to 8). The library
//!                     supports both common anode and common cathode displays,
//!                     decimal point, and the special characters defined in
//!                     sevenSegmentsDisplay.hpp
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_SEVEN_SEGMENTS_MUX_DISPLAY_HPP
#define __FUNSAPE_LIB_SEVEN_SEGMENTS_MUX_DISPLAY_HPP    2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE     /////////////////     //

#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_SEVEN_SEGMENTS_MUX_DISPLAY_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_SEVEN_SEGMENTS_MUX_DISPLAY_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

#include "../peripheral/funsapeLibGpioBus.hpp"
#ifndef __FUNSAPE_LIB_GPIO_BUS_HPP
#   error "Header file (funsapeLibGpioBus.hpp) is corrupted!"
#elif __FUNSAPE_LIB_GPIO_BUS_HPP != __FUNSAPE_LIB_SEVEN_SEGMENTS_MUX_DISPLAY_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibGpioBus.hpp)!"
#endif

#include "funsapeLibSevenSegmentsDisplay.hpp"
#if !defined(__FUNSAPE_LIB_SEVEN_SEGMENTS_DISPLAY_HPP)
#   error "Header file (funsapeLibSevenSegmentsDisplay.hpp) is corrupted!"
#elif __FUNSAPE_LIB_SEVEN_SEGMENTS_DISPLAY_HPP != __FUNSAPE_LIB_SEVEN_SEGMENTS_MUX_DISPLAY_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibSevenSegmentsDisplay.hpp)!"
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

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
// Classes
// =============================================================================

//!
//! \brief          SevenSegmentsMuxDisplay class
//! \details        This class can handle multiplexed seven segments displays,
//!                     from 2 to 8 digits.
//!
class SevenSegmentsMuxDisplay
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //!
    //! \brief      Number of digits
    //! \details    Use this enumeration to configure the number of digits of
    //!                 the multiplexed display.
    //!
    enum class Digits {
        DIGITS_2                        = 2,
        DIGITS_3                        = 3,
        DIGITS_4                        = 4,
        DIGITS_5                        = 5,
        DIGITS_6                        = 6,
        DIGITS_7                        = 7,
        DIGITS_8                        = 8,
    };

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief          SevenSegmentsMuxDisplay constructor
    //! \details        Creates a SevenSegmentsMuxDisplay object
    //!
    SevenSegmentsMuxDisplay(
            void
    );

    //!
    //! \brief          SevenSegmentsMuxDisplay destructor
    //! \details        Destroys a SevenSegmentsMuxDisplay object
    //!
    ~SevenSegmentsMuxDisplay(
            void
    );

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:

    //     ///////////////////     CONFIGURATION     ////////////////////     //

    //!
    //! \brief      Initializes a SevenSegmentsMuxDisplay object
    //! \details    This function initializes the SevenSegmentsMuxDisplay
    //!                 object, setting the display size and configuration.
    //! \param      numberOfDigits_p            Display size
    //! \param      displayType_p               Display configuration
    //! \return     bool_t                      True on success, False on failure
    //!
    bool_t init(
            Digits numberOfDigits_p,
            SevenSegmentsDisplayType displayType_p
    );

    //!
    //! \brief      Set data and control ports
    //! \details    This function sets the data and control port registers and
    //!                 pins.
    //! \param      dataPort_p                  Pointer to GpioBus controller of data port
    //! \param      controlPort_p               Pointer to GpioBus controller of control port
    //! \param      displayTurnOnLevel_p        Display activation logic level
    //! \return     bool_t                      True on success, False on failure
    //!
    bool_t setPorts(
            GpioBus *dataPort_p,
            GpioBus *controlPort_p,
            LogicLevel displayTurnOnLevel_p
    );

    //!
    //! \brief      Shows next digit of the display
    //! \details    This function turns current digit off and turns on the next
    //!             digit of the display
    //! \return     bool_t                      True on success, False on failure
    //!
    bool_t showNextDigit(
            void
    );

    //!
    //! \brief      Updates display digit values
    //! \details    This function updates the current value to be shown on the
    //!                 display.
    //! \param      digitValues_p               Array of digit values to be shown
    //! \param      digitPoints_p               Array of points to be turned on
    //! \return     bool_t                      True on success, False on failure
    //!
    bool_t updateDigitValues(
            cuint8_t *digitValues_p,
            cbool_t *digitPoints_p = nullptr
    );

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
public:

    // NONE

private:
    //     ///////////////////    DEVICE BUS PORT     ///////////////////     //

    GpioBus                             *_dataGpioBus;
    GpioBus                             *_controlGpioBus;

    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    bool_t                              _isInitialized          : 1;
    bool_t                              _isPortsSet             : 1;
    Error                               _lastError;

    //     ///////////////     HARDWARE CONFIGURATION     ///////////////     //
    SevenSegmentsDisplayType            _displayType            : 1;
    LogicLevel                          _controlActiveLevel     : 1;
    uint8_t                             _digitMax               : 3;
    uint8_t                             _digitIndex             : 3;
    uint8_t                             _digitValue[8];
    bool_t                              _digitPoint[8];

protected:

    // NONE

}; // class SevenSegmentsMuxDisplay

// =============================================================================
// Inlined class functions
// =============================================================================

// NONE

// =============================================================================
// External global variables
// =============================================================================

// NONE

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __FUNSAPE_LIB_SEVEN_SEGMENTS_MUX_DISPLAY_HPP

// =============================================================================
// END OF FILE - funsapeLibSevenSegmentsMuxDisplay.hpp
// =============================================================================
