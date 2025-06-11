/*
 * delay.c
 *
 *  Created on: Jun 19, 2024
 *      Author: hoatt
 */
//#include "main.h"
#include "clock.h"
#include "delay.h"
#include"stdint.h"
#define SYSTICK 1
#define TIMER1 2
#define DELAY_SRC TIMER1
#if DELAY_SRC != SYSTICK && DELAY_SRC != TIMER1
#error not build
#endif
void timer1_init()
{
#if DELAY_SRC == TIMER1
	// set 1 sec for timer
	// rcc -> 8M hz -> 1 sec --> psc =8000 -> 1000hz
	// ARR = 1000

    //__HAL_RCC_TIM1_CLK_ENABLE();
	clock_enable_APB2(TIM1EN);
    uint16_t *TIMER1_ARR = (uint16_t*)0x40012c2c;
    uint16_t *TIMER1_PSC = (uint16_t*)0x40012c28;
    uint16_t *TIMER1_CR1 = (uint16_t*)0x40012c00;
    uint16_t *TIMER1_DIER = (uint16_t*)0x40012c0c;

    *TIMER1_ARR = 1000;
    *TIMER1_PSC = 8 - 1;// as first psc value = 1 -> avoid devide 0

    *TIMER1_CR1 |= 1<<0; // enable cnt
    *TIMER1_DIER |=1<<0; // enable update interrupt ( when count 1ms)
    //*TIMER1_CCR1 |= 1<<0; // enable cnt

    uint32_t *NVIC_ISER0 = (uint32_t*)0xe000e100;
    *NVIC_ISER0 |= 1<<25; // enable timer1 update interrupt in NVIC
#else
    //setup delay using systick
    uint32_t *SYST_CSR = (uint32_t*)0xE000E010; // systick control and status reg
    uint32_t *SYST_RVR = (uint32_t*)0xE000E014; // systick reload value reg

    *SYST_RVR= 8000;
    *SYST_CSR |= (1<<0)|(1<<1)|(1<<2); // enable systick and enable tick interrupt and use clock external from core arm.

    // see vector table to get systick position
    // but systick lie position < 0 -> mean it is enable by default --> do not need turn on it by NVIC_ISER0


#endif

}
uint32_t timer1_cnt =0;
#if DELAY_SRC == TIMER1
void TIM1_UP_IRQHandler()
{
	uint16_t *TIMER1_SR = (uint16_t*)0x40012c10;
	*TIMER1_SR &= ~(1<<0); //clear update interrupt flag
	// khi nhảy vào hàm thì cần clear interrupt flag để reset.
	timer1_cnt++;
}
#else
void SysTick_Handler()
{
	timer1_cnt++;
}
#endif

#if 0
void timer1_delay_1s()
{
	uint16_t *TIMER1_SR = (uint16_t*)0x40012c10;
     while(((*TIMER1_SR>>0) & 1) ==0 ); // wait update interrupt flag is set to 1
    *TIMER1_SR &= ~(1<<0); //clear update interrupt flag

}
#else
void timer1_delay(uint32_t msec)
{
    uint32_t current_cnt = timer1_cnt;
    while((uint32_t)(timer1_cnt- current_cnt) < msec);
}
#endif
