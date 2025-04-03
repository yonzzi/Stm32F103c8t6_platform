
#include "clock.h"
#include <stdint.h>
// start address of RCC pheriperal

/*
 * @brief set up RCC to generate a clock 72Mhz (max)
 * @parameter none
 * @return value None
 */

void clock_init(){
	/*
		   * Use PLL clock(source from HSE), bộ chia bằng 1 và bộ nhân là 9
		   */
		   /*
		   * AHB <= 72 Mhz
		   * APB1 <= 36 Mhz
		   * APB2 <= 72 Mhz
		   */
		  uint32_t *RCC_CR = (uint32_t*)(0x40021000);
		  uint32_t *RCC_CFGR = (uint32_t*)(0x40021004);
		  uint32_t *FLASH_ACR =(uint32_t*)(0x40022000);
		  *RCC_CR |= (1 << 16);
		  // External high-speed clock ready flag
		  while(!(*RCC_CR & (1 << 17)));
		  //  Prefetch buffer enable
		  *FLASH_ACR |= (1 << 4);
		  // Two wait states, if 48 MHz < SYSCLK ≤ 72 MHz
		  *FLASH_ACR |= (0b001 << 0);
		  //  : HSE divider for PLL entry
		  *RCC_CFGR &= ~(1 << 17); // HSE clock not divided
		  // : PLL entry clock source
		  *RCC_CFGR |= (1 << 16); // HSE oscillator clock selected as PLL input clock
		  // PLL multiplication factor
		  *RCC_CFGR |= (0b0111 << 18); // PLL input clock x 3
		  //  PLL enable
		  *RCC_CR |= (1 << 24);
		  //  PLL clock ready flag
		  while(!(*RCC_CR & (1 << 25)));
		  // System clock switch
		  *RCC_CFGR |= (0b10 << 0); //   PLL selected as system clock
		  while(!(*RCC_CFGR & (0b10 << 2)));
		  //*RCC_CFGR |= 0x00000000U;
		  // APB high-speed prescaler (APB2)
		  *RCC_CFGR |= (0b000 << 11);  //// HCLK not divided HCLK not divided = 72M
		  // APB high-speed prescaler (APB1)
		  *RCC_CFGR |= (0b100 << 8);  //HCLK divided by 2 = 36M
}

void clock_enable_AHB(AHB_peripheral_t peripheral){
	uint32_t *RCC_AHBENR = (uint32_t *)(0x40021014);
	*RCC_AHBENR |= (1 << peripheral);
}
void clock_enable_APB1(APB1_peripheral_t peripheral){
	uint32_t *RCC_APB1ENR = (uint32_t *)(0x4002101c);
	*RCC_APB1ENR |= (1 << peripheral);
}
void clock_enable_APB2(APB2_peripheral_t peripheral){
	uint32_t *RCC_APB2ENR = (uint32_t *)(0x40021018);
	*RCC_APB2ENR |= (1 << peripheral);
}
