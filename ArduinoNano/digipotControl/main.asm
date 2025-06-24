; ------------------------------------------------------------------------------
; Project:  Digipot Control
; File:     main.asm
; Author:   Gabriel Garcia; Henrique Onuki
; Created:  2025-04-19
<<<<<<< Updated upstream
; Modified: 2025-05-29
; Version:  1.i
=======
; Modified: 2025-06-12
; Version:  1.k
>>>>>>> Stashed changes
; Notes:    Controle de Digipots. Fcpu = 16 MHz.
; ------------------------------------------------------------------------------

; ------------------------------------------------------------------------------
; Include definition files
; ------------------------------------------------------------------------------
.include "include/m328Pdef.inc"

; ------------------------------------------------------------------------------
; Register definitions
; ------------------------------------------------------------------------------
.def   tempReg                     = R16
.def   digiPotSelector             = R17
.def   counterBytesLeft            = R21
.def   loopReg                     = R22
.def   timer1FreqByteLow           = R23
.def   timer1FreqByteHigh          = R24
.def   timer2FreqByte              = R25
.def   receivedByte                = R0
.def   attackByte                  = R1
.def   holdByte                    = R2
.def   decayAndReleaseByte         = R3
.def   sustainByte                 = R4

; ------------------------------------------------------------------------------
<<<<<<< Updated upstream
=======
; equal definitions
; ------------------------------------------------------------------------------

.equ digipot_control_mask   = 0b11111101
.equ TRIGGER_SECTION        = 0x00
.equ TRIGGER_AUTO           = 0x00
.equ TRIGGER_MANUAL_AND_OFF = 0x01
.equ TRIGGER_MANUAL_AND_ON  = 0x03

; ------------------------------------------------------------------------------
>>>>>>> Stashed changes
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

; =====================[ INIT: Timer0 para delay de 1us ]======================

init_timer0_delay_us:

    ; Modo CTC + prescaler 8
    LDI tempReg, (1 << WGM01)
    OUT TCCR0A, tempReg

    LDI tempReg, (1 << CS01)
    OUT TCCR0B, tempReg

    LDI tempReg, 1
    OUT OCR0A, tempReg

; ===================[ INIT: Timer1 como trigger do ADSR ]=====================

init_timer1_adsr_trigger:

    ; PB1 como saída
    SBI DDRB, PB1

    ; Prescaler 256 + Modo CTC
    LDI tempReg, (1<<CS12) | (1<<WGM12)
    STS TCCR1B, tempReg

    ; Inicialização de OCR1A com valor equivalente a 3Hz
    LDI tempReg, high(10416)
    STS OCR1AH, tempReg

    LDI tempReg, low(10416)
    STS OCR1AL, tempReg

    ; Inicialização em modo manual
    RCALL set_trigger_manual_and_off

; ====================[ INIT: Timer2 como input do VCA ]=======================

init_timer2_vca_input:

    ; PB3 como saída
    SBI DDRB, PB3

    ; OC1A (PB3) como toggle + Modo CTC
    LDI tempReg, (1<<COM2A0) | (1<<WGM21)
    STS TCCR2A, tempReg

    ; prescaler 1024
    LDI tempReg, (1<<CS22) | (1<<CS21) 
    STS TCCR2B, tempReg

    ; Inicialização padrão com 1kHz
    LDI tempReg, 7
    STS OCR2A, tempReg

; ==========================[ INIT: USART 9600 bps ]===========================

init_usart:

    LDI tempReg, high(103)
    STS UBRR0H, tempReg
    LDI tempReg, low(103)
    STS UBRR0L, tempReg

    ; 8 bits, 1 stop, sem paridade
    LDI tempReg, (1 << UCSZ01) | (1 << UCSZ00)
    STS UCSR0C, tempReg

<<<<<<< Updated upstream
    ; Habilita pino RX (PD0)
    LDI tempReg, (1 << RXEN0)
=======
    ; Habilita pino RX (PD0) e interrupção
    LDI tempReg, (1 << RXCIE0) | (1 << RXEN0)
>>>>>>> Stashed changes
    STS UCSR0B, tempReg

; =====================[ INIT: Configurações das portas D ]====================

