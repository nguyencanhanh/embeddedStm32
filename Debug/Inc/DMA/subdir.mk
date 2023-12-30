################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/DMA/DMA_Configure.c 

OBJS += \
./Inc/DMA/DMA_Configure.o 

C_DEPS += \
./Inc/DMA/DMA_Configure.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/DMA/%.o Inc/DMA/%.su Inc/DMA/%.cyclo: ../Inc/DMA/%.c Inc/DMA/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F103xB -c -I../Inc -I../Inc/DHT -I../Inc/RTOS -I../Inc/TIM -I../Inc/ADC -I../Inc/LCD -I../Inc/DMA -I../Inc/RTOS -I../Inc/GPIO -I../Inc/I2C -I../Inc/UART -I../Inc/RCC -I../Drivers/CMSIS -I../Drivers/Devices -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-DMA

clean-Inc-2f-DMA:
	-$(RM) ./Inc/DMA/DMA_Configure.cyclo ./Inc/DMA/DMA_Configure.d ./Inc/DMA/DMA_Configure.o ./Inc/DMA/DMA_Configure.su

.PHONY: clean-Inc-2f-DMA

