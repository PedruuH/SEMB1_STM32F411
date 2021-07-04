/*
 * hw.h
 *
 *  Created on: May 29, 2021
 *      Author: pedro
 */

#ifndef HW_H_
#define HW_H_

typedef enum hw_tim_e
{
    HW_TIM1 = 0,
    HW_TIM2 = 1,
} hw_tim_t;
void hw_timer_start(void);


bool hw_switch_state_get(int sw);


void hw_led_toggle(void);
void hw_sleep(void);
uint32_t hw_get_tick_ms(void);
bool hw_get_led_state(void);

#endif /* HW_H_ */
