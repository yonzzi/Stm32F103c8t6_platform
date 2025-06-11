/*
 * capture.c
 *
 *  Created on: Jul 8, 2024
 *      Author: hoatt
 */
#include "main.h"
#include "capture.h"
#include"stdint.h"

#if 0
void capture_init(){
	//config for PA10 as TIM1 CH3
	__HAL_RCC_GPIOA_CLK_ENABLE();
	uint32_t *GPIOA_CRH = (uint32_t *)(0x40010804);
	*GPIOA_CRH &= ~(0b1111 << 8);
	*GPIOA_CRH |= (0b0100 << 8);

	__HAL_RCC_TIM1_CLK_ENABLE();
	uint16_t *TIM1_CR1 = (uint16_t *)(0x40012c00);
	uint16_t *TIM1_ARR = (uint16_t *)(0x40012c2c);
	uint16_t *TIM1_PSC = (uint16_t *)(0x40012c28);
	*TIM1_ARR = 0xffff;
	*TIM1_PSC = 800 - 1;
	/*timer1 channel 3 capture input*/
	uint16_t *TIM1_CCMR2_Input = (uint16_t *)(0x40012c1c);
	*TIM1_CCMR2_Input |= (0b01<<0); // set channel 3 input capture mode

	uint16_t *CCER = (uint16_t *)(0x40012c20);
	*CCER |= (1 << 8);
	*CCER &= ~(1 << 9); // set rising as trigger to capture

	uint16_t *TIM1_SMCR = (uint16_t *)(0x40012c08);
	*TIM1_SMCR |= (0b100 << 0) | (0b010 << 4); // reset cnt when rising
	*TIM1_SMCR |= (1<<14);

	*TIM1_CR1 |= (1 << 0);// enable cnt
}
uint16_t capture_read(){
	uint16_t *TIM1_CCR3 = (uint16_t *)(0x40012c3c);
	return *TIM1_CCR3;
}
#else
void capture_init()
{
	 //config for PA6 as TIM3 CH1
	    __HAL_RCC_GPIOA_CLK_ENABLE();
	    uint32_t *GPIOA_CRL = (uint32_t *)(0x40010800);
	    *GPIOA_CRL &= ~(0b1111 << 24);
	    *GPIOA_CRL |= (0b1011 << 24); // alternate function input float

//	    uint32_t* AFIO_MAPR = (uint32_t*)(0x40010000 + 0x04);
//		*AFIO_MAPR &=~(0x11<<6);
//		*AFIO_MAPR =(0x01<<6);		//map as time3 channel 1 for PA11

	    __HAL_RCC_TIM3_CLK_ENABLE();
	    uint16_t *TIM3_PSC = (uint16_t *)(0x40000428); // pre scaler
	    uint16_t *TIM3_CR1 = (uint16_t *)(0x40000400);// timerx control
	    uint16_t *TIM3_ARR = (uint16_t *)(0x4000042c); // set count
	    uint16_t *TIM3_SMCR = (uint16_t *)(0x40000408); // set slave value
	    uint16_t *TIM3_CCMR1_Input = (uint16_t *)(0x40000418); //capture/compare mode input
	    uint16_t *TIM3_CCER = (uint16_t *)(0x40000420); // enable compare or capture

	    *TIM3_ARR = 0xFFFF; //max count = max
	    *TIM3_PSC = 800-1; //set timer basic with cycle

	    //select Channel 1 work at capture
	    *TIM3_CCMR1_Input |= (0b01<<0); // set channel 1 in capture input mode

	    *TIM3_CCER &= ~(1<<1); //set rising as trigger to capture
	    *TIM3_CCER |=1<<0;//enable CH1( compare/capture)

	    //calculate pulse width
	    *TIM3_CCMR1_Input |= (0b10<<8); // set channel 2 in capture input mode ( map TI1)
	    *TIM3_CCER |= (1<<5); //set falling for CH2 as trigger to capture
		*TIM3_CCER |=1<<4;//enable CH2 in capture mode

	    *TIM3_SMCR |= (0b100 << 0) | (0b101 << 4); //reset cnt when rising
	    //enable counter
	    *TIM3_CR1 |=1<<0;
}
uint16_t capture_read_frequence()
{
	// read CCRx register
	uint16_t* TIM3_CCR1 = (uint16_t*)(0x40000434);
	return *TIM3_CCR1;
}

uint16_t capture_read_pulse_width()
{
	// read CCRx register
	uint16_t* TIM3_CCR2 = (uint16_t*)(0x40000438);
	return *TIM3_CCR2;
}
#endif

