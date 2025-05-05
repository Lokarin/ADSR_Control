; ------------------------------------------------------------------------------
; Project:  Digipot Control
; File:     main.asm
; Author:   Gabriel Garcia; Henrique Onuki
; Created:  2025-04-19
; Modified: 2025-05-1
; Version:  1.f
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
.def    digiPotSelectorReg          = R17
.def    opBytesLeft                 = R21
.def    UpOrDownReg                 = R22
.def    totalStepsReg               = R23
.def    loopReg                     = R24
.def    byteRecebido                = R0
.def    opCodeAttackReg             = R1
.def    opCodeHoldReg               = R2
.def    opCodeDecayAndReleaseReg    = R3
.def    opCodeSustainReg            = R4

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
mainStart:

    LDI   auxReg, 0xFF
    OUT   DDRD, auxReg ;habilita todas as portas D como saida

digital_potentiometer_inicial_reset:
    ;seta todos os potenciômetros para começarem na mesma resistencia

    LDI   auxReg, 0b00001000 ;ativa todos CS(chip select) e seta a resistencia para baixo(down)
    OUT   PORTD, auxReg

    LDI   loopReg, 0b1100100 ;carrega loopReg em 100

    ;RCALL delay500
    ;RCALL delay500
    ;RCALL delay500
    ;RCALL delay500

digital_potentiometer_loop:

    ORI   auxReg, 0b00000100 ;borda de subida
    OUT   PORTD, auxReg
    ;RCALL delay500
    RCALL delay1us

    ANDI  auxReg, 0b11111011 ;borda de descida
    OUT   PORTD, auxReg
    ;RCALL delay500
    RCALL delay1us

    DEC   loopReg ;Quando loopReg for zerado o reset inicial dos potenciometros esta completo
    BREQ  USART_init

    RJMP  digital_potentiometer_loop

USART_init:

    ;inicializa a USART (UBRR0 = 103 para 9600 bps)
    LDI auxReg, high(103)
    STS UBRR0H, auxReg
    LDI auxReg, low(103)
    STS UBRR0L, auxReg

    ;configura USART: 8 bits, 1 stop, sem paridade
    LDI auxReg, (1 << UCSZ01) | (1 << UCSZ00)
    STS UCSR0C, auxReg

    ;habilita RX
    LDI auxReg, (1 << RXEN0)
    STS UCSR0B, auxReg

mainLoop:

    LDI   digiPotSelectorReg, 0b10000000 ;PD7, PD6, PD5, PD4 = habilita o Chip Select dos digipots
    LDI   opBytesLeft, 0b00000100 ;quando opBytesLeft alcancar 0 o codigo retorna para mainLoop

    LDI   auxReg, 0b11110000 ;
    OUT   PORTD, auxReg ;inicia todas as saidas com 0V com excessao de PD7, PD6, PD5, PD4 (Chip Select)

    RCALL recebe4Bytes
    RCALL delay1us
    RCALL delay500
    ;RCALL delay500
    ;RCALL delay500
    ;RCALL delay500
    ;RCALL delay500
    MOV   auxReg, opCodeAttackReg ;o byte da fase de attack e carregado primeiro

resistanceDirectionCheck:
    ;verifica se o bit mais a esquerda do opCodeXReg e 0 ou 1
    ;caso bit == 1: upResistanceStart
    ;caso bit == 0: downResistanceStart

    MOV  UpOrDownReg, auxReg
    ANDI UpOrDownReg, 0b10000000
    CPI  UpOrDownReg, 0b10000000
    BREQ upResistanceStart
    RJMP downResistanceStart

upResistanceStart:

    DEC  opBytesLeft ;decrementa opByterLeft em 1

    ;determinar o numero de passos com os 7 outros bits do opCodeXReg
    MOV  totalStepsReg, auxReg
    ANDI totalStepsReg, 0b01111111 ;isolando os 7 bits
    MOV  loopReg, totalStepsReg ;valor resultante e armazenado no totalStepsReg
    CPI  loopReg, 0b00000000 ;se loop = 0, entao pula direto para o proximo opcode
    BREQ nextOpCodeContinue

    ;habilita o digiPot selecionado em digiPotSelectorReg para aumentar a resistencia
    LDI  auxReg, 0b00001000 ;PD3(digipots up/down pin) habilita o digipot para comecar em up
    ORI  digiPotSelectorReg, 0b00001111 ;prepara digiPotSelectorReg para ser invertido(ativo em low)
    COM  digiPotSelectorReg
    OR   auxReg, digiPotSelectorReg
    OUT  PORTD, auxReg
    RCALL delay1us
    RCALL delay500

upResistanceLoop:
    ;ativa e desativa o PD2(digipots CLK) enquanto o numero de steps(ou loops) armazenados em loopReg e != 0

    ORI  auxReg, 0b00000100 ;borda de subida
    OUT  PORTD, auxReg
    RCALL delay1us
    RCALL delay500

    ANDI auxReg, 0b11111011 ;borda de descida
    OUT  PORTD, auxReg
    RCALL delay1us
    RCALL delay500

    DEC  loopReg
    BREQ nextOpCode ;se loop foi finalizado pula para o proxima fase do ADSR

    RJMP upResistanceLoop ;caso o loop nao tenha acabado retorna para o comeco dele

