; ------------------------------------------------------------------------------
; Project:  Digipot Control
; File:     main.asm
; Author:   Gabriel Garcia
; Created:  2025-04-19
; Modified: 2025-04-19
; Version:  1.b
; Notes:    Controle de Digipots. Fcpu = 16 MHz.
; ------------------------------------------------------------------------------

; ------------------------------------------------------------------------------
; Include definition files
; ------------------------------------------------------------------------------
.include "include/m328Pdef.inc"

; ------------------------------------------------------------------------------
; Register definitions
; ------------------------------------------------------------------------------
.def    auxReg                      = R16
.def    byteRecebido                = R17
.def    loopReg                     = R21
.def    opCodeAttackReg             = R22
.def    opCodeDecayAndReleaseReg    = R23
.def    opCodeSustainReg            = R24
.def    UpOrDownReg                 = R25
.def    totalStepsReg               = R26
.def    flagReg                     = R27
.def    digiPotSelectorReg          = R28

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
; Main function
; ------------------------------------------------------------------------------
main:
USART_init:
    ;Inicializa a USART (UBRR0 = 103 para 9600 bps)
    ldi auxReg, high(103)
    sts UBRR0H, auxReg
    ldi auxReg, low(103)
    sts UBRR0L, auxReg

    ;Configura USART: 8 bits, 1 stop, sem paridade
    ldi auxReg, (1 << UCSZ01) | (1 << UCSZ00)
    sts UCSR0C, auxReg

    ;Habilita RX e TX
    ldi auxReg, (1 << RXEN0) | (1 << TXEN0)
    sts UCSR0B, auxReg

mainLoop:
    LDI   digiPotSelectorReg, 0b10000000 ;PD7, PD6, PD5 = Chip Select
    LDI   flagReg, 0b00000011 ;quando flagReg == 0 todos os digipots foram configurados
    LDI   auxReg, 0xFF

    OUT   DDRD, auxReg ;habilita todas as portas D como saida
    OUT   PORTD, R29 ;seta tensao de todas as saidas para 0

    RCALL recebe3Bytes
    MOV   auxReg, opCodeAttackReg ;fase de ataque e verificada primeiro

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
    ;RCALL delay500

    DEC   flagReg ;decrementa a flag em 1

upResistanceLoop:
    ;ativa e desativa o PD3(digipot CLK) enquanto o numero de steps(ou loops) armazenados em loopReg é != 0
    ORI   auxReg, 0b00001000 ;borda de subida
    OUT   PORTD, auxReg
    ;RCALL delay500

    ANDI  auxReg, 0b11110111 ;borda de descida
    OUT   PORTD, auxReg
    ;RCALL delay500

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
    ;RCALL delay500

    ;decrementa a flag em 1
    DEC   flagReg

downResistanceLoop:
    ;ativa e desativa o PD3(digipot CLK) enquanto o numero de steps(ou loops) armazenados em loopReg é != 0
    ORI   auxReg, 0b00001000 ;borda de subida
    OUT   PORTD, auxReg
    ;RCALL delay500

    ANDI  auxReg, 0b11110111 ;borda de descida
    OUT   PORTD, auxReg
    ;RCALL delay500

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
    RJMP  mainLoop

; =================================================
; Sub-rotina: espera e lê 3 bytes da interface USART
; =================================================
recebe3Bytes:
    ; Byte 1
recebeByte1:
    lds  auxReg, UCSR0A
    sbrs auxReg, RXC0
    rjmp recebeByte1

    lds  byteRecebido, UDR0
    MOV  opCodeAttackReg, byteRecebido

    ; Byte 2
recebeByte2:
    lds  auxReg, UCSR0A
    sbrs auxReg, RXC0
    rjmp recebeByte2

    lds  byteRecebido, UDR0
    MOV  opCodeDecayAndReleaseReg, byteRecebido

    ; Byte 3
recebeByte3:
    lds  auxReg, UCSR0A
    sbrs auxReg, RXC0
    rjmp recebeByte3

    lds  byteRecebido, UDR0
    MOV  opCodeSustainReg, byteRecebido

    ret

;enviaByte:
;esperaUDRE:
;    lds auxReg, UCSR0A
;    sbrs auxReg, UDRE0
;    rjmp esperaUDRE
;    sts UDR0, byteRecebido
;    ret
; ------------------------------------------------------------------------------
; Function definitions
; ------------------------------------------------------------------------------
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