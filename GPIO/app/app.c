/*
 * app.c
 *
 *  Created on: Apr 30, 2021
 *      Author: pedro
 */

#include <stdint.h>
#include <stdbool.h>
#include "app.h"
#include "hw.h"

void app_init(void)
{

}

void app_loop(void)
{
	uint32_t led_time_on;
	uint32_t led_time_off;

	if(get_state_sw(0))
	{
		if(get_state_sw(1))
		{
			led_time_on = 100;
			led_time_off = 100;
		}
		else
		{
			led_time_on = 300;
			led_time_off = 150;
		}
	}
	else
	{
		if(get_state_sw(1))
		{
			led_time_on = 600;
			led_time_off = 300;
		}
		else
		{
			led_time_on = 900;
			led_time_off = 450;
		}
	}

	led_set(true);
	timer_ms(led_time_on);

	led_set(false);
	timer_ms(led_time_off);

}