downResistanceStart:

    DEC  opBytesLeft ;decrementa a opBytesLeft em 1

    ;determina o numero de passos(ou loops) com os 7 outros bits do opCodeXReg
    MOV  totalStepsReg, auxReg
    ANDI totalStepsReg, 0b01111111 ;isolando os 7 bits
    MOV  loopReg, totalStepsReg ;valor resultante e armazenado no totalStepsReg
    CPI  loopReg, 0b00000000 ;se loop = 0, entao pula direto para o proximo opcode
    BREQ nextOpCodeContinue

    ;habilita o digiPot selecionado em digiPotSelectorReg para diminuir a resistencia
    LDI  auxReg, 0b00000000 ;PD3(digipots up/down pin) habilita o digipot para comecar em down
    ORI  digiPotSelectorReg, 0b00001111 ;prepara digiPotSelectorReg para ser invertido(ativo em low)
    COM  digiPotSelectorReg
    OR   auxReg, digiPotSelectorReg
    OUT  PORTD, auxReg
    RCALL delay1us
    RCALL delay500

downResistanceLoop:
    ;ativa e desativa o PD2(digipots CLK) enquanto o numero de steps(ou loops) armazenados em loopReg e != 0

    ORI  auxReg, 0b00000100 ;borda de subida
    OUT  PORTD, auxReg
    RCALL delay1us
    RCALL delay500

    ANDI auxReg, 0b11111011 ;borda de descida
    OUT  PORTD, auxReg
    RCALL delay1us
    RCALL delay500

    DEC  loopReg
    BREQ nextOpCode ;se loop foi finalizado pula para o proxima fase do ADSR

    RJMP downResistanceLoop ;caso o loop nao tenha acabado retorna para o comeco dele

nextOpCode:

    ;restaura digiPotSelectorReg para a forma binaria original
    ORI digiPotSelectorReg, 0b00001111
    COM digiPotSelectorReg

nextOpCodeContinue:

    ;ativa o proximo digipot
    LSR  digiPotSelectorReg

    ;se opBytesLeft == 0 jump para "fim" label
    CPI  opBytesLeft, 0b00000000
    BREQ fim

    ;se opBytesLeft == 3 jump para opCodeHoldReg label
    CPI  opBytesLeft, 0b00000011
    BREQ opCodeHold

    ;se opBytesLeft == 2 jump para opCodeSustain label
    ;se opBytesLeft != 2 codigo continua
    CPI  opBytesLeft, 0b00000010
    BREQ opCodeSustain

opCodeDecayAndRelease:

    ;carrega opCodeDecayAndReleaseReg para auxReg e reinicia o codigo em resistanceDirectionCheck
    MOV  auxReg, opCodeDecayAndReleaseReg
    RJMP resistanceDirectionCheck

opCodeHold:

    ;carrega opCodeSustainReg para auxReg e reinicia o codigo em resistanceDirectionCheck
    MOV  auxReg, opCodeHoldReg
    RJMP resistanceDirectionCheck

opCodeSustain:

    ;carrega opCodeSustainReg para auxReg e reinicia o codigo em resistanceDirectionCheck
    MOV  auxReg, opCodeSustainReg
    RJMP resistanceDirectionCheck

fim:

    RJMP mainLoop

; =================================================
; Sub-rotina: espera e le 4 bytes da interface USART
; =================================================
recebe4Bytes:
recebeByte1:

    ;Byte1
    LDS  auxReg, UCSR0A
    SBRS auxReg, RXC0
    RJMP recebeByte1

    LDS  byteRecebido, UDR0
    MOV  opCodeAttackReg, byteRecebido

recebeByte2:

    ;Byte2
    LDS  auxReg, UCSR0A
    SBRS auxReg, RXC0
    RJMP recebeByte2

    LDS  byteRecebido, UDR0
    MOV  opCodeHoldReg, byteRecebido

recebeByte3:

    ;Byte3
    LDS  auxReg, UCSR0A
    SBRS auxReg, RXC0
    RJMP recebeByte3

    LDS  byteRecebido, UDR0
    MOV  opCodeSustainReg, byteRecebido

recebeByte4:

    ;Byte4
    LDS  auxReg, UCSR0A
    SBRS auxReg, RXC0
    RJMP recebeByte4

    LDS  byteRecebido, UDR0
    MOV  opCodeDecayAndReleaseReg, byteRecebido

    RET

; ------------------------------------------------------------------------------
; Function definitions
; ------------------------------------------------------------------------------
delay500:
    NOP                     ; Comment line for CALL / Uncomment for RCALL
    LDI     R18, 41
    LDI     R19, 150
    LDI     R20, 125
    ;LDI     R18, 2      ; Outer loop
    ;LDI     R19, 53     ; Middle loop
    ;LDI     R20, 74     ; Inner loop
delay500Loop:
    DEC     R20
    BRNE    delay500Loop
    DEC     R19
    BRNE    delay500Loop
    DEC     R18
    BRNE    delay500Loop
    NOP
    RET

delay1us:
    LDI R20, 5       ; 1 ciclo
loop1us:
    DEC R20          ; 1 ciclo
    BRNE loop1us     ; 2 ciclos se desviar, 1 ciclo se não
    RET              ; 4 ciclos

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
