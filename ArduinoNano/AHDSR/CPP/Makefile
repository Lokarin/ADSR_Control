# ##############################################################################
# Sample Makefile for AVR/STM32 HAL Library applications in C and C++
# Leandro Schwarz
# ##############################################################################

# ==============================================================================
# Environment variables
# ==============================================================================

# ------------------------------------------------------------------------------
# Received through application -------------------------------------------------

BUILD_DIR								?= build
BUILD_NAME								?= application
COMPILE_C_AS_CPP						?= 0
COMPILER_DEBUG							?= 0
COMPILER_OPT							?= -Og
COMPILER_PATH							?=
COMPILER_STD_C							?= c11
COMPILER_STD_CPP						?= c++14
FUNSAPE_PATH							?= funsape
LIBRARY_PATH							?=
MCU_DEVICE_CORE_FLOAT_ABI				?=
MCU_DEVICE_CORE_FPU						?=
MCU_DEVICE_NAME							?= STM32F103C8Tx
PROGRAMMER_CONFIG_FILE					?= avrdude.conf
PROGRAMMER_TYPE							?= ST_LINK_SWD
USER_DEFINES_ASM						?=
USER_DEFINES_C							?= USE_HAL_DRIVER
USER_DEFINES_CPP						?= USE_HAL_DRIVER
USER_FLAGS_ASM							?=
USER_FLAGS_C							?= -Wno-switch
USER_FLAGS_CPP							?= -Wno-switch
USER_LIBS								?=
CXXFLAGS += -ffunction-sections -fdata-sections
LDFLAGS  += -Wl,--gc-sections
include libs/port.mk

# ==============================================================================
# Function definitions
# ==============================================================================

rwildcard								= $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
filter-out-any							= $(foreach v,$(2),$(if $(findstring $(1),$(v)),,$(v)))

# ------------------------------------------------------------------------------
# Fixed value - DO NOT CHANGE --------------------------------------------------

MCU_AVR_CODE_OFFSET						:= 0
MCU_STM32_CODE_OFFSET					:= 300

# ------------------------------------------------------------------------------
# Calculated based on received variables ---------------------------------------

MCU_DEVICE_CODE							:= 0
include libs/Makefile-AVR.mk
include libs/Makefile-ARM-STM32.mk
ifeq ($(MCU_DEVICE_CODE),0)
    $(error No supported device found. Verify the MCU_DEVICE_NAME environment variable!)
endif

# ==============================================================================
# Compiler exacutables
# ==============================================================================

# ------------------------------------------------------------------------------
# Evaluate compiler prefix based on MCU platform -------------------------------

ifeq ($(MCU_DEVICE_PLATFORM),AVR)
    COMPILER_PREFIX						= avr-
else ifeq  ($(MCU_DEVICE_PLATFORM),STM32)
    COMPILER_PREFIX						= arm-none-eabi-
else
    $(error Platform not supported. Verify the MCU_DEVICE_NAME environment variable!)
endif

# ------------------------------------------------------------------------------
# Evaluate executables names based on compiler path ----------------------------

ifneq ($(COMPILER_PATH),)
    COMPILER_PATH						:= $(COMPILER_PATH)/
endif

AR										:= $(COMPILER_PATH)$(COMPILER_PREFIX)ar
ifeq ($(MCU_DEVICE_PLATFORM),AVR)
    AS									:= $(COMPILER_PATH)$(COMPILER_PREFIX)gcc -x assemble-with-cpp
else ifeq  ($(MCU_DEVICE_PLATFORM),STM32)
    AS									:= $(COMPILER_PATH)$(COMPILER_PREFIX)gcc -x assembler-with-cpp
endif
BIN										:= $(COMPILER_PATH)$(COMPILER_PREFIX)objcopy -O binary -S
CC										:= $(COMPILER_PATH)$(COMPILER_PREFIX)gcc
CCPP									:= $(COMPILER_PATH)$(COMPILER_PREFIX)g++
CP										:= $(COMPILER_PATH)$(COMPILER_PREFIX)objcopy
HEX										:= $(COMPILER_PATH)$(COMPILER_PREFIX)objcopy -O ihex
SZ										:= $(COMPILER_PATH)$(COMPILER_PREFIX)size --mcu=$(MCU_DEVICE_NAME) --format=avr

# ==============================================================================
# Search for files
# ==============================================================================

# ------------------------------------------------------------------------------
# Declaring variables
# ------------------------------------------------------------------------------

CODE_HEADERS_ASM						=
CODE_HEADERS_H							=
CODE_HEADERS_HPP						=
CODE_HEADERS_HXX						=
CODE_HEADERS_ALL						=
CODE_SOURCES_ASM						=
CODE_SOURCES_S							=
CODE_SOURCES_AXX						=
CODE_SOURCES_C							=
CODE_SOURCES_CPP						=
CODE_SOURCES_CXX						=
FUNSAPE_HEADERS_ASM						=
FUNSAPE_HEADERS_H						=
FUNSAPE_HEADERS_HPP						=
FUNSAPE_HEADERS_HXX						=
FUNSAPE_HEADERS_ALL						=
FUNSAPE_SOURCES_ASM						=
FUNSAPE_SOURCES_S						=
FUNSAPE_SOURCES_AXX						=
FUNSAPE_SOURCES_C						=
FUNSAPE_SOURCES_CPP						=
FUNSAPE_SOURCES_CXX						=

# ------------------------------------------------------------------------------
# Main code
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Main code - ASM header files -------------------------------------------------

CODE_HEADERS_ASM		:= $(sort $(dir $(call rwildcard, , *.S)))
CODE_HEADERS_ASM		:= $(sort $(call filter-out-any,_hide/,$(CODE_HEADERS_ASM)))
CODE_HEADERS_ASM		:= $(sort $(call filter-out-any,doc/,$(CODE_HEADERS_ASM)))
CODE_HEADERS_ASM		:= $(sort $(call filter-out-any,Release/,$(CODE_HEADERS_ASM)))
CODE_HEADERS_ASM		:= $(sort $(call filter-out-any,temp/,$(CODE_HEADERS_ASM)))
CODE_HEADERS_ASM		:= $(sort $(call filter-out-any,$(FUNSAPE_PATH)/,$(CODE_HEADERS_ASM)))

