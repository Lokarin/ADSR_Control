# ----------------- Configurações -----------------
MCU = atmega328p
F_CPU = 16000000UL

TARGET = application
SRC = main.asm
BUILD_DIR = build
INCLUDES = include

AVRA = avra
AVRDUDE = avrdude
PROGRAMMER = usbasp
PORT = usb  # ou /dev/ttyUSB0 se for serial
BAUD = 19200

# Cria a pasta build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# ----------------- Compilação -----------------
assemble: $(BUILD_DIR)/$(TARGET).hex

$(BUILD_DIR)/$(TARGET).hex: $(SRC) | $(BUILD_DIR)
	$(AVRA) -fI -I $(INCLUDES) \
		-m "$(BUILD_DIR)/$(TARGET).map" \
		-l "$(BUILD_DIR)/$(TARGET).lss" \
		-e "$(BUILD_DIR)/$(TARGET).eep" \
		-d "$(BUILD_DIR)/$(TARGET).o" \
		-o "$(BUILD_DIR)/$(TARGET).hex" \
		$(SRC)

# ----------------- Upload para a placa -----------------
upload: all
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) \
		-U flash:w:$(BUILD_DIR)/$(TARGET).hex:i \
		-b $(BAUD) -P $(PORT)

# ----------------- Limpeza -----------------
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all upload clean
