#ifndef MY_DRIVER_INC_LED_H_
#define MY_DRIVER_INC_LED_H_

#define GPIOB_BASE_ADD 0x40010C00
typedef enum
{
	led1=2,
	led2=3
}led_t;

void led_init();
void led_control(led_t led,char led_state);

#endif /* MY_DRIVER_INC_LED_H_ */