# ------------------------------------------------------------------------------
# Main code - H header files ---------------------------------------------------

CODE_HEADERS_H			:= $(sort $(dir $(call rwildcard, , *.h)))

CODE_HEADERS_H			:= $(sort $(call filter-out-any,_hide/,$(CODE_HEADERS_H)))
CODE_HEADERS_H			:= $(sort $(call filter-out-any,doc/,$(CODE_HEADERS_H)))
CODE_HEADERS_H			:= $(sort $(call filter-out-any,Release/,$(CODE_HEADERS_H)))
CODE_HEADERS_H			:= $(sort $(call filter-out-any,temp/,$(CODE_HEADERS_H)))
ifeq ($(MCU_DEVICE_PLATFORM),AVR)
    # CODE_HEADERS_H		:= $(sort $(call filter-out-any,Core/,$(CODE_HEADERS_H)))
    # CODE_HEADERS_H		:= $(sort $(call filter-out-any,Drivers/,$(CODE_HEADERS_H)))
    # CODE_HEADERS_H		:= $(sort $(call filter-out-any,Middlewares/,$(CODE_HEADERS_H)))
    # CODE_HEADERS_H		:= $(sort $(call filter-out-any,USB_DEVICE/,$(CODE_HEADERS_H)))
endif

# ------------------------------------------------------------------------------
# Main cide - HPP header files -------------------------------------------------

CODE_HEADERS_HPP		:= $(sort $(dir $(call rwildcard, , *.hpp)))
CODE_HEADERS_HPP		:= $(sort $(call filter-out-any,_hide/,$(CODE_HEADERS_HPP)))
CODE_HEADERS_HPP		:= $(sort $(call filter-out-any,doc/,$(CODE_HEADERS_HPP)))
CODE_HEADERS_HPP		:= $(sort $(call filter-out-any,Release/,$(CODE_HEADERS_HPP)))
CODE_HEADERS_HPP		:= $(sort $(call filter-out-any,temp/,$(CODE_HEADERS_HPP)))
ifeq ($(MCU_DEVICE_PLATFORM),AVR)
    CODE_HEADERS_HPP	:= $(sort $(call filter-out-any,Core/,$(CODE_HEADERS_HPP)))
    CODE_HEADERS_HPP	:= $(sort $(call filter-out-any,Drivers/,$(CODE_HEADERS_HPP)))
    CODE_HEADERS_HPP	:= $(sort $(call filter-out-any,Middlewares/,$(CODE_HEADERS_HPP)))
    CODE_HEADERS_HPP	:= $(sort $(call filter-out-any,USB_DEVICE/,$(CODE_HEADERS_HPP)))
endif

# ------------------------------------------------------------------------------
# Main code - HXX header files -------------------------------------------------

CODE_HEADERS_HXX		:= $(sort $(CODE_HEADERS_H) $(CODE_HEADERS_HPP))

# ------------------------------------------------------------------------------
# Main code - All header files -------------------------------------------------

CODE_HEADERS_ALL		:= $(sort $(CODE_HEADERS_HXX) $(CODE_HEADERS_ASM))

# ------------------------------------------------------------------------------
# Main code - Assembly source files --------------------------------------------

CODE_SOURCES_S			:= $(sort $(call rwildcard, , *.s))
CODE_SOURCES_S			:= $(sort $(call filter-out-any,_hide/,$(CODE_SOURCES_S)))
CODE_SOURCES_S			:= $(sort $(call filter-out-any,doc/,$(CODE_SOURCES_S)))
CODE_SOURCES_S			:= $(sort $(call filter-out-any,Release/,$(CODE_SOURCES_S)))
CODE_SOURCES_S			:= $(sort $(call filter-out-any,temp/,$(CODE_SOURCES_S)))
ifeq ($(MCU_DEVICE_PLATFORM),AVR)
    CODE_SOURCES_S		:= $(sort $(call filter-out-any,Core/,$(CODE_SOURCES_S)))
    CODE_SOURCES_S		:= $(sort $(call filter-out-any,Drivers/,$(CODE_SOURCES_S)))
    CODE_SOURCES_S		:= $(sort $(call filter-out-any,Middlewares/,$(CODE_SOURCES_S)))
    CODE_SOURCES_S		:= $(sort $(call filter-out-any,USB_DEVICE/,$(CODE_SOURCES_S)))
    CODE_SOURCES_S		:= $(sort $(call filter-out-any,startup_stm32f103xb.s,$(CODE_SOURCES_S)))
endif

CODE_SOURCES_ASM		:= $(sort $(call rwildcard, , *.asm))
CODE_SOURCES_ASM		:= $(sort $(call filter-out-any,_hide/,$(CODE_SOURCES_ASM)))
CODE_SOURCES_ASM		:= $(sort $(call filter-out-any,doc/,$(CODE_SOURCES_ASM)))
CODE_SOURCES_ASM		:= $(sort $(call filter-out-any,Release/,$(CODE_SOURCES_ASM)))
CODE_SOURCES_ASM		:= $(sort $(call filter-out-any,temp/,$(CODE_SOURCES_ASM)))
ifeq ($(MCU_DEVICE_PLATFORM),AVR)
    CODE_SOURCES_ASM	:= $(sort $(call filter-out-any,Core/,$(CODE_SOURCES_ASM)))
    CODE_SOURCES_ASM	:= $(sort $(call filter-out-any,Drivers/,$(CODE_SOURCES_ASM)))
    CODE_SOURCES_ASM	:= $(sort $(call filter-out-any,Middlewares/,$(CODE_SOURCES_ASM)))
    CODE_SOURCES_ASM	:= $(sort $(call filter-out-any,USB_DEVICE/,$(CODE_SOURCES_ASM)))

