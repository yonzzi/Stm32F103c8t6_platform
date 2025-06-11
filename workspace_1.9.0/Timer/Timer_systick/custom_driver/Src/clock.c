/*
 * clock.c
 *
 *  Created on: Jul 13, 2024
 *      Author: hoatt
 */

/*
 * @brief setup RCC to generate clock 72Mhz ( max)
 * @param None
 * @retval None
 */
#include <stdint.h>
#include <clock.h>
// #include "main.h"
void clock_init()
{
   /*
    * use PLL clock ( source HSE= 8Mhz ) , không chia ( not devided) , PLLMUL= x9 -> clock= 72Mhz ( max)
    */
	uint32_t *RCC_CR = (uint32_t *)0x40021000; // control reg
	uint32_t *RCC_CFGR = (uint32_t *)0x40021004; //config reg
	uint32_t *FLASH_ACR = (uint32_t *)0x40022000; //config latency

	*RCC_CR |= 1<< 16; //enable HSE
	while ( ((*RCC_CR >> 17) & 1 ) ==0); // wait for HSE oscillator is stable ( HSE ready)


	*RCC_CFGR &= ~(1<<17); //set HSE devided = 1
	*RCC_CFGR |= 0x0111<< 18;//set HSE multiplication = 9 (x9)
	*RCC_CFGR |= 1<<16;//set HSE as PLL input clock

	*RCC_CR |= 1<< 24; //enable PLL
	while ( ((*RCC_CR >> 25) & 1 ) == 0); //wait PLL ready

	/*
	 * AHB <= 72Mhz
	 * APB1 <= 36Mhz //
	 * APB2 <= 72Mhz
	 */

	//as APB1 have lower pre => /2
	*RCC_CFGR |= 0x100<<8; //APB low-speed prescaler (APB1 /2)

	*FLASH_ACR &= ~(0b111<<0); //clear bit
	*FLASH_ACR |=0x010<<0; //Two wait states, if 48 MHz < SYSCLK ≤ 72 MHz

	*RCC_CFGR |= 0x10<<0;// PLL selected as system clock

}

void clock_enable_APB1(APB1_peripheral_t peripheral)
{
	uint32_t *RCC_APB1ENR = (uint32_t *)0x4002101c; // APB1 peripheral clock enable register
	*RCC_APB1ENR |= 1 << peripheral;
}

void clock_enable_APB2(APB2_peripheral_t peripheral)
{
	uint32_t *RCC_APB2ENR = (uint32_t *)0x40021018; // APB1 peripheral clock enable register
	*RCC_APB2ENR |= 1 << peripheral;
}

void clock_enable_AHB(AHB_peripheral_t peripheral)
{
	uint32_t *RCC_AHBENR = (uint32_t *)0x40021014; // APB1 peripheral clock enable register
	*RCC_AHBENR |= 1 << peripheral;
}
