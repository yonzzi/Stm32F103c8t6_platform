################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/My_drive/Src/I2c.c \
../Drivers/My_drive/Src/clock.c \
../Drivers/My_drive/Src/delay.c \
../Drivers/My_drive/Src/gpio.c 

OBJS += \
./Drivers/My_drive/Src/I2c.o \
./Drivers/My_drive/Src/clock.o \
./Drivers/My_drive/Src/delay.o \
./Drivers/My_drive/Src/gpio.o 

C_DEPS += \
./Drivers/My_drive/Src/I2c.d \
./Drivers/My_drive/Src/clock.d \
./Drivers/My_drive/Src/delay.d \
./Drivers/My_drive/Src/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/My_drive/Src/%.o Drivers/My_drive/Src/%.su Drivers/My_drive/Src/%.cyclo: ../Drivers/My_drive/Src/%.c Drivers/My_drive/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/STM/I2C_register_slave/Drivers/My_drive/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-My_drive-2f-Src

clean-Drivers-2f-My_drive-2f-Src:
	-$(RM) ./Drivers/My_drive/Src/I2c.cyclo ./Drivers/My_drive/Src/I2c.d ./Drivers/My_drive/Src/I2c.o ./Drivers/My_drive/Src/I2c.su ./Drivers/My_drive/Src/clock.cyclo ./Drivers/My_drive/Src/clock.d ./Drivers/My_drive/Src/clock.o ./Drivers/My_drive/Src/clock.su ./Drivers/My_drive/Src/delay.cyclo ./Drivers/My_drive/Src/delay.d ./Drivers/My_drive/Src/delay.o ./Drivers/My_drive/Src/delay.su ./Drivers/My_drive/Src/gpio.cyclo ./Drivers/My_drive/Src/gpio.d ./Drivers/My_drive/Src/gpio.o ./Drivers/My_drive/Src/gpio.su

.PHONY: clean-Drivers-2f-My_drive-2f-Src