endif

# ------------------------------------------------------------------------------
# Main code - AXX source files -------------------------------------------------

CODE_SOURCES_AXX		:= $(sort $(CODE_SOURCES_ASM) $(CODE_SOURCES_S))

# ------------------------------------------------------------------------------
# Main code - C source files ---------------------------------------------------

CODE_SOURCES_C			:= $(sort $(call rwildcard, , *.c))
CODE_SOURCES_C			:= $(sort $(call filter-out-any,_hide/,$(CODE_SOURCES_C)))
CODE_SOURCES_C			:= $(sort $(call filter-out-any,doc/,$(CODE_SOURCES_C)))
CODE_SOURCES_C			:= $(sort $(call filter-out-any,Release/,$(CODE_SOURCES_C)))
CODE_SOURCES_C			:= $(sort $(call filter-out-any,temp/,$(CODE_SOURCES_C)))
ifeq ($(MCU_DEVICE_PLATFORM),AVR)
    CODE_SOURCES_C		:= $(sort $(call filter-out-any,Core/,$(CODE_SOURCES_C)))
    CODE_SOURCES_C		:= $(sort $(call filter-out-any,Drivers/,$(CODE_SOURCES_C)))
    CODE_SOURCES_C		:= $(sort $(call filter-out-any,Middlewares/,$(CODE_SOURCES_C)))
    CODE_SOURCES_C		:= $(sort $(call filter-out-any,USB_DEVICE/,$(CODE_SOURCES_C)))
    CODE_SOURCES_C		:= $(sort $(call filter-out-any,syscalls.c,$(CODE_SOURCES_C)))
endif

# ------------------------------------------------------------------------------
# Main code - CPP source files -------------------------------------------------

CODE_SOURCES_CPP		:= $(sort $(call rwildcard, , *.cpp))
CODE_SOURCES_CPP		:= $(sort $(call filter-out-any,_hide/,$(CODE_SOURCES_CPP)))
CODE_SOURCES_CPP		:= $(sort $(call filter-out-any,doc/,$(CODE_SOURCES_CPP)))
CODE_SOURCES_CPP		:= $(sort $(call filter-out-any,Release/,$(CODE_SOURCES_CPP)))
CODE_SOURCES_CPP		:= $(sort $(call filter-out-any,temp/,$(CODE_SOURCES_CPP)))
ifeq ($(MCU_DEVICE_PLATFORM),AVR)
    CODE_SOURCES_CPP	:= $(sort $(call filter-out-any,Core/,$(CODE_SOURCES_CPP)))
    CODE_SOURCES_CPP	:= $(sort $(call filter-out-any,Drivers/,$(CODE_SOURCES_CPP)))
    CODE_SOURCES_CPP	:= $(sort $(call filter-out-any,Middlewares/,$(CODE_SOURCES_CPP)))
    CODE_SOURCES_CPP	:= $(sort $(call filter-out-any,USB_DEVICE/,$(CODE_SOURCES_CPP)))
else ifeq ($(MCU_DEVICE_PLATFORM),STM32)
    CODE_SOURCES_CPP	:= $(sort $(call filter-out-any,main_avr8.cpp,$(CODE_SOURCES_CPP)))
endif

# ------------------------------------------------------------------------------
# Main code - CXX source files -------------------------------------------------

CODE_SOURCES_CXX		:= $(sort $(CODE_SOURCES_C) $(CODE_SOURCES_CPP))

# ------------------------------------------------------------------------------
# FunSAPE Library
# ------------------------------------------------------------------------------

