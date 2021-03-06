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


uint16_t led_time = 250;

void hw_sleep(void)
{
	__WFI();
}

void hw_led_toggle(void)
{
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
}

void hw_timer_start(hw_tim_t tim_index)
{
	TIM_HandleTypeDef *tims[] = { &htim1, &htim2 };
	HAL_TIM_Base_Start_IT(tims[tim_index]);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim1)
	{
		hw_led_toggle();
	}
  if(htim == &htim2)
  {
	  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	  HAL_TIM_Base_Stop_IT(&htim2);
	  hw_set_time_led();
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		hw_timer_start(HW_TIM2);

	}
}

void hw_set_time_led(void)
{
	if(led_time == 500)
	{
		__HAL_TIM_SET_AUTORELOAD(&htim1, 499);
		__HAL_TIM_SET_COUNTER(&htim1, 0);
		led_time = 250;
		return;
	}
	if(led_time == 250)
	{
		__HAL_TIM_SET_AUTORELOAD(&htim1, 999);
		__HAL_TIM_SET_COUNTER(&htim1, 0);
		led_time = 500;
		return;
	}

//	if(__HAL_TIM_GET_AUTORELOAD(&htim1) == 499)
//	{
//		__HAL_TIM_SET_AUTORELOAD(&htim1, 999);
//		__HAL_TIM_SET_COUNTER(&htim1, 0);
//		return;
//	}
//	if(__HAL_TIM_GET_AUTORELOAD(&htim1) == 999)
//	{
//		__HAL_TIM_SET_AUTORELOAD(&htim1, 499);
//		__HAL_TIM_SET_COUNTER(&htim1, 0);
//		return;
//	}


}


