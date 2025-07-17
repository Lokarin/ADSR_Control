//!
//! \file           funsapeLibPinout.hpp
//! \brief          Microcontroller pinout file for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        Microcontroller support list:
//!                     - ATmegaX8Y (ATmega48, ATmega48A, ATmega48P, ATmega48PA,
//!                         ATmega88, ATmega88A, ATmega88P, ATmega88PA,
//!                         ATmega168, ATmega168A, ATmega168P, ATmega168PA,
//!                         ATmega328, ATmega328P)
//! \todo           Extend support other microcontrollers
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_PINOUT_HPP
#define __FUNSAPE_LIB_PINOUT_HPP                2407

// =============================================================================
// Dependencies
// =============================================================================

//     //////////////////     AVR STANDARD LIBRARY     //////////////////     //
#if defined(_FUNSAPE_PLATFORM_AVR)
#include <avr/io.h>
#endif

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
// Macrofunctions
// =============================================================================

// NONE

// =============================================================================
// Extern global variables
// =============================================================================

// NONE

// =============================================================================
// Inline functions declaration
// =============================================================================

// NONE

// =============================================================================
// Inline functions definitions
// =============================================================================

// NONE

// =============================================================================
// Public functions weakly defined
// =============================================================================

// NONE

// =============================================================================
// Includes Low Level Abstraction Layer
// =============================================================================

// NONE

// =============================================================================
// Microcontroller definitions
// =============================================================================

//     ///////     ATmega48, ATmega48A, ATmega48P, ATmega48PA     ///////     //
//     ///////     ATmega88, ATmega88A, ATmega88P, ATmega88PA     ///////     //
//     /////     ATmega168, ATmega168A, ATmega168P, ATmega168PA     /////     //
//     //////////////////     ATmega328, ATmega328P    //////////////////     //
#if defined(__AVR_ATmega48__)  || defined(__AVR_ATmega48A__)  || defined(__AVR_ATmega48P__)  || defined(__AVR_ATmega48PA__)  || \
    defined(__AVR_ATmega88__)  || defined(__AVR_ATmega88A__)  || defined(__AVR_ATmega88P__)  || defined(__AVR_ATmega88PA__)  || \
    defined(__AVR_ATmega168__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168PA__) || \
    defined(__AVR_ATmega328__) ||                                defined(__AVR_ATmega328P__)

#   define _FUNSAPE_GPIO_PORT_B_EXISTS
#   define _FUNSAPE_GPIO_PORT_C_EXISTS
#   define _FUNSAPE_GPIO_PORT_D_EXISTS
#   define IS_GPIO_ALL_INSTANCE(regAddress)    (bool_t)(        \
        ((regAddress >= &PINB) && (regAddress <= &PORTD))       \
        ? true                                                  \
        : false)
#   define IS_GPIO_ALL_PIN_NUMBER(pinNumber)    (bool_t)(       \
        (pinNumber <= 7)                                        \
        ? true                                                  \
        : false)
#   define getGpioDdrAddress(regAddress)        (ioRegAddress_t)((3 * ((uint16_t)(regAddress - __SFR_OFFSET) / 3)) + __SFR_OFFSET + 1)
#   define getGpioPinAddress(regAddress)        (ioRegAddress_t)((3 * ((uint16_t)(regAddress - __SFR_OFFSET) / 3)) + __SFR_OFFSET + 0)
#   define getGpioPortAddress(regAddress)       (ioRegAddress_t)((3 * ((uint16_t)(regAddress - __SFR_OFFSET) / 3)) + __SFR_OFFSET + 2)
#endif

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __FUNSAPE_LIB_PINOUT_HPP

// =============================================================================
// END OF FILE
// =============================================================================
