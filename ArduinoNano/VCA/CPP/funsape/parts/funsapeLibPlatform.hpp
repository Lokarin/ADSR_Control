/* =============================================================================
 * Project:         FunSAPE++ MCU Embedded Library
 * File name:       funsapeLibPlatform.hpp
 * Module:          Platform configuration for FunSAPE++ MCU Embedded Library
 *                      project
 * Authors:         Leandro Schwarz
 * Build:           20240111
 * Last edition:    2024-01-11
 * ========================================================================== */

// =============================================================================
// Include guard
// =============================================================================

#ifndef __FUNSAPE_LIB_PLATFORM_HPP
#define __FUNSAPE_LIB_PLATFORM_HPP              2407

// =============================================================================
// Dependencies
// =============================================================================

// -----------------------------------------------------------------------------
// Microcontroller codes -------------------------------------------------------

#include "funsapeLibAvrSupport.hpp"
#ifndef __FUNSAPE_LIB_AVR_SUPPORT_HPP
#   error [funsapeLibPlatform.hpp] Error - Header file (avrSupport.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_AVR_SUPPORT_HPP != __FUNSAPE_LIB_PLATFORM_HPP
#   error [funsapeLibPlatform.hpp] Error - Build mismatch between (funsapeLibPlatform.hpp) and (avrSupport.hpp) header files!
#endif

#include "funsapeLibStm32Support.hpp"
#ifndef __FUNSAPE_LIB_STM32_SUPPORT_HPP
#   error [funsapeLibPlatform.hpp] Error - Header file (stm32Support.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_STM32_SUPPORT_HPP != __FUNSAPE_LIB_PLATFORM_HPP
#   error [funsapeLibPlatform.hpp] Error - Build mismatch between (funsapeLibPlatform.hpp) and (stm32Support.hpp) header files!
#endif

// =============================================================================
// Microcontroller definition
// =============================================================================

// Check for microcontroller previous definition
#if defined(_FUNSAPE_MCU)
#   error   [funsapeLibPlatform.hpp] Error 3 - Microcontroller already defined!
#endif

// -----------------------------------------------------------------------------
// AVR microcontrollers --------------------------------------------------------

