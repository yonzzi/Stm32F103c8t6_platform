
#include "stdint.h"


typedef enum{
	TIM2EN,
	TIM3EN,
	TIM4EN,
	TIM5EN,
	TIM6EN,
	TIM7EN,
	TIM12EN,
	TIM13EN,
	TIM14EN,
	WWDGRST = 11,
	SPI2RST = 14,
	SPI3RST = 15,
	USART2RST = 17,
	USART3RST,
	USART4RST,
	USART5RST,
	I2C1RST = 21,
	I2C2RST = 22,
	USBRST,
	CANRST =25,
	BKPRST = 27,
	PWRRST,
	DACRST
}APB1_peripheral_t;

typedef enum{
	AFIOEN,
	GPIOAEN = 2,
	GPIOBEN,
	GPIOCEN,
	GPIODEN,
	GPIOEEN,
	GPIOFEN,
	GPIOGEN,
	ADC1EN,
	ADC2EN,
	TIM1EN = 11,
	TIM8EN = 13,
}APB2_peripheral_t;

typedef enum{
	DMA1EN,
	DMA2EN,
	CRCEN = 6,
}AHB_peripheral_t;

void clock_enable_AHB(AHB_peripheral_t peripheral);
void clock_enable_APB1(APB1_peripheral_t peripheral);
void clock_enable_APB2(APB2_peripheral_t peripheral);
void clock_init();

