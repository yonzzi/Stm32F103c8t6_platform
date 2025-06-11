################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/My_driver/Src/clock.c \
../Drivers/My_driver/Src/delay.c \
../Drivers/My_driver/Src/led.c \
../Drivers/My_driver/Src/uart.c 

OBJS += \
./Drivers/My_driver/Src/clock.o \
./Drivers/My_driver/Src/delay.o \
./Drivers/My_driver/Src/led.o \
./Drivers/My_driver/Src/uart.o 

C_DEPS += \
./Drivers/My_driver/Src/clock.d \
./Drivers/My_driver/Src/delay.d \
./Drivers/My_driver/Src/led.d \
./Drivers/My_driver/Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/My_driver/Src/%.o Drivers/My_driver/Src/%.su: ../Drivers/My_driver/Src/%.c Drivers/My_driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"C:/Users/hoatt/STM32CubeIDE/workspace_1.9.0/freeRTOS/Drivers/My_driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-My_driver-2f-Src

clean-Drivers-2f-My_driver-2f-Src:
	-$(RM) ./Drivers/My_driver/Src/clock.d ./Drivers/My_driver/Src/clock.o ./Drivers/My_driver/Src/clock.su ./Drivers/My_driver/Src/delay.d ./Drivers/My_driver/Src/delay.o ./Drivers/My_driver/Src/delay.su ./Drivers/My_driver/Src/led.d ./Drivers/My_driver/Src/led.o ./Drivers/My_driver/Src/led.su ./Drivers/My_driver/Src/uart.d ./Drivers/My_driver/Src/uart.o ./Drivers/My_driver/Src/uart.su

.PHONY: clean-Drivers-2f-My_driver-2f-Src

