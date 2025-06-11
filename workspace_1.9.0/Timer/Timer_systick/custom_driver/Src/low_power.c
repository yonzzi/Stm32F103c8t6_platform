/*
 * low_power.c
 *
 *  Created on: Jul 20, 2024
 *      Author: hoatt
 */
#include "low_power.h"
#include "clock.h"
#include <stdint.h>


void goto_low_power_mode()
{
    uint32_t *SCR = (uint32_t*) 0xE000ED10; // system control in core arm
    *SCR |= (1<<2); // enable SLEEPDEEP mode - turn off system clock ( high speed clock)
    __asm("WFI"); // using this assembly instruction to enter sleep mode/ stop mode

}

//exit low_power mode
//enable independent watchdog
void enable_iwdg()
{
	//set watchdog in 4sec to wake up MCU
	uint32_t *IWDG_RLR = (uint32_t*) 0x40003008; // reload reg
	uint32_t *IWDG_PR = (uint32_t*) 0x40003004; // pre reg
	uint32_t *IWDG_KR = (uint32_t*) 0x40003000; // key reg

	//need to unlock the protected of reload and prescaler reg
	*IWDG_KR = 0x5555;
	*IWDG_RLR =2500; // count to 4sec
	*IWDG_PR |=0x100<<0; //pre=64
	*IWDG_KR = 0xCCCC; //start watchdog

}

void feed_iwdg()
{
	uint32_t *IWDG_KR = (uint32_t*) 0x40003000; // key reg
	*IWDG_KR = 0xAAAA; // reload/update watchdog

}

