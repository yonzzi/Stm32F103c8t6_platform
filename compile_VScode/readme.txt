Sử dụng cmd trong chính VsCode để chạy lệnh

- Build và link source bằng gcc:
+ build: main.c
arm-none-eabi-gcc -c main.c -mcpu=cortex-m3 -std=gnu11 -Icustom_driver\Inc -o build/main.o
arm-none-eabi-gcc -c custom_driver\Src\led.c -mcpu=cortex-m3 -std=gnu11 -Icustom_driver\Inc -o build/led.o

gt: compile - file name -chọn target build cho dòng - tiêu chuẩn code - output: thư mục build
flag to add header file in gcc: using -I

+ build startup file :
arm-none-eabi-gcc -c -x assembler-with-cpp startup_stm32f103c8tx.s -mcpu=cortex-m3 -std=gnu11 -o build\startup.o

gt: -x lựa chọn language sd in this file 

+ link các file:
arm-none-eabi-gcc build\*.o -mcpu=cortex-m3 -T"STM32F103C8TX_FLASH.ld" -Wl,-Map="file.map" -Wl,--gc-sections -static -o build\blink_led.elf

gt: -T"file_name" -Wl link theo sự hướng dẫn của file_name , -map để tạo ra file.map ở ngoài

+ lấy các file .h ra từ file elf ( sd tool trong gcc):
  lệnh suggest( lệnh này sẽ tương ứng giải thích cmline bên dưới): 
  arm-none-eabi-objcopy [option(s)] in-file [out-file]
arm-none-eabi-objcopy -O ihex build\blink_led.elf build\blink_led.hex
arm-none-eabi-objcopy -O binary build\blink_led.elf build\blink_led.bin


- Sử dụng stm32 utinity để nạp code qua CLI ( command Line Interface):
  Syntax: -c [ID=<id>/SN=<sn>] [JTAG/SWD SWCLK=<f>] [UR/HOTPLUG] [LPM]
                     [RM=Hrst/Srst/Crst]
   [RM=Hrst/Srst/Crst] : Reset Mode = hardware reset\ software reset\ core reset
   Note: nạp xong ấn nút reset để chạy

ST-LINK_CLI -c SWD -P build\blink_led.hex

Không cần ấn reset:
ST-LINK_CLI -c SWD -P build\blink_led.hex -V -Run


- Sử dụng make để build và link và flash file:
câu lệnh:
make Clean -để xóa thư mục
make All  - để build và link các bước ở trên
make Flash - để nạp code
