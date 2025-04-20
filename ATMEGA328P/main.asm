; ------------------------------------------------------------------------------
; Project:  Digipot Control
; File:     main.asm
; Author:   Gabriel Garcia
; Created:  2025-04-19
; Modified: 2025-04-19
; Version:  1.a
; Notes:    Controle de Digipots. Fcpu = 16 MHz.
; ------------------------------------------------------------------------------

; ------------------------------------------------------------------------------
; Include definition files
; ------------------------------------------------------------------------------
.include "include/m328Pdef.inc"

; ------------------------------------------------------------------------------
; Register definitions
; ------------------------------------------------------------------------------
.def    auxReg       = R16
.def    loopReg      = R21
.def    opCodeAttackReg    = R22
.def    opCodeDecayAndReleaseReg    = R23
.def    opCodeSustainReg    = R24
.def    UpOrDownReg         = R25
.def    totalStepsReg       = R26
.def    flagReg             = R27
.def    digiPotSelectorReg  = R28

; ------------------------------------------------------------------------------
; Interrupt vectors
; ------------------------------------------------------------------------------
.org 0x0000
    JMP resetHandler
.org INT0addr
    JMP int0Handler
.org INT1addr
    JMP int1Handler
.org PCI0addr
    JMP pcint0Handler
.org PCI1addr
    JMP pcint1Handler
.org PCI2addr
    JMP pcint2Handler
.org WDTaddr
    JMP wdtHandler
.org OC2Aaddr
    JMP timer2CompAHandler
.org OC2Baddr
    JMP timer2CompBHandler
.org OVF2addr
    JMP timer2OvfHandler
.org ICP1addr
    JMP timer1CaptureHandler
.org OC1Aaddr
    JMP timer1CompAHandler
.org OC1Baddr
    JMP timer1CompBHandler
.org OVF1addr
    JMP timer1OvfHandler
.org OC0Aaddr
    JMP timer0CompAHandler
.org OC0Baddr
    JMP timer0CompBHandler
.org OVF0addr
    JMP timer0OvfHandler
.org SPIaddr
    JMP spiHandler
.org URXCaddr
    JMP usartRxHandler
.org UDREaddr
    JMP usartDataEmptyHandler
.org UTXCaddr
    JMP usartTxHandler
.org ADCCaddr
    JMP adcHandler
.org ERDYaddr
    JMP eepromHandler
.org ACIaddr
    JMP analogCompHandler
.org TWIaddr
    JMP twiHandler
.org SPMRaddr
    JMP flashHandler
.org INT_VECTORS_SIZE

; ------------------------------------------------------------------------------
; Include other assembly files
; ------------------------------------------------------------------------------
; NONE

; ------------------------------------------------------------------------------
; Constants stored in Flash memory
; Note: Variables must be multiples of 2, since memory is organized in 16 bits
; ------------------------------------------------------------------------------
; NONE

; ------------------------------------------------------------------------------
; Main function
; ------------------------------------------------------------------------------
main:
    ;Startup area
    LDI   opCodeAttackReg, 0b00000101
    LDI   opCodeDecayAndReleaseReg, 0b00000101
    LDI   opCodeSustainReg, 0b00000101
    LDI   digiPotSelectorReg, 0b10000000
    LDI   flagReg, 0b00000011
    LDI   auxReg, 0xFF

    OUT   DDRD, auxReg
    OUT   PORTD, R17
    MOV   auxReg, opCodeAttackReg

mainLoop:

resistanceDirectionCheck:
    ;verifica se o primeiro bit do opCodeReg é 0 ou 1
    MOV    UpOrDownReg, auxReg
    ANDI   UpOrDownReg, 0b10000000
    CPI    UpOrDownReg, 0b10000000
    BREQ   upResistanceStart
    RJMP   downResistanceStart

upResistanceStart:
    ;determinar o numero de passos com o restante 7 outros bits do opCodeReg
    MOV   totalStepsReg, auxReg
    ANDI  totalStepsReg, 0b01111111
    MOV   loopReg, totalStepsReg

    ;seta o digiPot para aumentar a resistencia
    LDI   auxReg, 0b00000000
    ORI   digiPotSelectorReg, 0b00011111    ; prepara digiPot para ser invertido
    COM   digiPotSelectorReg                ; chip Selector ativo em low
    OR    auxReg, digiPotSelectorReg
    OUT   PORTD, auxReg
    RCALL delay500

    ;decrementa a flag em 1
    DEC flagReg

