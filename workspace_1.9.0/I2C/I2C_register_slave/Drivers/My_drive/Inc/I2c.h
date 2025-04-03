/*
 * I2c.h
 *
 *  Created on: May 17, 2024
 *      Author: Admin
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "stdint.h"

#define I2C1_ADDRESS 0x40005400
#define I2C2_ADDRESS 0x40005800

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
#define I2C1 ((MY_I2C_Type*)I2C1_ADDRESS)
#define I2C2 ((MY_I2C_Type*)I2C2_ADDRESS)

void I2C_Slave_Init(MY_I2C_Type *I2Cx);


#endif /* INC_I2C_H_ */
