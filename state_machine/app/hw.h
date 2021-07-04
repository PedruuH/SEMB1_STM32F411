/*
 * hw.h
 *
 *  Created on: May 30, 2021
 *      Author: windysson
 */

#ifndef HW_H_
#define HW_H_

bool hw_switch_state_get(int sw);

void hw_led_state_set(bool state);
bool hw_led_state_get(void);

void hw_delay(uint32_t led_timer_ms);
void hw_led_toggle(void);
void hw_cpu_sleep(void);
uint32_t hw_get_tick_ms(void);

#endif /* HW_H_ */
