/*
 * delay.h
 *
 *  Created on: Apr 10, 2024
 *      Author: Admin
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_
#include <stdint.h>

#define TIM1_BASE            (0x40012c00)
#define TIM2_BASE            (0x40000000)
#define TIM3_BASE            (0x40000400)
#define TIM4_BASE            (0x40000800)

typedef struct{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMCR;
	uint32_t DIER;
	uint32_t SR;
	uint32_t EGR;
	uint32_t CCMR1_Output;
	//uint32_t CCMR1_Input;
	uint32_t CCMR2_Output;
	//uint32_t CCMR2_Input;
	uint32_t CCER;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t ARR;
	uint32_t CCR1;
	uint32_t CCR2;
	uint32_t CCR3;
	uint32_t CCR4;
	uint32_t DCR;
	uint32_t DMAR;
}My_TIM_Typedef;

#define TIM1  ((My_TIM_Typedef *)TIM1_BASE)
#define TIM2  ((My_TIM_Typedef *)TIM2_BASE)
#define TIM3  ((My_TIM_Typedef *)TIM3_BASE)
#define TIM4  ((My_TIM_Typedef *)TIM4_BASE)

void Timer_init(My_TIM_Typedef *TIMx);
void my_delay_ms(My_TIM_Typedef *TIM_x, uint32_t ms);
void hoang_timer_init();
void hoang_timer_delay(uint32_t ms);
void delay_hoang_td(uint32_t ms );
#endif /* INC_DELAY_H_ */
