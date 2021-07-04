/*
 * hw.c
 *
 *  Created on: May 30, 2021
 *      Author: windysson
 */


#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
		app_switch_interrupt('A');
	}
	if(GPIO_Pin == GPIO_PIN_1)
	{
		app_switch_interrupt('B');
	}
	if(GPIO_Pin == GPIO_PIN_2)
	{
		app_switch_interrupt('C');
	}
	if(GPIO_Pin == GPIO_PIN_3)
	{
		app_switch_interrupt('D');
	}
}

bool hw_switch_state_get(int sw)
{
	return true;
}

void hw_led_state_set(bool state)
{
	GPIO_PinState led_state = state ? GPIO_PIN_RESET : GPIO_PIN_SET;
	HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, led_state);
}

bool hw_led_state_get(void)
{
	GPIO_PinState pin_state = HAL_GPIO_ReadPin(USER_LED_GPIO_Port, USER_LED_Pin);
	return pin_state == GPIO_PIN_SET ? false : true;
}

void hw_delay(uint32_t led_timer_ms)
{
	HAL_Delay(led_timer_ms);
}

void hw_led_toggle(void)
{
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
}

uint32_t hw_get_tick_ms(void)
{
	return HAL_GetTick();
}

void hw_cpu_sleep(void)
{
	__WFI();
}
