OUT_PATH = bin
OUT_FILE = $(OUT_PATH)/out

OUT_FILE_HEX = $(OUT_FILE).hex
OUT_FILE_ELF = $(OUT_FILE).elf
OUT_FILE_BIN = $(OUT_FILE).bin

HAL_DRIVER_PATH = \
C:/Users/Mike/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.4

SOURCE_PATH = src

C_SOURCES = \
$(SOURCE_PATH)/system/system.c \
$(SOURCE_PATH)/system/system_stm32f1xx.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_usart.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2c.c \
$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_can.c \

CPP_SOURCES =  \
$(SOURCE_PATH)/system/stm32f1xx_hal_msp.cpp \
$(SOURCE_PATH)/system/interrupts.cpp \
$(SOURCE_PATH)/main.cpp

C_INCLUDES =  \
-I$(SOURCE_PATH) \
-I$(SOURCE_PATH)/system \
-I$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Inc \
-I$(HAL_DRIVER_PATH)/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy \
-I$(HAL_DRIVER_PATH)/Drivers/CMSIS/Device/ST/STM32F1xx/Include \
-I$(HAL_DRIVER_PATH)/Drivers/CMSIS/Include \

ASM_SOURCES =  \
$(HAL_DRIVER_PATH)/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xb.s

COMPILER = arm-none-eabi-c++.exe

CPU = -mcpu=cortex-m3
MCU = $(CPU) -mthumb


SIZE = arm-none-eabi-size

LDSCRIPT = STM32F103RBTX_FLASH.ld

LIBS = -lc -lm 

C_DEFS =  \
-DSTM32F103xB

OPTIMALIZATION = -Og

COMPILE_FLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) -T$(LDSCRIPT) $(OPTIMALIZATION) $(LIBS) \
-g -Wall -fdata-sections -ffunction-sections --specs=nosys.specs -Wl,-Map=$(OUT_FILE).map,--cref \
-fno-threadsafe-statics -fno-common -fno-exceptions -fno-rtti -fno-builtin -fno-use-cxa-atexit \
-std=gnu++14 -ggdb3

all: build size

build: mkdir_out
	${COMPILER} ${CPP_SOURCES} ${C_SOURCES} ${ASM_SOURCES} $(COMPILE_FLAGS) -o $(OUT_FILE_ELF)

clean:
	rd /s /q "$(OUT_PATH)"

size:
	${SIZE} $(OUT_FILE_ELF)

mkdir_out:
	if not exist "$(OUT_PATH)" mkdir "$(OUT_PATH)"