main_start:
init_ports:

    LDI tempReg, 0xFF
    OUT DDRD, tempReg                           ; Habilita todas as portas D como saída

; =====================[ LOOP: loop principal do programa ]====================

main_loop:

    LDI counterBytesLeft, 0b00000100
    LDI digiPotSelector, 0b10000000             ; PD7, PD6, PD5, PD4 = habilita o Chip Select dos digipots

    LDI tempReg, 0b11110000
    OUT PORTD, tempReg                          ; Inicia todas as saídas com 0V menos PD7, PD6, PD5, PD4 (Chip Select)

; ==================[ USART: recepção de bytes ]===============================

<<<<<<< Updated upstream
read_adsr_and_timer_bytes:
=======
    SEI

; =====================[ MAIN LOOP: Espera por bytes ]=========================

main_loop:

waiting_for_bytes:
    RJMP waiting_for_bytes

; ======================[ SUB ROTINA: Espera e lê byte ]=======================

usart_receive_byte:
USART_read:
    LDS  tempReg, UCSR0A
    SBRS tempReg, RXC0
    RJMP USART_read
    LDS  tempReg, UDR0
    RET

; ================[ SUB ROTINA: zera todos os potenciômetros ]=================

reset_all_digipots:
    ; Configura todos os potenciômetros para começarem do valor mais baixo
    ; de resistência

    LDI tempReg, 0b00001000             ; Ativa todos CS(chip select) e configura a resistência para baixo(down)
    OUT PORTD, tempReg

    LDI loopReg, 0b1101001              ; Carrega loopReg com 105 (garante que haverá mais que 100 ciclos)

digipot_reset_loop:

    ORI   tempReg, 0b00000100           ; Borda de subida
    OUT   PORTD, tempReg
    ;RCALL delay100
    RCALL delay_250n

    ANDI  tempReg, 0b11111011           ; Borda de descida
    OUT   PORTD, tempReg
    ;RCALL delay100
    RCALL delay_250n

    DEC   loopReg                       ; Quando loopReg atingir zero o reset dos potenciômetros está completo
    BRNE  digipot_reset_loop

    RET

; ===============[ SUB ROTINA: Ativa ou desativa VCA input ]===================

jack_detector_input:

    IN   tempReg, PINB ; Carrega o estado dos pinos atuais
    ANDI tempReg, 0b00010000 ; Isola o bit PB4

    SBRS tempReg, PB4
    RJMP activate_vca_input
    RJMP deactivate_vca_input

deactivate_vca_input:

    ; Desliga Timer2
    LDI  tempReg, 0
    STS  TCCR2B, tempReg

    LDI  tempReg, 0
    STS  TCCR2A, tempReg

    ; Configura PB3 como entrada
    CBI  DDRB, PB3
    ; Desativa o pull-up interno
    CBI  PORTB, PB3
    RJMP jack_detector_input_end

activate_vca_input:

    ; PB3 como saída
    SBI DDRB, PB3

    ; OC1A (PB3) como toggle + Modo CTC
    LDI tempReg, (1<<COM2A0) | (1<<WGM21)
    STS TCCR2A, tempReg

    ; prescaler 256
    LDI tempReg, (1<<CS22) | (1<<CS21)
    STS TCCR2B, tempReg

jack_detector_input_end:

    RET

; ==============[ SUB ROTINA: configura modo auto do trigger  ]================

set_trigger_auto:
    ; OC1A (PB1) como toggle
    LDI tempReg, (1<<COM1A0)
    STS TCCR1A, tempReg

    RET

; =========[ SUB ROTINA: configura modo manual e ligado do trigger  ]==========

set_trigger_manual_and_on:
    ; OC1A (PB1) toggle desativado
    LDI tempReg, (0<<COM1A0)
    STS TCCR1A, tempReg

    ; Ativa PB1 (nível HIGH)
    SBI PORTB, PB1

    RET

; =======[ SUB ROTINA: configura modo manual e desligado do trigger  ]=========

set_trigger_manual_and_off:
    ; OC1A (PB1) toggle desativado
    LDI tempReg, (0<<COM1A0)
    STS TCCR1A, tempReg

    ; Desativa PB1 (nível LOW)
    CBI PORTB, PB1

    RET

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

