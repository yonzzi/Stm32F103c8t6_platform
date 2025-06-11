/*
 * I2c.c
 *
 *  Created on: May 17, 2024
 *      Author: Admin
 */
#include "i2c.h"
#include "clock.h"
#include "gpio.h"
#include "stdint.h"

void I2C_Master_Init(MY_I2C_Type *I2Cx) {
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

	// Reset I2C
		I2Cx->MY_CR1 &= ~(1<<0);

	// configuration I2C
		I2Cx->MY_CR2 = 36; // APB1 clock frequency is 16 MHz
		I2Cx->MY_CCR = 360; // Standard mode, 100 kHz clock
	//	I2Cx->MY_TRISE = 37; // Maximum rise time

		I2Cx->MY_SR1 |= (1<<10); // enable ACK
	// Set I2C
		I2Cx->MY_CR1 |= (1<<0);
}

void I2C_start(MY_I2C_Type *I2Cx){
	I2Cx->MY_CR1 |= (1<<8); //generate start bit
	while (!(I2Cx->MY_SR1  & (1 << 0))); // Đợi cho đến khi START bit được gửi
}

void I2C_Address(MY_I2C_Type *I2Cx, uint8_t address){
	// Gửi địa chỉ Slave với bit R/W là 0 (ghi)
	I2Cx->MY_DR = (address << 1) | 0;

	//while ((I2Cx->MY_SR1  & (1 << 2)) ==0);
	while (((I2Cx->MY_SR1 >>1) & 1)!= 1); // Đợi cho đến khi địa chỉ được gửi
	uint8_t temp = I2Cx->MY_SR1 | I2Cx->MY_SR2;  // read SR1 and SR2 to clear the ADDR bit
	(void)(temp);
}

void I2C_Write(MY_I2C_Type *I2Cx, uint8_t *buffer, uint32_t size){
    // Gửi dữ liệu
	for(int i =0; i <size; i ++){
		I2Cx->MY_DR = buffer[i];
		while (!(I2Cx->MY_SR1 & (1<<7))){}  // wait for TXE bit to set
	}
	I2Cx->MY_SR1 |= (1<<10);
}
void I2C_Stop (MY_I2C_Type *I2Cx){
	    I2Cx->MY_CR1 |= (1<<0); // Gửi stop bit
}
void I2C_read(MY_I2C_Type *I2Cx,uint8_t address,uint8_t *buffer,uint8_t size){
	I2Cx->MY_DR = (address <<1) | 1;  //  send the address
	while (!(I2Cx->MY_SR1 & (1<<1)));  // wait for ADDR bit to set
	uint8_t temp = I2Cx->MY_SR1 | I2Cx->MY_SR2;  // read SR1 and SR2 to clear the ADDR bit
	(void)(temp);

	for(int i = 0; i <size; i ++){
	if(i == (size - 1)){
		I2Cx->MY_CR1 &= ~(1 << 10);
	}
	while (!(I2Cx->MY_SR1 & (1 << 6)));// Đợi cho đến khi dữ liệu được gửi
	buffer[i] = I2Cx->MY_DR;
	}
	while (((I2Cx->MY_SR1 >>2) & 1) !=1) ;// Đợi cho đến khi dữ liệu được gửi
	I2C_Stop(I2Cx);
	I2Cx->MY_CR1 |= (1 << 10);
}

void MPU_Write (MY_I2C_Type *I2Cx, uint8_t address, uint8_t *buffer, uint32_t size)
{
	I2C_start(I2Cx);
	I2C_Address(I2Cx, address);
	I2C_Write(I2Cx, buffer, size);
	I2C_Stop(I2Cx);
}

void MPU_Read (MY_I2C_Type *I2Cx, uint8_t address, uint8_t *buffer, uint32_t size)
{
	I2C_start(I2Cx);  // repeated start
	DMA1_I2C_read(I2Cx, address, buffer, size);
	//I2C_read(I2Cx, address, buffer, size);
}

char DMA1_I2c_Init(MY_I2C_Type *I2Cx,uint8_t *buffer, uint32_t size){
	clock_enable_AHB(DMA1EN);

	// enable I2C_x
	//I2C_Master_Init(I2Cx);

	/* Config UART DMA1 */
	//when RXNE is set, send signal to DMA1, DMA1 move data to RAM
	I2Cx->MY_CR2 |= (1<<11);
//	I2Cx->MY_CR2 |= (1<<12);

	// use DMA1 with chanel_x
	uint32_t *DMA1_CCR5   = (uint32_t*)(0x40020058); //DMA channel x configuration register
	uint32_t *DMA1_CNDTR5 = (uint32_t*)(0x4002005c); //DMA channel x number of data register
	uint32_t *DMA1_CPAR5  = (uint32_t*)(0x40020060); //DMA channel x peripheral address register
	uint32_t *DMA1_CMAR5  = (uint32_t*)(0x40020064); //DMA channel x memory address register
	/*
	 * size : size_of_data byte
	 * from: UARTx_DR
	 * to: recv_data
	 */
	*DMA1_CCR5 &= ~(1<<0);
	*DMA1_CNDTR5 = size;
	*DMA1_CPAR5 = &(I2Cx->MY_DR);
	*DMA1_CMAR5 = (uint32_t)buffer;





	*DMA1_CCR5 |= (1 << 7); //enable Memory increment mode: 0 -> 'size_of_data' byte
	//*DMA1_CCR5 |= (1<< 4); // Circular mode enabled: quay vong

//	*DMA1_CCRx |= (1<< 1); // TCIE: Transfer complete interrupt enabl
	                      // DMA send interrupt even to NVIC

	*DMA1_CCR5 |= (1<<0); //Channel enable (Enable DMA)

//	// config NVIC : when DMA1 send to interrupt event to NVIC, NVIC have to accept that event so we have to config NVIC
//	uint32_t * NVIC_ISER0 = (uint32_t*) (0xe000e100);
//	*NVIC_ISER0 |= (1 << 15);  //  enable interrupt for event in position 15 vector table (DMA1)
}
void DMA1_I2C_read(MY_I2C_Type *I2Cx,uint8_t address,uint8_t *buffer,uint8_t size){
	I2Cx->MY_DR = (address <<1) | 1;  //  send the address
	while (!(I2Cx->MY_SR1 & (1<<1)));  // wait for ADDR bit to set
	uint8_t temp = I2Cx->MY_SR1 | I2Cx->MY_SR2;  // read SR1 and SR2 to clear the ADDR bit
	(void)(temp);


	DMA1_I2c_Init(I2Cx, buffer, size);

	I2Cx->MY_CR2 |= (1<<12); // Đánh dấu truyền DMA cuối cùng
	uint32_t *DMA1_ISR   = (uint32_t*)(0x40020000); //DMA channel x configuration register
	uint32_t *DMA1_IFCR   = (uint32_t*)(0x40020004);

	I2Cx->MY_CR1 |= (1 << 10);


	while (((*DMA1_ISR >> 17) & 1) != 1); // Chờ DMA hoàn thành truyền dữ liệu
	*DMA1_IFCR |= (0b1111 << 16); // complete clear
	// Tắt DMA
	I2Cx->MY_CR2 &= ~(1<<10);
	uint32_t *DMA1_CCR5   = (uint32_t*)(0x40020058); //DMA channel x configuration register
	*DMA1_CCR5  &= ~(1<<0);
	I2C_Stop(I2Cx);

}
