/*
 * RTC_DS3231.c
 *
 *  Created on: May 24, 2024
 *      Author: ThanhDat
 *
 */


 /* ============================ Information of The DS3231 =============================================
  *
  *
  *      The DS3231 is a extremely accurate I2C real-time clock (RTC)
  *      https://www.analog.com/media/en/technical-documentation/data-sheets/DS3231.pdf
  *
  *
  *=====================================================================================================
  */

#include "RTC_DS3231.h"
#include "I2c.h"


DS3231_Struct ds3231;


/*  DEC to Bin */
static uint8_t D_to_B (uint8_t num)
{
	return ((num/16 *10) + (num%16));
}

/* Bin to DEC */
//static uint8_t B_to_D (uint8_t num)
//{
//	return ((num/10 * 16) + (num%10));
//}

void DS3231_setTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year){
	uint8_t buffer[8];
	buffer[0] = 0x00;
	buffer[1] = (sec / 10) << 4 | ( sec % 10);
	buffer[2] = (min / 10) << 4 | ( min % 10);
	buffer[3] = (hour / 10) << 4 | ( hour % 10);
	buffer[4] = D_to_B(day);
	buffer[5] = (date / 10) << 4 | ( date % 10);
	buffer[6] = (month / 10) << 4 | ( month % 10);
	buffer[7] = (year / 10) << 4 | ( year % 10);

	MPU_Write (I2C2, DS3231_ADD, buffer, 8);
	//_Chuc_I2C_Write (I2C1, 0x68 << 1, buffer, 8);
}

/*
 * \brief: This function get real time and contain value into DS3231_Struct ds3231
 * 		   If you want to get time, you have to " extern DS3231_Struct ds3231; " to  main.c
 *
 */
void DS3231_getTime(){
	uint8_t buffer[7];

	MPU_Write (I2C2, DS3231_ADD, 0x00, 1);
	MPU_Read (I2C2, DS3231_ADD, buffer, 7);

	/* read time*/
	//ds3231.sec   = B_to_D(buffer[0]);
	ds3231.sec   = ((buffer[0] >> 4) & 0x07) * 10 + (buffer[0] & 0x0f);
	ds3231.min   = ((buffer[1] >> 4) & 0x07) * 10 + (buffer[1] & 0x0f);
	ds3231.hour  = ((buffer[2] >> 4) & 0x03) * 10 + (buffer[2] & 0x0f);
	ds3231.day   =   buffer[3] & 0x07;
	ds3231.date  = ((buffer[4] >> 4) & 0x03) * 10 + (buffer[4] & 0x0f);
	ds3231.month = ((buffer[5] >> 4) & 0x01) * 10 + (buffer[5] & 0x0f);
	ds3231.year  = ((buffer[6] >> 4) & 0x03) * 10 + (buffer[6] & 0x0f);
}
