/*
 * I2c.c
 *
 *  Created on: May 17, 2024
 *      Author: Admin
 */
#include "i2c.h"
#include "clock.h"
#include "stdint.h"
#include "gpio.h"

void I2C_Slave_Init(MY_I2C_Type *I2Cx) {
	// set clock for I2C and GPIOB
		if(I2Cx == I2C1){
			// set clock for I2C and GPIOB
			clock_enable_APB1(I2C1RST);
			clock_enable_APB2(AFIOEN);

			// configuration SDA(PB11) and SCL(PB10)
			Cus_Config_GPIO(GPIOB, PIN_6, AF_OPEN_DRAIN);
			Cus_Config_GPIO(GPIOB, PIN_7, AF_OPEN_DRAIN);
		}
		else if(I2Cx == I2C2){
			// set clock for I2C and GPIOB
			clock_enable_APB1(I2C2RST);
			clock_enable_APB2(AFIOEN);

			// configuration SDA(PB11) and SCL(PB10)
			Cus_Config_GPIO(GPIOB, PIN_10, AF_OPEN_DRAIN);
			Cus_Config_GPIO(GPIOB, PIN_11, AF_OPEN_DRAIN);
		}
	// Kích hoạt I2C
		I2Cx->MY_CR1 &= ~(1<<0);

	// Cấu hình I2C
		I2Cx->MY_CR2 = 36; // APB1 clock frequency is 36 MHz
		I2Cx->MY_OAR1 = 0x68 << 1; // Địa chỉ Slave
		I2Cx->MY_OAR2 |= (1<<0); // Địa chỉ Slave
		I2Cx->MY_OAR1 &= ~(1<<15); // 7-bit address mode

	// Kích hoạt I2C và ACK
		I2Cx->MY_CR1 |= (1<<10); // Kích hoạt ACK
		I2Cx->MY_CR1 |= (1<<0);
}


void I2C_Address(MY_I2C_Type *I2Cx){
	// Gửi địa chỉ Slave với bit R/W là 0 (ghi)
	//I2Cx->MY_DR = (0x68 << 1) | 1;

	//while ((I2Cx->MY_SR1  & (1 << 2)) ==0);
	while (((I2Cx->MY_SR1 >>1) & 1)!= 1); // Đợi cho đến khi địa chỉ được gửi
	uint8_t temp = I2Cx->MY_SR1 | I2Cx->MY_SR2;  // read SR1 and SR2 to clear the ADDR bit
	(void)(temp);
	I2Cx->MY_CR1 |= (1<<10); // Kích hoạt ACK
}
void I2C_Stop (MY_I2C_Type *I2Cx){
	    I2Cx->MY_CR1 |= (1<<0); // Gửi stop bit
}

char I2C_receive_data(MY_I2C_Type *I2Cx){
	I2C_Address(I2Cx);
	while (((I2Cx->MY_SR1 >> 6) & 1) != 1);
	uint8_t receivedData = I2Cx->MY_DR; // Đọc dữ liệu nhận được
	I2Cx->MY_CR1 |= (1<<10); // Kích hoạt ACK
	I2Cx->MY_CR1 |= (1<<0);
	// Chờ cho STOP flag được set
	while (((I2Cx->MY_SR1 >> 4) & 1) != 1);
	// Clear STOP flag
	uint8_t temp = I2Cx->MY_SR1;
	(void)(temp);
	I2Cx->MY_CR1 |= (1<<0);
	return receivedData;
}


