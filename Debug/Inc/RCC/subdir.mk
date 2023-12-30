################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/RCC/STM32F103.c 

OBJS += \
./Inc/RCC/STM32F103.o 

C_DEPS += \
./Inc/RCC/STM32F103.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/RCC/%.o Inc/RCC/%.su Inc/RCC/%.cyclo: ../Inc/RCC/%.c Inc/RCC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F103xB -c -I../Inc -I../Inc/DHT -I../Inc/RTOS -I../Inc/TIM -I../Inc/ADC -I../Inc/LCD -I../Inc/DMA -I../Inc/RTOS -I../Inc/GPIO -I../Inc/I2C -I../Inc/UART -I../Inc/RCC -I../Drivers/CMSIS -I../Drivers/Devices -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-RCC

clean-Inc-2f-RCC:
	-$(RM) ./Inc/RCC/STM32F103.cyclo ./Inc/RCC/STM32F103.d ./Inc/RCC/STM32F103.o ./Inc/RCC/STM32F103.su

.PHONY: clean-Inc-2f-RCC

