#include "low_power.h"
#include "clock.h"
#include <stdint.h>

// into stop mode
void goto_low_power_mode()
{
    uint32_t *SCR = (uint32_t*) 0xE000ED10; // system control in core arm
    *SCR |= (1<<2); // enable SLEEPDEEP mode - turn of system clock ( high speed clock)
    __asm("WFI"); // using assembly instruction to enter sleep mode/ stop mode
    
}