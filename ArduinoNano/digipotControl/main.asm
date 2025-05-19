; ------------------------------------------------------------------------------
; Project:  Digipot Control
; File:     main.asm
; Author:   Gabriel Garcia; Henrique Onuki
; Created:  2025-04-19
; Modified: 2025-05-6
; Version:  1.g
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
.def    BytesLeft                   = R21
.def    loopReg                     = R22
.def    byteRecebido                = R0
.def    byteAttackReg               = R1
.def    byteHoldReg                 = R2
.def    byteDecayAndReleaseReg      = R3
.def    byteSustainReg              = R4

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

TIMER0_delay1us_init:

    ;Modo CTC (WGM01 = 1), Prescaler = 1 (CS00 = 1)
    LDI auxReg, 0x00
    STS TCCR0A, auxReg

    LDI auxReg, (1 << WGM01) | (1 << CS00)
    STS TCCR0B, auxReg

    ;OCR0A = 7 -> 1 µs TOTAL
    LDI auxReg, 7
    STS OCR0A, auxReg

TIMER1_wave_form_init:

    ;configura PB1 como saída
    LDI auxReg, (1<<PB1)
    OUT DDRB, auxReg

    ;ativa toggle (inversão) no pino OC1A (PB1) ao atingir OCR1A
    LDI auxReg, (1<<COM1A0)
    STS TCCR1A, auxReg

    ;modo CTC (WGM12) + prescaler 256 (CS12)
    LDI auxReg, (1<<WGM12) | (1<<CS12)
    STS TCCR1B, auxReg

    LDI auxReg, high(10416)
    STS OCR1AH, auxReg

    LDI auxReg, low(10416)
    STS OCR1AL, auxReg

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

main_start:

    LDI   auxReg, 0xFF
    OUT   DDRD, auxReg ;habilita todas as portas D como saida

main_loop:

    LDI   digiPotSelectorReg, 0b10000000 ;PD7, PD6, PD5, PD4 = habilita o Chip Select dos digipots
    LDI   BytesLeft, 0b00000100 ;quando BytesLeft alcancar 0 o codigo retorna para main_loop

    LDI   auxReg, 0b11110000 ;
    OUT   PORTD, auxReg ;inicia todas as saidas com 0V com excessao de PD7, PD6, PD5, PD4 (Chip Select)

wait_for_4_byes:

    RCALL recebe4Bytes

resistance_reset:
    ;seta todos os potenciômetros para começarem na mesma resistencia (0 ohm) após
    ;receber 4 bytes

    LDI   auxReg, 0b00001000 ;ativa todos CS(chip select) e seta a resistencia para baixo(down)
    OUT   PORTD, auxReg

    LDI   loopReg, 0b1101001 ;carrega loopReg com 105 (garante que haverá mais que 100 ciclos)

resistance_reset_loop:

    ORI   auxReg, 0b00000100 ;borda de subida
    OUT   PORTD, auxReg
    ;RCALL delay100
    RCALL delay1us

    ANDI  auxReg, 0b11111011 ;borda de descida
    OUT   PORTD, auxReg
    ;RCALL delay100
    RCALL delay1us

    DEC   loopReg ;Quando loopReg for zerado o reset dos potenciometros esta completo
    BREQ load_first_byte

    RJMP  resistance_reset_loop

load_first_byte:

    MOV   auxReg, byteAttackReg ;o byte da fase de attack e carregado primeiro

up_resistance_start:

    DEC  BytesLeft ;decrementa opByterLeft em 1

    MOV  loopReg, auxReg
    CPI  loopReg, 0x0 ;se loop = 0, entao pula direto para o proximo opcode
    BREQ next_byte_continue

    LDI  auxReg, 0b00000000 ;PD3(digipots up/down pin) habilita o digipot para comecar em up
    ORI  digiPotSelectorReg, 0b00001111 ;prepara digiPotSelectorReg para ser invertido(ativo em low)
    COM  digiPotSelectorReg
    OR   auxReg, digiPotSelectorReg
    OUT  PORTD, auxReg

    ;RCALL delay500
    RCALL delay1us

up_resistance_loop:
    ;ativa e desativa o PD2(digipots CLK) enquanto o numero de steps(ou loops) armazenados em loopReg e != 0

    ORI  auxReg, 0b00000100 ;borda de subida
    OUT  PORTD, auxReg

    ;RCALL delay500
    RCALL delay1us

    ANDI auxReg, 0b11111011 ;borda de descida
    OUT  PORTD, auxReg

    ;RCALL delay500
    RCALL delay1us

    DEC  loopReg
    BREQ next_byte ;se loop foi finalizado pula para o proxima fase do ADSR

    RJMP up_resistance_loop ;caso o loop nao tenha acabado retorna para o comeco dele

next_byte:

    ;restaura digiPotSelectorReg para a forma binaria original
    ORI digiPotSelectorReg, 0b00001111
    COM digiPotSelectorReg

next_byte_continue:

    ;ativa o proximo digipot
    LSR  digiPotSelectorReg

    ;se BytesLeft == 0 jump para "fim" label
    CPI  BytesLeft, 0b00000000
    BREQ fim

    ;se BytesLeft == 3 jump para byte_hold label
    CPI  BytesLeft, 0b00000011
    BREQ byte_hold

    ;se BytesLeft == 2 jump para byte_sustain label
    ;se BytesLeft != 2 codigo continua
    CPI  BytesLeft, 0b00000010
    BREQ byte_sustain

byte_decay_and_release:

    ;carrega byteDecayAndReleaseReg para auxReg e reinicia o codigo em up_resistance_start
    MOV  auxReg, byteDecayAndReleaseReg
    RJMP up_resistance_start

byte_hold:

    ;carrega byteSustainReg para auxReg e reinicia o codigo em up_resistance_start
    MOV  auxReg, byteHoldReg
    RJMP up_resistance_start

byte_sustain:

    ;carrega byteSustainReg para auxReg e reinicia o codigo em up_resistance_start
    MOV  auxReg, byteSustainReg
    RJMP up_resistance_start

fim:

    RJMP main_loop

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
    MOV  byteAttackReg, byteRecebido

recebeByte2:

    ;Byte2
    LDS  auxReg, UCSR0A
    SBRS auxReg, RXC0
    RJMP recebeByte2

    LDS  byteRecebido, UDR0
    MOV  byteHoldReg, byteRecebido

recebeByte3:

    ;Byte3
    LDS  auxReg, UCSR0A
    SBRS auxReg, RXC0
    RJMP recebeByte3

    LDS  byteRecebido, UDR0
    MOV  byteSustainReg, byteRecebido

recebeByte4:

    ;Byte4
    LDS  auxReg, UCSR0A
    SBRS auxReg, RXC0
    RJMP recebeByte4

    LDS  byteRecebido, UDR0
    MOV  byteDecayAndReleaseReg, byteRecebido

    RET

; ------------------------------------------------------------------------------
; Function definitions
; ------------------------------------------------------------------------------
delay1us:
    ; Zera TCNT1
    LDI auxReg, 0
    STS TCNT1H, auxReg
    STS TCNT1L, auxReg

delay1us_polling:
    LDS auxReg, TIFR1
    SBRS auxReg, OCF1A     ; Verifica flag de comparação
    RJMP delay1us_polling

    ; Limpa a flag escrevendo 1
    LDI auxReg, (1 << OCF1A)
    STS TIFR1, auxReg

    RET

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
