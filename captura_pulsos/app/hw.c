/*
 * hw.c
 *
 *  Created on: Apr 30, 2021
 *      Author: pedro
 */
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"
#include "hw.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

TIM_HandleTypeDef *tims[] = { &htim1, &htim2 };


void hw_led_toggle(void)
{
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
}

void hw_timer_start(hw_tim_t tim_index)
{
	HAL_TIM_Base_Start_IT(tims[tim_index]);
	hw_set_TIM_counterTOzero(HW_TIM1);
}

void hw_timer_stop(hw_tim_t tim_index)
{
	HAL_TIM_Base_Stop_IT(tims[tim_index]);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim2)
	{
	  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	  HAL_TIM_Base_Stop_IT(&htim2);
	  app_caixa_esvaziada();
	}
}

void hw_set_TIM_counterTOzero(hw_tim_t tim_index)
{
	__HAL_TIM_SET_COUNTER(tims[tim_index], 0);
}

uint16_t hw_get_TIM1_counter(void)
{
	return __HAL_TIM_GET_COUNTER(&htim1);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		hw_timer_start(HW_TIM2);

	}
}

