/*
 * main.c
 *
 *  Created on: Jun 19, 2024
 *      Author: hoatt
 */
#include"stdint.h"
#include "clock.h"
#include "led.h"
#include "delay.h"
//#include "pwm.h"
//#include "capture.h"
#include "adc.h"
#include "FreeRTOS.h"
#include "task.h"


//uint16_t t_pwm;
//uint16_t t_pulse_width;

void vApplicationGetTimerTaskMemory()
{

}
void vAssertCalled()
{

}
void vPortFreeStack(void * pv)
{

}
void ucHeap()
{

}

void func_1();
void func_2();
void SystemInit();
void setup()
{
	//freeRos
   //led_init();
   


   //freetos
   //led_control(1);
//    timer1_init();
// //   pwm_init();
// //   capture_init();
// //   pwm_pulse_ctrl(50); //PWM=50%
//    clock_init();
//    adc_init();
}
int cnt=0;
float temp_sensor;
void loop()
{
	//for timer pwm with độ sáng tăng dần
//   cnt++;
//   if(cnt > 100)
//   {
//	   cnt=0;
//   }
   //pwm_pulse_ctrl(50);

	/* for use timer capture
	t_pwm=capture_read_frequence();
	t_pulse_width=capture_read_pulse_width();
 * */


// 	temp_sensor= adc_get_tem_sensor();
//    led_control(1);
//    timer1_delay(1000); //will count every 1000ms
//    led_control(0);
//    timer1_delay(1000);

//freetos


//freetos

}

int main()
{
	setup();
	// while (1)
	// {
	//   loop();
	// }
	TaskHandle_t task1 =NULL;
	TaskHandle_t task2 =NULL;
	TaskHandle_t task3 =NULL;
	xTaskCreate(func_1,"task 1",128, NULL , 0 , &task1); // target to create func to execute 
	// paramater3 = 128, p4= paramater for func1, p5= priority of task, p6= argument return ~ id of value return func 
	xTaskCreate(func_2,"task 2",128, NULL , 0 , &task2);
	xTaskCreate(func_3,"task 3",128, NULL , 0 , &task3);
	vTaskStartScheduler();
	while(1)
	{

	}
	return 0;
}

void SystemInit()
{
	led_init();
}

void func_1( void * param)
{
	while(1)
	{
		led_control(led1,1);
		vTaskDelay(500);
		led_control(led1,0);
        vTaskDelay(500);
	}
}

void func_2( void * param)
{
	while(1)
	{
		led_control(led2,1);
		vTaskDelay(1000);
		led_control(led2,0);
		vTaskDelay(1000);
	}
}

void func_3(void *param)
{
	for(;;)
	{
		printf("hello world");

	}
}