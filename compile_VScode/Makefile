FREE_DIR= FreeRTOS-LTS/FreeRTOS/FreeRTOS-Kernel/
HEADER = -mthumb -mcpu=cortex-m3 -std=gnu11 -Icustom_driver/Inc -I$(FREE_DIR)include -I. -I$(FREE_DIR)portable/GCC/ARM_CM3/
All:
	arm-none-eabi-gcc -c $(FREE_DIR)croutine.c $(HEADER) -o build/croutine.o
	arm-none-eabi-gcc -c $(FREE_DIR)event_groups.c $(HEADER) -o build/event_groups.o
	arm-none-eabi-gcc -c $(FREE_DIR)list.c $(HEADER) -o build/list.o
	arm-none-eabi-gcc -c $(FREE_DIR)queue.c $(HEADER) -o build/queue.o
	arm-none-eabi-gcc -c $(FREE_DIR)tasks.c $(HEADER) -o build/tasks.o
	arm-none-eabi-gcc -c $(FREE_DIR)timers.c $(HEADER) -o build/timers.o
	arm-none-eabi-gcc -c $(FREE_DIR)stream_buffer.c $(HEADER) -o build/stream_buffer.o
	arm-none-eabi-gcc -c $(FREE_DIR)portable/GCC/ARM_CM3/port.c $(HEADER) -o build/port.o
	arm-none-eabi-gcc -c $(FREE_DIR)portable/MemMang/heap_3.c $(HEADER) -o build/heap_3.o
	arm-none-eabi-gcc -c main.c $(HEADER) -o build/main.o
	arm-none-eabi-gcc -c custom_driver/Src/led.c $(HEADER) -o build/led.o
	arm-none-eabi-gcc -c custom_driver/Src/clock.c $(HEADER) -o build/clock.o
	arm-none-eabi-gcc -c custom_driver/Src/delay.c $(HEADER) -o build/delay.o
	arm-none-eabi-gcc -c custom_driver/Src/pwm.c $(HEADER) -o build/pwm.o
	arm-none-eabi-gcc -c custom_driver/Src/capture.c $(HEADER) -o build/capture.o
	arm-none-eabi-gcc -c custom_driver/Src/adc.c $(HEADER) -o build/adc.o
	arm-none-eabi-gcc -c -x assembler-with-cpp startup_stm32f103c8tx.s -mcpu=cortex-m3 -std=gnu11 -o build/startup.o
	arm-none-eabi-gcc build/*.o $(HEADER) -T"STM32F103C8TX_FLASH.ld" -Wl,-Map="file.map" -Wl,--gc-sections -static -o build/blink_led.elf
Run:	
	arm-none-eabi-objcopy -O ihex build/blink_led.elf build/blink_led.hex
	arm-none-eabi-objcopy -O binary build/blink_led.elf build/blink_led.bin
Clean:
	rm build/*
Flash:
	ST-LINK_CLI -c SWD -P build/blink_led.hex -V -Run
