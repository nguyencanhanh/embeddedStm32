################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/LCD/LiquidCrystal_I2C.c 

OBJS += \
./Inc/LCD/LiquidCrystal_I2C.o 

C_DEPS += \
./Inc/LCD/LiquidCrystal_I2C.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/LCD/%.o Inc/LCD/%.su Inc/LCD/%.cyclo: ../Inc/LCD/%.c Inc/LCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F103xB -c -I../Inc -I../Inc/DHT -I../Inc/RTOS -I../Inc/TIM -I../Inc/ADC -I../Inc/LCD -I../Inc/DMA -I../Inc/RTOS -I../Inc/GPIO -I../Inc/I2C -I../Inc/UART -I../Inc/RCC -I../Drivers/CMSIS -I../Drivers/Devices -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-LCD

clean-Inc-2f-LCD:
	-$(RM) ./Inc/LCD/LiquidCrystal_I2C.cyclo ./Inc/LCD/LiquidCrystal_I2C.d ./Inc/LCD/LiquidCrystal_I2C.o ./Inc/LCD/LiquidCrystal_I2C.su

.PHONY: clean-Inc-2f-LCD

