/*
 * app.c
 *
 *  Created on: May 14, 2021
 *      Author: pedro
 */

#include <stdint.h>
#include "hw.h"

void app_average_adc_value(uint16_t adc_val1, uint16_t adc_val2, uint16_t *adc_avg)
{
	*adc_avg = (uint16_t) (adc_val1 + adc_val2)/2;
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

}

