/*
 * hw.c
 *
 *  Created on: Apr 30, 2021
 *      Author: pedro
 */
#include <stdint.h>
#include <stdbool.h>
#include "main.h"

bool get_state_sw(uint32_t pin)
{
	GPIO_PinState switch0_state = HAL_GPIO_ReadPin(SWITCH_0_GPIO_Port, SWITCH_0_Pin);
	GPIO_PinState switch1_state = HAL_GPIO_ReadPin(SWITCH_1_GPIO_Port, SWITCH_1_Pin);

	if(pin == 0)
	{
		if(switch0_state == GPIO_PIN_RESET)
			return true;
		else
			return false;
	}
	if(pin == 1)
		{
			if(switch1_state == GPIO_PIN_RESET)
				return true;
			else
				return false;
		}

}

void led_set(bool state)
{
	GPIO_PinState led_state = state ? GPIO_PIN_SET : GPIO_PIN_RESET;
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, led_state);
}

void timer_ms(uint32_t time)
{
	HAL_Delay(time);
}
