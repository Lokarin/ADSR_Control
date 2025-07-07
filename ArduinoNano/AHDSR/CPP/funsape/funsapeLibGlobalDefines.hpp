//!
//! \file           funsapeLibGlobalDefines.hpp
//! \brief          Global definitions file for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        Global definitions file.
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_GLOBAL_DEFINES_HPP
#define __FUNSAPE_LIB_GLOBAL_DEFINES_HPP        2407

// =============================================================================
// Basic definitions
// =============================================================================

#ifndef F_CPU
#   define F_CPU    16000000UL
#endif

// =============================================================================
// Dependencies
// =============================================================================

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "funsapeLibProjectConfig.hpp"
#ifndef __FUNSAPE_LIB_PROJECT_CONFIG_HPP
#   error [funsapeLibGlobalDefines.hpp] Error - Project configuration file (projectConfig.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_PROJECT_CONFIG_HPP != __FUNSAPE_LIB_GLOBAL_DEFINES_HPP
#   error [funsapeLibGlobalDefines.hpp] Error - Build mismatch between project configuration file (projectConfig.hpp) and global definitions file (funsapeLibGlobalDefines.hpp)!
#endif

//     //////////////////     AVR STANDARD LIBRARY     //////////////////     //
#if defined(_FUNSAPE_PLATFORM_AVR)
#   include <avr/io.h>
#   include <avr/interrupt.h>
#   include <util/delay.h>
#   include <util/atomic.h>
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#if defined(_FUNSAPE_PLATFORM_AVR)
#   include "funsapeLibPinout.hpp"
#   if !defined(__FUNSAPE_LIB_PINOUT_HPP)
#       error "Header file (pinout.hpp) is corrupted!"
#   elif __FUNSAPE_LIB_PINOUT_HPP != __FUNSAPE_LIB_GLOBAL_DEFINES_HPP
#       error "Version mismatch between header file and library dependency (pinout.hpp)!"
#   endif
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Global_Definitions
//! \brief          System global definitions.
//! \{
//!

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Alias" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Alias
//! \brief          Alias definitions.
//! \{
//!

//!
//! \details        Alias to shorten unused attribute.
//!
#define ignored                         __attribute__((unused))
//!
//! \details        Alias to shorten inline attribute.
//!
#define inlined                         inline __attribute__((always_inline))
//!
//! \details        Alias to shorten weak attribute.
//!
#define weakened                        __attribute__((weak))

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Alias" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// =============================================================================
// Macro functions
// =============================================================================

//     //////////////////////     DATA VALIDITY    //////////////////////     //

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Data_Validity" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Data_Validity
//! \brief          Data validation macro-functions.
//! \{
//!

//!
//! \details        Checks if the given parameter is a valid GPIO address.
//! \param[in]      gpioPort            GPIO address
//! \retval         true                GPIO address is valid
//! \retval         false               GPIO address is not valid
//!
#define isGpioAddressValid(gpioPort)    (       \
        (IS_GPIO_ALL_INSTANCE(gpioPort))        \
        ? (bool_t)true                          \
        : (bool_t)false)

//!
//! \details        Checks if the given parameter is a valid GPIO pin index.
//! \param[in]      gpioPin             GPIO pin index
//! \retval         true                GPIO pin index is valid
//! \retval         false               GPIO pin index is not valid
//!
#define isGpioPinIndexValid(gpioPin)    (       \
        (IS_GPIO_ALL_PIN_NUMBER(gpioPin))       \
        ? (bool_t)true                          \
        : (bool_t)false)

//!
//! \details        Checks if the given parameter is a valid pointer address.
//! \param[in]      ptr                 pointer address
//! \retval         true                pointer address is valid
//! \retval         false               pointer address is not valid
//!
#define isPointerValid(ptr)             (       \
        ((void *)(ptr))                         \
        ? (bool_t)true                          \
        : (bool_t)false)

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Data_Validity" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

//     //////////////////////     BIT HANDLING     //////////////////////     //

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Bit_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup Bit_Handling
//! \details        Performs bitwise operations in one bit of a variable or register.
//! \{
//!

#ifndef setBit
//!
//! \details        Sets one bit of a register or variable.
//! \param[in,out]  reg                 register or variable
//! \param[in]      pos                 position of the bit to be set
//! \return         none
//!
#   define setBit(reg, pos)                     do{(reg) |= (1 << (pos));}while(0)
#endif

#ifndef clrBit
//!
//! \details        Clears one bit of a register or variable.
//! \param[in,out]  reg                 register or variable
//! \param[in]      pos                 position of the bit to be cleared
//! \return         none
//!
#   define clrBit(reg, pos)                     do{(reg) &= ~(1 << (pos));}while(0)
#endif

#ifndef cplBit
//!
//! \details        Complements (invert) one bit of a register or variable.
//! \param[in,out]  reg                 register or variable
//! \param[in]      pos                 position of the bit to be complemented
//! \return         none
//!
#   define cplBit(reg, pos)                     do{(reg) ^= (1 << (pos));}while(0)
#endif

//     ///////////////////////     BIT TESTING    ///////////////////////     //
#ifndef isBitSet
//!
//! \details        Verifies if the bit at position <i>pos</i> is set.
//! \param[in]      reg                 register or variable
//! \param[in]      pos                 position of the bit to be evaluated
//! \retval         true                the bit at position <i>pos</i> is set
//! \retval         false               the bit at position <i>pos</i> is cleared
//!
#   define isBitSet(reg, pos)                   (((reg) >> (pos)) & 1)
#endif

#ifndef isBitClr
//!
//! \details        Verifies if the bit at position <i>pos</i> is cleared.
//! \param[in]      reg                 register or variable
//! \param[in]      pos                 position of the bit to be evaluated
//! \retval         true                the bit at position <i>pos</i> is cleared
//! \retval         false               the bit at position <i>pos</i> is set
//!
#   define isBitClr(reg, pos)                   (!isBitSet(reg,pos))
#endif

//     ///////////////////////     BIT LOOPING    ///////////////////////     //
#ifndef waitUntilBitIsSet
//!
//! \details        Prevents the code execution while the bit in position <i>pos</i> is cleared.
//! \param[in]      reg                 register or variable
//! \param[in]      pos                 position of the bit to be evaluated
//! \return         none
//!
#   define waitUntilBitIsSet(reg, pos)          do{     \
        doNothing();                                    \
    } while (isBitClr((reg), (pos)))
#endif

#ifndef waitUntilBitIsClear
//!
//! \details        Prevents the code execution while the bit in position <i>pos</i> is set.
//! \param[in]      reg                 register or variable
//! \param[in]      pos                 position of the bit to be evaluated
//! \return         none
//!
#   define waitUntilBitIsClear(reg, pos)        do{     \
        doNothing();                                    \
    }while(isBitSet((reg), (pos)))
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Bit_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

//     ////////////////////     BIT MASK HANDLING    ////////////////////     //

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Mask_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup Mask_Handling
//! \details        Performs bitwise operations in a set of one bits of a variable or register.
//! \attention      The desired bits of the mask must be always marked as '1', even when the mask is used in a clear operation.
//! \{
//!

#ifndef setMask
//!
//! \details        Sets the bits of a register or variable that are set on the supplied mask.
//! \param[in,out]  reg                 register or variable
//! \param[in]      mask                mask of the bits to be set, marked as one
//! \return         none
//!
#   define setMask(reg, mask)                   do{(reg) |= (mask);}while(0)
#endif

#ifndef clrMask
//!
//! \details        Clears the bits of a register or variable that are set on the supplied mask.
//! \param[in,out]  reg                 register or variable
//! \param[in]      mask                mask of the bits to be cleared, marked as one
//! \return         none
//!
#   define clrMask(reg, mask)                   do{(reg) &= ~(mask);}while(0)
#endif

#ifndef cplMask
//!
//! \details        Complements (inverts) the bits of a register or variable that are set on the supplied mask.
//! \param[in,out]  reg                 register or variable
//! \param[in]      mask                mask of the bits to be complemented, marked as one
//! \return         none
//!
#   define cplMask(reg, mask)                   do{(reg) ^= (mask);}while(0)
#endif

