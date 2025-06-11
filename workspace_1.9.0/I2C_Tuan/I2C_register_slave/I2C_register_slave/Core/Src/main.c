
#include "clock.h"
#include "I2c.h"
char x = 0;
int main(void)
{
 	clock_init();
	I2C_Slave_Init(I2C2);
  while (1)
  {
	 x = I2C_receive_data(I2C2);
  }

}


