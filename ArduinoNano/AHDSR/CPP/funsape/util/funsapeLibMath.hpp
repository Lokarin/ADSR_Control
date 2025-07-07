//!
//! \file           funsapeLibMath.hpp
//! \brief          Math support to Funsape AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        This file ... of the Funsape AVR8 Library
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_MATH_HPP
#define __FUNSAPE_LIB_MATH_HPP                  2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_MATH_HPP
#   error "Version mismatch between file header and global definitions file!"
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
// Interrupt callback functions
// =============================================================================

// NONE

// =============================================================================
// Public functions declarations
// =============================================================================

int16_t     integerHyperbolicSine(int16_t value_p);
int16_t     integerHyperbolicCosine(int16_t value_p);
int16_t     integerHyperbolicTangent(int16_t value_p);
int16_t     integerArcHyperbolicSine(int16_t value_p);
int16_t     integerArcHyperbolicCosine(int16_t value_p);
int16_t     integerArcHyperbolicTangent(int16_t value_p);
uint16_t    integerSqrt(uint16_t value_p);
int16_t     integerLog(int16_t value_p);
int16_t     integerSine(uint16_t angle_p);
int16_t     integerCosine(uint16_t angle_p);
int16_t     integerTangent(uint16_t angle_p);
uint16_t    integerArcSine(int16_t value_p);
uint16_t    integerArcCosine(int16_t value_p);
uint16_t    integerArcTangent(int16_t value_p);

// =============================================================================
// Debug Class
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

// =============================================================================
// Include guard (END)
// =============================================================================

#endif // defined(__FUNSAPE_LIB_MATH_HPP)

// =============================================================================
// END OF FILE
// =============================================================================
