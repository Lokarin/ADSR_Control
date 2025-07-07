; ------------------------------------------------------------------------------
; Project:  Digipot Control
; File:     main.asm
; Author:   Gabriel Garcia; Henrique Onuki
; Created:  2025-04-19
; Modified: 2025-06-15
; Version:  1.l
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
.def   timer1FreqByteLow           = R17
.def   timer1FreqByteHigh          = R18
.def   timer2FreqByte              = R19
.def   receivedByte                = R0
.def   attackByte                  = R1
.def   holdByte                    = R2
.def   decayAndReleaseByte         = R3
.def   sustainByte                 = R4

; ------------------------------------------------------------------------------
; equal definitions
; ------------------------------------------------------------------------------
.equ TRIGGER_SECTION        = 0x00
.equ TRIGGER_AUTO           = 0x00
.equ TRIGGER_MANUAL_AND_OFF = 0x01
.equ TRIGGER_MANUAL_AND_ON  = 0x03
.equ TWBR_BIT_RATE          = 18
.equ SLA0_W                 = 0b01010000
.equ SLA1_W                 = 0b01010010
.equ WR_POT_0               = 0b10101001
.equ WR_POT_1               = 0b10101010

; ------------------------------------------------------------------------------
; Interrupt vectors
; ------------------------------------------------------------------------------
.org 0x0000
    JMP resetHandler
.org PCI0addr
    JMP pcint0Handler
.org URXCaddr
    JMP usartRxHandler
.org SPMRaddr
    JMP flashHandler
.org INT_VECTORS_SIZE

; ------------------------------------------------------------------------------
; Main function
; ------------------------------------------------------------------------------
main:

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

    ; Configura origem inicial do VCA input
    RCALL jack_detector_input

    ; Inicialização padrão com 130Hz
    LDI   tempReg, 238
    STS   OCR2A, tempReg

; ==========================[ INIT: USART 9600 bps ]===========================

init_usart:

    LDI tempReg, high(103)
    STS UBRR0H, tempReg
    LDI tempReg, low(103)
    STS UBRR0L, tempReg

    ; 8 bits, 1 stop, sem paridade
    LDI tempReg, (1 << UCSZ01) | (1 << UCSZ00)
    STS UCSR0C, tempReg

    ; Habilita pino RX (PD0) e interrupção
    LDI tempReg, (1 << RXCIE0) | (1 << RXEN0)
    STS UCSR0B, tempReg

; ===============================[ INIT: TWI ]=================================

init_twi:

    ; Scl freq = 100kHz
    LDI tempReg, TWBR_BIT_RATE
    STS TWBR, tempReg

    ; Prescaler = 1
    LDI tempReg, (0<<TWPS1) | (0<<TWPS0)
    STS TWSR, tempReg

    ; Ativa TWI
    LDI tempReg, (1<<TWEN)
    STS TWCR, tempReg

; ======================[ INIT: Configurações da PCINT0 ]======================

init_PCINT0:

    ; Habilita o grupo de interrupção (PCINT0-PCINT7)
    LDI tempReg, (1 << PCIE0)
    STS PCICR, tempReg

    ; Ativando interrupção em PCIN7
    LDI tempReg, (1 << PCINT4)
    STS PCMSK0, tempReg

    ; Habilita PB4 como entrada com pull-up interno
    CBI DDRB, PB4
    SBI PORTB, PB4

; ===================[ INIT: Ativa interrupções globais ]======================

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

; =============[ SUB ROTINA: configura trigger para modo auto  ]===============

set_trigger_auto:
    ; OC1A (PB1) como toggle
    LDI tempReg, (1<<COM1A0)
    STS TCCR1A, tempReg

    RET

; ========[ SUB ROTINA: configura trigger para modo manual e ligado  ]=========

set_trigger_manual_and_on:
    ; OC1A (PB1) toggle desativado
    LDI tempReg, (0<<COM1A0)
    STS TCCR1A, tempReg

    ; Ativa PB1 (nível HIGH)
    SBI PORTB, PB1

    RET

; ======[ SUB ROTINA: configura trigger para modo manual e desligado  ]========