ifneq ($(FUNSAPE_PATH),)
    # --------------------------------------------------------------------------
    # FunSAPE Library - ASM header files ---------------------------------------

    FUNSAPE_HEADERS_ASM		:= $(sort $(dir $(call rwildcard, $(FUNSAPE_PATH), *.S)))
    FUNSAPE_HEADERS_ASM		:= $(sort $(call filter-out-any,_hide/,$(FUNSAPE_HEADERS_ASM)))
    FUNSAPE_HEADERS_ASM		:= $(sort $(call filter-out-any,doc/,$(FUNSAPE_HEADERS_ASM)))
    FUNSAPE_HEADERS_ASM		:= $(sort $(call filter-out-any,Release/,$(FUNSAPE_HEADERS_ASM)))
    FUNSAPE_HEADERS_ASM		:= $(sort $(call filter-out-any,temp/,$(FUNSAPE_HEADERS_ASM)))

    # --------------------------------------------------------------------------
    # FunSAPE Library - H header files -----------------------------------------

    FUNSAPE_HEADERS_H		:= $(sort $(dir $(call rwildcard, $(FUNSAPE_PATH), *.h)))
    FUNSAPE_HEADERS_H		:= $(sort $(call filter-out-any,_hide/,$(FUNSAPE_HEADERS_H)))
    FUNSAPE_HEADERS_H		:= $(sort $(call filter-out-any,doc/,$(FUNSAPE_HEADERS_H)))
    FUNSAPE_HEADERS_H		:= $(sort $(call filter-out-any,Release/,$(FUNSAPE_HEADERS_H)))
    FUNSAPE_HEADERS_H		:= $(sort $(call filter-out-any,temp/,$(FUNSAPE_HEADERS_H)))

    # --------------------------------------------------------------------------
    # FunSAPE Library - HPP header files ---------------------------------------

    FUNSAPE_HEADERS_HPP		:= $(sort $(dir $(call rwildcard, $(FUNSAPE_PATH), *.hpp)))
    FUNSAPE_HEADERS_HPP		:= $(sort $(call filter-out-any,_hide/,$(FUNSAPE_HEADERS_HPP)))
    FUNSAPE_HEADERS_HPP		:= $(sort $(call filter-out-any,doc/,$(FUNSAPE_HEADERS_HPP)))
    FUNSAPE_HEADERS_HPP		:= $(sort $(call filter-out-any,Release/,$(FUNSAPE_HEADERS_HPP)))
    FUNSAPE_HEADERS_HPP		:= $(sort $(call filter-out-any,temp/,$(FUNSAPE_HEADERS_HPP)))

    # --------------------------------------------------------------------------
    # FunSAPE Library - HXX header files ---------------------------------------

    FUNSAPE_HEADERS_HXX		:= $(sort $(FUNSAPE_HEADERS_H) $(FUNSAPE_HEADERS_HPP))

    # --------------------------------------------------------------------------
    # FunSAPE Library - All header files ---------------------------------------

    FUNSAPE_HEADERS_ALL		:= $(sort $(FUNSAPE_HEADERS_HXX) $(FUNSAPE_HEADERS_ASM))

    # --------------------------------------------------------------------------
    # FunSAPE Library - Assembly source files ----------------------------------

    FUNSAPE_SOURCES_S		:= $(sort $(call rwildcard, $(FUNSAPE_PATH), *.s))
    FUNSAPE_SOURCES_S		:= $(sort $(call filter-out-any,_hide/,$(FUNSAPE_SOURCES_S)))
    FUNSAPE_SOURCES_S		:= $(sort $(call filter-out-any,doc/,$(FUNSAPE_SOURCES_S)))
    FUNSAPE_SOURCES_S		:= $(sort $(call filter-out-any,Release/,$(FUNSAPE_SOURCES_S)))
    FUNSAPE_SOURCES_S		:= $(sort $(call filter-out-any,temp/,$(FUNSAPE_SOURCES_S)))
    FUNSAPE_SOURCES_ASM		:= $(sort $(call rwildcard, $(FUNSAPE_PATH), *.asm))
    FUNSAPE_SOURCES_ASM		:= $(sort $(call filter-out-any,_hide/,$(FUNSAPE_SOURCES_ASM)))
    FUNSAPE_SOURCES_ASM		:= $(sort $(call filter-out-any,doc/,$(FUNSAPE_SOURCES_ASM)))
    FUNSAPE_SOURCES_ASM		:= $(sort $(call filter-out-any,Release/,$(FUNSAPE_SOURCES_ASM)))
    FUNSAPE_SOURCES_ASM		:= $(sort $(call filter-out-any,temp/,$(FUNSAPE_SOURCES_ASM)))

    # --------------------------------------------------------------------------
    # FunSAPE Library - AXX source files ---------------------------------------

    FUNSAPE_SOURCES_AXX		:= $(sort $(FUNSAPE_SOURCES_ASM) $(FUNSAPE_SOURCES_S))

    # --------------------------------------------------------------------------
    # FunSAPE Library - C source files -----------------------------------------

    FUNSAPE_SOURCES_C		:= $(sort $(call rwildcard, $(FUNSAPE_PATH), *.c))
    FUNSAPE_SOURCES_C		:= $(sort $(call filter-out-any,_hide/,$(FUNSAPE_SOURCES_C)))
    FUNSAPE_SOURCES_C		:= $(sort $(call filter-out-any,doc/,$(FUNSAPE_SOURCES_C)))
    FUNSAPE_SOURCES_C		:= $(sort $(call filter-out-any,Release/,$(FUNSAPE_SOURCES_C)))
    FUNSAPE_SOURCES_C		:= $(sort $(call filter-out-any,temp/,$(FUNSAPE_SOURCES_C)))

    # --------------------------------------------------------------------------
    # FunSAPE Library - CPP source files ---------------------------------------

    FUNSAPE_SOURCES_CPP		:= $(sort $(call rwildcard, $(FUNSAPE_PATH), *.cpp))
    FUNSAPE_SOURCES_CPP		:= $(sort $(call filter-out-any,_hide/,$(FUNSAPE_SOURCES_CPP)))
    FUNSAPE_SOURCES_CPP		:= $(sort $(call filter-out-any,doc/,$(FUNSAPE_SOURCES_CPP)))
    FUNSAPE_SOURCES_CPP		:= $(sort $(call filter-out-any,Release/,$(FUNSAPE_SOURCES_CPP)))
    FUNSAPE_SOURCES_CPP		:= $(sort $(call filter-out-any,temp/,$(FUNSAPE_SOURCES_CPP)))

    # --------------------------------------------------------------------------
    # FunSAPE Library - CXX source files ---------------------------------------

    FUNSAPE_SOURCES_CXX		:= $(sort $(FUNSAPE_SOURCES_C) $(FUNSAPE_SOURCES_CPP))
endif

HEADERS_ASM				:= $(sort $(FUNSAPE_HEADERS_ASM) $(CODE_HEADERS_ASM))
HEADERS_H				:= $(sort $(FUNSAPE_HEADERS_H) $(CODE_HEADERS_H))
HEADERS_HPP				:= $(sort $(FUNSAPE_HEADERS_HPP) $(CODE_HEADERS_HPP))
HEADERS_HXX				:= $(sort $(FUNSAPE_HEADERS_HXX) $(CODE_HEADERS_HXX))
SOURCES_ASM				:= $(sort $(FUNSAPE_SOURCES_ASM) $(CODE_SOURCES_ASM))
SOURCES_S				:= $(sort $(FUNSAPE_SOURCES_S) $(CODE_SOURCES_S))
SOURCES_AXX				:= $(sort $(FUNSAPE_SOURCES_AXX) $(CODE_SOURCES_AXX))
SOURCES_C				:= $(sort $(FUNSAPE_SOURCES_C) $(CODE_SOURCES_C))
SOURCES_CPP				:= $(sort $(FUNSAPE_SOURCES_CPP) $(CODE_SOURCES_CPP))
SOURCES_CXX				:= $(sort $(FUNSAPE_SOURCES_CXX) $(CODE_SOURCES_CXX))

# ==============================================================================
# Create flags
# ==============================================================================

# ------------------------------------------------------------------------------
# Include flags ----------------------------------------------------------------

