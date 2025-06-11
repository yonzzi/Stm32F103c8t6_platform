/*
 * RTC_DS3231.h
 *
 *  Created on: May 24, 2024
 *      Author: ThanhDat
 */

#ifndef INC_RTC_DS3231_H_
#define INC_RTC_DS3231_H_

#include "stdint.h"
#define DS3231_ADD 			(0x68U)

typedef struct{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint32_t year;
}DS3231_Struct;

void DS3231_setTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year);
void DS3231_getTime();

#endif /* INC_RTC_DS3231_H_ */
