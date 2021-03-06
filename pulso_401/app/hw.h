/*
 * hw.h
 *
 *  Created on: Nov 15, 2020
 *      Author: marce
 */

#ifndef HW_H_
#define HW_H_

bool hw_switch_state_get(void);
void hw_led_state_set(bool state);
void hw_delay_ms(uint32_t time_ms);
void hw_led_toggle(void);
void hw_cpu_sleep(void);
uint32_t hw_tick_ms_get(void);
uint16_t hw_input_capture_get(void);
void hw_input_capture_set(uint16_t cnt);
void hw_input_capture_init(void);
void hw_stop_timer(void);
void hw_start_timer(void);

#endif /* HW_H_ */