INCLUDES_ASM		:= $(addprefix -I, $(HEADERS_ASM))
INCLUDES_H			:= $(addprefix -I, $(HEADERS_H))
INCLUDES_HPP		:= $(addprefix -I, $(HEADERS_HPP))
INCLUDES_HXX		:= $(sort $(INCLUDES_HPP) $(INCLUDES_H))
INCLUDES_ALL		:= $(sort $(INCLUDES_ASM) $(INCLUDES_HXX))

ifneq ($(USER_DEFINES_ASM),)
    USER_DEFINES_ASM	:= $(addprefix -D,$(USER_DEFINES_ASM))
endif
DEFINES_ASM			:= $(sort $(USER_DEFINES_ASM))
# DEFINES_ASM			:= $(sort $(USER_DEFINES_ASM) -D$(MCU_DEVICE_MACRO))
ifneq ($(USER_DEFINES_C),)
    USER_DEFINES_C	:= $(addprefix -D,$(USER_DEFINES_C))
endif
DEFINES_C			:= $(sort $(USER_DEFINES_C) -D$(MCU_DEVICE_MACRO))
ifneq ($(USER_DEFINES_CPP),)
    USER_DEFINES_CPP	:= $(addprefix -D,$(USER_DEFINES_CPP))
endif
DEFINES_CPP			:= $(sort $(USER_DEFINES_CPP) -D$(MCU_DEVICE_MACRO))
DEFINES_CXX			:= $(sort $(DEFINES_C) $(DEFINES_CPP))

# ------------------------------------------------------------------------------
# MCU compiler flags -----------------------------------------------------------

ifeq ($(MCU_DEVICE_PLATFORM),AVR)
    FLAG_MCU				= -mmcu=$(MCU_DEVICE_NAME)
else ifeq ($(MCU_DEVICE_PLATFORM),STM32)
    FLAG_MCU				= -mcpu=$(MCU_DEVICE_CORE_ID) -mthumb $(MCU_DEVICE_CORE_FPU) $(MCU_DEVICE_CORE_FLOAT_ABI)
endif

# ------------------------------------------------------------------------------
# ASM compiler flags -----------------------------------------------------------

FLAGS_ASM					= $(FLAG_MCU)
# ifneq ($(COMPILER_STD),)
#     FLAGS_ASM				+= -std=$(COMPILER_STD)
# endif
FLAGS_ASM					+= $(COMPILER_OPT)
FLAGS_ASM					+= -Wall -fdata-sections -ffunction-sections
FLAGS_ASM					+= $(USER_FLAGS_ASM)
FLAGS_ASM					+= $(DEFINES_ASM)
FLAGS_ASM					+= $(INCLUDES_AXX)
# FLAGS_ASM					+= -fno-exceptions -fno-rtti

# ------------------------------------------------------------------------------
# C compiler flags -------------------------------------------------------------

FLAGS_C						= $(FLAG_MCU)
ifneq ($(COMPILER_STD_C),)
    FLAGS_C					+= -std=$(COMPILER_STD_C)
endif
FLAGS_C						+= $(COMPILER_OPT)
FLAGS_C						+= -Wall -fdata-sections -ffunction-sections -fno-exceptions
FLAGS_C						+= $(USER_FLAGS_C)
FLAGS_C						+= $(DEFINES_C)
FLAGS_C						+= $(INCLUDES_HXX)
ifeq ($(COMPILER_DEBUG),1)
    FLAGS_C					+= -g -gdwarf-2
endif
FLAGS_C						+= -MMD -MP -MF"$(@:%.o=%.d)"

# ------------------------------------------------------------------------------
# CPP compiler flags -----------------------------------------------------------

FLAGS_CPP					= $(FLAG_MCU)
ifneq ($(COMPILER_STD_CPP),)
    FLAGS_CPP				+= -std=$(COMPILER_STD_CPP)
endif
FLAGS_CPP					+= $(COMPILER_OPT)
FLAGS_CPP					+= -Wall -fdata-sections -ffunction-sections -fno-exceptions -fno-rtti
FLAGS_CPP					+= $(USER_FLAGS_CPP)
FLAGS_CPP					+= $(DEFINES_CPP)
FLAGS_CPP					+= $(INCLUDES_HXX)
ifeq ($(COMPILER_DEBUG),1)
    FLAGS_CPP				+= -g -gdwarf-2
endif
FLAGS_CPP					+= -MMD -MP -MF"$(@:%.o=%.d)"

# ------------------------------------------------------------------------------
# CXX compiler flags -----------------------------------------------------------

FLAGS_CXX					= $(FLAG_MCU)
ifneq ($(COMPILER_STD_CPP),)
    FLAGS_CXX				+= -std=$(COMPILER_STD_CPP)
endif
FLAGS_CXX					+= $(COMPILER_OPT)
FLAGS_CXX					+= -Wall -fdata-sections -ffunction-sections -fno-exceptions -fno-rtti
FLAGS_CXX					+= $(USER_FLAGS_CPP)
FLAGS_CXX					+= $(DEFINES_CXX)
FLAGS_CXX					+= $(INCLUDES_HXX)
ifeq ($(COMPILER_DEBUG),1)
    FLAGS_CXX				+= -g -gdwarf-2
endif
FLAGS_CXX					+= -MMD -MP -MF"$(@:%.o=%.d)"

# ------------------------------------------------------------------------------
# Linker flags -----------------------------------------------------------------

ifneq ($(USER_LIBS),)
    USER_LIBS					:= $(addprefix -l,$(USER_LIBS))
endif

FLAGS_LINKER					= $(FLAG_MCU)
ifneq ($(MCU_LINKER_FILE),)
    FLAGS_LINKER				+=-T$(MCU_LINKER_FILE)
endif
ifeq ($(MCU_DEVICE_PLATFORM),STM32)
    FLAGS_LINKER				+= -specs=nano.specs
