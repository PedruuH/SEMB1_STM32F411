/*
 * hw.c
 *
 *  Created on: May 23, 2021
 *      Author: pedro
 */
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"
#include "hw.h"


extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3; // timer DMA
extern TIM_HandleTypeDef htim2; // piscar led
extern DMA_HandleTypeDef hdma_adc1;

//ARR 399 -> 200ms
//ARR 1199 -> 600ms

void hw_sleep(void)
{
	__WFI();
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hdac)
{
	app_set_adc_finished();
}
void hw_set_timer_led(uint16_t media_final)
{
	if(media_final <= 100)
	{
		__HAL_TIM_SET_AUTORELOAD(&htim2, 399); //200ms
	}
	if(media_final >= 4000) //considerando um erro bem pequeno.
	{
		__HAL_TIM_SET_AUTORELOAD(&htim2, 1199); // 600ms
	}
	if( media_final > 0 && media_final < 3999 )
	{
		__HAL_TIM_SET_AUTORELOAD(&htim2, 999); //400 ms
	}
}



void hw_ADC_start(uint16_t *values, uint32_t size)
{
	HAL_TIM_Base_Start(&htim3);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)values, size);
}

void hw_ADC_stop(void)
{
	HAL_TIM_Base_Stop(&htim3);
	HAL_ADC_Stop_DMA(&hadc1);
}

void hw_led_toggle(void)
{
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
}

void hw_timer_start(void)
{
	HAL_TIM_Base_Start_IT(&htim2); //para toggle do led
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim2)
	{
		hw_led_toggle();
	}

}

void hw_delay(uint32_t time)
{
	HAL_Delay(time);
}


