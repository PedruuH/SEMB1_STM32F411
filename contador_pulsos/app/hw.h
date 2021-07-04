/*
 * hw.h
 *
 *  Created on: May 14, 2021
 *      Author: pedro
 */
#ifndef HW_H_
#define HW_H_


void hw_timer_start();
void hw_sleep(void);
void hw_led_toggle(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif /* HW_H_ */

