################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/I2C/I2C_Configure.c 

OBJS += \
./Inc/I2C/I2C_Configure.o 

C_DEPS += \
./Inc/I2C/I2C_Configure.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/I2C/%.o Inc/I2C/%.su Inc/I2C/%.cyclo: ../Inc/I2C/%.c Inc/I2C/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F103xB -c -I../Inc -I../Inc/RTOS -I../Inc/TIM -I../Inc/ADC -I../Inc/LCD -I../Inc/DMA -I../Inc/RTOS -I../Inc/GPIO -I../Inc/I2C -I../Inc/UART -I../Inc/RCC -I../Drivers/CMSIS -I../Drivers/Devices -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-I2C

clean-Inc-2f-I2C:
	-$(RM) ./Inc/I2C/I2C_Configure.cyclo ./Inc/I2C/I2C_Configure.d ./Inc/I2C/I2C_Configure.o ./Inc/I2C/I2C_Configure.su

.PHONY: clean-Inc-2f-I2C

