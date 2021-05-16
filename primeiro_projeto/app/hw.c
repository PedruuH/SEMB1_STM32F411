/*
 * hw.c
 *
 *  Created on: Apr 22, 2021
 *      Author: pedro
 */
#include "main.h"
#include "hw.h"

void hw_time_delay_ms(uint32_t tmr_ms)
{
	HAL_Delay(tmr_ms);
}

void hw_led_toggle (hw_led_set_t led)
{
	switch(led)
	{
		case HW_LED_USER:
			HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
			break;
		default:
			break;
	}
}