//     ////////////////     BIT MASK OFFSET HANDLING     ////////////////     //
#ifndef setMaskOffset
//!
//! \details        Sets the bits of a register or variable that are set on the supplied mask. The mask is first left-shifted by an offset.
//! \param[in,out]  reg                 register or variable
//! \param[in]      mask                mask of the bits to be set, marked as one
//! \param[in]      offset              left-shift offset value
//! \return         none
//!
#   define setMaskOffset(reg, mask, offset)     do{(reg) |= ((mask) << (offset));}while(0)
#endif

#ifndef clrMaskOffset
//!
//! \details        Clears the bits of a register or variable that are set on the supplied mask. The mask is first left-shifted by an offset.
//! \param[in,out]  reg                 register or variable
//! \param[in]      mask                mask of the bits to be cleared, marked as one
//! \param[in]      offset              left-shift offset value
//! \return         none
//!
#   define clrMaskOffset(reg, mask, offset)     do{(reg) &= ~((mask) << (offset));}while(0)
#endif

#ifndef cplMaskOffset
//!
//! \details        Complements (inverts) the bits of a register or variable that are set on the supplied mask. The mask is first left-shifted by an offset.
//! \param[in,out]  reg                 register or variable
//! \param[in]      mask                mask of the bits to be complemented, marked as one
//! \param[in]      offset              left-shift offset value
//! \return         none
//!
#   define cplMaskOffset(reg, mask, offset)     do{(reg) ^= ((mask) << (offset));}while(0)
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Mask_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

//     ////////////////////     I/O PIN HANDLING     ////////////////////     //

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Pin_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup Pin_Handling
//! \details        Performs basic bitwise operations in an I/O pin.
//! \{
//!
#if defined(_FUNSAPE_PLATFORM_AVR)
#   define clrIoPin(portAddress, portPin)        do{clrBit(*(getGpioPortAddress(portAddress)), portPin);} while(0)
#   define cplIoPin(portAddress, portPin)        do{cplBit(*(getGpioPortAddress(portAddress)), portPin);} while(0)
#   define setIoPin(portAddress, portPin)        do{setBit(*(getGpioPortAddress(portAddress)), portPin);} while(0)
#elif defined(_FUNSAPE_PLATFORM_ARM_STM32)
#   if defined(USE_HAL_DRIVER)
#       define clrIoPin(GPIOx, GPIO_Pin)        do {GPIOx->BRR = (uint32_t)(GPIO_Pin);} while(0)
#       define cplIoPin(GPIOx, GPIO_Pin)        do {((GPIOx->ODR & GPIO_Pin) != 0x00u) ? (GPIOx->BRR = (uint32_t)(GPIO_Pin)) : (GPIOx->BSRR = (uint32_t)(GPIO_Pin));} while(0)
#       define setIoPin(GPIOx, GPIO_Pin)        do {GPIOx->BSRR = (uint32_t)(GPIO_Pin);} while(0)
#   endif
#else
#   define clrIoPin(GPIOx, GPIO_Pin)            {}
#   define cplIoPin(GPIOx, GPIO_Pin)            {}
#   define setIoPin(GPIOx, GPIO_Pin)            {}
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Pin_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Data_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup Data_Handling
//! \details        Performs general data handling, shifting and swapping a variable data.
//! \{
//!

//     /////////////     DATA MANIPULATION (8-BITS WIDE)    /////////////     //
//!
//! \details        Returns the nibble 1 of a byte.
//! \param[in]      dataByte            variable
//! \return         <i>dataByte</i> nibble 1
//!
#define byteGetNibble1(dataByte)        (((dataByte) >> 4) & 0x0F)
//!
//! \details        Returns the nibble 0 of a byte.
//! \param[in]      dataByte            variable
//! \return         <i>dataByte</i>  nibble 0
//!
#define byteGetNibble0(dataByte)        ((dataByte) & 0x0F)
//!
//! \details        Switches the nibbles of a byte.
//! \param[in]      dataByte            variable
//! \return         new variable value
//!
#define byteSwitchNibbles(dataByte)     ((byteGetNibble0(dataByte) << 4) | \
        (byteGetNibble1(dataByte)))

//     ////////////     DATA MANIPULATION (16-BITS WIDE)     ////////////     //
//!
//! \details        Returns the byte 1 of a half-word.
//! \param[in]      dataHword           variable
//! \return         <i>dataHword</i> byte 1
//!
#define hwordGetByte1(dataHword)        (((dataHword) >> 8) & 0x00FF)
//!
//! \details        Returns the byte 0 of a half-word.
//! \param[in]      dataHword           variable
//! \return         <i>dataHword</i> byte 0
//!
#define hwordGetByte0(dataHword)        ((dataHword) & 0x00FF)
//!
//! \details        Switches the bytes of a half-word.
//! \param[in]      dataHword           variable
//! \return         new variable value
//!
#define hwordSwitchBytes(dataHword)     ((hwordGetByte0(dataHword) << 8) | \
        (hwordGetByte1(dataHword)))

//     ////////////     DATA MANIPULATION (32-BITS WIDE)     ////////////     //
//!
//! \details        Returns the byte 3 of a word.
//! \param[in]      dataWord            variable
//! \return         <i>dataWord</i> byte 3
//!
#define wordGetByte3(dataWord)          (((dataWord) >> 24) & 0x000000FF)
//!
//! \details        Returns the byte 2 of a word.
//! \param[in]      dataWord            variable
//! \return         <i>dataWord</i> byte 2
//!
#define wordGetByte2(dataWord)          (((dataWord) >> 16) & 0x000000FF)
//!
//! \details        Returns the byte 1 of a word.
//! \param[in]      dataWord            variable
//! \return         <i>dataWord</i> byte 1
//!
#define wordGetByte1(dataWord)          (((dataWord) >> 8) & 0x000000FF)
//!
//! \details        Returns the byte 0 of a word.
//! \param[in]      dataWord            variable
//! \return         <i>dataWord</i> byte 0
//!
#define wordGetByte0(dataWord)          ((dataWord) & 0x000000FF)

//!
//! \details        Switches the bytes of a word.
//! \param[in]      dataWord            variable
//! \return         new variable value
//!
#define wordSwitchBytes(dataWord)       ((wordGetByte0(dataWord) << 24)  | \
        (wordGetByte1(dataWord) << 16) | \
        (wordGetByte2(dataWord) << 8)  | \
        (wordGetByte3(dataWord)))
//!
//! \details        Returns the half-word 1 of a word.
//! \param[in]      dataWord            variable
//! \return         <i>dataWord</i> half-word 1
//!
#define wordGetHword1(dataWord)         (((dataWord) >> 16) & 0x0000FFFF)
//!
//! \details        Returns the half-word 0 of a word.
//! \param[in]      dataWord            variable
//! \return         <i>dataWord</i> half-word 0
//!
#define wordGetHword0(dataWord)         ((dataWord) & 0x0000FFFF)

//!
//! \details        Switches the half-words of a word.
//! \param[in]      dataWord            variable
//! \return         new variable value
//!
#define wordSwitchHwords(dataWord)      ((wordGetHword0(dataWord) << 16) | \
        (wordGetHword1(dataWord)))

