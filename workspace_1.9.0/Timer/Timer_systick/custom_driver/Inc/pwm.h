/*
 * pwm.h
 *
 *  Created on: Jun 20, 2024
 *      Author: hoatt
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

/**
 * @brief generate pwm with frequency =1Hz, pulse width=50%
 * @pama None // parameter
 * @reval None // return value
 */

 void  pwm_init();
 void pwm_pulse_ctrl(uint16_t pulse); //control pulse - độ rộng xung

#endif /* INC_PWM_H_ */