#if defined(__AVR_AT43USB320__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT43USB320
#elif defined(__AVR_AT43USB355__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT43USB355
#elif defined(__AVR_AT76C711__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT76C711
#elif defined(__AVR_AT86RF401__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT86RF401
#elif defined(__AVR_AT90C8534__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90C8534
#elif defined(__AVR_AT90CAN128__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90CAN128
#elif defined(__AVR_AT90CAN32__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90CAN32
#elif defined(__AVR_AT90CAN64__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90CAN64
#elif defined(__AVR_AT90PWM1__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90PWM1
#elif defined(__AVR_AT90PWM161__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90PWM161
#elif defined(__AVR_AT90PWM2__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90PWM2
#elif defined(__AVR_AT90PWM216__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90PWM216
#elif defined(__AVR_AT90PWM2B__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90PWM2B
#elif defined(__AVR_AT90PWM3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90PWM3
#elif defined(__AVR_AT90PWM316__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90PWM316
#elif defined(__AVR_AT90PWM3B__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90PWM3B
#elif defined(__AVR_AT90PWM81__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90PWM81
#elif defined(__AVR_AT90S1200__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90S1200
#elif defined(__AVR_AT90S2313__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90S2313
#elif defined(__AVR_AT90S2323__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90S2323
#elif defined(__AVR_AT90S2333__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90S2333
#elif defined(__AVR_AT90S2343__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90S2343
#elif defined(__AVR_AT90S4414__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90S4414
#elif defined(__AVR_AT90S4433__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90S4433
#elif defined(__AVR_AT90S4434__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90S4434
#elif defined(__AVR_AT90S8515__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90S8515
#elif defined(__AVR_AT90S8535__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90S8535
#elif defined(__AVR_AT90SCR100__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90SCR100
#elif defined(__AVR_AT90USB1286__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90USB1286
#elif defined(__AVR_AT90USB1287__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90USB1287
#elif defined(__AVR_AT90USB162__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90USB162
#elif defined(__AVR_AT90USB646__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90USB646
#elif defined(__AVR_AT90USB647__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90USB647
#elif defined(__AVR_AT90USB82__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT90USB82
#elif defined(__AVR_AT94K__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_AT94K
#elif defined(__AVR_ATA5272__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA5272
#elif defined(__AVR_ATA5505__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA5505
#elif defined(__AVR_ATA5702M322__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA5702M322
#elif defined(__AVR_ATA5782__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA5782
#elif defined(__AVR_ATA5790__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA5790
#elif defined(__AVR_ATA5790N__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA5790N
#elif defined(__AVR_ATA5791__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA5791
#elif defined(__AVR_ATA5795__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA5795
#elif defined(__AVR_ATA5831__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA5831
#elif defined(__AVR_ATA6285__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA6285
#elif defined(__AVR_ATA6286__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA6286
#elif defined(__AVR_ATA6289__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA6289
#elif defined(__AVR_ATA6612C__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA6612C
#elif defined(__AVR_ATA6613C__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA6613C
#elif defined(__AVR_ATA6614Q__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA6614Q
#elif defined(__AVR_ATA6616C__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA6616C
#elif defined(__AVR_ATA6617C__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA6617C
#elif defined(__AVR_ATA664251__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA664251
#elif defined(__AVR_ATA8210__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA8210
#elif defined(__AVR_ATA8510__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATA8510
#elif defined(__AVR_ATmega103__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA103
#elif defined(__AVR_ATmega128__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA128
#elif defined(__AVR_ATmega1280__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA1280
#elif defined(__AVR_ATmega1281__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA1281
#elif defined(__AVR_ATmega1284__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA1284
#elif defined(__AVR_ATmega1284P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA1284P
#elif defined(__AVR_ATmega1284RFR2__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA1284RFR2
#elif defined(__AVR_ATmega128A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA128A
#elif defined(__AVR_ATmega128RFA1__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA128RFA1
#elif defined(__AVR_ATmega128RFR2__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA128RFR2
#elif defined(__AVR_ATmega16__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA16
#elif defined(__AVR_ATmega161__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA161
#elif defined(__AVR_ATmega162__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA162
#elif defined(__AVR_ATmega163__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA163
#elif defined(__AVR_ATmega164A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA164A
#elif defined(__AVR_ATmega164P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA164P
#elif defined(__AVR_ATmega164PA__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA164PA
#elif defined(__AVR_ATmega165__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA165
#elif defined(__AVR_ATmega165A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA165A
#elif defined(__AVR_ATmega165P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA165P
#elif defined(__AVR_ATmega165PA__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA165PA
#elif defined(__AVR_ATmega168__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA168
#elif defined(__AVR_ATmega168A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA168A
#elif defined(__AVR_ATmega168P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA168P
#elif defined(__AVR_ATmega168PA__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA168PA
#elif defined(__AVR_ATmega168PB__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA168PB
#elif defined(__AVR_ATmega169__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA169
#elif defined(__AVR_ATmega169A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA169A
#elif defined(__AVR_ATmega169P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA169P
#elif defined(__AVR_ATmega169PA__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA169PA
#elif defined(__AVR_ATmega16A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA16A
#elif defined(__AVR_ATmega16HVA__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA16HVA
#elif defined(__AVR_ATmega16HVA2__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA16HVA2
#elif defined(__AVR_ATmega16HVB__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA16HVB
#elif defined(__AVR_ATmega16HVBREVB__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA16HVBREVB
#elif defined(__AVR_ATmega16M1__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA16M1
#elif defined(__AVR_ATmega16U2__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA16U2
#elif defined(__AVR_ATmega16U4__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA16U4
#elif defined(__AVR_ATmega2560__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA2560
#elif defined(__AVR_ATmega2561__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA2561
#elif defined(__AVR_ATmega2564RFR2__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA2564RFR2
#elif defined(__AVR_ATmega256RFR2__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA256RFR2
#elif defined(__AVR_ATmega32__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA32
#elif defined(__AVR_ATmega323__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA323
#elif defined(__AVR_ATmega324A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA324A
#elif defined(__AVR_ATmega324P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA324P
#elif defined(__AVR_ATmega324PA__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA324PA
#elif defined(__AVR_ATmega325__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA325
#elif defined(__AVR_ATmega3250__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA3250
#elif defined(__AVR_ATmega3250A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA3250A
#elif defined(__AVR_ATmega3250P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA3250P
#elif defined(__AVR_ATmega3250PA__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA3250PA
#elif defined(__AVR_ATmega325A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA325A
#elif defined(__AVR_ATmega325P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA325P
#elif defined(__AVR_ATmega325PA__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA325PA
#elif defined(__AVR_ATmega328__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA328
#elif defined(__AVR_ATmega328P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA328P
#elif defined(__AVR_ATmega329__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA329
#elif defined(__AVR_ATmega3290__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA3290
#elif defined(__AVR_ATmega3290A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA3290A
#elif defined(__AVR_ATmega3290P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA3290P
#elif defined(__AVR_ATmega3290PA__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA3290PA
#elif defined(__AVR_ATmega329A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA329A
#elif defined(__AVR_ATmega329P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA329P
#elif defined(__AVR_ATmega329PA__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA329PA
#elif defined(__AVR_ATmega32A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA32A
#elif defined(__AVR_ATmega32C1__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA32C1
#elif defined(__AVR_ATmega32HVB__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA32HVB
#elif defined(__AVR_ATmega32HVBREVB__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA32HVBREVB
#elif defined(__AVR_ATmega32M1__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA32M1
#elif defined(__AVR_ATmega32U2__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA32U2
#elif defined(__AVR_ATmega32U4__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA32U4
#elif defined(__AVR_ATmega32U6__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA32U6
#elif defined(__AVR_ATmega406__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA406
#elif defined(__AVR_ATmega48__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA48
#elif defined(__AVR_ATmega48A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA48A
#elif defined(__AVR_ATmega48P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA48P
#elif defined(__AVR_ATmega48PA__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA48PA
#elif defined(__AVR_ATmega48PB__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA48PB
#elif defined(__AVR_ATmega64__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA64
#elif defined(__AVR_ATmega640__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA640
#elif defined(__AVR_ATmega644__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA644
#elif defined(__AVR_ATmega644A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA644A
#elif defined(__AVR_ATmega644P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA644P
#elif defined(__AVR_ATmega644PA__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA644PA
#elif defined(__AVR_ATmega644RFR2__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA644RFR2
#elif defined(__AVR_ATmega645__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA645
#elif defined(__AVR_ATmega6450__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA6450
#elif defined(__AVR_ATmega6450A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA6450A
#elif defined(__AVR_ATmega6450P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA6450P
#elif defined(__AVR_ATmega645A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA645A
#elif defined(__AVR_ATmega645P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA645P
#elif defined(__AVR_ATmega649__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA649
#elif defined(__AVR_ATmega6490__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA6490
#elif defined(__AVR_ATmega6490A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA6490A
#elif defined(__AVR_ATmega6490P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA6490P
#elif defined(__AVR_ATmega649A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA649A
#elif defined(__AVR_ATmega649P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA649P
#elif defined(__AVR_ATmega64A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA64A
#elif defined(__AVR_ATmega64C1__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA64C1
#elif defined(__AVR_ATmega64HVE__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA64HVE
#elif defined(__AVR_ATmega64HVE2__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA64HVE2
#elif defined(__AVR_ATmega64M1__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA64M1
#elif defined(__AVR_ATmega64RFR2__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA64RFR2
#elif defined(__AVR_ATmega8__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA8
#elif defined(__AVR_ATmega8515__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA8515
#elif defined(__AVR_ATmega8535__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA8535
#elif defined(__AVR_ATmega88__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA88
#elif defined(__AVR_ATmega88A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA88A
#elif defined(__AVR_ATmega88P__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA88P
#elif defined(__AVR_ATmega88PA__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA88PA
#elif defined(__AVR_ATmega88PB__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA88PB
#elif defined(__AVR_ATmega8A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA8A
#elif defined(__AVR_ATmega8HVA__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA8HVA
#elif defined(__AVR_ATmega8U2__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATMEGA8U2
#elif defined(__AVR_ATtiny10__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY10
#elif defined(__AVR_ATtiny11__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY11
#elif defined(__AVR_ATtiny12__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY12
#elif defined(__AVR_ATtiny13__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY13
#elif defined(__AVR_ATtiny13A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY13A
#elif defined(__AVR_ATtiny15__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY15
#elif defined(__AVR_ATtiny1634__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY1634
#elif defined(__AVR_ATtiny167__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY167
#elif defined(__AVR_ATtiny20__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY20
#elif defined(__AVR_ATtiny22__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY22
#elif defined(__AVR_ATtiny2313__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY2313
#elif defined(__AVR_ATtiny2313A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY2313A
#elif defined(__AVR_ATtiny24__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY24
#elif defined(__AVR_ATtiny24A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY24A
#elif defined(__AVR_ATtiny25__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY25
#elif defined(__AVR_ATtiny26__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY26
#elif defined(__AVR_ATtiny261__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY261
#elif defined(__AVR_ATtiny261A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY261A
#elif defined(__AVR_ATtiny28__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY28
#elif defined(__AVR_ATtiny4__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY4
#elif defined(__AVR_ATtiny40__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY40
#elif defined(__AVR_ATtiny4313__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY4313
#elif defined(__AVR_ATtiny43U__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY43U
#elif defined(__AVR_ATtiny44__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY44
#elif defined(__AVR_ATtiny441__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY441
#elif defined(__AVR_ATtiny44A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY44A
#elif defined(__AVR_ATtiny45__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY45
#elif defined(__AVR_ATtiny461__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY461
#elif defined(__AVR_ATtiny461A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY461A
#elif defined(__AVR_ATtiny48__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY48
#elif defined(__AVR_ATtiny5__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY5
#elif defined(__AVR_ATtiny828__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY828
#elif defined(__AVR_ATtiny84__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY84
#elif defined(__AVR_ATtiny841__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY841
#elif defined(__AVR_ATtiny84A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY84A
#elif defined(__AVR_ATtiny85__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY85
#elif defined(__AVR_ATtiny861__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY861
#elif defined(__AVR_ATtiny861A__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY861A
#elif defined(__AVR_ATtiny87__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY87
#elif defined(__AVR_ATtiny88__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY88
#elif defined(__AVR_ATtiny9__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATTINY9
#elif defined(__AVR_ATxmega128A1__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA128A1
#elif defined(__AVR_ATxmega128A1U__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA128A1U
#elif defined(__AVR_ATxmega128A3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA128A3
#elif defined(__AVR_ATxmega128A3U__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA128A3U
#elif defined(__AVR_ATxmega128A4U__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA128A4U
#elif defined(__AVR_ATxmega128B1__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA128B1
#elif defined(__AVR_ATxmega128B3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA128B3
#elif defined(__AVR_ATxmega128C3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA128C3
#elif defined(__AVR_ATxmega128D3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA128D3
#elif defined(__AVR_ATxmega128D4__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA128D4
#elif defined(__AVR_ATxmega16A4__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA16A4
#elif defined(__AVR_ATxmega16A4U__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA16A4U
#elif defined(__AVR_ATxmega16C4__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA16C4
#elif defined(__AVR_ATxmega16D4__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA16D4
#elif defined(__AVR_ATxmega16E5__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA16E5
#elif defined(__AVR_ATxmega192A3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA192A3
#elif defined(__AVR_ATxmega192A3U__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA192A3U
#elif defined(__AVR_ATxmega192C3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA192C3
#elif defined(__AVR_ATxmega192D3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA192D3
#elif defined(__AVR_ATxmega256A3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA256A3
#elif defined(__AVR_ATxmega256A3B__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA256A3B
#elif defined(__AVR_ATxmega256A3BU__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA256A3BU
#elif defined(__AVR_ATxmega256A3U__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA256A3U
#elif defined(__AVR_ATxmega256C3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA256C3
#elif defined(__AVR_ATxmega256D3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA256D3
#elif defined(__AVR_ATxmega32A4__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA32A4
#elif defined(__AVR_ATxmega32A4U__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA32A4U
#elif defined(__AVR_ATxmega32C3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA32C3
#elif defined(__AVR_ATxmega32C4__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA32C4
#elif defined(__AVR_ATxmega32D3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA32D3
#elif defined(__AVR_ATxmega32D4__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA32D4
#elif defined(__AVR_ATxmega32E5__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA32E5
#elif defined(__AVR_ATxmega384C3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA384C3
#elif defined(__AVR_ATxmega384D3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA384D3
#elif defined(__AVR_ATxmega64A1__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA64A1
#elif defined(__AVR_ATxmega64A1U__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA64A1U
#elif defined(__AVR_ATxmega64A3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA64A3
#elif defined(__AVR_ATxmega64A3U__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA64A3U
#elif defined(__AVR_ATxmega64A4U__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA64A4U
#elif defined(__AVR_ATxmega64B1__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA64B1
#elif defined(__AVR_ATxmega64B3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA64B3
#elif defined(__AVR_ATxmega64C3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA64C3
#elif defined(__AVR_ATxmega64D3__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA64D3
#elif defined(__AVR_ATxmega64D4__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA64D4
#elif defined(__AVR_ATxmega8E5__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_ATXMEGA8E5
#elif defined(__AVR_M3000__)
#   define _FUNSAPE_MCU                 _FUNSAPE_AVR_M3000
// Listing continues below

