# ##############################################################################
# MCU Makefile essentials - ARM STM32 device detection
# ##############################################################################

# ##############################################################################
# Process device name
# ##############################################################################

# Checking if device was not found yet
ifeq ($(MCU_DEVICE_CODE), 0)
    # Extracting device platform
    MCU_DEVICE_PLATFORM := $(shell echo $(MCU_DEVICE_NAME) | cut -c 1-5)
    # Checking if platform is correct
    ifeq ($(MCU_DEVICE_PLATFORM),STM32)
        MCU_DEVICE_CODE := 1

        # Extract device data
        AUX_VAR := $(shell echo $(MCU_DEVICE_NAME) | cut -c 1-7)
        MCU_DEVICE_LINE := $(shell echo $(MCU_DEVICE_NAME) | cut -c 1-9)
        MCU_DEVICE_FLASH := $(shell echo $(MCU_DEVICE_NAME) | cut -c 11-11)

        # Get device core
        ifeq ($(AUX_VAR),STM32F0)
            MCU_DEVICE_CORE_ID := cortex-m0
        else ifeq ($(AUX_VAR),STM32F1)
            MCU_DEVICE_CORE_ID := cortex-m3
        else ifeq ($(AUX_VAR),STM32F2)
            MCU_DEVICE_CORE_ID := cortex-m3
        else ifeq ($(AUX_VAR),STM32F3)
            MCU_DEVICE_CORE_ID := cortex-m4
        else ifeq ($(AUX_VAR),STM32F4)
            MCU_DEVICE_CORE_ID := cortex-m4
        else ifeq ($(AUX_VAR),STM32F7)
            MCU_DEVICE_CORE_ID := cortex-m7
        else ifeq ($(AUX_VAR),STM32G0)
            MCU_DEVICE_CORE_ID := cortex-m0plus
        else ifeq ($(AUX_VAR),STM32G4)
            MCU_DEVICE_CORE_ID := cortex-m4
        else ifeq ($(AUX_VAR),STM32H7)
            AUX_VAR := $(call substr,$(MCU_DEVICE_NAME),1,9)
            ifeq ($(AUX_VAR),STM32H742)
                MCU_DEVICE_CORE_ID := cortex-m7
            else ifeq ($(AUX_VAR),STM32H743)
                MCU_DEVICE_CORE_ID := cortex-m7
            else ifeq ($(AUX_VAR),STM32H750)
                MCU_DEVICE_CORE_ID := cortex-m7
            else ifeq ($(AUX_VAR),STM32H753)
                MCU_DEVICE_CORE_ID := cortex-m7
            else ifeq ($(AUX_VAR),STM32H745)
                MCU_DEVICE_CORE_ID := cortex-m7+m4
            else ifeq ($(AUX_VAR),STM32H747)
                MCU_DEVICE_CORE_ID := cortex-m7+m4
            else ifeq ($(AUX_VAR),STM32H755)
                MCU_DEVICE_CORE_ID := cortex-m7+m4
            else ifeq ($(AUX_VAR),STM32H757)
                MCU_DEVICE_CORE_ID := cortex-m7+m4
            else
                MCU_DEVICE_CODE := 0
            endif
        else ifeq ($(AUX_VAR),STM32L0)
            MCU_DEVICE_CORE_ID := cortex-m0plus
        else ifeq ($(AUX_VAR),STM32L1)
            MCU_DEVICE_CORE_ID := cortex-m3
        else ifeq ($(AUX_VAR),STM32L4)
            MCU_DEVICE_CORE_ID := cortex-m4
        else ifeq ($(AUX_VAR),STM32L5)
            MCU_DEVICE_CORE_ID := cortex-m33
        else ifeq ($(AUX_VAR),STM32MP)
            AUX_VAR := $(call substr,$(MCU_DEVICE_NAME),1,8)
            MCU_DEVICE_LINE := $(call substr,$(MCU_DEVICE_NAME),1,10)
            MCU_DEVICE_FLASH := $(call substr,$(MCU_DEVICE_NAME),12,12)
            ifeq ($(AUX_VAR),STM32MP1)
                MCU_DEVICE_CORE_ID := cortex-m7
            else
                MCU_DEVICE_CODE := 0
            endif
        else ifeq ($(AUX_VAR),STM32U5)
            MCU_DEVICE_CORE_ID := cortex-m33
        else ifeq ($(AUX_VAR),STM32WB)
            MCU_DEVICE_CORE_ID := cortex-m4
        else ifeq ($(AUX_VAR),STM32WL)
            MCU_DEVICE_CORE_ID := cortex-m0plus
        else
            MCU_DEVICE_CODE := 0
        endif
    else
        MCU_DEVICE_CODE := 0
    endif

    # Get linker file name and mcu macros
    ifeq ($(MCU_DEVICE_CODE), 1)
        MCU_LINKER_FILE		:= $(MCU_DEVICE_NAME)_FLASH.ld
        MCU_DEVICE_MACRO	:= $(MCU_DEVICE_LINE)x$(MCU_DEVICE_FLASH)
        # MAJOR HACK>>>>
        # I REALLY DONT KNOW WHY STM32F103x8 MACRO DOES NOT EXISTS
        # MAJOR HACK>>>>
        ifeq ($(MCU_DEVICE_MACRO),STM32F103x8)
            MCU_DEVICE_MACRO := STM32F103xB
        endif
    endif
endif