upResistanceLoop:
    LDI   auxReg, 0b00000001
    OR    auxReg, digiPotSelectorReg
    OUT   PORTD, auxReg
    RCALL delay500

    LDI   auxReg, 0b00000000
    OR    auxReg, digiPotSelectorReg
    OUT   PORTD, auxReg
    RCALL delay500

    DEC   loopReg
    BREQ  nextOpCode

    RJMP upResistanceLoop

downResistanceStart:
    ;determinar o numero de passos com o restante 7 outros bits do opCodeReg
    MOV   totalStepsReg, auxReg
    ANDI  totalStepsReg, 0b01111111
    MOV   loopReg, totalStepsReg

    ;seta o digiPot para diminuir a resistencia e seleciona o chip
    LDI   auxReg, 0b00000100
    ORI   digiPotSelectorReg, 0b00011111    ; prepara digiPot para ser invertido
    COM   digiPotSelectorReg                ; chip Selector ativo em low
    OR    auxReg, digiPotSelectorReg
    OUT   PORTD, auxReg
    RCALL delay500

    ;decrementa a flag em 1
    DEC flagReg

downResistanceLoop:
    LDI   auxReg, 0b00000101
    OR    auxReg, digiPotSelectorReg
    OUT   PORTD, auxReg
    RCALL delay500

    LDI   auxReg, 0b00000100
    OR    auxReg, digiPotSelectorReg
    OUT   PORTD, auxReg
    RCALL delay500

    DEC   loopReg
    BREQ  nextOpCode

    RJMP  downResistanceLoop

nextOpCode:
    ; restaura digiPotSelectorReg para a forma binaria original
    ORI   digiPotSelectorReg, 0b00011111
    COM   digiPotSelectorReg
    LSR   digiPotSelectorReg

    CPI   flagReg, 0b00000000
    BREQ  fim

    CPI   flagReg, 0b00000010
    BREQ  opCodeDecayAndRelease

opCodeSustain:
    MOV   auxReg, opCodeSustainReg
    RJMP  resistanceDirectionCheck

opCodeDecayAndRelease:
    MOV   auxReg, opCodeDecayAndReleaseReg
    RJMP  resistanceDirectionCheck

fim:
    RJMP  fim

; ------------------------------------------------------------------------------
; Function definitions
; ------------------------------------------------------------------------------
delay100:
    NOP                     ; Comment line for CALL / Uncomment for RCALL
    LDI     R18, 9
    LDI     R19, 30
    LDI     R20, 226
delay100Loop:
    DEC     R20
    BRNE    delay100Loop
    DEC     R19
    BRNE    delay100Loop
    DEC     R18
    BRNE    delay100Loop
    RJMP    PC + 1
    RET

delay250:
    NOP                     ; Comment line for CALL / Uncomment for RCALL
    LDI     R18, 21
    LDI     R19, 75
    LDI     R20, 188
delay250Loop:
    DEC     R20
    BRNE    delay250Loop
    DEC     R19
    BRNE    delay250Loop
    DEC     R18
    BRNE    delay250Loop
    RJMP    PC + 1
    RET

delay500:
    NOP                     ; Comment line for CALL / Uncomment for RCALL
    LDI     R18, 41
    LDI     R19, 150
    LDI     R20, 125
delay500Loop:
    DEC     R20
    BRNE    delay500Loop
    DEC     R19
    BRNE    delay500Loop
    DEC     R18
    BRNE    delay500Loop
    NOP
    RET

; ------------------------------------------------------------------------------
; Interrupt handlers
; ------------------------------------------------------------------------------
int0Handler:
int1Handler:
pcint0Handler:
pcint1Handler:
pcint2Handler:
wdtHandler:
timer2CompAHandler:
timer2CompBHandler:
timer2OvfHandler:
timer1CaptureHandler:
timer1CompAHandler:
timer1CompBHandler:
timer1OvfHandler:
timer0CompAHandler:
timer0CompBHandler:
timer0OvfHandler:
spiHandler:
usartRxHandler:
usartDataEmptyHandler:
usartTxHandler:
adcHandler:
eepromHandler:
analogCompHandler:
twiHandler:
flashHandler:
    RETI
resetHandler:
    LDI     R16, 0
    STS     UCSR0B, R16
    LDI     R19, LOW(RAMEND)
    OUT     SPL, R19
    LDI     R19, HIGH(RAMEND)
    OUT     SPH,R19
    LDI     R19, 0
    LDI     R16, 0
    JMP     main