// -----------------------------------------------------------------------------
// ARM (STM32) microcontrollers ------------------------------------------------

#elif defined(STM32F030x6)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F030X6
#elif defined(STM32F030x8)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F030X8
#elif defined(STM32F030xC)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F030XC
#elif defined(STM32F031x6)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F031X6
#elif defined(STM32F038xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F038XX
#elif defined(STM32F042x6)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F042X6
#elif defined(STM32F048xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F048XX
#elif defined(STM32F051x8)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F051X8
#elif defined(STM32F058xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F058XX
#elif defined(STM32F070x6)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F070X6
#elif defined(STM32F070xB)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F070XB
#elif defined(STM32F071xB)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F071XB
#elif defined(STM32F072xB)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F072XB
#elif defined(STM32F078xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F078XX
#elif defined(STM32F091xC)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F091XC
#elif defined(STM32F098xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F098XX
#elif defined(STM32F100xB)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F100XB
#elif defined(STM32F100xE)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F100XE
#elif defined(STM32F101x6)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F101X6
#elif defined(STM32F101xB)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F101XB
#elif defined(STM32F101xE)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F101XE
#elif defined(STM32F101xG)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F101XG
#elif defined(STM32F102x6)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F102X6
#elif defined(STM32F102xB)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F102XB
#elif defined(STM32F103x6)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F103X6
#elif defined(STM32F103xB)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F103XB
#elif defined(STM32F103xE)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F103XE
#elif defined(STM32F103xG)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F103XG
#elif defined(STM32F105xC)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F105XC
#elif defined(STM32F107xC)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F107XC
#elif defined(STM32F205xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F205XX
#elif defined(STM32F207xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F207XX
#elif defined(STM32F215xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F215XX
#elif defined(STM32F217xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F217XX
#elif defined(STM32F301x8)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F301X8
#elif defined(STM32F302x8)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F302X8
#elif defined(STM32F302xC)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F302XC
#elif defined(STM32F302xE)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F302XE
#elif defined(STM32F303x8)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F303X8
#elif defined(STM32F303xC)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F303XC
#elif defined(STM32F303xE)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F303XE
#elif defined(STM32F318xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F318XX
#elif defined(STM32F328xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F328XX
#elif defined(STM32F334x8)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F334X8
#elif defined(STM32F358xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F358XX
#elif defined(STM32F373xC)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F373XC
#elif defined(STM32F378xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F378XX
#elif defined(STM32F398xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F398XX
#elif defined(STM32F401xC)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F401XC
#elif defined(STM32F401xE)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F401XE
#elif defined(STM32F405xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F405XX
#elif defined(STM32F407xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F407XX
#elif defined(STM32F410Cx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F410CX
#elif defined(STM32F410Rx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F410RX
#elif defined(STM32F410Tx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F410TX
#elif defined(STM32F411xE)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F411XE
#elif defined(STM32F412Cx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F412CX
#elif defined(STM32F412Rx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F412RX
#elif defined(STM32F412Vx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F412VX
#elif defined(STM32F412Zx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F412ZX
#elif defined(STM32F413xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F413XX
#elif defined(STM32F415xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F415XX
#elif defined(STM32F417xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F417XX
#elif defined(STM32F423xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F423XX
#elif defined(STM32F427xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F427XX
#elif defined(STM32F429xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F429XX
#elif defined(STM32F437xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F437XX
#elif defined(STM32F439xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F439XX
#elif defined(STM32F446xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F446XX
#elif defined(STM32F469xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F469XX
#elif defined(STM32F479xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F479XX
#elif defined(STM32F722xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F722XX
#elif defined(STM32F723xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F723XX
#elif defined(STM32F730xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F730XX
#elif defined(STM32F732xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F732XX
#elif defined(STM32F733xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F733XX
#elif defined(STM32F745xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F745XX
#elif defined(STM32F746xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F746XX
#elif defined(STM32F750xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F750XX
#elif defined(STM32F756xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F756XX
#elif defined(STM32F765xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F765XX
#elif defined(STM32F767xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F767XX
#elif defined(STM32F769xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F769XX
#elif defined(STM32F777xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F777XX
#elif defined(STM32F779xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32F779XX
#elif defined(STM32G070xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32G070XX
#elif defined(STM32G071xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32G071XX
#elif defined(STM32G081xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32G081XX
#elif defined(STM32H743xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32H743XX
#elif defined(STM32H750xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32H750XX
#elif defined(STM32H753xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32H753XX
#elif defined(STM32L010x4)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L010X4
#elif defined(STM32L010x6)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L010X6
#elif defined(STM32L010x8)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L010X8
#elif defined(STM32L010xB)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L010XB
#elif defined(STM32L011xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L011XX
#elif defined(STM32L021xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L021XX
#elif defined(STM32L031xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L031XX
#elif defined(STM32L041xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L041XX
#elif defined(STM32L051xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L051XX
#elif defined(STM32L052xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L052XX
#elif defined(STM32L053xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L053XX
#elif defined(STM32L061xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L061XX
#elif defined(STM32L062xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L062XX
#elif defined(STM32L063xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L063XX
#elif defined(STM32L071xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L071XX
#elif defined(STM32L072xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L072XX
#elif defined(STM32L073xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L073XX
#elif defined(STM32L081xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L081XX
#elif defined(STM32L082xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L082XX
#elif defined(STM32L083xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L083XX
#elif defined(STM32L100xB)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L100XB
#elif defined(STM32L100xBA)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L100XBA
#elif defined(STM32L100xC)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L100XC
#elif defined(STM32L151xB)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L151XB
#elif defined(STM32L151xBA)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L151XBA
#elif defined(STM32L151xC)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L151XC
#elif defined(STM32L151xCA)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L151XCA
#elif defined(STM32L151xD)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L151XD
#elif defined(STM32L151xDX)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L151XDX
#elif defined(STM32L151xE)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L151XE
#elif defined(STM32L152xB)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L152XB
#elif defined(STM32L152xBA)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L152XBA
#elif defined(STM32L152xC)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L152XC
#elif defined(STM32L152xCA)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L152XCA
#elif defined(STM32L152xD)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L152XD
#elif defined(STM32L152xDX)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L152XDX
#elif defined(STM32L152xE)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L152XE
#elif defined(STM32L162xC)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L162XC
#elif defined(STM32L162xCA)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L162XCA
#elif defined(STM32L162xD)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L162XD
#elif defined(STM32L162xDX)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L162XDX
#elif defined(STM32L162xE)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L162XE
#elif defined(STM32L412xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L412XX
#elif defined(STM32L422xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L422XX
#elif defined(STM32L431xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L431XX
#elif defined(STM32L432xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L432XX
#elif defined(STM32L433xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L433XX
#elif defined(STM32L442xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L442XX
#elif defined(STM32L443xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L443XX
#elif defined(STM32L451xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L451XX
#elif defined(STM32L452xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L452XX
#elif defined(STM32L462xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L462XX
#elif defined(STM32L471xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L471XX
#elif defined(STM32L475xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L475XX
#elif defined(STM32L476xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L476XX
#elif defined(STM32L485xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L485XX
#elif defined(STM32L486xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L486XX
#elif defined(STM32L496xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L496XX
#elif defined(STM32L4A6xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L4A6XX
#elif defined(STM32L4R5xx)
#   define _FUNSAPE_MCU                 _FUNSAPE_ARM_STM32L4R5XX
// Listing continues below

// -----------------------------------------------------------------------------
// End of list -----------------------------------------------------------------

#endif

// Final MCU Part number
#if !defined(_FUNSAPE_MCU)
#   error [funsapeLibPlatform.hpp] Error 4 - Microcontroller not defined!
#endif

// =============================================================================
// Platform definition
// =============================================================================

#if     (_FUNSAPE_MCU >= _FUNSAPE_AVR_FIRST) && (_FUNSAPE_MCU <= _FUNSAPE_AVR_LAST)
#   define _FUNSAPE_PLATFORM_AVR
#elif   (_FUNSAPE_MCU >= _FUNSAPE_ARM_STM32_FIRST) && (_FUNSAPE_MCU <= _FUNSAPE_ARM_STM32_LAST)
#   define _FUNSAPE_PLATFORM_ARM_STM32
#else
#   error [funsapeLibPlatform.hpp] Error - Unable to identify platform!
#endif

#endif // __FUNSAPE_LIB_PLATFORM_HPP

// =============================================================================
// END OF FILE
// =============================================================================