endif
FLAGS_LINKER					+=$(LIBRARY_PATH)
ifeq ($(MCU_DEVICE_PLATFORM),STM32)
    FLAGS_LINKER				+= -lc -lm -lnosys
endif
FLAGS_LINKER					+= $(USER_LIBS)
FLAGS_LINKER					+= -Wl,--gc-sections -Wl,--strip-all -Wl,-Map=$(BUILD_DIR)/$(BUILD_NAME).map,--cref

# ##############################################################################
# TEST
# ##############################################################################

ifeq ($(COMPILE_C_AS_CPP),1)
    CC							:= $(CCPP)
    FLAGS_C						:= $(FLAGS_CPP)
endif

# ==============================================================================
# Build recipes
# ==============================================================================

.PHONY: assemble compile program cleanCompile cleanCompileProgram clean compileProgram compileCleanProgram cleanCompileCleanProgram cleanAssemble cleanAssembleProgram assembleProgram assembleCleanProgram cleanAssembleCleanProgram flashErase doNothing

# ------------------------------------------------------------------------------
# Assemble recipe
# ------------------------------------------------------------------------------

assemble: $(BUILD_DIR)
	avra -fI -m "$(BUILD_DIR)/application.map" -l "$(BUILD_DIR)/application.lss" -e "$(BUILD_DIR)/application.eep" -d "$(BUILD_DIR)/application.o" -o "$(BUILD_DIR)/application.hex" main.asm
#	mv -f main.eep.hex $(BUILD_DIR)/application.hex
#	mv -f main.cof $(BUILD_DIR)/application.cof
#	mv -f main.obj $(BUILD_DIR)/application.obj
#	mv -f main.hex $(BUILD_DIR)/application.hex
#	avrasm2 -fI -o "$(BUILD_DIR)/application.hex" -m "$(BUILD_DIR)/application.map" -l "$(BUILD_DIR)/application.lss" -e "$(BUILD_DIR)/application.eep" -S "$(BUILD_DIR)/application.tmp" -W+ie -d "$(BUILD_DIR)/application.o" main.asm

# ------------------------------------------------------------------------------
# Compile recipe
# ------------------------------------------------------------------------------

compile: $(BUILD_DIR)/$(BUILD_NAME).elf $(BUILD_DIR)/$(BUILD_NAME).hex $(BUILD_DIR)/$(BUILD_NAME).bin

# List of C objects
OBJECTS			+= $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES_C:.c=.o)))
vpath %.c $(sort $(dir $(SOURCES_C)))

# List of CPP objects
OBJECTS			+= $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES_CPP:.cpp=.o)))
vpath %.cpp $(sort $(dir $(SOURCES_CPP)))

# List of Assembly objects
OBJECTS			+= $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES_S:.s=.o)))
vpath %.s $(sort $(dir $(SOURCES_S)))