delay_250n:

    ; Zera contador TCNT0
    CLR R18
    OUT TCNT0, R18

delay_250n_polling:

    ; Espera OCF0A == 3
    IN   R18, TIFR0
    SBRS R18, OCF0A
    RJMP delay_250n_polling

    ; Limpa a flag de compare A
    LDI  R18, (1 << OCF0A)
    OUT  TIFR0, R18

    RET

; ------------------------------------------------------------------------------
; Interrupt handlers
; ------------------------------------------------------------------------------
pcint0Handler:
    CLI
    RCALL jack_detector_input
    RETI

usartRxHandler:
    CLI

read_adsr_and_timer_bytes:

    ; Lê primeiro o byte que informa de qual label o programa deve partir
    ; Se byte = 0x00, então jump para triggerSection
    ; Se byte = 0x01, então jump para ahdsrSection
    RCALL usart_receive_byte
    CPI   tempReg, TRIGGER_SECTION
    BREQ  triggerSection
    RJMP  ahdsrSection

triggerSection:
    ; Lê segundo byte que informa o comando a ser executado
    RCALL usart_receive_byte

    ; Verifica qual é o comando
    CPI   tempReg, TRIGGER_AUTO
    BREQ  handle_cmd_mode_auto

    CPI   tempReg, TRIGGER_MANUAL_AND_ON
    BREQ  handle_cmd_mode_manual_on

    CPI   tempReg, TRIGGER_MANUAL_AND_OFF
    BREQ  handle_cmd_mode_manual_off

handle_cmd_mode_auto:
    RCALL set_trigger_auto
    RETI

handle_cmd_mode_manual_on:
    RCALL set_trigger_manual_and_on
    RETI

handle_cmd_mode_manual_off:
    RCALL set_trigger_manual_and_off
    RETI

ahdsrSection:
>>>>>>> Stashed changes

    RCALL usart_receive_byte
    MOV   attackByte, tempReg

    RCALL usart_receive_byte
    MOV   holdByte, tempReg

    RCALL usart_receive_byte
    MOV   sustainByte, tempReg

    RCALL usart_receive_byte
    MOV   decayAndReleaseByte, tempReg

    RCALL usart_receive_byte
    MOV   timer1FreqByteHigh, tempReg

    RCALL usart_receive_byte
    MOV   timer1FreqByteLow, tempReg

    RCALL usart_receive_byte
    MOV   timer2FreqByte, tempReg

; ===============[ ADSR_CTRL: Ajuste de frequência do trigger ]================

set_adsr_trigger_freq:

    ; Para o Timer1 temporariamente
    LDI tempReg, 0
    STS TCCR1B, tempReg

    ; Reseta o contador do Timer1
    LDI tempReg, 0
    STS TCNT1H, tempReg
    STS TCNT1L, tempReg

    ; Atualiza os valores de comparação
    STS OCR1AH, timer1FreqByteHigh
    STS OCR1AL, timer1FreqByteLow

    ; Religa o Timer1 com prescaler 256 + Modo CTC
    LDI tempReg, (1<<CS12) | (1<<WGM12)
    STS TCCR1B, tempReg

; =============[ VCA_CTRL: Ajuste de frequência de entrada ]===================

set_vca_input_freq:

    STS OCR2A, timer2FreqByte

; =================[ DIGIPOTS: Zera todos os potenciômetros ]==================

reset_all_digipots:
    ; Seta todos os potenciômetros para começarem do valor mais baixo
    ; de resistência após receber os bytes correspondentes a cada fase

    LDI tempReg, 0b00001000             ; Ativa todos CS(chip select) e seta a resistência para baixo(down)
    OUT PORTD, tempReg

    LDI loopReg, 0b1101001              ; Carrega loopReg com 105 (garante que haverá mais que 100 ciclos)

digipot_reset_loop:

    ORI   tempReg, 0b00000100           ; Borda de subida
    OUT   PORTD, tempReg
    ;RCALL delay100
    RCALL delay_1us

    ANDI  tempReg, 0b11111011           ; Borda de descida
    OUT   PORTD, tempReg
    ;RCALL delay100
    RCALL delay_1us

    DEC   loopReg                       ; Quando loopReg for zerado o reset dos potenciômetros está completo
    BREQ  load_first_phase_byte

    RJMP  digipot_reset_loop

