################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/GPIO/GPIO_Configure.c 

OBJS += \
./Inc/GPIO/GPIO_Configure.o 

C_DEPS += \
./Inc/GPIO/GPIO_Configure.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/GPIO/%.o Inc/GPIO/%.su Inc/GPIO/%.cyclo: ../Inc/GPIO/%.c Inc/GPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F103xB -c -I../Inc -I../Inc/RTOS -I../Inc/TIM -I../Inc/ADC -I../Inc/LCD -I../Inc/DMA -I../Inc/RTOS -I../Inc/GPIO -I../Inc/I2C -I../Inc/UART -I../Inc/RCC -I../Drivers/CMSIS -I../Drivers/Devices -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-GPIO

clean-Inc-2f-GPIO:
	-$(RM) ./Inc/GPIO/GPIO_Configure.cyclo ./Inc/GPIO/GPIO_Configure.d ./Inc/GPIO/GPIO_Configure.o ./Inc/GPIO/GPIO_Configure.su

.PHONY: clean-Inc-2f-GPIO

