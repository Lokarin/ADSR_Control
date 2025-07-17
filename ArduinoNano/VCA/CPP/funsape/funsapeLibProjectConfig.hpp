/* =============================================================================
 * Project:         FunSAPE++ MCU Embedded Library
 * File name:       funsapeLibProjectConfig.hpp
 * Module:          Project configurations for FunSAPE++ MCU Embedded Library
 *                      project
 * Authors:         Leandro Schwarz
 * Build:           20240111
 * Last edition:    2024-01-11
 * ========================================================================== */

// =============================================================================
// Include guard
// =============================================================================

#ifndef __FUNSAPE_LIB_PROJECT_CONFIG_HPP
#define __FUNSAPE_LIB_PROJECT_CONFIG_HPP        2407

// =============================================================================
// Dependencies
// =============================================================================

// Header files
#include "parts/funsapeLibPlatform.hpp"
#ifndef __FUNSAPE_LIB_PLATFORM_HPP
#   error [funsapeLibProjectConfig.hpp] Error - Header file (funsapeLibPlatform.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_PLATFORM_HPP != __FUNSAPE_LIB_PROJECT_CONFIG_HPP
#   error [funsapeLibProjectConfig.hpp] Error - Build mismatch between header file (funsapeLibProjectConfig.hpp) and project configuration file (funsapeLibProjectConfig.hpp)!
#endif

// =============================================================================
// Include microcontroller header files
// =============================================================================

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
#   if      ((_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F030X6) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F030X8) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F030XC) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F031X6) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F038XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F042X6) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F048XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F051X8) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F058XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F070X6) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F070XB) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F071XB) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F072XB) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F078XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F091XC) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F098XX))
#       include "stm32f0xx.h"
#   elif    ((_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F100XB) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F100XE) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F101X6) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F101XB) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F101XE) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F101XG) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F102X6) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F102XB) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F103X6) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F103XB) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F103XE) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F103XG) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F105XC) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F107XC))
#       include "stm32f1xx.h"
#   elif    ((_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F205XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F207XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F215XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F217XX))
#       include "stm32f2xx.h"
#   elif    ((_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F301X8) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F302X8) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F302XC) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F302XE) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F303X8) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F303XC) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F303XE) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F318XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F328XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F334X8) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F358XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F373XC) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F378XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F398XX))
#       include "stm32f3xx.h"
#   elif    ((_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F401XC) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F401XE) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F405XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F407XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F410CX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F410RX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F410TX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F411XE) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F412CX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F412RX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F412VX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F412ZX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F413XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F415XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F417XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F423XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F427XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F429XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F437XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F439XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F446XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F469XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F479XX))
#       include "stm32f4xx.h"
#   elif    ((_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F722XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F723XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F730XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F732XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F733XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F745XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F746XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F750XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F756XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F765XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F767XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F769XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F777XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32F779XX))
#       include "stm32f7xx.h"
#   elif    ((_FUNSAPE_MCU == _FUNSAPE_ARM_STM32G070XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32G071XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32G081XX))
#       include "stm32g0xx.h"
#   elif    ((_FUNSAPE_MCU == _FUNSAPE_ARM_STM32H743XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32H750XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32H753XX))
#       include "stm32h7xx.h"
#   elif    ((_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L010X4) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L010X6) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L010X8) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L010XB) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L011XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L021XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L031XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L041XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L051XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L052XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L053XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L061XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L062XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L063XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L071XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L072XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L073XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L081XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L082XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L083XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L100XB) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L100XBA) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L100XC))
#       include "stm32l0xx.h"
#   elif    ((_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L151XB) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L151XBA) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L151XC) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L151XCA) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L151XD) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L151XDX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L151XE) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L152XB) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L152XBA) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L152XC) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L152XCA) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L152XD) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L152XDX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L152XE) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L162XC) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L162XCA) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L162XD) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L162XDX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L162XE))
#       include "stm32l1xx.h"
#   elif    ((_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L412XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L422XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L431XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L432XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L433XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L442XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L443XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L451XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L452XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L462XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L471XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L475XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L476XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L485XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L486XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L496XX) || \
            (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L4A6XX) || (_FUNSAPE_MCU == _FUNSAPE_ARM_STM32L4R5XX))
#       include "stm32l4xx.h"
#   else
#   error [funsapeLibProjectConfig.hpp] Error 6 - ARM device unsupported!
#   endif
#endif

#endif // __FUNSAPE_LIB_PROJECT_CONFIG_HPP

// =============================================================================
// END OF FILE
// =============================================================================
