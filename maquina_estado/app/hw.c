/*
 * hw.c
 *
 *  Created on: May 29, 2021
 *      Author: pedro
 */


#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"

extern TIM_HandleTypeDef htim1;

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

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	machine_state();
//}

void hw_timer_start(void)
{
	HAL_TIM_Base_Start_IT(&htim1);

}

bool hw_get_led_state(void)
{
	GPIO_PinState pin_state = HAL_GPIO_ReadPin(USER_LED_GPIO_Port, USER_LED_Pin);
	return pin_state == GPIO_PIN_SET ? false : true;
}

void hw_led_toggle(void)
{
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
}

uint32_t hw_get_tick_ms(void)
{
	return HAL_GetTick();
}

void hw_sleep(void)
{
	__WFI();
}
