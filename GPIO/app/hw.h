/*
 * hw.h
 *
 *  Created on: Apr 30, 2021
 *      Author: pedro
 */
#ifndef HW_H_
#define HW_H_

bool get_state_sw(uint32_t pin);
void led_set(bool state);
void timer_ms(uint32_t time);

#endif /* HW_H_ */

