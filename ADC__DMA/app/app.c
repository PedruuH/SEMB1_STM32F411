/*
 * app.c
 *
 *  Created on: May 23, 2021
 *      Author: pedro
 */

#include <stdint.h>
#include <stdbool.h>
#include "hw.h"

volatile bool adc_finisehd = false;
uint16_t adc_raw_data[10]={0};

void app_set_adc_finished(void)
{
	adc_finisehd = true;
	hw_ADC_stop();
}


void app_average_adc_value(uint16_t *adc_raw_val, uint16_t *adc_avg_val_1, uint16_t *adc_avg_val_2, uint16_t *media_final)
{
	uint16_t cnt = 0;
	uint32_t sum_temp[2] = {0,0};

	while(cnt< 10)
	{
		for(uint8_t i=0; i< 2; i++)
		{
			sum_temp[i]=sum_temp[i] + adc_raw_val[cnt+1];
		}
		cnt+=2;
	}
	for(uint8_t i=0; i< 10; i++)
		sum_temp[i] = sum_temp[i] / 5;

	*media_final = (uint16_t) (sum_temp[0] + sum_temp[1])/2;
}

void app_convert_adc_digital_to_voltage_int(uint16_t adc_avg, uint16_t *adc_voltage_digital)
{
	*adc_voltage_digital = (uint16_t) (adc_avg*(33000))/(4095);
}

void app_init(void)
{
	hw_timer_start();

}

void app_loop(void)
{
	uint16_t adc_avg_val_1,adc_avg_val_2,media_final;

	hw_ADC_start(adc_raw_data, 10);

	if(adc_finisehd)
	{
		adc_finisehd = false;
		app_average_adc_value(adc_raw_data,&adc_avg_val_1, &adc_avg_val_2, &media_final);
		hw_set_timer_led(media_final);

	}

	hw_delay(1000);
}

