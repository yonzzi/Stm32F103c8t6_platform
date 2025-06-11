/*
 * I2c.h
 *
 *  Created on: May 17, 2024
 *      Author: Admin
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "stdint.h"

#define I2C1_ADDRESS (0x40005400U)
#define I2C2_ADDRESS (0x40005800U)
typedef struct {
	uint32_t MY_CR1;
	uint32_t MY_CR2;
	uint32_t MY_OAR1;
	uint32_t MY_OAR2;
	uint32_t MY_DR;
	uint32_t MY_SR1;
	uint32_t MY_SR2;
	uint32_t MY_CCR;
	uint32_t MY_TRISE;
}MY_I2C_Type;

typedef enum{
	Channel_1 = 1,
	Channel_2,
	Channel_3,
	Channel_4,
	Channel_5,
	Channel_6,
	Channel_7,
}I2C_channel_typedef;

#define I2C1 ((MY_I2C_Type*)I2C1_ADDRESS)
#define I2C2 ((MY_I2C_Type*)I2C2_ADDRESS)

void I2C_Master_Init(MY_I2C_Type *I2Cx);
void I2C_start(MY_I2C_Type *I2Cx);
void I2C_Address(MY_I2C_Type *I2Cx, uint8_t address);
void I2C_Write(MY_I2C_Type *I2Cx, uint8_t *data, uint32_t size);
void I2C_Stop (MY_I2C_Type *I2Cx);
void I2C_read(MY_I2C_Type *I2Cx,uint8_t address,uint8_t *buffer,uint8_t size);
void MPU_Write (MY_I2C_Type *I2Cx, uint8_t address, uint8_t *buffer, uint32_t size);
void MPU_Read (MY_I2C_Type *I2Cx, uint8_t address, uint8_t *buffer, uint32_t size);
char DMA1_I2c_Init(MY_I2C_Type *I2Cx, uint8_t *buffer, uint32_t size);
void DMA1_I2C_read(MY_I2C_Type *I2Cx,uint8_t address,uint8_t *buffer,uint8_t size);

#endif /* INC_I2C_H_ */
