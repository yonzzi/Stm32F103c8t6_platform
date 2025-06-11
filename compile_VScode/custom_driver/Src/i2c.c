#include "i2c.h"
#include "clock.h"
#include "stdint.h"

uint32_t* GPIOB_CRL = (uint32_t*)(0x40010C00 + 0x0);
void i2c_init()
{
    // set PB6 as I2C1-SCL , PB7 as I2C1-SDA
    clock_enable_APB1(I2C1RST);
    clock_enable_APB2(GPIOBEN);
    
    //clear reg
    *GPIOB_CRL &= ~ (0xffff<<24);
    *GPIOB_CRL |= (0x1011<<24); //Set PB6 as alternate output pushpull
    *GPIOB_CRL |= (0x0100<<26); // set PB7 as input float

    //set map for alternate I2C
    uint32_t* AFIO_MAPR = (uint32_t*)(0x40010004);
    *AFIO_MAPR &=~(1<<2);    //clear flag
    *AFIO_MAPR =(1<<2);      //set map for using PP6,7

    uint32_t* I2C_CR1 = (uint32_t*)(0x40005400);
    uint32_t* I2C_CR2 = (uint32_t*)(0x40005400 + 0x04);
    uint32_t* I2C_CCR = (uint32_t*)(0x40005400 + 0x08);
    uint32_t* I2C_CCR = (uint32_t*)(0x40005400 + 0x14);

    *I2C_CR1 &= ~(1<<0); // clear reg
    *I2C_CR2 |= 16; // set clock to 16mHz
    *I2C_CCR |= 80; // set clock master mode 80 -> Thigh= 200khz
    *I2C_CCR |= 1<<10; // enable ACK
    *I2C_CR1 |= 1<<0; //enable i2c peripheral
    

    



}