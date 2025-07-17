# ##############################################################################
# MCU Makefile essentials - AVR device detection
# ##############################################################################

ifeq ($(MCU_DEVICE_CODE), 0)
    ifeq ($(MCU_DEVICE_NAME),at43usb320)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 1)
        MCU_DEVICE_MACRO				= __AVR_AT43USB320__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at43usb355)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 2)
        MCU_DEVICE_MACRO				= __AVR_AT43USB355__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at76c711)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 3)
        MCU_DEVICE_MACRO				= __AVR_AT76C711__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at86rf401)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 4)
        MCU_DEVICE_MACRO				= __AVR_AT86RF401__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90c8534)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 5)
        MCU_DEVICE_MACRO				= __AVR_AT90C8534__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90can128)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 6)
        MCU_DEVICE_MACRO				= __AVR_AT90CAN128__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90can32)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 7)
        MCU_DEVICE_MACRO				= __AVR_AT90CAN32__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90can64)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 8)
        MCU_DEVICE_MACRO				= __AVR_AT90CAN64__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90pwm1)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 9)
        MCU_DEVICE_MACRO				= __AVR_AT90PWM1__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90pwm161)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 10)
        MCU_DEVICE_MACRO				= __AVR_AT90PWM161__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90pwm2)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 11)
        MCU_DEVICE_MACRO				= __AVR_AT90PWM2__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90pwm216)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 12)
        MCU_DEVICE_MACRO				= __AVR_AT90PWM216__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90pwm2b)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 13)
        MCU_DEVICE_MACRO				= __AVR_AT90PWM2B__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90pwm3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 14)
        MCU_DEVICE_MACRO				= __AVR_AT90PWM3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90pwm316)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 15)
        MCU_DEVICE_MACRO				= __AVR_AT90PWM316__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90pwm3b)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 16)
        MCU_DEVICE_MACRO				= __AVR_AT90PWM3B__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90pwm81)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 17)
        MCU_DEVICE_MACRO				= __AVR_AT90PWM81__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90s1200)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 18)
        MCU_DEVICE_MACRO				= __AVR_AT90S1200__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90s2313)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 19)
        MCU_DEVICE_MACRO				= __AVR_AT90S2313__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90s2323)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 20)
        MCU_DEVICE_MACRO				= __AVR_AT90S2323__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90s2333)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 21)
        MCU_DEVICE_MACRO				= __AVR_AT90S2333__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90s2343)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 22)
        MCU_DEVICE_MACRO				= __AVR_AT90S2343__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90s4414)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 23)
        MCU_DEVICE_MACRO				= __AVR_AT90S4414__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90s4433)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 24)
        MCU_DEVICE_MACRO				= __AVR_AT90S4433__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90s4434)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 25)
        MCU_DEVICE_MACRO				= __AVR_AT90S4434__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90s8515)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 26)
        MCU_DEVICE_MACRO				= __AVR_AT90S8515__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90s8535)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 27)
        MCU_DEVICE_MACRO				= __AVR_AT90S8535__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90scr100)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 28)
        MCU_DEVICE_MACRO				= __AVR_AT90SCR100__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90usb1286)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 29)
        MCU_DEVICE_MACRO				= __AVR_AT90USB1286__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90usb1287)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 30)
        MCU_DEVICE_MACRO				= __AVR_AT90USB1287__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90usb162)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 31)
        MCU_DEVICE_MACRO				= __AVR_AT90USB162__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90usb646)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 32)
        MCU_DEVICE_MACRO				= __AVR_AT90USB646__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90usb647)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 33)
        MCU_DEVICE_MACRO				= __AVR_AT90USB647__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at90usb82)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 34)
        MCU_DEVICE_MACRO				= __AVR_AT90USB82__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),at94k)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 35)
        MCU_DEVICE_MACRO				= __AVR_AT94K__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata5272)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 36)
        MCU_DEVICE_MACRO				= __AVR_ATA5272__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata5505)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 37)
        MCU_DEVICE_MACRO				= __AVR_ATA5505__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata5702m322)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 38)
        MCU_DEVICE_MACRO				= __AVR_ATA5702M322__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata5782)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 39)
        MCU_DEVICE_MACRO				= __AVR_ATA5782__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata5790)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 40)
        MCU_DEVICE_MACRO				= __AVR_ATA5790__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata5790n)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 41)
        MCU_DEVICE_MACRO				= __AVR_ATA5790N__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata5795)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 42)
        MCU_DEVICE_MACRO				= __AVR_ATA5795__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata5831)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 43)
        MCU_DEVICE_MACRO				= __AVR_ATA5831__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata6285)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 44)
        MCU_DEVICE_MACRO				= __AVR_ATA6285__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata6286)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 45)
        MCU_DEVICE_MACRO				= __AVR_ATA6286__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata6289)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 46)
        MCU_DEVICE_MACRO				= __AVR_ATA6289__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata6612c)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 47)
        MCU_DEVICE_MACRO				= __AVR_ATA6612C__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata6613c)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 48)
        MCU_DEVICE_MACRO				= __AVR_ATA6613C__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata6614q)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 49)
        MCU_DEVICE_MACRO				= __AVR_ATA6614Q__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata6616c)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 50)
        MCU_DEVICE_MACRO				= __AVR_ATA6616C__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata6617c)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 51)
        MCU_DEVICE_MACRO				= __AVR_ATA6617C__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),ata664251)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 52)
        MCU_DEVICE_MACRO				= __AVR_ATA664251__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega103)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 53)
        MCU_DEVICE_MACRO				= __AVR_ATmega103__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega128)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 54)
        MCU_DEVICE_MACRO				= __AVR_ATmega128__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega1280)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 55)
        MCU_DEVICE_MACRO				= __AVR_ATmega1280__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega1281)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 56)
        MCU_DEVICE_MACRO				= __AVR_ATmega1281__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega1284)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 57)
        MCU_DEVICE_MACRO				= __AVR_ATmega1284__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega1284p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 58)
        MCU_DEVICE_MACRO				= __AVR_ATmega1284P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega1284rfr2)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 59)
        MCU_DEVICE_MACRO				= __AVR_ATmega1284RFR2__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega128a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 60)
        MCU_DEVICE_MACRO				= __AVR_ATmega128A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega128rfr2)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 61)
        MCU_DEVICE_MACRO				= __AVR_ATmega128RFR2__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega16)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 62)
        MCU_DEVICE_MACRO				= __AVR_ATmega16__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega161)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 63)
        MCU_DEVICE_MACRO				= __AVR_ATmega161__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega162)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 64)
        MCU_DEVICE_MACRO				= __AVR_ATmega162__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega163)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 65)
        MCU_DEVICE_MACRO				= __AVR_ATmega163__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega164a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 66)
        MCU_DEVICE_MACRO				= __AVR_ATmega164A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega164p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 67)
        MCU_DEVICE_MACRO				= __AVR_ATmega164P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega164pa)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 68)
        MCU_DEVICE_MACRO				= __AVR_ATmega164PA__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega165)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 69)
        MCU_DEVICE_MACRO				= __AVR_ATmega165__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega165a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 70)
        MCU_DEVICE_MACRO				= __AVR_ATmega165A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega165p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 71)
        MCU_DEVICE_MACRO				= __AVR_ATmega165P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega165pa)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 72)
        MCU_DEVICE_MACRO				= __AVR_ATmega165PA__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega168)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 73)
        MCU_DEVICE_MACRO				= __AVR_ATmega168__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega168a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 74)
        MCU_DEVICE_MACRO				= __AVR_ATmega168A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega168p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 75)
        MCU_DEVICE_MACRO				= __AVR_ATmega168P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega168pa)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 76)
        MCU_DEVICE_MACRO				= __AVR_ATmega168PA__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega169)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 77)
        MCU_DEVICE_MACRO				= __AVR_ATmega169__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega169a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 78)
        MCU_DEVICE_MACRO				= __AVR_ATmega169A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega169p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 79)
        MCU_DEVICE_MACRO				= __AVR_ATmega169P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega169pa)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 80)
        MCU_DEVICE_MACRO				= __AVR_ATmega169PA__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega16a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 81)
        MCU_DEVICE_MACRO				= __AVR_ATmega16A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega16hva)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 82)
        MCU_DEVICE_MACRO				= __AVR_ATmega16HVA__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega16hva2)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 83)
        MCU_DEVICE_MACRO				= __AVR_ATmega16HVA2__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega16hvb)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 84)
        MCU_DEVICE_MACRO				= __AVR_ATmega16HVB__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega16hvbrevb)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 85)
        MCU_DEVICE_MACRO				= __AVR_ATmega16HVBREVB__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega16m1)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 86)
        MCU_DEVICE_MACRO				= __AVR_ATmega16M1__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega16u2)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 87)
        MCU_DEVICE_MACRO				= __AVR_ATmega16U2__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega16u4)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 88)
        MCU_DEVICE_MACRO				= __AVR_ATmega16U4__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega2560)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 89)
        MCU_DEVICE_MACRO				= __AVR_ATmega2560__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega2561)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 90)
        MCU_DEVICE_MACRO				= __AVR_ATmega2561__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega2564rfr2)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 91)
        MCU_DEVICE_MACRO				= __AVR_ATmega2564RFR2__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega256rfr2)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 92)
        MCU_DEVICE_MACRO				= __AVR_ATmega256RFR2__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega32)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 93)
        MCU_DEVICE_MACRO				= __AVR_ATmega32__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega323)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 94)
        MCU_DEVICE_MACRO				= __AVR_ATmega323__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega324a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 95)
        MCU_DEVICE_MACRO				= __AVR_ATmega324A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega324p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 96)
        MCU_DEVICE_MACRO				= __AVR_ATmega324P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega324pa)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 97)
        MCU_DEVICE_MACRO				= __AVR_ATmega324PA__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega325)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 98)
        MCU_DEVICE_MACRO				= __AVR_ATmega325__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega3250)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 99)
        MCU_DEVICE_MACRO				= __AVR_ATmega3250__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega3250a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 100)
        MCU_DEVICE_MACRO				= __AVR_ATmega3250A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega3250p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 101)
        MCU_DEVICE_MACRO				= __AVR_ATmega3250P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega3250pa)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 102)
        MCU_DEVICE_MACRO				= __AVR_ATmega3250PA__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega325a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 103)
        MCU_DEVICE_MACRO				= __AVR_ATmega325A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega325p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 104)
        MCU_DEVICE_MACRO				= __AVR_ATmega325P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega325pa)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 105)
        MCU_DEVICE_MACRO				= __AVR_ATmega325PA__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega328)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 106)
        MCU_DEVICE_MACRO				= __AVR_ATmega328__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega328p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 107)
        MCU_DEVICE_MACRO				= __AVR_ATmega328P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega329)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 108)
        MCU_DEVICE_MACRO				= __AVR_ATmega329__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega3290)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 109)
        MCU_DEVICE_MACRO				= __AVR_ATmega3290__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega3290a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 110)
        MCU_DEVICE_MACRO				= __AVR_ATmega3290A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega3290p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 111)
        MCU_DEVICE_MACRO				= __AVR_ATmega3290P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega3290pa)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 112)
        MCU_DEVICE_MACRO				= __AVR_ATmega3290PA__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega329a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 113)
        MCU_DEVICE_MACRO				= __AVR_ATmega329A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega329p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 114)
        MCU_DEVICE_MACRO				= __AVR_ATmega329P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega329pa)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 115)
        MCU_DEVICE_MACRO				= __AVR_ATmega329PA__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega32a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 116)
        MCU_DEVICE_MACRO				= __AVR_ATmega32A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega32c1)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 117)
        MCU_DEVICE_MACRO				= __AVR_ATmega32C1__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega32hvb)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 118)
        MCU_DEVICE_MACRO				= __AVR_ATmega32HVB__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega32hvbrevb)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 119)
        MCU_DEVICE_MACRO				= __AVR_ATmega32HVBREVB__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega32m1)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 120)
        MCU_DEVICE_MACRO				= __AVR_ATmega32M1__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega32u2)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 121)
        MCU_DEVICE_MACRO				= __AVR_ATmega32U2__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega32u4)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 122)
        MCU_DEVICE_MACRO				= __AVR_ATmega32U4__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega32u6)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 123)
        MCU_DEVICE_MACRO				= __AVR_ATmega32U6__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega406)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 124)
        MCU_DEVICE_MACRO				= __AVR_ATmega406__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega48)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 125)
        MCU_DEVICE_MACRO				= __AVR_ATmega48__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega48a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 126)
        MCU_DEVICE_MACRO				= __AVR_ATmega48A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega48p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 127)
        MCU_DEVICE_MACRO				= __AVR_ATmega48P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega48pa)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 128)
        MCU_DEVICE_MACRO				= __AVR_ATmega48PA__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega603)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 129)
        MCU_DEVICE_MACRO				= __AVR_ATmega603__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega64)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 130)
        MCU_DEVICE_MACRO				= __AVR_ATmega64__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega640)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 131)
        MCU_DEVICE_MACRO				= __AVR_ATmega640__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega644)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 132)
        MCU_DEVICE_MACRO				= __AVR_ATmega644__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega644a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 133)
        MCU_DEVICE_MACRO				= __AVR_ATmega644A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega644p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 134)
        MCU_DEVICE_MACRO				= __AVR_ATmega644P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega644pa)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 135)
        MCU_DEVICE_MACRO				= __AVR_ATmega644PA__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega644rfr2)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 136)
        MCU_DEVICE_MACRO				= __AVR_ATmega644RFR2__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega645)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 137)
        MCU_DEVICE_MACRO				= __AVR_ATmega645__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega6450)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 138)
        MCU_DEVICE_MACRO				= __AVR_ATmega6450__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega6450a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 139)
        MCU_DEVICE_MACRO				= __AVR_ATmega6450A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega6450p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 140)
        MCU_DEVICE_MACRO				= __AVR_ATmega6450P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega645a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 141)
        MCU_DEVICE_MACRO				= __AVR_ATmega645A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega645p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 142)
        MCU_DEVICE_MACRO				= __AVR_ATmega645P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega649)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 143)
        MCU_DEVICE_MACRO				= __AVR_ATmega649__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega6490)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 144)
        MCU_DEVICE_MACRO				= __AVR_ATmega6490__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega6490a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 145)
        MCU_DEVICE_MACRO				= __AVR_ATmega6490A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega6490p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 146)
        MCU_DEVICE_MACRO				= __AVR_ATmega6490P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega649a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 147)
        MCU_DEVICE_MACRO				= __AVR_ATmega649A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega649p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 148)
        MCU_DEVICE_MACRO				= __AVR_ATmega649P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega64a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 149)
        MCU_DEVICE_MACRO				= __AVR_ATmega64A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega64c1)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 150)
        MCU_DEVICE_MACRO				= __AVR_ATmega64C1__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega64hve)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 151)
        MCU_DEVICE_MACRO				= __AVR_ATmega64HVE__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega64hve2)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 152)
        MCU_DEVICE_MACRO				= __AVR_ATmega64HVE2__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega64m1)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 153)
        MCU_DEVICE_MACRO				= __AVR_ATmega64M1__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega64rfr2)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 154)
        MCU_DEVICE_MACRO				= __AVR_ATmega64RFR2__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega8)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 155)
        MCU_DEVICE_MACRO				= __AVR_ATmega8__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega8515)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 156)
        MCU_DEVICE_MACRO				= __AVR_ATmega8515__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega8535)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 157)
        MCU_DEVICE_MACRO				= __AVR_ATmega8535__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega88)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 158)
        MCU_DEVICE_MACRO				= __AVR_ATmega88__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega88a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 159)
        MCU_DEVICE_MACRO				= __AVR_ATmega88A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega88p)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 160)
        MCU_DEVICE_MACRO				= __AVR_ATmega88P__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega88pa)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 161)
        MCU_DEVICE_MACRO				= __AVR_ATmega88PA__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega8a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 162)
        MCU_DEVICE_MACRO				= __AVR_ATmega8A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega8hva)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 163)
        MCU_DEVICE_MACRO				= __AVR_ATmega8HVA__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atmega8u2)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 164)
        MCU_DEVICE_MACRO				= __AVR_ATmega8U2__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny10)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 165)
        MCU_DEVICE_MACRO				= __AVR_ATtiny10__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny11)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 166)
        MCU_DEVICE_MACRO				= __AVR_ATtiny11__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny12)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 167)
        MCU_DEVICE_MACRO				= __AVR_ATtiny12__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny13)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 168)
        MCU_DEVICE_MACRO				= __AVR_ATtiny13__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny13a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 169)
        MCU_DEVICE_MACRO				= __AVR_ATtiny13A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny15)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 170)
        MCU_DEVICE_MACRO				= __AVR_ATtiny15__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny1634)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 171)
        MCU_DEVICE_MACRO				= __AVR_ATtiny1634__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny167)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 172)
        MCU_DEVICE_MACRO				= __AVR_ATtiny167__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny20)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 173)
        MCU_DEVICE_MACRO				= __AVR_ATtiny20__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny22)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 174)
        MCU_DEVICE_MACRO				= __AVR_ATtiny22__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny2313)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 175)
        MCU_DEVICE_MACRO				= __AVR_ATtiny2313__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny2313a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 176)
        MCU_DEVICE_MACRO				= __AVR_ATtiny2313A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny24)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 177)
        MCU_DEVICE_MACRO				= __AVR_ATtiny24__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny24a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 178)
        MCU_DEVICE_MACRO				= __AVR_ATtiny24A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny25)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 179)
        MCU_DEVICE_MACRO				= __AVR_ATtiny25__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny26)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 180)
        MCU_DEVICE_MACRO				= __AVR_ATtiny26__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny261)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 181)
        MCU_DEVICE_MACRO				= __AVR_ATtiny261__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny261a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 182)
        MCU_DEVICE_MACRO				= __AVR_ATtiny261A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny28)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 183)
        MCU_DEVICE_MACRO				= __AVR_ATtiny28__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny4)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 184)
        MCU_DEVICE_MACRO				= __AVR_ATtiny4__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny40)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 185)
        MCU_DEVICE_MACRO				= __AVR_ATtiny40__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny4313)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 186)
        MCU_DEVICE_MACRO				= __AVR_ATtiny4313__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny43u)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 187)
        MCU_DEVICE_MACRO				= __AVR_ATtiny43U__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny44)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 188)
        MCU_DEVICE_MACRO				= __AVR_ATtiny44__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny441)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 189)
        MCU_DEVICE_MACRO				= __AVR_ATtiny441__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny44a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 190)
        MCU_DEVICE_MACRO				= __AVR_ATtiny44A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny45)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 191)
        MCU_DEVICE_MACRO				= __AVR_ATtiny45__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny461)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 192)
        MCU_DEVICE_MACRO				= __AVR_ATtiny461__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny461a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 193)
        MCU_DEVICE_MACRO				= __AVR_ATtiny461A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny48)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 194)
        MCU_DEVICE_MACRO				= __AVR_ATtiny48__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny5)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 195)
        MCU_DEVICE_MACRO				= __AVR_ATtiny5__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny828)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 196)
        MCU_DEVICE_MACRO				= __AVR_ATtiny828__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny84)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 197)
        MCU_DEVICE_MACRO				= __AVR_ATtiny84__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny841)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 198)
        MCU_DEVICE_MACRO				= __AVR_ATtiny841__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny84a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 199)
        MCU_DEVICE_MACRO				= __AVR_ATtiny84A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny85)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 200)
        MCU_DEVICE_MACRO				= __AVR_ATtiny85__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny861)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 201)
        MCU_DEVICE_MACRO				= __AVR_ATtiny861__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny861a)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 202)
        MCU_DEVICE_MACRO				= __AVR_ATtiny861A__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny87)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 203)
        MCU_DEVICE_MACRO				= __AVR_ATtiny87__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny88)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 204)
        MCU_DEVICE_MACRO				= __AVR_ATtiny88__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),attiny9)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 205)
        MCU_DEVICE_MACRO				= __AVR_ATtiny9__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega128a1)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 206)
        MCU_DEVICE_MACRO				= __AVR_ATxmega128A1__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega128a1u)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 207)
        MCU_DEVICE_MACRO				= __AVR_ATxmega128A1U__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega128a3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 208)
        MCU_DEVICE_MACRO				= __AVR_ATxmega128A3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega128a3u)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 209)
        MCU_DEVICE_MACRO				= __AVR_ATxmega128A3U__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega128a4u)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 210)
        MCU_DEVICE_MACRO				= __AVR_ATxmega128A4U__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega128b1)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 211)
        MCU_DEVICE_MACRO				= __AVR_ATxmega128B1__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega128b3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 212)
        MCU_DEVICE_MACRO				= __AVR_ATxmega128B3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega128c3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 213)
        MCU_DEVICE_MACRO				= __AVR_ATxmega128C3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega128d3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 214)
        MCU_DEVICE_MACRO				= __AVR_ATxmega128D3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega128d4)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 215)
        MCU_DEVICE_MACRO				= __AVR_ATxmega128D4__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega16a4)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 216)
        MCU_DEVICE_MACRO				= __AVR_ATxmega16A4__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega16a4u)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 217)
        MCU_DEVICE_MACRO				= __AVR_ATxmega16A4U__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega16c4)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 218)
        MCU_DEVICE_MACRO				= __AVR_ATxmega16C4__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega16d4)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 219)
        MCU_DEVICE_MACRO				= __AVR_ATxmega16D4__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega16e5)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 220)
        MCU_DEVICE_MACRO				= __AVR_ATxmega16E5__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega192a3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 221)
        MCU_DEVICE_MACRO				= __AVR_ATxmega192A3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega192a3u)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 222)
        MCU_DEVICE_MACRO				= __AVR_ATxmega192A3U__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega192c3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 223)
        MCU_DEVICE_MACRO				= __AVR_ATxmega192C3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega192d3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 224)
        MCU_DEVICE_MACRO				= __AVR_ATxmega192D3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega256a3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 225)
        MCU_DEVICE_MACRO				= __AVR_ATxmega256A3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega256a3b)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 226)
        MCU_DEVICE_MACRO				= __AVR_ATxmega256A3B__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega256a3bu)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 227)
        MCU_DEVICE_MACRO				= __AVR_ATxmega256A3BU__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega256a3u)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 228)
        MCU_DEVICE_MACRO				= __AVR_ATxmega256A3U__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega256c3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 229)
        MCU_DEVICE_MACRO				= __AVR_ATxmega256C3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega256d3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 230)
        MCU_DEVICE_MACRO				= __AVR_ATxmega256D3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega32a4)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 231)
        MCU_DEVICE_MACRO				= __AVR_ATxmega32A4__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega32a4u)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 232)
        MCU_DEVICE_MACRO				= __AVR_ATxmega32A4U__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega32c3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 233)
        MCU_DEVICE_MACRO				= __AVR_ATxmega32C3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega32c4)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 234)
        MCU_DEVICE_MACRO				= __AVR_ATxmega32C4__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega32d3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 235)
        MCU_DEVICE_MACRO				= __AVR_ATxmega32D3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega32d4)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 236)
        MCU_DEVICE_MACRO				= __AVR_ATxmega32D4__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega32e5)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 237)
        MCU_DEVICE_MACRO				= __AVR_ATxmega32E5__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega384c3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 238)
        MCU_DEVICE_MACRO				= __AVR_ATxmega384C3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega384d3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 239)
        MCU_DEVICE_MACRO				= __AVR_ATxmega384D3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega64a1)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 240)
        MCU_DEVICE_MACRO				= __AVR_ATxmega64A1__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega64a1u)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 241)
        MCU_DEVICE_MACRO				= __AVR_ATxmega64A1U__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega64a3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 242)
        MCU_DEVICE_MACRO				= __AVR_ATxmega64A3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega64a3u)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 243)
        MCU_DEVICE_MACRO				= __AVR_ATxmega64A3U__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega64a4u)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 244)
        MCU_DEVICE_MACRO				= __AVR_ATxmega64A4U__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega64b1)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 245)
        MCU_DEVICE_MACRO				= __AVR_ATxmega64B1__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega64b3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 246)
        MCU_DEVICE_MACRO				= __AVR_ATxmega64B3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega64c3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 247)
        MCU_DEVICE_MACRO				= __AVR_ATxmega64C3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega64d3)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 248)
        MCU_DEVICE_MACRO				= __AVR_ATxmega64D3__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega64d4)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 249)
        MCU_DEVICE_MACRO				= __AVR_ATxmega64D4__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),atxmega8e5)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 250)
        MCU_DEVICE_MACRO				= __AVR_ATxmega8E5__
        MCU_DEVICE_PLATFORM				= AVR
    else ifeq ($(MCU_DEVICE_NAME),m3000)
        MCU_DEVICE_CODE					= ($(MCU_AVR_CODE_OFFSET) + 251)
        MCU_DEVICE_MACRO				= __AVR_M3000__
        MCU_DEVICE_PLATFORM				= AVR
    endif
endif
