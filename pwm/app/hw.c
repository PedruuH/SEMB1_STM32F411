/*
 * hw.c
 *
 *  Created on: May 30, 2021
 *      Author: pedro
 */
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"
#include "hw.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

bool sw_pressed = false;

uint16_t CCR_PULSE = 0;

// TIM1 - PWM ARR 999 CCR initial 1000
// TIM2 - debouncing 100ms  ARR 99
// TIM3 - timer 3s	ARR 6000

void hw_sleep(void)
{
	__WFI();
}

void hw_pwm_init(void)
{
	HAL_TIM_PWM_Init(&htim1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

void hw_set_pwm_pulse(void)
{
	CCR_PULSE += 100;
	if(CCR_PULSE <= 1000)
	{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,CCR_PULSE);
	}
	else
	{
		CCR_PULSE = 0;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,CCR_PULSE);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim == &htim2)
  {
	  HAL_TIM_Base_Stop_IT(&htim2);
	  hw_set_pwm_pulse();
	  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
  }
  if(htim == &htim3)
  {
	  HAL_TIM_Base_Stop_IT(&htim3);
	  if(HAL_GPIO_ReadPin(USER_SW_GPIO_Port, USER_SW_Pin) == GPIO_PIN_RESET)
	  {
		  sw_pressed = true;
		  CCR_PULSE = 0;
		  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,1000);
	  }

  }
}
void hw_tick_ms(void)
{

}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		hw_timer_start(HW_TIM2);
		hw_timer_start(HW_TIM3);


	}
}

void hw_timer_start(hw_tim_t tim_index)
{
	TIM_HandleTypeDef *tims[] = { &htim2, &htim3 };
	HAL_TIM_Base_Start_IT(tims[tim_index]);

}
