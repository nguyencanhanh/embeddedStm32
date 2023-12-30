################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/Src/ACD_Cofigure.c \
../Inc/Src/DMA_Configure.c \
../Inc/Src/GPIO_Configure.c \
../Inc/Src/I2C_Configure.c \
../Inc/Src/LiquidCrystal_I2C.c \
../Inc/Src/PWM.c \
../Inc/Src/STM32F103.c \
../Inc/Src/TIM_Configure.c \
../Inc/Src/UART_Configure.c \
../Inc/Src/dht.c \
../Inc/Src/queue.c 

OBJS += \
./Inc/Src/ACD_Cofigure.o \
./Inc/Src/DMA_Configure.o \
./Inc/Src/GPIO_Configure.o \
./Inc/Src/I2C_Configure.o \
./Inc/Src/LiquidCrystal_I2C.o \
./Inc/Src/PWM.o \
./Inc/Src/STM32F103.o \
./Inc/Src/TIM_Configure.o \
./Inc/Src/UART_Configure.o \
./Inc/Src/dht.o \
./Inc/Src/queue.o 

C_DEPS += \
./Inc/Src/ACD_Cofigure.d \
./Inc/Src/DMA_Configure.d \
./Inc/Src/GPIO_Configure.d \
./Inc/Src/I2C_Configure.d \
./Inc/Src/LiquidCrystal_I2C.d \
./Inc/Src/PWM.d \
./Inc/Src/STM32F103.d \
./Inc/Src/TIM_Configure.d \
./Inc/Src/UART_Configure.d \
./Inc/Src/dht.d \
./Inc/Src/queue.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/Src/%.o Inc/Src/%.su Inc/Src/%.cyclo: ../Inc/Src/%.c Inc/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F103xB -c -I../Inc/Lib -I../Drivers/CMSIS -I../Drivers/Devices -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-Src

clean-Inc-2f-Src:
	-$(RM) ./Inc/Src/ACD_Cofigure.cyclo ./Inc/Src/ACD_Cofigure.d ./Inc/Src/ACD_Cofigure.o ./Inc/Src/ACD_Cofigure.su ./Inc/Src/DMA_Configure.cyclo ./Inc/Src/DMA_Configure.d ./Inc/Src/DMA_Configure.o ./Inc/Src/DMA_Configure.su ./Inc/Src/GPIO_Configure.cyclo ./Inc/Src/GPIO_Configure.d ./Inc/Src/GPIO_Configure.o ./Inc/Src/GPIO_Configure.su ./Inc/Src/I2C_Configure.cyclo ./Inc/Src/I2C_Configure.d ./Inc/Src/I2C_Configure.o ./Inc/Src/I2C_Configure.su ./Inc/Src/LiquidCrystal_I2C.cyclo ./Inc/Src/LiquidCrystal_I2C.d ./Inc/Src/LiquidCrystal_I2C.o ./Inc/Src/LiquidCrystal_I2C.su ./Inc/Src/PWM.cyclo ./Inc/Src/PWM.d ./Inc/Src/PWM.o ./Inc/Src/PWM.su ./Inc/Src/STM32F103.cyclo ./Inc/Src/STM32F103.d ./Inc/Src/STM32F103.o ./Inc/Src/STM32F103.su ./Inc/Src/TIM_Configure.cyclo ./Inc/Src/TIM_Configure.d ./Inc/Src/TIM_Configure.o ./Inc/Src/TIM_Configure.su ./Inc/Src/UART_Configure.cyclo ./Inc/Src/UART_Configure.d ./Inc/Src/UART_Configure.o ./Inc/Src/UART_Configure.su ./Inc/Src/dht.cyclo ./Inc/Src/dht.d ./Inc/Src/dht.o ./Inc/Src/dht.su ./Inc/Src/queue.cyclo ./Inc/Src/queue.d ./Inc/Src/queue.o ./Inc/Src/queue.su

.PHONY: clean-Inc-2f-Src

