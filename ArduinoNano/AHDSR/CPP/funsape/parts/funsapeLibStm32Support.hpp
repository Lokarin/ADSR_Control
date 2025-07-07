/* =============================================================================
 * Project:         FunSAPE++ MCU Embedded Library
 * File name:       funsapeLibStm32Support.hpp
 * Module:          ARM STM32 microcontrollers support for FunSAPE++ MCU
 *                      Embedded Library project
 * Authors:         Leandro Schwarz
 * Build:           20240111
 * Last edition:    2024-01-11
 * ========================================================================== */

// =============================================================================
// Include guard
// =============================================================================

#ifndef __FUNSAPE_LIB_STM32_SUPPORT_HPP
#define __FUNSAPE_LIB_STM32_SUPPORT_HPP         2407

// =============================================================================
// Microcontroller codes
// =============================================================================

#define _FUNSAPE_ARM_STM32F030X6        501
#define _FUNSAPE_ARM_STM32F030X8        502
#define _FUNSAPE_ARM_STM32F030XC        503
#define _FUNSAPE_ARM_STM32F031X6        504
#define _FUNSAPE_ARM_STM32F038XX        505
#define _FUNSAPE_ARM_STM32F042X6        506
#define _FUNSAPE_ARM_STM32F048XX        507
#define _FUNSAPE_ARM_STM32F051X8        508
#define _FUNSAPE_ARM_STM32F058XX        509
#define _FUNSAPE_ARM_STM32F070X6        510
#define _FUNSAPE_ARM_STM32F070XB        511
#define _FUNSAPE_ARM_STM32F071XB        512
#define _FUNSAPE_ARM_STM32F072XB        513
#define _FUNSAPE_ARM_STM32F078XX        514
#define _FUNSAPE_ARM_STM32F091XC        515
#define _FUNSAPE_ARM_STM32F098XX        516
#define _FUNSAPE_ARM_STM32F100XB        517
#define _FUNSAPE_ARM_STM32F100XE        518
#define _FUNSAPE_ARM_STM32F101X6        519
#define _FUNSAPE_ARM_STM32F101XB        520
#define _FUNSAPE_ARM_STM32F101XE        521
#define _FUNSAPE_ARM_STM32F101XG        522
#define _FUNSAPE_ARM_STM32F102X6        523
#define _FUNSAPE_ARM_STM32F102XB        524
#define _FUNSAPE_ARM_STM32F103X6        525
#define _FUNSAPE_ARM_STM32F103XB        526
#define _FUNSAPE_ARM_STM32F103XE        527
#define _FUNSAPE_ARM_STM32F103XG        528
#define _FUNSAPE_ARM_STM32F105XC        529
#define _FUNSAPE_ARM_STM32F107XC        530
#define _FUNSAPE_ARM_STM32F205XX        531
#define _FUNSAPE_ARM_STM32F207XX        532
#define _FUNSAPE_ARM_STM32F215XX        533
#define _FUNSAPE_ARM_STM32F217XX        534
#define _FUNSAPE_ARM_STM32F301X8        535
#define _FUNSAPE_ARM_STM32F302X8        536
#define _FUNSAPE_ARM_STM32F302XC        537
#define _FUNSAPE_ARM_STM32F302XE        538
#define _FUNSAPE_ARM_STM32F303X8        539
#define _FUNSAPE_ARM_STM32F303XC        540
#define _FUNSAPE_ARM_STM32F303XE        541
#define _FUNSAPE_ARM_STM32F318XX        542
#define _FUNSAPE_ARM_STM32F328XX        543
#define _FUNSAPE_ARM_STM32F334X8        544
#define _FUNSAPE_ARM_STM32F358XX        545
#define _FUNSAPE_ARM_STM32F373XC        546
#define _FUNSAPE_ARM_STM32F378XX        547
#define _FUNSAPE_ARM_STM32F398XX        548
#define _FUNSAPE_ARM_STM32F401XC        549
#define _FUNSAPE_ARM_STM32F401XE        550
#define _FUNSAPE_ARM_STM32F405XX        551
#define _FUNSAPE_ARM_STM32F407XX        552
#define _FUNSAPE_ARM_STM32F410CX        553
#define _FUNSAPE_ARM_STM32F410RX        554
#define _FUNSAPE_ARM_STM32F410TX        555
#define _FUNSAPE_ARM_STM32F411XE        556
#define _FUNSAPE_ARM_STM32F412CX        557
#define _FUNSAPE_ARM_STM32F412RX        558
#define _FUNSAPE_ARM_STM32F412VX        559
#define _FUNSAPE_ARM_STM32F412ZX        560
#define _FUNSAPE_ARM_STM32F413XX        561
#define _FUNSAPE_ARM_STM32F415XX        562
#define _FUNSAPE_ARM_STM32F417XX        563
#define _FUNSAPE_ARM_STM32F423XX        564
#define _FUNSAPE_ARM_STM32F427XX        565
#define _FUNSAPE_ARM_STM32F429XX        566
#define _FUNSAPE_ARM_STM32F437XX        567
#define _FUNSAPE_ARM_STM32F439XX        568
#define _FUNSAPE_ARM_STM32F446XX        569
#define _FUNSAPE_ARM_STM32F469XX        570
#define _FUNSAPE_ARM_STM32F479XX        571
#define _FUNSAPE_ARM_STM32F722XX        572
#define _FUNSAPE_ARM_STM32F723XX        573
#define _FUNSAPE_ARM_STM32F730XX        574
#define _FUNSAPE_ARM_STM32F732XX        575
#define _FUNSAPE_ARM_STM32F733XX        576
#define _FUNSAPE_ARM_STM32F745XX        577
#define _FUNSAPE_ARM_STM32F746XX        578
#define _FUNSAPE_ARM_STM32F750XX        579
#define _FUNSAPE_ARM_STM32F756XX        580
#define _FUNSAPE_ARM_STM32F765XX        581
#define _FUNSAPE_ARM_STM32F767XX        582
#define _FUNSAPE_ARM_STM32F769XX        583
#define _FUNSAPE_ARM_STM32F777XX        584
#define _FUNSAPE_ARM_STM32F779XX        585
#define _FUNSAPE_ARM_STM32G070XX        586
#define _FUNSAPE_ARM_STM32G071XX        587
#define _FUNSAPE_ARM_STM32G081XX        588
#define _FUNSAPE_ARM_STM32H743XX        589
#define _FUNSAPE_ARM_STM32H750XX        590
#define _FUNSAPE_ARM_STM32H753XX        591
#define _FUNSAPE_ARM_STM32L010X4        592
#define _FUNSAPE_ARM_STM32L010X6        593
#define _FUNSAPE_ARM_STM32L010X8        594
#define _FUNSAPE_ARM_STM32L010XB        595
#define _FUNSAPE_ARM_STM32L011XX        596
#define _FUNSAPE_ARM_STM32L021XX        597
#define _FUNSAPE_ARM_STM32L031XX        598
#define _FUNSAPE_ARM_STM32L041XX        599
#define _FUNSAPE_ARM_STM32L051XX        600
#define _FUNSAPE_ARM_STM32L052XX        601
#define _FUNSAPE_ARM_STM32L053XX        602
#define _FUNSAPE_ARM_STM32L061XX        603
#define _FUNSAPE_ARM_STM32L062XX        604
#define _FUNSAPE_ARM_STM32L063XX        605
#define _FUNSAPE_ARM_STM32L071XX        606
#define _FUNSAPE_ARM_STM32L072XX        607
#define _FUNSAPE_ARM_STM32L073XX        608
#define _FUNSAPE_ARM_STM32L081XX        609
#define _FUNSAPE_ARM_STM32L082XX        610
#define _FUNSAPE_ARM_STM32L083XX        611
#define _FUNSAPE_ARM_STM32L100XB        612
#define _FUNSAPE_ARM_STM32L100XBA       613
#define _FUNSAPE_ARM_STM32L100XC        614
#define _FUNSAPE_ARM_STM32L151XB        615
#define _FUNSAPE_ARM_STM32L151XBA       616
#define _FUNSAPE_ARM_STM32L151XC        617
#define _FUNSAPE_ARM_STM32L151XCA       618
#define _FUNSAPE_ARM_STM32L151XD        619
#define _FUNSAPE_ARM_STM32L151XDX       620
#define _FUNSAPE_ARM_STM32L151XE        621
#define _FUNSAPE_ARM_STM32L152XB        622
#define _FUNSAPE_ARM_STM32L152XBA       623
#define _FUNSAPE_ARM_STM32L152XC        624
#define _FUNSAPE_ARM_STM32L152XCA       625
#define _FUNSAPE_ARM_STM32L152XD        626
#define _FUNSAPE_ARM_STM32L152XDX       627
#define _FUNSAPE_ARM_STM32L152XE        628
#define _FUNSAPE_ARM_STM32L162XC        629
#define _FUNSAPE_ARM_STM32L162XCA       630
#define _FUNSAPE_ARM_STM32L162XD        631
#define _FUNSAPE_ARM_STM32L162XDX       632
#define _FUNSAPE_ARM_STM32L162XE        633
#define _FUNSAPE_ARM_STM32L412XX        634
#define _FUNSAPE_ARM_STM32L422XX        635
#define _FUNSAPE_ARM_STM32L431XX        636
#define _FUNSAPE_ARM_STM32L432XX        637
#define _FUNSAPE_ARM_STM32L433XX        638
#define _FUNSAPE_ARM_STM32L442XX        639
#define _FUNSAPE_ARM_STM32L443XX        640
#define _FUNSAPE_ARM_STM32L451XX        641
#define _FUNSAPE_ARM_STM32L452XX        642
#define _FUNSAPE_ARM_STM32L462XX        643
#define _FUNSAPE_ARM_STM32L471XX        644
#define _FUNSAPE_ARM_STM32L475XX        645
#define _FUNSAPE_ARM_STM32L476XX        646
#define _FUNSAPE_ARM_STM32L485XX        647
#define _FUNSAPE_ARM_STM32L486XX        648
#define _FUNSAPE_ARM_STM32L496XX        649
#define _FUNSAPE_ARM_STM32L4A6XX        650
#define _FUNSAPE_ARM_STM32L4R5XX        651

#define _FUNSAPE_ARM_STM32_FIRST        501
#define _FUNSAPE_ARM_STM32_LAST         651

#endif // __FUNSAPE_LIB_STM32_SUPPORT_HPP

// =============================================================================
// END OF FILE
// =============================================================================
