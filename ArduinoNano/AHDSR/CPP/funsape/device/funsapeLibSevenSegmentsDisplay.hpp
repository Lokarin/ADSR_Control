//!
//! \file           funsapeLibSevenSegmentsDisplay.hpp
//! \brief          Seven Segments Display module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-07-10
//! \version        24.07
//! \copyright      license
//! \details        Seven segments display controller with support to both
//!                     common anode and common cathode displays. The following
//!                     special characters were also implemented: dash, H, i, j,
//!                     L, n, O, P, q, r, S, t, U, y, display off
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_SEVEN_SEGMENTS_DISPLAY_HPP
#define __FUNSAPE_LIB_SEVEN_SEGMENTS_DISPLAY_HPP        2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////    GLOBAL DEFINITIONS FILE     /////////////////     //

#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_SEVEN_SEGMENTS_DISPLAY_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

// NONE

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Devices"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Devices
//! \brief          External devices.
//! \{
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Devices/Seven_Segments_Display"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Seven_Segments_Display
//! \brief          Seven Segments Display controller module.
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

//!
//! \brief          Seven segments code enumeration.
//! \details        Seven segments code enumeration.
//! \warning        The value associate with the symbolic names may change
//!                     between builds and might not reflect the register/bits
//!                     real values. In order to ensure compatibility between
//!                     builds, always refer to the SYMBOLIC NAME, instead of
//!                     the VALUE.
//!
enum class SevenSegmentsCode : uint8_t {
    HEX_0           = 0,                //!< Hexadecimal number 0.
    HEX_1           = 1,                //!< Hexadecimal number 1.
    HEX_2           = 2,                //!< Hexadecimal number 2.
    HEX_3           = 3,                //!< Hexadecimal number 3.
    HEX_4           = 4,                //!< Hexadecimal number 4.
    HEX_5           = 5,                //!< Hexadecimal number 5.
    HEX_6           = 6,                //!< Hexadecimal number 6.
    HEX_7           = 7,                //!< Hexadecimal number 7.
    HEX_8           = 8,                //!< Hexadecimal number 8.
    HEX_9           = 9,                //!< Hexadecimal number 9.
    HEX_A           = 10,               //!< Hexadecimal number A.
    HEX_B           = 11,               //!< Hexadecimal number B.
    HEX_C           = 12,               //!< Hexadecimal number C.
    HEX_D           = 13,               //!< Hexadecimal number D.
    HEX_E           = 14,               //!< Hexadecimal number E.
    HEX_F           = 15,               //!< Hexadecimal number F.
    LETTER_A        = 'A',              //!< Letter A.
    LETTER_B        = 'B',              //!< Letter B.
    LETTER_C        = 'C',              //!< Letter C.
    LETTER_D        = 'D',              //!< Letter D.
    LETTER_E        = 'E',              //!< Letter E.
    LETTER_F        = 'F',              //!< Letter F.
    LETTER_H        = 'H',              //!< Letter H.
    LETTER_I        = 'i',              //!< Letter I.
    LETTER_J        = 'j',              //!< Letter J.
    LETTER_L        = 'L',              //!< Letter L.
    LETTER_N        = 'n',              //!< Letter N.
    LETTER_O        = 'O',              //!< Letter O.
    LETTER_P        = 'P',              //!< Letter P.
    LETTER_Q        = 'q',              //!< Letter Q.
    LETTER_R        = 'r',              //!< Letter R.
    LETTER_S        = 'S',              //!< Letter S.
    LETTER_T        = 't',              //!< Letter T.
    LETTER_U        = 'U',              //!< Letter U.
    LETTER_Y        = 'y',              //!< Letter Y.
    DASH            = '-',              //!< Dash.
    ON              = 0xFD,             //!< Display ON.
    OFF             = 0xFF              //!< Display OFF.
};

//!
//! \brief          Display hardware configuration.
//! \details        Display hardware configuration.
//! \warning        The value associate with the symbolic names may change
//!                     between builds and might not reflect the register/bits
//!                     real values. In order to ensure compatibility between
//!                     builds, always refer to the SYMBOLIC NAME, instead of
//!                     the VALUE.
//!
enum class SevenSegmentsDisplayType : cbool_t {
    COMMON_ANODE    = false,            //!< Common anode displays; negative logic.
    COMMON_CATHODE  = true              //!< Common cathode displays; positive logic.
};

// =============================================================================
// Interrupt callback functions
// =============================================================================

// NONE

// =============================================================================
// Public functions declarations
// =============================================================================

//!
//! \brief          Converts a value to segments code.
//! \details        This function receives a numeric value and decodes it to
//!                     seven segments code, according to given display type,
//!                     with decimal point support.
//! \param[in]      numericValue_p      Numeric value to be converted.
//! \param[in]      point_p             Decimal point status.
//! \param[in]      displayType_p       Display type, defaults to COMMON_ANODE.
//! \return         uint8_t             Returns segments code in 0bPGFEDCBA order.
//!
uint8_t convertToSevenSegments(
        cuint8_t numericValue_p,
        cbool_t point_p,
        SevenSegmentsDisplayType displayType_p = SevenSegmentsDisplayType::COMMON_ANODE
);

//!
//! \brief          Converts a value to segments code.
//! \details        This function receives a coded value and decodes it to
//!                     seven segments code, according to given display type,
//!                     with decimal point support.
//! \param[in]      numericCode_p       Numeric value to be converted.
//! \param[in]      point_p             Decimal point status.
//! \param[in]      displayType_p       Display type, defaults to COMMON_ANODE.
//! \return         uint8_t             Returns segments code in 0bPGFEDCBA order.
//!
uint8_t convertToSevenSegments(
        SevenSegmentsCode numericCode_p,
        cbool_t point_p,
        SevenSegmentsDisplayType displayType_p = SevenSegmentsDisplayType::COMMON_ANODE
);

// =============================================================================
// Classes
// =============================================================================

// NONE

// =============================================================================
// Inlined class functions
// =============================================================================

// NONE

// =============================================================================
// External global variables
// =============================================================================

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Devices/Seven_Segments_Display"
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

#endif  // __FUNSAPE_LIB_SEVEN_SEGMENTS_DISPLAY_HPP

// =============================================================================
// END OF FILE - funsapeLibSevenSegmentsDisplay.hpp
// =============================================================================
