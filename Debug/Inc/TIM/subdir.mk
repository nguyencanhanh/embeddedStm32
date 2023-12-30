################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/TIM/PWM.c \
../Inc/TIM/TIM_Configure.c 

OBJS += \
./Inc/TIM/PWM.o \
./Inc/TIM/TIM_Configure.o 

C_DEPS += \
./Inc/TIM/PWM.d \
./Inc/TIM/TIM_Configure.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/TIM/%.o Inc/TIM/%.su Inc/TIM/%.cyclo: ../Inc/TIM/%.c Inc/TIM/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F103xB -c -I../Inc -I../Inc/DHT -I../Inc/RTOS -I../Inc/TIM -I../Inc/ADC -I../Inc/LCD -I../Inc/DMA -I../Inc/RTOS -I../Inc/GPIO -I../Inc/I2C -I../Inc/UART -I../Inc/RCC -I../Drivers/CMSIS -I../Drivers/Devices -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-TIM

clean-Inc-2f-TIM:
	-$(RM) ./Inc/TIM/PWM.cyclo ./Inc/TIM/PWM.d ./Inc/TIM/PWM.o ./Inc/TIM/PWM.su ./Inc/TIM/TIM_Configure.cyclo ./Inc/TIM/TIM_Configure.d ./Inc/TIM/TIM_Configure.o ./Inc/TIM/TIM_Configure.su

.PHONY: clean-Inc-2f-TIM

