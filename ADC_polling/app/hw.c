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


extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;





uint16_t adc_val1,adc_val2, adc_avg, adc_voltage_digital;


//ARR 399 -> 200ms
//ARR 1199 -> 600ms

//ADC_CHANNEL_3 -> PA3
//ADC_CHANNEL_4 -> PA4

void hw_sleep(void)
{
	__WFI();
}

void ADC_Select_CH3 (void)   //main modificado para esta implementação
{
	ADC_Channelconfig Config={0};
	Config.Channel = ADC_CHANNEL_3;
	Config.Rank = 1;
	Config.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &Config) != HAL_OK)
	{
		Error_Handler();
	}
}

void ADC_Select_CH4 (void) //main modificado para esta implementação
{
	ADC_Channelconfig Config={0};
	Config.Channel = ADC_CHANNEL_4;
	Config.Rank = 2;
	Config.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &Config) != HAL_OK)    //está dando warning na passagem (incompatible pointer type), gostaria de retorno para solucionar.
	{
		Error_Handler();
	}
}

void hw_ADC_start(void)
{
	HAL_ADC_Start(&hadc1);

}

void hw_ADC_stop(void)
{
	HAL_ADC_Stop(&hadc1);

}

void hw_led_toggle(void)
{
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
}

void hw_timer_start()
{
	HAL_TIM_Base_Start_IT(&htim1); //para tempo de 1s
	HAL_TIM_Base_Start_IT(&htim2); //para toggle do led
}

void hw_convert_adc_digital_to_voltage_int(void)
{
	adc_val1 = (adc_val1 * 33000)/ 4095;
	adc_val2 = (adc_val2 * 33000)/ 4095;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim1)
	{
		ADC_Select_CH3();
		hw_ADC_start();
		hw_ADC_getValueCH3(&adc_val1);
		hw_ADC_stop();

		ADC_Select_CH4();
		hw_ADC_start();
		hw_ADC_getValueCH4(&adc_val2);
		hw_ADC_stop();

		app_average_adc_value(adc_val1, adc_val2, &adc_avg);
		app_convert_adc_digital_to_voltage_int(adc_avg,&adc_voltage_digital);

		if(adc_avg <= 100)
		{
			__HAL_TIM_SET_AUTORELOAD(&htim2, 399); //200ms
		}
		if(adc_avg >= 4000) //considerando um erro bem pequeno.
		{
			__HAL_TIM_SET_AUTORELOAD(&htim2, 1199); // 600ms
		}
		if( adc_avg > 0 && adc_avg < 3999 )
		{
			__HAL_TIM_SET_AUTORELOAD(&htim2, 999); //400 ms
		}



	}
	if(htim == &htim2)
	{
		hw_led_toggle();
	}

}

void hw_ADC_getValueCH3(uint16_t *adc_val1)
{
	HAL_StatusTypeDef adc_hal_status;

			while(1)
			{
				adc_hal_status = HAL_ADC_PollForConversion(&hadc1, 100);
				if(adc_hal_status == HAL_OK)
				{
					*adc_val1 = (uint16_t) HAL_ADC_GetValue(&hadc1);
					break;
				}
				else if(adc_hal_status != HAL_OK)
				{

				}
			}

}
void hw_ADC_getValueCH4(uint16_t *adc_val2)
{
	HAL_StatusTypeDef adc_hal_status;

			while(1)
			{
				adc_hal_status = HAL_ADC_PollForConversion(&hadc1, 100);
				if(adc_hal_status == HAL_OK)
				{
					*adc_val2 = (uint16_t) HAL_ADC_GetValue(&hadc1);
					break;
				}
				else if(adc_hal_status != HAL_OK)
				{

				}
			}

}


