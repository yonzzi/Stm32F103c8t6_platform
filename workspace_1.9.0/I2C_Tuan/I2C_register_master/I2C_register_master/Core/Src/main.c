#include "clock.h"
#include "I2c.h"
#include "delay.h"
#include"RTC_DS3231.h"

extern DS3231_Struct ds3231;

int main(void)
{
	clock_init();
	Timer_init(TIM1);
	I2C_Master_Init(I2C2);
	//DMA1_I2c_Init(I2C2, buffer,  7);
	uint8_t buffer[7];
	//DS3231_setTime(55, 15, 2, 2, 14, 2, 20);
  while (1)
  {
	 // DS3231_getTime();
	  MPU_Write(I2C2, 0x68, 0x55, 1);
	  my_delay_ms(TIM1,100);
  }
}

