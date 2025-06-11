/*
 * led.c
 *
 *  Created on: Jun 19, 2024
 *      Author: hoatt
 */

//#include "main.h"
#include "clock.h"
#include "led.h"
#include"stdint.h"
void led_init()
{
	//before using any peripheral -> have to give clock for work
	//__HAL_RCC_GPIOB_CLK_ENABLE(); //hal : tÃªn hÃ£ng, RCC: bá»™ táº¡o clock
	clock_enable_APB2(GPIOBEN);
	//initial to set PB2 in output push-pull
	uint32_t* GPIOB_CRH = (uint32_t*)(GPIOB_BASE_ADD + 0x00);// add base + add offset
	*GPIOB_CRH |=(0b01<<8); //set PB2 in output config ( Mode[1,0] >00-> output; =00-> input) // <<22 lÃ  vá»‹ trÃ­ nha, do mÃ¬nh Ä‘á»ƒ cÃ³ 0bxx nÃªn nÃ³ Ä‘ang khÃ´ng lÃ  32 bit, pháº£i dá»‹ch nÃ³ Ä‘á»ƒ Ä‘Ãºng vá»‹ trÃ­
	*GPIOB_CRH &=~(0b11<<10); // set PB2  in push-pull mode (00)

}
void led_control(char led_state)
{
	//set led in PB2 light
	// add of output data register
	uint32_t* GPIOB_ODR = (uint32_t*)(GPIOB_BASE_ADD + 0x0C);
	if( led_state==1)
	*GPIOB_ODR |= 1<<2;
	else
    *GPIOB_ODR &= ~(1<<2);
}
