/*
 * hw.h
 *
 *  Created on: Apr 22, 2021
 *      Author: pedro
 */

#ifndef HW_H_
#define HW_H_

typedef enum hw_led_set_e
{
	HW_LED_USER = 0,
	//
}hw_led_set_t;

void hw_time_delay_ms(uint32_t tmr_ms);

void hw_led_toggle (hw_led_set_t led);

#endif /* HW_H_ */
