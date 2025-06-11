/*
 * led.h
 *
 *  Created on: Jun 19, 2024
 *      Author: hoatt
 */

#ifndef INC_LED_H_
#define INC_LED_H_
#include"stdint.h"
#define GPIOB_BASE_ADD 0x40010C00
void led_init();
void led_control(char led_state);
#endif /* INC_LED_H_ */
