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
    LDI   opCodeAttackReg, 0b10000101
    LDI   opCodeDecayAndReleaseReg, 0b10000101
    LDI   opCodeSustainReg, 0b00000101
    LDI   digiPotSelectorReg, 0b10000000 ;PD7, PD6, PD5 = Chip Select
    LDI   flagReg, 0b00000011 ;quando flagReg == 0 todos os digipots foram configurados
    LDI   auxReg, 0xFF

    OUT   DDRD, auxReg ;habilita todas as portas D como saida
    OUT   PORTD, R17 ;seta tensao de todas as saidas para 0
    MOV   auxReg, opCodeAttackReg ;fase de ataque e verificada primeiro

mainLoop:

resistanceDirectionCheck:
    ;verifica se o bit mais a esquerda do opCodeXReg é 0 ou 1
    ;caso bit == 1: upResistanceStart
    ;caso bit == 0: downResistanceStart

    MOV    UpOrDownReg, auxReg
    ANDI   UpOrDownReg, 0b10000000
    CPI    UpOrDownReg, 0b10000000
    BREQ   upResistanceStart
    RJMP   downResistanceStart

upResistanceStart:
    ;determina o numero de passos(ou loops) com os 7 outros bits do opCodeXReg
    MOV   totalStepsReg, auxReg
    ANDI  totalStepsReg, 0b01111111 ;isolando os 7 bits
    MOV   loopReg, totalStepsReg ;valor resultante e armazenado no totalStepsReg

    ;prepara apenas um digiPot para aumentar a resistencia
    LDI   auxReg, 0b00000000 ;PD4 seta o digipot para começar em up
    ORI   digiPotSelectorReg, 0b00011111 ; prepara digiPotSelectorReg para ser invertido
    COM   digiPotSelectorReg ;cigiPotSelectorReg ativo em low
    OR    auxReg, digiPotSelectorReg
    OUT   PORTD, auxReg
    RCALL delay500

    DEC   flagReg ;decrementa a flag em 1

upResistanceLoop:
    ;ativa e desativa o PD3(digipot CLK) enquanto o numero de steps(ou loops) armazenados em loopReg é != 0
    ORI   auxReg, 0b00001000 ;borda de subida
    OUT   PORTD, auxReg
    RCALL delay500

    ANDI  auxReg, 0b11110111 ;borda de descida
    OUT   PORTD, auxReg
    RCALL delay500

    DEC   loopReg
    BREQ  nextOpCode ;se loop acabou pula para o proxima fase do ADSR

    RJMP  upResistanceLoop ;se o loop não acabou retorna para o comeco dele

downResistanceStart:
    ;determinar o numero de passos com o restante 7 outros bits do opCodeXReg
    MOV   totalStepsReg, auxReg
    ANDI  totalStepsReg, 0b01111111 ;isolando os 7 bits
    MOV   loopReg, totalStepsReg ;valor resultante e armazenado no totalStepsReg

    ;prepara apenas um digiPot para diminuir a resistencia
    LDI   auxReg, 0b00010000 ;PD4 seta o digipot para começar em down
    ORI   digiPotSelectorReg, 0b00011111 ;prepara digiPotSelectorReg para ser invertido
    COM   digiPotSelectorReg ;digiPotSelectorReg ativo em low
    OR    auxReg, digiPotSelectorReg
    OUT   PORTD, auxReg
    RCALL delay500

    ;decrementa a flag em 1
    DEC   flagReg

downResistanceLoop:
    ;ativa e desativa o PD3(digipot CLK) enquanto o numero de steps(ou loops) armazenados em loopReg é != 0
    ORI   auxReg, 0b00001000 ;borda de subida
    OUT   PORTD, auxReg
    RCALL delay500

    ANDI  auxReg, 0b11110111 ;borda de descida
    OUT   PORTD, auxReg
    RCALL delay500

    DEC   loopReg
    BREQ  nextOpCode ;se loop acabou pula para o proxima fase do ADSR

    RJMP  downResistanceLoop ;se o loop não acabou retorna para o comeco dele

nextOpCode:
    ;restaura digiPotSelectorReg para a forma binaria original e ativa proxima digipot
    ORI   digiPotSelectorReg, 0b00011111
    COM   digiPotSelectorReg
    LSR   digiPotSelectorReg

    ;se flagReg == 0 jump para fim label
    CPI   flagReg, 0b00000000
    BREQ  fim

    ;se flagReg == 2 jump para opCodeDecayAndRelease label
    ;se flagReg != 2 codigo continua
    CPI   flagReg, 0b00000010
    BREQ  opCodeDecayAndRelease

opCodeSustain:
    ;carrega opCodeSustainReg para auxReg e reinicia o codigo em resistanceDirectionCheck
    MOV   auxReg, opCodeSustainReg
    RJMP  resistanceDirectionCheck

opCodeDecayAndRelease:
    ;carrega opCodeDecayAndReleaseReg para auxReg e reinicia o codigo em resistanceDirectionCheck
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