# List of Assembly objects
OBJECTS			+= $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES_ASM:.asm=.o)))
vpath %.asm $(sort $(dir $(SOURCES_ASM)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(FLAGS_C) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	$(CCPP) -c $(FLAGS_CPP) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(FLAGS_ASM) $< -o $@

$(BUILD_DIR)/%.o: %.asm Makefile | $(BUILD_DIR)
	$(AS) -c $(FLAGS_ASM) $< -o $@

$(BUILD_DIR)/$(BUILD_NAME).elf: $(OBJECTS) Makefile
	$(CCPP) $(OBJECTS) $(FLAGS_LINKER) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir build

# ------------------------------------------------------------------------------
# Clean recipe
# ------------------------------------------------------------------------------

clean:
	@echo
	@echo ================================================================================
	@echo Removing auxiliary files...
	@echo ================================================================================
	@echo
	@rm -r -f -v $(BUILD_DIR)/*.d
	@rm -r -f -v $(BUILD_DIR)/*.lst
	@rm -r -f -v $(BUILD_DIR)/*.o
	@rm -r -f -v $(BUILD_DIR)/*.lss
	@rm -r -f -v $(BUILD_DIR)/*.map
	@rm -r -f -v $(BUILD_DIR)/*.tmp
	@echo Auxiliary files removed!
	@echo
	@echo --------------------------------------------------------------------------------
	@echo End of clean process!
	@echo ================================================================================
	@echo

# ------------------------------------------------------------------------------
# Program recipe
# ------------------------------------------------------------------------------

program:
	@echo
	@echo ================================================================================
	@echo Loading program...
	@echo ================================================================================
	@echo
ifeq ($(MCU_DEVICE_PLATFORM),STM32)
    ifeq ($(PROGRAMMER_TYPE),ST_LINK_SWD)
		@echo Using STM32 - ST_LINK - SWD!
		ST-LINK_CLI -c SWD UR -P $(BUILD_DIR)/$(BUILD_NAME).hex -V -HardRst PULSE=2000 -Rst
    else ifeq ($(PROGRAMMER_TYPE),ST_LINK_JTAG)
		@echo Using STM32 - ST_LINK - JTAG!
		ST-LINK_CLI -c JTAG UR -P $(BUILD_DIR)/$(BUILD_NAME).hex -V -HardRst PULSE=2000 -Rst
    else ifeq ($(PROGRAMMER_TYPE),ST_FLASH)
		@echo Using STM32 - ST_FLASH - SWD!
		st-flash --reset --connect-under-reset --hot-plug --format ihex write $(BUILD_DIR)/$(BUILD_NAME).hex
    else ifeq ($(PROGRAMMER_TYPE),STM32_PROGRAMMER_SWD)
		@echo Using STM32 - STM32_PROGRAMMER - SWD!
		STM32_Programmer_CLI -c port=SWD mode=UR reset=HWrst -w $(BUILD_DIR)/$(BUILD_NAME).hex 0x08000000 -V -rst
    else ifeq ($(PROGRAMMER_TYPE),STM32_PROGRAMMER_JTAG)
		@echo Using STM32 - STM32_PROGRAMMER - JTAG!
		STM32_Programmer_CLI -c port=JTAG mode=UR reset=HWrst -w $(BUILD_DIR)/$(BUILD_NAME).hex 0x08000000 -V -rst
    else
		@echo Programmer not suitable for this device!
		exit 0
    endif
else ifeq ($(MCU_DEVICE_PLATFORM),AVR)
    ifeq ($(PROGRAMMER_TYPE),arduino)
		@echo Using AVR - ARDUINO - USART!
		avrdude -C $(PROGRAMMER_CONFIG_FILE) -v -p $(MCU_DEVICE_NAME) -c $(PROGRAMMER_TYPE) -P $(PROGRAMMER_PORT) -b$(PROGRAMMER_BAUDRATE) -D -Uflash:w:$(BUILD_DIR)/$(BUILD_NAME).hex:i
    else
		@echo Programmer not suitable for this device!
		exit 0
    endif
endif
	@echo
	@echo --------------------------------------------------------------------------------
	@echo Program loaded!
	@echo ================================================================================

# ------------------------------------------------------------------------------
# Fix Bootloader recipe
# ------------------------------------------------------------------------------

flashErase:
	@echo
	@echo ================================================================================
	@echo Fixing bootloader...
	@echo ================================================================================
	@echo
	@echo Hold Reset button until ST-LINK respond!
	@sleep 5s
ifeq ($(MCU_DEVICE_PLATFORM),STM32)
    ifeq ($(PROGRAMMER_TYPE),ST_LINK_SWD)
		ST-LINK_CLI -c SWD UR -ME
    else ifeq ($(PROGRAMMER_TYPE),ST_LINK_JTAG)
		ST-LINK_CLI -c JTAG UR -ME
    else ifeq ($(PROGRAMMER_TYPE),ST_FLASH)
		st-flash --reset --connect-under-reset --hot-plug erase
    else ifeq ($(PROGRAMMER_TYPE),STM32_PROGRAMMER_SWD)
		STM32_Programmer_CLI -c port=SWD mode=UR -e all
    else ifeq ($(PROGRAMMER_TYPE),STM32_PROGRAMMER_JTAG)
		STM32_Programmer_CLI -c port=JTAG mode=UR -e all
    else
		@echo Programmer not suitable for this device!
		exit 0
    endif
else ifeq ($(MCU_DEVICE_PLATFORM),AVR)
	@echo This feature was not implemented for AVR architecture.
endif
	@echo --------------------------------------------------------------------------------
	@echo Bootloader fixed!
	@echo ================================================================================
	@echo

# ------------------------------------------------------------------------------
# Compound recipes
# ------------------------------------------------------------------------------

cleanCompile:				clean compile

compileProgram:				compile program

cleanCompileProgram:		clean compile program

compileCleanProgram:		compile clean program

cleanCompileCleanProgram:	clean compile clean program

cleanAssemble:				clean assemble

cleanAssembleProgram:		clean assemble program

assembleProgram:			assemble program

assembleCleanProgram:		assemble clean program

cleanAssembleCleanProgram:	clean assemble clean program

# ------------------------------------------------------------------------------
# Information recipe
# ------------------------------------------------------------------------------
doNothing:
	@echo
	@echo ================================================================================
	@echo Dumping...
	@echo ================================================================================
	@echo
	@echo ------------------------------
	@echo Device information
	@echo ------------------------------
	@echo
	@echo MCU_DEVICE_PLATFORM		= $(MCU_DEVICE_PLATFORM)
	@echo MCU_DEVICE_CODE			= $(MCU_DEVICE_CODE)
	@echo MCU_DEVICE_NAME			= $(MCU_DEVICE_NAME)
	@echo MCU_DEVICE_LINE			= $(MCU_DEVICE_LINE)
	@echo MCU_DEVICE_MACRO			= $(MCU_DEVICE_MACRO)
	@echo MCU_DEVICE_FLASH			= $(MCU_DEVICE_FLASH)
	@echo MCU_DEVICE_CORE_ID		= $(MCU_DEVICE_CORE_ID)
	@echo MCU_DEVICE_CORE_FPU		= $(MCU_DEVICE_CORE_FPU)
	@echo MCU_DEVICE_CORE_FLOAT_ABI	= $(MCU_DEVICE_CORE_FLOAT_ABI)
	@echo MCU_LINKER_FILE			= $(MCU_LINKER_FILE)
	@echo
	@echo ------------------------------
	@echo System information
	@echo ------------------------------
	@echo
	@echo MY_SHELL		= $(MY_SHELL)
	@echo SHELL			= $(SHELL)
	@echo SPACE			= $(SPACE)
	@echo USED_ARC		= $(USED_ARC)
	@echo USED_OS		= $(USED_OS)
	@echo USED_SHELL	= $(USED_SHELL)
	@echo
	@echo ------------------------------
	@echo Toolchain data
	@echo ------------------------------
	@echo
	@echo COMPILER_PREFIX			= $(COMPILER_PREFIX)
	@echo COMPILER_PATH				= $(COMPILER_PATH)
	@echo AR						= $(AR)
	@echo AS						= $(AS)
	@echo BIN						= $(BIN)
	@echo CC						= $(CC)
	@echo CCPP						= $(CCPP)
	@echo CP						= $(CP)
	@echo HEX						= $(HEX)
	@echo SZ						= $(SZ)
	@echo PROGRAMMER_TYPE			= $(PROGRAMMER_TYPE)
	@echo PROGRAMMER_CONFIG_FILE	= $(PROGRAMMER_CONFIG_FILE)
	@echo PROGRAMMER_PORT			= $(PROGRAMMER_PORT)
	@echo PROGRAMMER_BAUDRATE		= $(PROGRAMMER_BAUDRATE)
	@echo
	@echo ------------------------------
	@echo Toolchain version
	@echo ------------------------------
	@echo
	@$(CC) --version
	@echo
	@echo ------------------------------
	@echo User defined parameters
	@echo ------------------------------
	@echo
	@echo BUILD_NAME		= $(BUILD_NAME)
	@echo BUILD_DIR			= $(BUILD_DIR)
	@echo COMPILE_C_AS_CPP	= $(COMPILE_C_AS_CPP)
	@echo COMPILER_DEBUG	= $(COMPILER_DEBUG)
	@echo COMPILER_OPT		= $(COMPILER_OPT)
	@echo COMPILER_STD_C	= $(COMPILER_STD_C)
	@echo COMPILER_STD_CPP	= $(COMPILER_STD_CPP)
	@echo USER_DEFINES_ASM	= $(USER_DEFINES_ASM)
	@echo USER_DEFINES_C	= $(USER_DEFINES_C)
	@echo USER_DEFINES_CPP	= $(USER_DEFINES_CPP)
	@echo USER_FLAGS_ASM	= $(USER_FLAGS_ASM)
	@echo USER_FLAGS_C		= $(USER_FLAGS_C)
	@echo USER_FLAGS_CPP	= $(USER_FLAGS_CPP)
	@echo USER_LIBS			= $(USER_LIBS)
	@echo
	@echo ------------------------------
	@echo Compilation parameters
	@echo ------------------------------
	@echo
	@echo FLAGS_ASM		= $(FLAGS_ASM)
	@echo FLAGS_C		= $(FLAGS_C)
	@echo FLAGS_CPP		= $(FLAGS_CPP)
	@echo FLAGS_CXX		= $(FLAGS_CXX)
	@echo FLAGS_LINKER	= $(FLAGS_LINKER)
	@echo SOURCES_ASM	= $(SOURCES_ASM)
	@echo SOURCES_AXX	= $(SOURCES_AXX)
	@echo SOURCES_S		= $(SOURCES_S)
	@echo SOURCES_C		= $(SOURCES_C)
	@echo SOURCES_CPP	= $(SOURCES_CPP)
	@echo SOURCES_CXX	= $(SOURCES_CXX)
	@echo OBJECTS		= $(OBJECTS)
	@echo
	@echo ------------------------------
	@echo Library parameters
	@echo ------------------------------
	@echo
	@echo LIBRARY_PATH			= $(LIBRARY_PATH)
	@echo FUNSAPE_PATH			= $(FUNSAPE_PATH)
	@echo FUNSAPE_HEADERS_ASM	= $(FUNSAPE_HEADERS_ASM)
	@echo FUNSAPE_HEADERS_H		= $(FUNSAPE_HEADERS_H)
	@echo FUNSAPE_HEADERS_HPP	= $(FUNSAPE_HEADERS_HPP)
	@echo FUNSAPE_HEADERS_HXX	= $(FUNSAPE_HEADERS_HXX)
	@echo FUNSAPE_HEADERS_ALL	= $(FUNSAPE_HEADERS_ALL)
	@echo FUNSAPE_SOURCES_ASM	= $(FUNSAPE_SOURCES_ASM)
	@echo FUNSAPE_SOURCES_S		= $(FUNSAPE_SOURCES_S)
	@echo FUNSAPE_SOURCES_AXX	= $(FUNSAPE_SOURCES_AXX)
	@echo FUNSAPE_SOURCES_C		= $(FUNSAPE_SOURCES_C)
	@echo FUNSAPE_SOURCES_CPP	= $(FUNSAPE_SOURCES_CPP)
	@echo FUNSAPE_SOURCES_CXX	= $(FUNSAPE_SOURCES_CXX)
	@echo
	@echo ------------------------------
	@echo File listing
	@echo ------------------------------
	@echo
	@echo CODE_HEADERS_ALL	= $(CODE_HEADERS_ALL)
	@echo CODE_HEADERS_ASM	= $(CODE_HEADERS_ASM)
	@echo CODE_HEADERS_H	= $(CODE_HEADERS_H)
	@echo CODE_HEADERS_HPP	= $(CODE_HEADERS_HPP)
	@echo CODE_HEADERS_HXX	= $(CODE_HEADERS_HXX)
	@echo CODE_SOURCES_ASM	= $(CODE_SOURCES_ASM)
	@echo CODE_SOURCES_S	= $(CODE_SOURCES_S)
	@echo CODE_SOURCES_AXX	= $(CODE_SOURCES_AXX)
	@echo CODE_SOURCES_C	= $(CODE_SOURCES_C)
	@echo CODE_SOURCES_CPP	= $(CODE_SOURCES_CPP)
	@echo CODE_SOURCES_CXX	= $(CODE_SOURCES_CXX)
	@echo
	@echo ------------------------------
	@echo Auxiliary
	@echo ------------------------------
	@echo
	@echo DEFINES_ASM			= $(DEFINES_ASM)
	@echo DEFINES_C				= $(DEFINES_C)
	@echo DEFINES_CPP			= $(DEFINES_CPP)
	@echo DEFINES_CXX			= $(DEFINES_CXX)
	@echo FLAG_MCU				= $(FLAG_MCU)
	@echo HEADERS_ASM			= $(HEADERS_ASM)
	@echo HEADERS_H				= $(HEADERS_H)
	@echo HEADERS_HPP			= $(HEADERS_HPP)
	@echo HEADERS_HXX			= $(HEADERS_HXX)
	@echo INCLUDES_ALL			= $(INCLUDES_ALL)
	@echo INCLUDES_ASM			= $(INCLUDES_ASM)
	@echo INCLUDES_H			= $(INCLUDES_H)
	@echo INCLUDES_HPP			= $(INCLUDES_HPP)
	@echo INCLUDES_HXX			= $(INCLUDES_HXX)
	@echo MCU_AVR_CODE_OFFSET	= $(MCU_AVR_CODE_OFFSET)
	@echo MCU_STM32_CODE_OFFSET	= $(MCU_STM32_CODE_OFFSET)
	@echo
	@echo --------------------------------------------------------------------------------
	@echo end of dump process!
	@echo ================================================================================