//     ////////////     DATA MANIPULATION (64-BITS WIDE)     ////////////     //
//!
//! \details        Returns the byte 7 of a double-word.
//! \param[in]      dataDword           variable
//! \return         <i>dataDword</i> byte 7
//!
#define dwordGetByte7(dataDword)        (((dataDword) >> 56) & 0x00000000000000FF)
//!
//! \details        Returns the byte 6 of a double-word.
//! \param[in]      dataDword           variable
//! \return         <i>dataDword</i> byte 6
//!
#define dwordGetByte6(dataDword)        (((dataDword) >> 48) & 0x00000000000000FF)
//!
//! \details        Returns the byte 5 of a double-word.
//! \param[in]      dataDword           variable
//! \return         <i>dataDword</i> byte 5
//!
#define dwordGetByte5(dataDword)        (((dataDword) >> 40) & 0x00000000000000FF)
//!
//! \details        Returns the byte 4 of a double-word.
//! \param[in]      dataDword           variable
//! \return         <i>dataDword</i> byte 4
//!
#define dwordGetByte4(dataDword)        (((dataDword) >> 32) & 0x00000000000000FF)
//!
//! \details        Returns the byte 3 of a double-word.
//! \param[in]      dataDword           variable
//! \return         <i>dataDword</i> byte 3
//!
#define dwordGetByte3(dataDword)        (((dataDword) >> 24) & 0x00000000000000FF)
//!
//! \details        Returns the byte 2 of a double-word.
//! \param[in]      dataDword           variable
//! \return         <i>dataDword</i> byte 2
//!
#define dwordGetByte2(dataDword)        (((dataDword) >> 16) & 0x00000000000000FF)
//!
//! \details        Returns the byte 1 of a double-word.
//! \param[in]      dataDword           variable
//! \return         <i>dataDword</i> byte 1
//!
#define dwordGetByte1(dataDword)        (((dataDword) >> 8) & 0x00000000000000FF)
//!
//! \details        Returns the byte 0 of a double-word.
//! \param[in]      dataDword           variable
//! \return         <i>dataDword</i> byte 0
//!
#define dwordGetByte0(dataDword)        ((dataDword) & 0x00000000000000FF)
//!
//! \details        Switches the bytes of a double-word.
//! \param[in]      dataDword           variable
//! \return         new variable value
//!
#define dwordSwitchBytes(dataDword)     ((dwordGetByte0(dataDword) << 56)  | \
        (dwordGetByte1(dataDword) << 48) | \
        (dwordGetByte2(dataDword) << 40) | \
        (dwordGetByte3(dataDword) << 32) | \
        (dwordGetByte4(dataDword) << 24) | \
        (dwordGetByte5(dataDword) << 16) | \
        (dwordGetByte6(dataDword) << 8)  | \
        (dwordGetByte7(dataDword)))
//!
//! \details        Returns the half-word 3 of a double-word.
//! \param[in]      dataDword           variable
//! \return         <i>dataDword</i> half-word 3
//!
#define dwordGetHword3(dataDword)       ((dataDword >> 48) & 0x000000000000FFFF)
//!
//! \details        Returns the half-word 2 of a double-word.
//! \param[in]      dataDword           variable
//! \return         <i>dataDword</i> half-word 2
//!
#define dwordGetHword2(dataDword)       ((dataDword >> 32) & 0x000000000000FFFF)
//!
//! \details        Returns the half-word 1 of a double-word.
//! \param[in]      dataDword           variable
//! \return         <i>dataDword</i> half-word 1
//!
#define dwordGetHword1(dataDword)       ((dataDword >> 16) & 0x000000000000FFFF)
//!
//! \details        Returns the half-word 0 of a double-word.
//! \param[in]      dataDword           variable
//! \return         <i>dataDword</i> half-word 0
//!
#define dwordGetHword0(dataDword)       ((dataDword >> 0) & 0x000000000000FFFF)
//!
//! \details        Switches the half-words of a double-word.
//! \param[in]      dataDword           variable
//! \return         new variable value
//!
#define dwordSwitchHwords(dataDword)    ((dwordGetHword0(dataDword) << 48)  | \
        (dwordGetHword1(dataDword) << 32) | \
        (dwordGetHword2(dataDword) << 16) | \
        (dwordGetHword3(dataDword)))
//!
//! \details        Returns the word 1 of a double-word.
//! \param[in]      dataDword           variable
//! \return         <i>dataDword</i> word 1
//!
#define dwordGetWord1(dataDword)         (((dataDword) >> 32) & 0x00000000FFFFFFFF)
//!
//! \details        Returns the word 0 of a double-word.
//! \param[in]      dataDword           variable
//! \return         <i>dataDword</i> word 0
//!
#define dwordGetWord0(dataDword)         ((dataDword) & 0x00000000FFFFFFFF)
//!
//! \details        Switches the words of a double-word.
//! \param[in]      dataDword           variable
//! \return         new variable value
//!
#define dwordSwitchWords(dataDword)     ((dwordGetWord0(dataDword) << 32)  | \
        (dwordGetWord1(dataDword)))

//     /////////////////////     TRUNCATE VALUES    /////////////////////     //
//!
//! \details        Returns the greater of two values.
//! \param[in]      var1                first value
//! \param[in]      var2                second value
//! \return         the greater value between <i>var1</i> and <i>var2</i>
//!
#define getMaximumOf(var1, var2)        (       \
        ((var1) > (var2))                       \
        ? (var1)                                \
        : (var2))
//!
//! \details        Returns the lower of two values.
//! \param[in]      var1                first value
//! \param[in]      var2                second value
//! \return         the lower value between <i>var1</i> and <i>var2</i>
//!
#define getMinimumOf(var1, var2)        (       \
        ((var1) < (var2))                       \
        ? (var1)                                \
        : (var2))
//!
//! \details        Truncates (trims) the value between maximum and minimum values.
//! \param[in]      var                 value to be truncated
//! \param[in]      max                 maximum allowed value
//! \param[in]      min                 minumum allowed value
//! \retval         min                 if the value is lower than <i>min</i>
//! \retval         max                 if the value is greater than <i>max</i>
//! \retval         var                 if the value is placed between <i>min</i> and <i>max</i>
//!
#define truncateBetween(var, min, max)  (       \
        ((var) < (min))                         \
        ? (min)                                 \
        : (((var) > (max))                      \
                ? (max)                         \
                : (var)                         \
        ))

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Data_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "String_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     String_Handling
//! \details        Performs general handling on <tt>char</tt> and strings.
//! \{
//!

//     //////////////////////     STRINGIFYING    ///////////////////////     //
// #define stringifyName(constant)         #constant
// #define stringifyValue(constant)        stringifyName(constant)

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "String_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// =============================================================================
// New data types
// =============================================================================

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Data_Types" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Data_Types
//! \brief          Definition of new data types.
//! \{
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Single_Types" in "Global_Definitions/Data_Types"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Single_Types
//! \details        Single variables renaming or shortening names.
//! \{
//!

//     ////////////////////     BASIC VARIABLES     /////////////////////     //
//!
//! \details        Renamed to ensure code standardization
//!
typedef bool                            bool_t;
//!
//! \details        Renamed to ensure code standardization
//!
typedef char                            char_t;

//     ///////////////////     CONSTANT VARIABLES    ////////////////////     //
//!
//! \details        Short for <b><tt>const bool</tt></b>
//!
typedef const bool_t                    cbool_t;
//!
//! \details        Short for <b><tt>const char</tt></b>
//!
typedef const char_t                    cchar_t;
//!
//! \details        Short for <b><tt>const int8_t</tt></b>
//!
typedef const int8_t                    cint8_t;
//!
//! \details        Short for <b><tt>const int16_t</tt></b>
//!
typedef const int16_t                   cint16_t;
//!
//! \details        Short for <b><tt>const int32_t</tt></b>
//!
typedef const int32_t                   cint32_t;
//!
//! \details        Short for <b><tt>const int64_t</tt></b>
//!
typedef const int64_t                   cint64_t;
//!
//! \details        Short for <b><tt>const uint8_t</tt></b>
//!
typedef const uint8_t                   cuint8_t;
//!
//! \details        Short for <b><tt>const uint16_t</tt></b>
//!
typedef const uint16_t                  cuint16_t;
//!
//! \details        Short for <b><tt>const uint32_t</tt></b>
//!
typedef const uint32_t                  cuint32_t;
//!
//! \details        Short for <b><tt>const uint64_t</tt></b>
//!
typedef const uint64_t                  cuint64_t;

