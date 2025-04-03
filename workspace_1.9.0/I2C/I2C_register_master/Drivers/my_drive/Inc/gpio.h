/*
 * gpio.h
 *
 *  Created on: May 18, 2024
 *      Author: Admin
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "stdint.h"

#define APB2PERIPH_BASE            (0x40010000U)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x00000800UL)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x00000C00UL)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x00001000UL)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x00001400UL)

typedef enum{
	PIN_0 = 0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
	PIN_8,
	PIN_9,
	PIN_10,
	PIN_11,
	PIN_12,
	PIN_13,
	PIN_14,
	PIN_15
}My_PIN_Typedef;

typedef enum{
	RESET =0,
	SET
}My_GPIO_State_Typedef;

typedef struct{
	uint32_t CRL;
	uint32_t CRH;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t BRR;
	uint32_t CLKR;
}My_GPIO_Typedef;

typedef enum
{
	INPUT_ANALOG,
	INPUT_FLOATING,
	INPUT_PULL_UP,
	INPUT_PULL_DOWN,

	OUTPUT_PUSH_PULL,
	OUTPUT_OPEN_DRAIN,
	AF_PUSH_PULL,
	AF_OPEN_DRAIN
}My_GPIO_Mode_Typedef;

void Cus_Config_GPIO(My_GPIO_Typedef *GPIOx, My_PIN_Typedef PIN_x, My_GPIO_Mode_Typedef mode);


void Cus_Write_GPIO_Pin(My_GPIO_Typedef *GPIOx, My_PIN_Typedef PIN_x, My_GPIO_State_Typedef state);
uint32_t Cus_Read_GPIO_Pin(My_GPIO_Typedef *GPIOx, My_PIN_Typedef PIN_x);
void Cus_Toggle_GPIO_Pin(My_GPIO_Typedef *GPIOx, My_PIN_Typedef PIN_x );

#define GPIOA  ((My_GPIO_Typedef *)GPIOA_BASE)
#define GPIOB  ((My_GPIO_Typedef *)GPIOB_BASE)
#define GPIOC  ((My_GPIO_Typedef *)GPIOC_BASE)
#define GPIOD  ((My_GPIO_Typedef *)GPIOD_BASE)

#endif /* INC_GPIO_H_ */