set_trigger_manual_and_off:
    ; OC1A (PB1) toggle desativado
    LDI tempReg, (0<<COM1A0)
    STS TCCR1A, tempReg

    ; Desativa PB1 (nível LOW)
    CBI PORTB, PB1

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

    STS OCR1AH, timer1FreqByteHigh
    STS OCR1AL, timer1FreqByteLow

; =============[ VCA_CTRL: Ajuste de frequência de entrada ]===================

set_vca_input_freq:

    STS OCR2A, timer2FreqByte

; ===============[ DIGIPOTS: Atualiza valores dos digipots ]==================

    ; Limpa flag, start twi, liga twi
    LDI tempReg, (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) ; limpa flag e dá start
    STS TWCR, tempReg

    ; Espera transmissão ser completada
    wait:
    LDS tempReg, TWCR
    SBRS tempReg, TWINT
    RJMP wait;

    ; Carrega adress + write e inicia transmissão
    LDI tempReg, SLA0_W
    STS TWDR, tempReg
    LDI tempReg, (1<<TWINT) | (1<<TWEN)
    STS TWCR, tempReg

    ; Espera transmissão ser completada
    wait1:
    LDS tempReg, TWCR
    SBRS tempReg, TWINT
    RJMP wait1;

    ; Carrega command byte e inicia transmissão
    LDI tempReg, WR_POT_0
    STS TWDR, tempReg
    LDI tempReg, (1<<TWINT) | (1<<TWEN)
    STS TWCR, tempReg

    ; Espera transmissão ser completada
    wait2:
    LDS tempReg, TWCR
    SBRS tempReg, TWINT
    RJMP wait2;

    ; Carrega data byte e inicia transmissão para configurar pot0
    STS TWDR, attackByte
    LDI tempReg, (1<<TWINT) | (1<<TWEN)
    STS TWCR, tempReg

    ; Espera transmissão ser completada
    wait3:
    LDS tempReg, TWCR
    SBRS tempReg, TWINT
    RJMP wait3

    ; Carrega data byte e inicia transmissão para configurar pot1
    STS TWDR, decayAndReleaseByte
    LDI tempReg, (1<<TWINT) | (1<<TWEN)
    STS TWCR, tempReg

    ; Espera transmissão ser completada
    wait4:
    LDS tempReg, TWCR
    SBRS tempReg, TWINT
    RJMP wait4

    ; Repeated Start
    LDI tempReg, (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) ; limpa flag e dá start
    STS TWCR, tempReg

    ; Espera transmissão ser completada
    wait5:
    LDS tempReg, TWCR
    SBRS tempReg, TWINT
    RJMP wait5;

    ; Carrega adress + write e inicia transmissão
    LDI tempReg, SLA1_W
    STS TWDR, tempReg
    LDI tempReg, (1<<TWINT) | (1<<TWEN)
    STS TWCR, tempReg

    ; Espera transmissão ser completada
    wait6:
    LDS tempReg, TWCR
    SBRS tempReg, TWINT
    RJMP wait6;

    ; Carrega command byte e inicia transmissão
    LDI tempReg, WR_POT_0
    STS TWDR, tempReg
    LDI tempReg, (1<<TWINT) | (1<<TWEN)
    STS TWCR, tempReg

    ; Espera transmissão ser completada
    wait7:
    LDS tempReg, TWCR
    SBRS tempReg, TWINT
    RJMP wait7;

    ; Carrega data byte e inicia transmissão para configurar pot0
    STS TWDR, holdByte
    LDI tempReg, (1<<TWINT) | (1<<TWEN)
    STS TWCR, tempReg

    ; Espera transmissão ser completada
    wait8:
    LDS tempReg, TWCR
    SBRS tempReg, TWINT
    RJMP wait8

    ; Carrega data byte e inicia transmissão para configurar pot1
    STS TWDR, sustainByte
    LDI tempReg, (1<<TWINT) | (1<<TWEN)
    STS TWCR, tempReg

    ; Espera transmissão ser completada
    wait9:
    LDS tempReg, TWCR
    SBRS tempReg, TWINT
    RJMP wait9

    ; Stop
    LDI tempReg, (1<<TWSTO) | (1<<TWINT) | (1<<TWEN)
    STS TWCR, tempReg

    RETI
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

