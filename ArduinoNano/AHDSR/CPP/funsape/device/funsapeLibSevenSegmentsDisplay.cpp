//!
//! \file           funsapeLibSevenSegmentsDisplay.cpp
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
// System file dependencies
// =============================================================================

#include "funsapeLibSevenSegmentsDisplay.hpp"
#if !defined(__FUNSAPE_LIB_SEVEN_SEGMENTS_DISPLAY_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_SEVEN_SEGMENTS_DISPLAY_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

// NONE

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Public function declarations
// =============================================================================

uint8_t convertToSevenSegments(SevenSegmentsCode numericCode_p, cbool_t point_p, SevenSegmentsDisplayType displayType_p)
{
    uint8_t aux8 = (uint8_t)numericCode_p;

    return convertToSevenSegments(aux8, point_p, displayType_p);
}

uint8_t convertToSevenSegments(cuint8_t numericValue_p, cbool_t point_p, SevenSegmentsDisplayType displayType_p)
{
    uint8_t auxData = 0;

    switch(numericValue_p) {  //                         0bPGFEDCBA
    case(uint8_t)SevenSegmentsCode::LETTER_O:
    case(uint8_t)SevenSegmentsCode::HEX_0:      auxData = 0b00111111;   break;
    case(uint8_t)SevenSegmentsCode::HEX_1:      auxData = 0b00000110;   break;
    case(uint8_t)SevenSegmentsCode::HEX_2:      auxData = 0b01011011;   break;
    case(uint8_t)SevenSegmentsCode::HEX_3:      auxData = 0b01001111;   break;
    case(uint8_t)SevenSegmentsCode::HEX_4:      auxData = 0b01100110;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_S:
    case(uint8_t)SevenSegmentsCode::HEX_5:      auxData = 0b01101101;   break;
    case(uint8_t)SevenSegmentsCode::HEX_6:      auxData = 0b01111101;   break;
    case(uint8_t)SevenSegmentsCode::HEX_7:      auxData = 0b00000111;   break;
    case(uint8_t)SevenSegmentsCode::HEX_8:      auxData = 0b01111111;   break;
    case(uint8_t)SevenSegmentsCode::HEX_9:      auxData = 0b01101111;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_A:
    case(uint8_t)SevenSegmentsCode::HEX_A:      auxData = 0b01110111;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_B:
    case(uint8_t)SevenSegmentsCode::HEX_B:      auxData = 0b01111100;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_C:
    case(uint8_t)SevenSegmentsCode::HEX_C:      auxData = 0b00111001;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_D:
    case(uint8_t)SevenSegmentsCode::HEX_D:      auxData = 0b01011110;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_E:
    case(uint8_t)SevenSegmentsCode::HEX_E:      auxData = 0b01111001;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_F:
    case(uint8_t)SevenSegmentsCode::HEX_F:      auxData = 0b01110001;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_H:   auxData = 0b01110110;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_I:   auxData = 0b00000100;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_J:   auxData = 0b00011110;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_L:   auxData = 0b00111000;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_N:   auxData = 0b01010100;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_P:   auxData = 0b01110011;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_Q:   auxData = 0b01100111;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_R:   auxData = 0b01010000;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_T:   auxData = 0b01111000;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_U:   auxData = 0b00111110;   break;
    case(uint8_t)SevenSegmentsCode::LETTER_Y:   auxData = 0b01101110;   break;
    case(uint8_t)SevenSegmentsCode::DASH:       auxData = 0b01000000;   break;
    case(uint8_t)SevenSegmentsCode::ON:         auxData = 0b11111111;   break;
    case(uint8_t)SevenSegmentsCode::OFF:        auxData = 0b00000000;   break;
    default:                                    auxData = 0b00000000;   break;
    }
    if(point_p) {
        setBit(auxData, 7);
    }
    auxData = (displayType_p == SevenSegmentsDisplayType::COMMON_CATHODE) ? auxData : (~auxData);

    return auxData;
}

// =============================================================================
// Interrupt callback functions
// =============================================================================

// NONE

// =============================================================================
// Interrupt handlers
// =============================================================================

// NONE

// =============================================================================
// END OF FILE - funsapeLibSevenSegmentsDisplay.cpp
// =============================================================================