//     ///////////////////     VOLATILE VARIABLES    ////////////////////     //
//!
//! \details        Short for <b><tt>volatile bool</tt></b>
//!
typedef volatile bool_t                 vbool_t;
//!
//! \details        Short for <b><tt>volatile char</tt></b>
//!
typedef volatile char_t                 vchar_t;
//!
//! \details        Short for <b><tt>volatile int8_t</tt></b>
//!
typedef volatile int8_t                 vint8_t;
//!
//! \details        Short for <b><tt>volatile int16_t</tt></b>
//!
typedef volatile int16_t                vint16_t;
//!
//! \details        Short for <b><tt>volatile int32_t</tt></b>
//!
typedef volatile int32_t                vint32_t;
//!
//! \details        Short for <b><tt>volatile int64_t</tt></b>
//!
typedef volatile int64_t                vint64_t;
//!
//! \details        Short for <b><tt>volatile uint8_t</tt></b>
//!
typedef volatile uint8_t                vuint8_t;
//!
//! \details        Short for <b><tt>volatile uint16_t</tt></b>
//!
typedef volatile uint16_t               vuint16_t;
//!
//! \details        Short for <b><tt>volatile uint32_t</tt></b>
//!
typedef volatile uint32_t               vuint32_t;
//!
//! \details        Short for <b><tt>volatile uint64_t</tt></b>
//!
typedef volatile uint64_t               vuint64_t;

#if defined(_FUNSAPE_PLATFORM_AVR)
//     /////////////////     AVR PLATFORM VARIABLES    //////////////////     //
//!
//! \details        Standard <b><tt>int</tt></b> data size (16-bit in AVR processors).
//!
typedef int16_t                         int_t;
//!
//! \details        Standard <b><tt>unsigned int</tt></b> data size (16-bit in AVR processors).
//!
typedef uint16_t                        uint_t;
//!
//! \details        Standard <b><tt>const int</tt></b> data size (16-bit in AVR processors).
//!
typedef cint16_t                        cint_t;
//!
//! \details        Standard <b><tt>const unsigned int</tt></b> data size (16-bit in AVR processors).
//!
typedef cuint16_t                       cuint_t;
//!
//! \details        Standard <b><tt>volatile int</tt></b> data size (16-bit in AVR processors).
//!
typedef vint16_t                        vint_t;
//!
//! \details        Standard <b><tt>volatile unsigned int</tt></b> data size (16-bit in AVR processors).
//!
typedef vuint16_t                       vuint_t;
//!
//! \details        Alias to handle a GPIO pin index
//!
typedef uint8_t                         ioPinIndex_t;
typedef uint8_t                         ioPinMask_t;
//!
//! \details        Alias to handle a GPIO register address
//!
typedef vuint8_t                       *ioRegAddress_t;
#elif defined(_FUNSAPE_PLATFORM_ARM_STM32)
typedef int32_t                         int_t;                  // 32-bit value (STM32)
typedef uint32_t                        uint_t;                 // 32-bit value (STM32)
typedef const int32_t                   cint_t;                 // 32-bit value (STM32)
typedef const uint32_t                  cuint_t;                // 32-bit value (STM32)
typedef volatile int32_t                vint_t;                 // 32-bit value (STM32)
typedef volatile uint32_t               vuint_t;                // 32-bit value (STM32)
typedef volatile uint32_t               reg_t;                  // 32-bit value (STM32)
typedef uint16_t                        ioPinMask_t;            // 16-bit value (STM32)
#   if defined(USE_HAL_DRIVER)
typedef GPIO_TypeDef                    *ioRegAddress_t;        // I/O port structure (STM32)
typedef uint8_t                         ioPinIndex_t;           // 8-bit value (STM32)
typedef uint16_t                        ioPinMask_t;           // 8-bit value (STM32)
#   else
typedef volatile uint32_t               ioReg_t;                // 32-bit value (STM32)
typedef uint8_t                         ioPinIndex_t;           // 8-bit value (STM32)
typedef uint16_t                        ioPinMask_t;            // 16-bit value (STM32)
#   endif
#endif
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Single_Types" in "Global_Definitions/Data_Types"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

//     //////////////////     BINARY ENUMERATIONS     ///////////////////     //

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Binary_Enumerations" in "Global_Definitions/Data_Types"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Binary_Enumerations
//! \details        Enumerations with only two possible values.
//! \{
//!

//!
//! \details        Used to refer to the activation state of an peripheral.
//!
enum class Activation : cbool_t {
    OFF                                 = false,        //!< Deactivated
    ON                                  = true          //!< Activated
};

//!
//! \details        Used to refer to the orientation of a display screen.
//!
enum class DisplayOrientation : cbool_t {
    LANDSCAPE                           = false,        //!< Display is on landscape orientation
    PORTRAIT                            = true          //!< Display is on portrait orientation
};

//!
//! \details        Used to refer to the GPIO Pin output driver mode.
//!
enum class DriverMode : cbool_t {
    PUSH_PULL                           = false,        //!< Push-pull driver
    OPEN_DRAIN                          = true,         //!< Open-drain driver
};

//!
//! \details        Used to specify the edge of a signal.
//!
enum class Edge : cbool_t {
    FALLING                             = false,        //!< Falling edge of the signal
    RISING                              = true          //!< Rising edge of the signal
};

//!
//! \details        Used to specify the GPIO or communications operation.
//!
enum class IoOperation : cbool_t {
    WRITE                               = false,        //!< Write operation
    READ                                = true          //!< Read operation
};

//!
//! \details        Used to specify the logic level of a signal.
//!
enum class LogicLevel : cbool_t {
    LOW                                 = false,        //!< Low level
    HIGH                                = true          //!< High level
};

//!
//! \details        Used to specify the direction of a GPIO pin.
//!
enum class PinDirection : cbool_t {
    INPUT                               = false,        //!< Pin is an input
    OUTPUT                              = true,         //!< Pis is an output
};

//!
//! \details        Used to specify a rotation direction.
//!
enum class Rotation : cbool_t {
    CLOCKWISE                           = false,        //!< Clockwise direction
    COUNTERCLOCKWISE                    = true          //!< Counter-clockwise direction
};

