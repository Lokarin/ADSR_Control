# Caminho do diretório de build
BUILD_DIR := build

# Alvo padrão
all: rebuild

# Remove o diretório de build, cria um novo, roda cmake e make
rebuild:
	@echo ">> Limpando build antigo..."
	@rm -rf $(BUILD_DIR)
	@mkdir $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake ..
	@cd $(BUILD_DIR) && $(MAKE)

# Executa apenas make no diretório de build existente
build:
	@cd $(BUILD_DIR) && $(MAKE)

# Limpa o diretório de build
clean:
	@rm -rf $(BUILD_DIR)
	@echo ">> Diretório '$(BUILD_DIR)' removido."

.PHONY: all rebuild build clean

