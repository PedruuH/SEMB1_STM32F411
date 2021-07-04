/*
 * hw.c
 *
 *  Created on: May 14, 2021
 *      Author: pedro
 */
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"
#include "hw.h"

extern TIM_HandleTypeDef htim1;

bool IT_TIM_occurred = false;

void hw_sleep(void)
{
	__WFI();
}

void hw_led_toggle(void)
{
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
}

void hw_timer_start()
{
	hw_led_toggle();
	HAL_TIM_Base_Start_IT(&htim1);
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	__HAL_TIM_SET_AUTORELOAD(&htim1, 10);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	IT_TIM_occurred = false;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim1)
	{
		IT_TIM_occurred = true;
		hw_led_toggle();
		HAL_TIM_Base_Stop_IT(&htim1);

	}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
		if(IT_TIM_occurred)
		{
			HAL_NVIC_DisableIRQ(EXTI0_IRQn);
			hw_timer_start();
		}

	}
}