//!
//! \details        Used to generically refer to an state or status. For example, the state of a LED.
//!
enum class State : cbool_t {
    OFF                                 = false,        //!< State is OFF
    ON                                  = true          //!< State is ON
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Binary_Enumerations" in "Global_Definitions/Data_Types"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Plain_Enumerations" in "Global_Definitions/Data_Types"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Plain_Enumerations
//! \details        Enumerations with multiple possible values.
//! \{
//!

//     ///////////////////     PLAIN ENUMERATIONS    ////////////////////     //
//!
//! \details        Used to specify the 3d Cartesian axes.
//!
enum class Axis : cuint8_t {
    //                                     Z-AXIS     Y-AXIS     X-AXIS
    NONE                                = (0 << 2) | (0 << 1) | (0 << 0),       //!< No axis selected
    X                                   = (0 << 2) | (0 << 1) | (1 << 0),       //!< X axis selected
    Y                                   = (0 << 2) | (1 << 1) | (0 << 0),       //!< Y axis selected
    XY                                  = (0 << 2) | (1 << 1) | (1 << 0),       //!< X and Y axes selected
    Z                                   = (1 << 2) | (0 << 1) | (0 << 0),       //!< Z axis selected
    XZ                                  = (1 << 2) | (0 << 1) | (1 << 0),       //!< X and Z axes selected
    YZ                                  = (1 << 2) | (1 << 1) | (0 << 0),       //!< Y and Z axes selected
    ALL                                 = (1 << 2) | (1 << 1) | (1 << 0)        //!< X, Y and Z axes selected
};

//!
//! \cond
//!

inlined Axis operator|(Axis a, Axis b)
{
    return static_cast<Axis>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inlined Axis &operator|=(Axis &a, Axis b)
{
    return a = static_cast<Axis>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inlined Axis operator&(Axis a, Axis b)
{
    return static_cast<Axis>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

inlined Axis &operator&=(Axis &a, Axis b)
{
    return a = static_cast<Axis>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

//!
//! \endcond
//!

//!
//! \details        Used to specify 2d plain directions.
//!
enum class Direction : cuint8_t {
    LEFT                                = 0,            //!< Left planar direction
    RIGHT                               = 1,            //!< Right planar direction
    UP                                  = 2,            //!< Up planar direction
    DOWN                                = 3             //!< Down planar direction
};

//!
//! \details        Used to specify the access mode to the peripheral.
//!
enum class InterfaceMode : cuint8_t {
    BLOCKING_MODE                       = 0,            //!< Do not use interrupt or DMA
    INTERRUPT_MODE                      = 1,            //!< Use the peripheral interrupt
    DMA_MODE                            = 2             //!< Use the DMA interrupt
};

//!
//! \details        Used to specify a Thermometric scale.
//!
enum class ThermometricScale : cuint8_t {
    CELSIUS                             = 0,            //!< Celsius thermometric scale
    DELISLE                             = 1,            //!< Delisle thermometric scale
    FAHRENHEIT                          = 2,            //!< Fahrenheit thermometric scale
    KELVIN                              = 3,            //!< Kelvin absolute temperature
    NEWTON                              = 4,            //!< Newton thermometric scale
    RANKINE                             = 5,            //!< Rankine thermometric scale
    REAUMUR                             = 6,            //!< Reaumur thermometric scale
    ROMER                               = 7             //!< Romer thermometric scale
};

//!
//! \details        Funsape Error codes.
//!
enum class Error : cuint16_t {
    // General error codes
    NONE                                                = 0x0000,   //!< Success - No errors occurred.

    // AXIS_INVALID                                        = 0x0001,   //!< Invalid axis
    NOT_IMPLEMENTED                                     = 0x0002,   //!< This feature is not implemented yet, but is marked for future implementation.
    // UNDER_DEVELOPMENT                                   = 0x0003,   //!< This part of the code is still under development
    NOT_INITIALIZED                                     = 0x0004,   //!< The module was not initialized.
    // BUSY                                                = 0x0005,   //!< TODO: Describe parameter
    // DEVICE_NOT_SUPPORTED                                = 0x0006,   //!< Device is not currently supported
    FEATURE_NOT_SUPPORTED                               = 0x0007,   //!< Unsupported feature or configuration.
    // FUNCTION_POINTER_NULL                               = 0x0008,   //!< TODO: Describe parameter
    // INSTANCE_INVALID                                    = 0x0009,   //!< Invalid instance
    // LOCKED                                              = 0x000A,   //!< Accessed a locked device
    MEMORY_ALLOCATION                                   = 0x000B,   //!< Memory allocation failed.
    MODE_NOT_SUPPORTED                                  = 0x000C,   //!< This operation mode is not supported by the module.
    // NOT_READY                                           = 0x000D,   //!< TODO: Describe parameter
    // READ_PROTECTED                                      = 0x000E,   //!< Tried to read a read protected device
    // WRITE_PROTECTED                                     = 0x000F,   //!< Tried to write a write protected device

    // Function arguments related error codes
    ARGUMENT_CANNOT_BE_ZERO                             = 0x0010,   //!< The argument value must not be zero (0).
    ARGUMENT_POINTER_NULL                               = 0x0011,   //!< NULL pointer was passed as an argument to function.
    ARGUMENT_VALUE_INVALID                              = 0x0012,   //!< The argument value is not valid.
    // ARGUMENTS_MISMATCH                                  = 0x0013,   //!< A function was called with dubious argument values
    // ARGUMENTS_WRONG_NUMBER                              = 0x0014,   //!< A function was called with wrong number of arguments
    // ARGUMENT_GENERIC_ERROR_5                            = 0x0015,   //!< Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_6                            = 0x0016,   //!< Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_7                            = 0x0017,   //!< Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_8                            = 0x0018,   //!< Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_9                            = 0x0019,   //!< Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_10                           = 0x001A,   //!< Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_11                           = 0x001B,   //!< Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_12                           = 0x001C,   //!< Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_13                           = 0x001D,   //!< Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR_14                           = 0x001E,   //!< Generic error (use only on temporary basis)
    // ARGUMENT_GENERIC_ERROR                              = 0x001F,   //!< Generic error (use only on temporary basis)

    // Buffer related error codes
    // BUFFER_EMPTY                                        = 0x0020,   //!< Buffer is empty
    // BUFFER_FULL                                         = 0x0021,   //!< Buffer is full
    // BUFFER_NOT_ENOUGH_ELEMENTS                          = 0x0022,   //!< Not enough space in buffer to perform operation
    // BUFFER_NOT_ENOUGH_SPACE                             = 0x0023,   //!< Not enough space in buffer to perform operation
    // BUFFER_POINTER_NULL                                 = 0x0024,   //!< Buffer size was set to zero
    BUFFER_SIZE_TOO_LARGE                               = 0x0025,   //!< Buffer size was set to a large value.
    BUFFER_SIZE_TOO_SMALL                               = 0x0026,   //!< Buffer size was set to a very small value.
    // BUFFER_SIZE_ZERO                                    = 0x0027,   //!< Buffer size was set to zero
    // BUFFER_GENERIC_ERROR_8                              = 0x0028,   //!< Generic error (use only on temporary basis)
    // BUFFER_GENERIC_ERROR_9                              = 0x0029,   //!< Generic error (use only on temporary basis)
    // BUFFER_GENERIC_ERROR_10                             = 0x002A,   //!< Generic error (use only on temporary basis)
    // BUFFER_GENERIC_ERROR_11                             = 0x002B,   //!< Generic error (use only on temporary basis)
    // BUFFER_GENERIC_ERROR_12                             = 0x002C,   //!< Generic error (use only on temporary basis)
    // BUFFER_GENERIC_ERROR_13                             = 0x002D,   //!< Generic error (use only on temporary basis)
    // BUFFER_GENERIC_ERROR_14                             = 0x002E,   //!< Generic error (use only on temporary basis)
    // BUFFER_GENERIC_ERROR_15                             = 0x002F,   //!< Generic error (use only on temporary basis)

    // Clock configuration related error codes
    CLOCK_PRESCALER_CHANGE_FAILED                       = 0x0030,   //!< Clock prescaler change failed.
    CLOCK_PRESCALER_NOT_SUPPORTED                       = 0x0031,   //!< Clock prescaler configuration unsupported.
    CLOCK_SPEED_TOO_HIGH                                = 0x0032,   //!< The clock speed is too high.
    CLOCK_SPEED_TOO_LOW                                 = 0x0033,   //!< The clock speed id too low.
    // CLOCK_GENERIC_ERROR_4                               = 0x0034,   //!< Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_5                               = 0x0035,   //!< Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_6                               = 0x0036,   //!< Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_7                               = 0x0037,   //!< Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_8                               = 0x0038,   //!< Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_9                               = 0x0039,   //!< Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_10                              = 0x003A,   //!< Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_11                              = 0x003B,   //!< Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_12                              = 0x003C,   //!< Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_13                              = 0x003D,   //!< Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_14                              = 0x003E,   //!< Generic error (use only on temporary basis)
    // CLOCK_GENERIC_ERROR_15                              = 0x003F,   //!< Generic error (use only on temporary basis)

    // Communication related error codes
    COMMUNICATION_FAILED                                = 0x0040,   //!< The communication has failed.
    COMMUNICATION_NO_DEVICE_SELECTED                    = 0x0041,   //!< No communication device was selected.
    // COMMUNICATION_PORT_NOT_SET                          = 0x0042,   //!< TODO: Describe parameter
    COMMUNICATION_TIMEOUT                               = 0x0043,   //!< The operation timed out.
    // COMMUNICATION_DEVICE_ID_MATCH_FAILED                = 0x0044,   //!< TODO: Describe parameter
    // CHECKSUM_ERROR                                      = 0x0045,   //!< TODO: Describe parameter
    // FRAME_ERROR                                         = 0x0046,   //!< TODO: Describe parameter
    // PACKAGE_AWAITING                                    = 0x0047,   //!< Try to write data to a ready package
    // PACKAGE_NOT_READY                                   = 0x0048,   //!< Try to read data from a not ready package
    // COMMUNICATION_GENERIC_ERROR_9                       = 0x0049,   //!< Generic error (use only on temporary basis)
    // COMMUNICATION_GENERIC_ERROR_10                      = 0x004A,   //!< Generic error (use only on temporary basis)
    // COMMUNICATION_GENERIC_ERROR_11                      = 0x004B,   //!< Generic error (use only on temporary basis)
    // COMMUNICATION_GENERIC_ERROR_12                      = 0x004C,   //!< Generic error (use only on temporary basis)
    // COMMUNICATION_GENERIC_ERROR_13                      = 0x004D,   //!< Generic error (use only on temporary basis)
    // COMMUNICATION_GENERIC_ERROR_14                      = 0x004E,   //!< Generic error (use only on temporary basis)
    // COMMUNICATION_GENERIC_ERROR_15                      = 0x004F,   //!< Generic error (use only on temporary basis)

    // DateTime class related error codes
    DATE_NOT_INITIALIZED                                = 0x0050,   //!< The date was not initialized.
    // HOUR_INVALID                                        = 0x0051,   //!< TODO: Describe parameter
    // MILLISECOND_INVALID                                 = 0x0052,   //!< TODO: Describe parameter
    // MINUTE_INVALID                                      = 0x0053,   //!< TODO: Describe parameter
    // MONTH_DAY_INVALID                                   = 0x0054,   //!< TODO: Describe parameter
    // MONTH_INVALID                                       = 0x0055,   //!< TODO: Describe parameter
    // SECOND_INVALID                                      = 0x0056,   //!< TODO: Describe parameter
    TIME_NOT_INITIALIZED                                = 0x0057,   //!< The time was not initialized.
    // TIMEZONE_INVALID                                    = 0x0058,   //!< TODO: Describe parameter
    // YEAR_INVALID                                        = 0x0059,   //!< TODO: Describe parameter
    DATE_INVALID                                        = 0x005A,   //!< The date value is invalid.
    TIME_INVALID                                        = 0x005B,   //!< The time value is invalid.
    // GENERIC_ERROR_13                                    = 0x005C,   //!< Generic error (use only on temporary basis)
    // GENERIC_ERROR_14                                    = 0x005D,   //!< Generic error (use only on temporary basis)
    // GENERIC_ERROR_15                                    = 0x005F,   //!< Generic error (use only on temporary basis)

    // Handler related error codes
    BUS_HANDLER_NOT_SUPPORTED                           = 0x0060,   //!< The specified bus handler type is not supported by this module.
    BUS_HANDLER_POINTER_NULL                            = 0x0061,   //!< The bus handler pointer cannot be null.
    // HANDLER_GENERIC_ERROR_2                             = 0x0062,   //!< Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_3                             = 0x0063,   //!< Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_4                             = 0x0064,   //!< Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_5                             = 0x0065,   //!< Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_6                             = 0x0066,   //!< Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_7                             = 0x0067,   //!< Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_8                             = 0x0068,   //!< Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_9                             = 0x0069,   //!< Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_10                            = 0x006A,   //!< Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_11                            = 0x006B,   //!< Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_12                            = 0x006C,   //!< Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_13                            = 0x006D,   //!< Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_14                            = 0x006E,   //!< Generic error (use only on temporary basis)
    // HANDLER_GENERIC_ERROR_15                            = 0x006F,   //!< Generic error (use only on temporary basis)

    // External interrupts related error codes
    // INTERRUPT_NOT_AVAILABLE                             = 0x0070,   //!< TODO: Describe parameter
    // INTERRUPT_PORT_OUTPUT_MODE_NOT_SUPPORTED            = 0x0071,   //!< TODO: Describe parameter
    // INTERRUPT_SENSE_MODE_NOT_SUPPORTED                  = 0x0072,   //!< TODO: Describe parameter
    // INTERRUPT_GENERIC_ERROR_3                           = 0x0073,   //!< Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_4                           = 0x0074,   //!< Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_5                           = 0x0075,   //!< Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_6                           = 0x0076,   //!< Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_7                           = 0x0077,   //!< Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_8                           = 0x0078,   //!< Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_9                           = 0x0079,   //!< Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_10                          = 0x007A,   //!< Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_11                          = 0x007B,   //!< Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_12                          = 0x007C,   //!< Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_13                          = 0x007D,   //!< Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_14                          = 0x007E,   //!< Generic error (use only on temporary basis)
    // INTERRUPT_GENERIC_ERROR_15                          = 0x007F,   //!< Generic error (use only on temporary basis)


    // Package API class related error codes
    // PACKAGE_API_PACKAGE_DATA_FULL                       = 0x0080,   //!< TODO: Describe parameter
    // PACKAGE_API_PACKAGE_NOT_READY                       = 0x0081,   //!< TODO: Describe parameter
    // PACKAGE_API_PAYLOAD_DATA_NULL                       = 0x0082,   //!< TODO: Describe parameter
    // PACKAGE_API_PAYLOAD_SIZE_NULL                       = 0x0083,   //!< TODO: Describe parameter
    // PACKAGE_API_SOURCE_ADDRESS_INVALID                  = 0x0084,   //!< TODO: Describe parameter
    // PACKAGE_API_GENERIC_ERROR_5                         = 0x0085,   //!< Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_6                         = 0x0086,   //!< Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_7                         = 0x0087,   //!< Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_8                         = 0x0088,   //!< Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_9                         = 0x0089,   //!< Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_10                        = 0x008A,   //!< Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_11                        = 0x008B,   //!< Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_12                        = 0x008C,   //!< Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_13                        = 0x008D,   //!< Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_14                        = 0x008E,   //!< Generic error (use only on temporary basis)
    // PACKAGE_API_GENERIC_ERROR_15                        = 0x008F,   //!< Generic error (use only on temporary basis)

    // SPI related error codes
    // SPI_BUSY_FLAG                                       = 0x0090,   //!< TODO: Describe parameter
    // SPI_CRC                                             = 0x0091,   //!< TODO: Describe parameter
    // SPI_DMA                                             = 0x0092,   //!< TODO: Describe parameter
    // SPI_MODE_FAULT                                      = 0x0093,   //!< TODO: Describe parameter
    // SPI_OVERRUN                                         = 0x0094,   //!< TODO: Describe parameter
    // SPI_GENERIC_ERROR_5                                 = 0x0095,   //!< Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_6                                 = 0x0096,   //!< Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_7                                 = 0x0097,   //!< Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_8                                 = 0x0098,   //!< Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_9                                 = 0x0099,   //!< Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_10                                = 0x009A,   //!< Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_11                                = 0x009B,   //!< Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_12                                = 0x009C,   //!< Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_13                                = 0x009D,   //!< Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_14                                = 0x009E,   //!< Generic error (use only on temporary basis)
    // SPI_GENERIC_ERROR_15                                = 0x009F,   //!< Generic error (use only on temporary basis)

    // TWI related error codes
    // TWI_AF_FLAG                                         = 0x00A0,   //!< TWI AF flag error
    // TWI_ARBITRATION_LOST                                = 0x00A1,   //!< TWI bus arbitration lost
    // TWI_BUS_ERROR                                       = 0x00A2,   //!< TWI bus error
    // TWI_DMA                                             = 0x00A3,   //!< DMA parameter error
    // TWI_DMA_PARAM                                       = 0x00A4,   //!< DMA transfer error
    // TWI_OVERRUN                                         = 0x00A5,   //!< TWI overrun
    // TWI_SIZE_MANAGEMENT_ERROR                           = 0x00A6,   //!< Size management error
    // TWI_INVALID_DEVICE_ADDRESS                          = 0x00A7,   //!< TODO: Describe parameter
    // TWI_GENERIC_ERROR_8                                 = 0x00A8,   //!< Generic error (use only on temporary basis)
    // TWI_GENERIC_ERROR_9                                 = 0x00A9,   //!< Generic error (use only on temporary basis)
    // TWI_GENERIC_ERROR_10                                = 0x00AA,   //!< Generic error (use only on temporary basis)
    // TWI_GENERIC_ERROR_11                                = 0x00AB,   //!< Generic error (use only on temporary basis)
    // TWI_GENERIC_ERROR_12                                = 0x00AC,   //!< Generic error (use only on temporary basis)
    // TWI_GENERIC_ERROR_13                                = 0x00AD,   //!< Generic error (use only on temporary basis)
    // TWI_GENERIC_ERROR_14                                = 0x00AE,   //!< Generic error (use only on temporary basis)
    // TWI_GENERIC_ERROR_15                                = 0x00AF,   //!< Generic error (use only on temporary basis)

    // USART related error codes
    USART_BAUD_RATE_NOT_SUPPORTED                       = 0x00B0,   //!< The baud rate value is not supported.
    // USART_CONFIGURATION_PARAMETER_WRONG                 = 0x00B1,   //!< TODO: Describe parameter
    USART_DATA_SIZE_NOT_SUPPORTED                       = 0x00B2,   //!< The number of data bits is invalid.
    USART_FRAME_FORMAT_NOT_SUPPORTED                    = 0x00B3,   //!< The format of the frame is not supported.
    USART_PARITY_NOT_SUPPORTED                          = 0x00B4,   //!< Parity mode not supported.
    USART_STOP_BIT_NOT_SUPPORTED                        = 0x00B5,   //!< Invalid number of stop bits.

    // LCD related error codes
    LCD_CONTROL_PORT_NOT_SET                            = 0x00C0,   //!< TODO: Describe parameter
    // LCD_CONTROL_PIN_E_INVALID                           = 0x00C1,   //!< TODO: Describe parameter
    // LCD_CONTROL_PIN_RS_INVALID                          = 0x00C2,   //!< TODO: Describe parameter
    // LCD_CONTROL_PIN_RW_INVALID                          = 0x00C3,   //!< TODO: Describe parameter
    LCD_DATA_PORT_NOT_SET                               = 0x00C4,   //!< TODO: Describe parameter
    // LCD_DATA_PIN_INDEX_OUT_OF_BOUNDARIES                = 0x00C5,   //!< TODO: Describe parameter
    // LCD_GENERIC_ERROR_6                                 = 0x00C6,   //!< Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_7                                 = 0x00C7,   //!< Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_8                                 = 0x00C8,   //!< Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_9                                 = 0x00C9,   //!< Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_10                                = 0x00CA,   //!< Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_11                                = 0x00CB,   //!< Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_12                                = 0x00CC,   //!< Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_13                                = 0x00CD,   //!< Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_14                                = 0x00CE,   //!< Generic error (use only on temporary basis)
    // LCD_GENERIC_ERROR_15                                = 0x00CF,   //!< Generic error (use only on temporary basis)

    // GPIO related error codes
    GPIO_PORT_NOT_SET                                   = 0x00D0,   //!< Gpio port was not set before use.
    // GPIO_DATA_PORT_NOT_SET                              = 0x00D1,   //!< Gpio data port was not set before use
    // GPIO_CONTROL_PORT_NOT_SET                           = 0x00D2,   //!< Gpio control port was not set before use
    GPIO_PORT_INVALID                                   = 0x00D3,   //!< Gpio port address is invalid.
    GPIO_DATA_PORT_INVALID                              = 0x00D4,   //!< Gpio data port address is invalid.
    GPIO_CONTROL_PORT_INVALID                           = 0x00D5,   //!< Gpio control port address is invalid.
    GPIO_PIN_INDEX_INVALID                              = 0x00D6,   //!< Invalid GPIO Pin.
    GPIO_PIN_OUT_OF_BOUNDARIES                          = 0x00D7,   //!< Gpio pin index was out of bounds after processing.
    // GPIO_NO_PIN_SET                                     = 0x00D8,   //!< No pin selected at Gpio peripheral
    // GPIO_ADDRESS_INVALID                                = 0x00D9,   //!< Invalid GPIO Port
    // GPIO_PORT_LOGIC_CONTENTION                          = 0x00DA,   //!< TODO: Describe parameter
    GPIO_BUS_SIZE_INVALID   = 0x00DB,
    GPIO_NOT_INITIALIZED    = 0x00DC,
    // GPIO_GENERIC_ERROR_13                               = 0x00DD,   //!< Generic error (use only on temporary basis)
    // GPIO_GENERIC_ERROR_14                               = 0x00DE,   //!< Generic error (use only on temporary basis)
    // GPIO_GENERIC_ERROR_15                               = 0x00DF,   //!< Generic error (use only on temporary basis)

    // HAL related error codes
    // HAL_UNKNOWN_ERROR                                   = 0x00E0,   //!< TODO: Describe parameter
    // HAL_STATUS_ERROR                                    = 0x00E1,   //!< TODO: Describe parameter
    // HAL_STATUS_BUSY                                     = 0x00E2,   //!< TODO: Describe parameter
    // HAL_STATUS_TIMEOUT                                  = 0x00E3,   //!< TODO: Describe parameter
    // HAL_GENERIC_ERROR_4                                 = 0x00E4,   //!< Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_5                                 = 0x00E5,   //!< Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_6                                 = 0x00E6,   //!< Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_7                                 = 0x00E7,   //!< Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_8                                 = 0x00E8,   //!< Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_9                                 = 0x00E9,   //!< Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_10                                = 0x00EA,   //!< Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_11                                = 0x00EB,   //!< Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_12                                = 0x00EC,   //!< Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_13                                = 0x00ED,   //!< Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_14                                = 0x00EE,   //!< Generic error (use only on temporary basis)
    // HAL_GENERIC_ERROR_15                                = 0x00EF,   //!< Generic error (use only on temporary basis)

    // System related error codes
    // SYSTEM_US_TIMER_HANDLER_NULL                        = 0x00F0,   //!< TODO: Describe parameter
    // SYSTEM_GENERIC_ERROR_1                              = 0x00F1,   //!< Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_2                              = 0x00F2,   //!< Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_3                              = 0x00F3,   //!< Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_4                              = 0x00F4,   //!< Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_5                              = 0x00F5,   //!< Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_6                              = 0x00F6,   //!< Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_7                              = 0x00F7,   //!< Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_8                              = 0x00F8,   //!< Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_9                              = 0x00F9,   //!< Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_10                             = 0x00FA,   //!< Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_11                             = 0x00FB,   //!< Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_12                             = 0x00FC,   //!< Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_13                             = 0x00FD,   //!< Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_14                             = 0x00FE,   //!< Generic error (use only on temporary basis)
    // SYSTEM_GENERIC_ERROR_15                             = 0x00FF,   //!< Generic error (use only on temporary basis)

    // FatFs related error codes
    // FAT_FS_UNKNOWN_ERROR                                = 0x0100,   //!< TODO: Describe parameter
    // FAT_FS_DRIVE_UNSUPPORTED                            = 0x0101,   //!< TODO: Describe parameter
    // FAT_FS_DISK_NOT_INSERTED                            = 0x0102,   //!< TODO: Describe parameter
    // FAT_FS_INITIALIZATION_FAILED                        = 0x0103,   //!< TODO: Describe parameter
    // FAT_FS_GENERIC_ERROR_4                              = 0x0104,   //!< Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_5                              = 0x0105,   //!< Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_6                              = 0x0106,   //!< Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_7                              = 0x0107,   //!< Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_8                              = 0x0108,   //!< Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_9                              = 0x0109,   //!< Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_10                             = 0x010A,   //!< Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_11                             = 0x010B,   //!< Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_12                             = 0x010C,   //!< Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_13                             = 0x010D,   //!< Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_14                             = 0x010E,   //!< Generic error (use only on temporary basis)
    // FAT_FS_GENERIC_ERROR_15                             = 0x010F,   //!< Generic error (use only on temporary basis)

    // Uncategorized error codes
    // LCD_OUT_OF_BOUNDARIES                               = 0xFFF1,   //!< TODO: Describe parameter
    // CONTROLLER_NOT_SUPPORTED                            = 0xFFF2,   //!< Unsupported controller
    // DEVICE_ID_MATCH_FAILED                              = 0xFFF3,   //!< Device ID doesn't match
    // DMA_NOT_SUPPORTED                                   = 0xFFF4,   //!< DMA interface mode is not supported for this module
    // DMA_TRANSFER_ERROR                                  = 0xFFF5,   //!< DMA transfer error
    // MESSAGE_TOO_LONG                                    = 0xFFF6,   //!< Message is to long to be stored inside buffer
    // VALID_DATA_NOT_AVAILABLE                            = 0xFFF7,   //!< Valid data was unavailable
    // PERIPHERAL_NOT_READY                                = 0xFFF8,   //!< TODO: Describe parameter
    // STOPWATCH_NOT_STARTED                               = 0xFFF9,   //!< TODO: Describe parameter


    KEYPAD_TYPE_UNSUPPORTED                             = 0xFFFD,       //!< This keypad is not supported.
    KEY_VALUES_NOT_SET                                  = 0xFFFE,       //!< The values of the keys was not configured.
    // "I don't have the slightest idea" error code
    UNKNOWN                                             = 0xFFFF,   // Unknown error - Ops!!!!
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Plain_Enumerations" in "Global_Definitions/Data_Types"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Data_Types" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// =============================================================================
// Extern global variables
// =============================================================================

// NONE

// =============================================================================
// Inline functions declaration
// =============================================================================

//     ///////////////////     CHARACTER HANDLING    ////////////////////     //

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "String_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     String_Handling
//! \details        Performs general handling on <tt>char</tt> and strings.
//! \{
//!

//!
//! \details        Returns the lowercase version of the character. If the character is not a uppercase letter, the same character will be returned.
//! \param[in]      character_p         character to be lowercased
//! \return         the lowercase version of the character
//!
char_t inlined toLowerCase(cchar_t character_p);
//!
//! \details        Returns the uppercase version of the character. If the character is not a lowercase letter, the same character will be returned.
//! \param[in]      character_p         character to be upper-cased
//! \return         the uppercase version of the character
//!
char_t inlined toUpperCase(cchar_t character_p);

//     /////////////////////     DATA VALIDITY     //////////////////////     //
//!
//! \details        Verifies if the character is an ASCII lowercase letter.
//! \param[in]      character_p         character to be evaluated
//! \retval         true                it is an ASCII lowercase letter
//! \retval         false               it is not an ASCII lowercase letter
//!
bool_t inlined isAsciiLowerCaseLetter(cchar_t character_p);
//!
//! \details        Verifies if the character is an ASCII uppercase letter.
//! \param[in]      character_p         character to be evaluated
//! \retval         true                it is an ASCII uppercase letter
//! \retval         false               it is not an ASCII uppercase letter
//!
bool_t inlined isAsciiUpperCaseLetter(cchar_t character_p);
//!
//! \details        Verifies if the character is an ASCII command character.
//! \param[in]      character_p         character to be evaluated
//! \retval         true                it is an ASCII command character
//! \retval         false               it is not an ASCII command character
//!
bool_t inlined isAsciiCommand(cchar_t character_p);
//!
//! \details        Verifies if the character is an ASCII letter character.
//! \param[in]      character_p         character to be evaluated
//! \retval         true                it is an ASCII letter character
//! \retval         false               it is not an ASCII letter character
//!
bool_t inlined isAsciiLetter(cchar_t character_p);
//!
//! \details        Verifies if the character is an ASCII numeric character.
//! \param[in]      character_p         character to be evaluated
//! \retval         true                it is an ASCII numeric character
//! \retval         false               it is not an ASCII numeric character
//!
bool_t inlined isAsciiNumber(cchar_t character_p);
//!
//! \details        Verifies if the character is an ASCII symbol character.
//! \param[in]      character_p         character to be evaluated
//! \retval         true                it is an ASCII symbol character
//! \retval         false               it is not an ASCII symbol character
//!
bool_t inlined isAsciiSymbol(cchar_t character_p);

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "String_Handling" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "System_Functions" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     System_Functions
//! \details        General system functions.
//! \{
//!

//     /////////////////////     SYSTEM ACTIONS    //////////////////////     //
//!
//! \details        Halts system execution printing a formatted string with the error code.
//! \param[in]      errorCode_p         Error enumeration
//! \return         none
//!
void inlined die(Error errorCode_p);
//!
//! \details        Executes a NOP assembly instruction.
//! \return         none
//!
void inlined doNop(void);
//!
//! \details        This function does nothing and do not generate any code. Must be used as a placeholder (code standardization).
//! \return         none
//!
void inlined doNothing(void);
//!
//! \details        Calls the <i>callBack_p</i> function and halts system execution.
//! \param[in]      callBack_p          function to be called
//! \return         none
//!
void inlined systemHalt(void (*callBack_p)(void) = nullptr);

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "System_Functions" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// =============================================================================
// Inline functions definitions
// =============================================================================

//     ///////////////////     CHARACTER HANDLING    ////////////////////     //
char_t inlined toLowerCase(cchar_t character_p)
{
    return ((isAsciiUpperCaseLetter(character_p)) ? (character_p + 0x20) : character_p);
}

char_t inlined toUpperCase(cchar_t character_p)
{
    return ((isAsciiLowerCaseLetter(character_p)) ? (character_p - 0x20) : character_p);
}

//     /////////////////////     DATA VALIDITY     //////////////////////     //
bool_t inlined isAsciiLowerCaseLetter(cchar_t character_p)
{
    return ((bool_t)(((character_p >= 'a') && (character_p <= 'z')) ? true : false));
}

bool_t inlined isAsciiUpperCaseLetter(cchar_t character_p)
{
    return ((bool_t)(((character_p >= 'A') && (character_p <= 'Z')) ? true : false));
}

bool_t inlined isAsciiCommand(cchar_t character_p)
{
    return ((bool_t)((character_p < ' ') ? true : false));
}

bool_t inlined isAsciiLetter(cchar_t character_p)
{
    return ((bool_t)((isAsciiLowerCaseLetter(character_p) || (isAsciiUpperCaseLetter(character_p)) ? true : false)));
}

bool_t inlined isAsciiNumber(cchar_t character_p)
{
    return ((bool_t)(((character_p >= '0') && (character_p <= '9')) ? true : false));
}

bool_t inlined isAsciiSymbol(cchar_t character_p)
{
    return ((bool_t)(((!isAsciiNumber(character_p)) && (!isAsciiCommand(character_p)) &&
                                    (!isAsciiLetter(character_p))) ? true : false));
}

//     /////////////////////     SYSTEM ACTIONS    //////////////////////     //
void inlined die(Error errorCode_p)
{
    printf("Failed with error=%u (0x%04x).\r", (cuint16_t)errorCode_p, (cuint16_t)errorCode_p);
    systemHalt();

    return;
}

void inlined doNop(void)
{
    asm volatile("nop");

    return;
}

void inlined doNothing(void)
{
    return;
}

void inlined systemHalt(void (*function_p)(void))
{
    if(isPointerValid(function_p)) {
        function_p();
    }
    while(1) {
        doNothing();
    }

    return;
}

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
void inlined DWT_delay_us(volatile uint32_t microseconds)
{
    uint32_t clk_cycle_start = DWT->CYCCNT;

    /* Go to number of cycles for system */
    microseconds *= (HAL_RCC_GetHCLKFreq() / 1000000);

    /* Delay till end */
    while((DWT->CYCCNT - clk_cycle_start) < microseconds);
}
#endif

// =============================================================================
// Public functions weakly defined
// =============================================================================

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "System_Functions" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     System_Functions
//! \details        General system functions.
//! \{
//!

//!
//! \details        Alias of the millisecond delay function
//!
#if defined(_FUNSAPE_PLATFORM_AVR)
#   define delayMs(time)                _delay_ms(time)
#elif defined(_FUNSAPE_PLATFORM_ARM_STM32)
#   define delayMs(time)                HAL_Delay(time)
#endif

//!
//! \details        Alias of the microsecond delay function
//!
#if defined(_FUNSAPE_PLATFORM_AVR)
#   define delayUs(time)                _delay_us(time)
#elif defined(_FUNSAPE_PLATFORM_ARM_STM32)
// #   define delayUs(time)                DWT_delay_us(time)
#   define delayUs(time)                HAL_Delay(1)
#endif

//!
//! \details        Returns the System Ticks counter value. Since the AVR doesn't have a System Tick counter, it always returns 0.
//! \return         0
//!
weakened uint32_t getTick(void)
{
#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
    return HAL_GetTick();
#else
    return 0;
#endif
}

// =============================================================================
// Includes Low Level Abstraction Layer
// =============================================================================

//!
//! \details        Returns the textual value of a boolean
//!
#define dumpBool(auxBool)       (char_t *)((auxBool) ? "true" : "false")

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "System_Functions" in "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End main group "Global_Definitions"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __FUNSAPE_LIB_GLOBAL_DEFINES_HPP

// =============================================================================
// END OF FILE
// =============================================================================
