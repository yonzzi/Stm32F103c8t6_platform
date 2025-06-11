/*
 * capture.h
 *
 *  Created on: Jul 8, 2024
 *      Author: hoatt
 */
#include <stdint.h>
#ifndef INC_CAPTURE_H_
#define INC_CAPTURE_H_

void capture_init();
uint16_t capture_read_frequence();
uint16_t capture_read_pulse_width();

#endif /* INC_CAPTURE_H_ */
