/*
 * hw.h
 *
 *  Created on: Apr 30, 2021
 *      Author: pedro
 */
#ifndef HW_H_
#define HW_H_

typedef enum hw_tim_e
{
    HW_TIM1 = 0,
    HW_TIM2 = 1,
} hw_tim_t;
void hw_timer_start(hw_tim_t tim_index);

void hw_sleep(void);
void hw_led_toggle(void);
void hw_set_time_led();
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif /* HW_H_ */

