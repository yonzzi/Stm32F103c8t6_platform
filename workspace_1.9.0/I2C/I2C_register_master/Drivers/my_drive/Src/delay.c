/*
 * delay.c
 *
 *  Created on: Apr 10, 2024
 *      Author: Anh Tuan Phung
 */
#include "delay.h"
#include "clock.h"



#define TIMER1 1
#define SYS_TICK 2
#define DELAY_SRC TIMER1
#if DELAY_SRC != TIMER1 && DELAY_SRC != SYS_TICK
#error DELAY_SRC must be SYS_TICK or TIMER1
#endif

uint32_t tim1_cnt = 0;
#if 0
void SysTick_Handler(){
	tim1_cnt ++;
}
#endif

void Timer_init(My_TIM_Typedef *TIM_x){

#if 1
	// set 1 ,sec for timer
	// rcc --> 16Mhz --> pcs (16) --> 1000000hz
	// ARR = 1000
	clock_enable_APB2(TIM1EN);
	clock_enable_APB1(TIM2EN);
	clock_enable_APB1(TIM3EN);
	clock_enable_APB1(TIM4EN);
	TIM_x->ARR = 1000;
	TIM_x->PSC = 36 - 1;

    TIM_x->CR1 &= ~(1 << 4);
	TIM_x->CR1 |= (1 << 0);// enable cnt

	TIM_x->EGR |= (1 << 0);
	 // Update interrupt flag
	//while(!(TIM_x->SR & (1 << 0)));

//    *TIMx_DIER |= (1<<0); // enable interrupt
//
//	uint32_t *NVIC_ISER0 = (uint32_t *)(0xe000e100);
//	*NVIC_ISER0 |= (1 << 25); //position 25
#endif
#if 0
	uint32_t *TIM1_CSR = (uint32_t *)(0xE000E010);
	uint32_t *TIM1_RVR = (uint32_t *)(0xE000E014);
	*TIM1_RVR |= 16000;
	*TIM1_CSR |= (1<<0) | (1<<1);
#endif
}
int G_count_timer =  0 ;
void hoang_timer_init(){
	clock_enable_APB2(TIM1EN);
	uint32_t* timer_psc =(uint32_t*)0x40012c28 ;
	uint32_t* timer_arr =(uint32_t*)0x40012c2c ;
	uint32_t* timer_cr1 =(uint32_t*)0x40012c00 ;
	//uint32_t* timer_dier =(uint32_t*)0x40012c0c ;
	uint32_t* timer_cnt =(uint32_t*)0x40012c24 ;
	*timer_cnt = 0 ;
	*timer_psc = 72 - 1 ;

	*timer_arr = 1000;
	*timer_cr1 |= 1<<0 ;

//	*timer_dier |= 1<< 0 ;
//	uint32_t *isr0 = (uint32_t*)0xe000e100;
//	*isr0 |= 1 << 25 ;
}
void TIM1_UP_IRQHandler(){
	uint32_t* timer_sr =(uint32_t*)0x40012c10 ;
	*timer_sr &=~(1<< 0);
	G_count_timer ++ ;
}
void hoang_timer_delay(uint32_t ms){
	int current = G_count_timer ;
	while((G_count_timer - current) < ms ){
	}
}

void my_delay_ms(My_TIM_Typedef *TIM_x, uint32_t ms){
	uint32_t i = 0;
	while(i < ms ){
		if(((TIM_x->SR >> 0 )&1) == 1){
		TIM_x->SR &=~(1<< 0);
		i++;
		}
	}
}
//void delay_hoang_td_ms(int ms){
//	int current = G_count_timer ;
//	while((G_count_timer - current) < ms ){
//			}
//}
//	uint32_t* timer_cnt =(uint32_t*)0x40012c24 ;
//	if(*timer_cnt >= 1000 ){
//		*timer_cnt = 0 ;
//		G_count++;
//	}
//	int current = G_count_timer ;
//		while((G_count_timer - current) < ms ){
//		}
