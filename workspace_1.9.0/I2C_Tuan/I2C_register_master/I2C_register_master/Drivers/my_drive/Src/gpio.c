/*
 * gpio.c
 *
 *  Created on: May 18, 2024
 *      Author: Anh Tuan Phung
 */
#include "gpio.h"
#include "clock.h"

void Cus_Config_GPIO(My_GPIO_Typedef *GPIOx, My_PIN_Typedef PIN_x, My_GPIO_Mode_Typedef mode){
	if((GPIOx == GPIOA)){clock_enable_APB2(GPIOAEN);}
	else if((GPIOx == GPIOB)) {clock_enable_APB2(GPIOBEN);}
	else if((GPIOx == GPIOC)) {clock_enable_APB2(GPIOCEN);}
	else if((GPIOx == GPIOD)) {clock_enable_APB2(GPIODEN);}
	volatile uint32_t *config_register;
	uint8_t set_pin_x = 0;
	config_register = (PIN_x <= PIN_7) ? &GPIOx->CRL : &GPIOx->CRH;
	set_pin_x = (PIN_x <= PIN_7) ? (PIN_x *4) : ((PIN_x - 8)*4);
	if(PIN_x <= PIN_7){
		GPIOx->CRL &= ~(0b1111 << set_pin_x);
	}
	else if(PIN_x <= PIN_15){
		GPIOx->CRH &= ~(0b1111 << set_pin_x);
	}
	switch(mode){
	case OUTPUT_PUSH_PULL :
		(*config_register)  |=  (0b0001U << set_pin_x );  //General purpose output push-pull
		break;
	case OUTPUT_OPEN_DRAIN :
		(*config_register)  |=  (0b0101U << set_pin_x );  // General purpose output Open-drain
		break;
	case AF_PUSH_PULL :
		(*config_register)  |=  (0b1001U << set_pin_x );  // Alternate function output Push-pull
		break;
	case AF_OPEN_DRAIN:
		(*config_register)  |=  (0b1110U << set_pin_x );  // Alternate function output Open-drain
		break;
	case INPUT_ANALOG :
		(*config_register)  |=  (0b0000U << set_pin_x );  //InPut Analog mode
		break;
	case INPUT_FLOATING :
		(*config_register)  |=  (0b0100U << set_pin_x );  // Floating input
		break;
	case INPUT_PULL_UP :
		(*config_register)  |=  (0b1000U << set_pin_x );  //  Input with pull-up
		(GPIOx->ODR)  |= (1<< PIN_x);
		break;
	case INPUT_PULL_DOWN:
		(*config_register)  |=  (0b1100U << set_pin_x );  // Input with pull-up / pull-down
		(GPIOx->ODR)  &= ~(1<< PIN_x);
		break;
	default: break;
	}
}
void Cus_Write_GPIO_Pin(My_GPIO_Typedef *GPIOx, My_PIN_Typedef PIN_x, My_GPIO_State_Typedef state){

	if(state == 1 ){
		GPIOx->ODR |= (1 << PIN_x);
	}
	else GPIOx->ODR &= ~(1 << PIN_x);
}
uint32_t Cus_Read_GPIO_Pin(My_GPIO_Typedef *GPIOx, My_PIN_Typedef PIN_x){
	uint32_t read_state;
	  if (((GPIOx->IDR >> PIN_x) & 1) == 1)
	  {
		  read_state = 1;
	  }
	  else
	  {
		  read_state = 0;
	  }
	  return read_state;
}


void Cus_Toggle_GPIO_Pin(My_GPIO_Typedef *GPIOx, My_PIN_Typedef PIN_x ){
	GPIOx->ODR ^= (1 << PIN_x);
}
