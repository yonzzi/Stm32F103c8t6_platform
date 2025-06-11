################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../custom_driver/Src/adc.c \
../custom_driver/Src/capture.c \
../custom_driver/Src/clock.c \
../custom_driver/Src/delay.c \
../custom_driver/Src/led.c \
../custom_driver/Src/low_power.c \
../custom_driver/Src/pwm.c 

OBJS += \
./custom_driver/Src/adc.o \
./custom_driver/Src/capture.o \
./custom_driver/Src/clock.o \
./custom_driver/Src/delay.o \
./custom_driver/Src/led.o \
./custom_driver/Src/low_power.o \
./custom_driver/Src/pwm.o 

C_DEPS += \
./custom_driver/Src/adc.d \
./custom_driver/Src/capture.d \
./custom_driver/Src/clock.d \
./custom_driver/Src/delay.d \
./custom_driver/Src/led.d \
./custom_driver/Src/low_power.d \
./custom_driver/Src/pwm.d 


# Each subdirectory must supply rules for building sources it contributes
custom_driver/Src/%.o custom_driver/Src/%.su: ../custom_driver/Src/%.c custom_driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/hoatt/STM32CubeIDE/workspace_1.9.0/Timer/Timer_systick/custom_driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-custom_driver-2f-Src

clean-custom_driver-2f-Src:
	-$(RM) ./custom_driver/Src/adc.d ./custom_driver/Src/adc.o ./custom_driver/Src/adc.su ./custom_driver/Src/capture.d ./custom_driver/Src/capture.o ./custom_driver/Src/capture.su ./custom_driver/Src/clock.d ./custom_driver/Src/clock.o ./custom_driver/Src/clock.su ./custom_driver/Src/delay.d ./custom_driver/Src/delay.o ./custom_driver/Src/delay.su ./custom_driver/Src/led.d ./custom_driver/Src/led.o ./custom_driver/Src/led.su ./custom_driver/Src/low_power.d ./custom_driver/Src/low_power.o ./custom_driver/Src/low_power.su ./custom_driver/Src/pwm.d ./custom_driver/Src/pwm.o ./custom_driver/Src/pwm.su

.PHONY: clean-custom_driver-2f-Src