; ===============[ DIGIPOTS: Atualiza valores dos digipots ]==================

load_first_phase_byte:

    MOV   tempReg, attackByte                   ; Byte da fase de attack é carregado primeiro

digipot_step_up_start:

    DEC   counterBytesLeft                      ; Decrementa counterBytesLeft em 1

    MOV   loopReg, tempReg
    CPI   loopReg, 0x0                          ; Se loop = 0 jump para o próximo byte
    BREQ  prepare_next_phase

    LDI   tempReg, 0b00000000                   ; PD3(digipots up/down pino) habilita o digipot para começar em up
    ORI   digiPotSelector, 0b00001111           ; Prepara digiPotSelector para ser invertido(ativo em low)
    COM   digiPotSelector
    OR    tempReg, digiPotSelector
    OUT   PORTD, tempReg

    ;RCALL delay500
    RCALL delay_1us

digipot_step_up_loop:
    ; Ativa e desativa o PD2(digipots CLK) enquanto o número de steps(ou loops) armazenados em loopReg e != 0

    ORI   tempReg, 0b00000100           ; Borda de subida
    OUT   PORTD, tempReg

    ;RCALL delay500
    RCALL delay_1us

    ANDI  tempReg, 0b11111011           ; Borda de descida
    OUT   PORTD, tempReg

    ;RCALL delay500
    RCALL delay_1us

    DEC   loopReg
    BREQ  next_adsr_phase               ; Se loop foi finalizado jump para a próxima fase do ADSR

    RJMP  digipot_step_up_loop          ; Caso o loop nao tenha acabado retorna para o começo dele

; =============[ BYTE_LOAD: Carrega byte da próxima fase do ADSR ]=============

next_adsr_phase:

    ; Restaura digiPotSelector para a forma binária original
    ORI digiPotSelector, 0b00001111
    COM digiPotSelector

prepare_next_phase:

    ; Ativa o próximo digipot
    LSR  digiPotSelector

    ; Se counterBytesLeft == 0 jump para "fim" label
    CPI  counterBytesLeft, 0b00000000
    BREQ fim

    ; Se counterBytesLeft == 3 jump para load_hold_byte label
    CPI  counterBytesLeft, 0b00000011
    BREQ load_hold_byte

    ; Se counterBytesLeft == 2 jump para load_sustain_byte label
    ; Se counterBytesLeft != 2 código continua
    CPI  counterBytesLeft, 0b00000010
    BREQ load_sustain_byte

load_decay_release_byte:

    ; Carrega decayAndReleaseByte para tempReg e reinicia o código em digipot_step_up_start
    MOV  tempReg, decayAndReleaseByte
    RJMP digipot_step_up_start

load_hold_byte:

    ; Carrega holdByte para tempReg e reinicia o código em digipot_step_up_start
    MOV  tempReg, holdByte
    RJMP digipot_step_up_start

load_sustain_byte:

    ; Carrega sustainByte para tempReg e reinicia o código em digipot_step_up_start
    MOV  tempReg, sustainByte
    RJMP digipot_step_up_start

fim:

<<<<<<< Updated upstream
    RJMP main_loop
=======
    LDI digiPotSelector, 0b10000000             ; PD7, PD6, PD5, PD4 = habilita o Chip Select dos digipots
    LDI counterBytesLeft, 0b00000100            ; Quando counterBytesLeft alcançar 0 o código retorna para main_loop
>>>>>>> Stashed changes

; ======================[ SUB ROTINA: Espera e lê byte ]=======================

usart_receive_byte:
USART_read:
    LDS  tempReg, UCSR0A
    SBRS tempReg, RXC0
    RJMP USART_read
    LDS  tempReg, UDR0
    RET

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

delay_1us:

    ; Zera contador TCNT0
    CLR R18
    OUT TCNT0, R18

delay_1us_polling:

    ; Espera OCF0A == 1
    IN   R18, TIFR0
    SBRS R18, OCF0A
    RJMP delay_1us_polling

    ; Limpa a flag de compare A (escreve 1 para limpar)
    LDI  R18, (1 << OCF0A)
    OUT  TIFR0, R18

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
