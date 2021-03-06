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

uint32_t led_time_on=100;
uint32_t led_time_off=100 ;

void app_interrupt(bool pin0, bool pin1)
{
	if(pin0)
	{
		if(pin1)
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
		if(pin1)
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
}

void app_tick_1ms(void)
{
	static uint32_t led_counter1,led_counter2 = 0;
	led_counter1++;
	led_counter2++;

	if(led_counter1 >= led_time_on)
	{
		hw_led_toggle();
		led_counter1=0;
	}
	if(led_counter2 >= led_time_off )
	{
		hw_led_toggle();
		led_counter2=0;
	}
}


void app_init(void)
{

}

void app_loop(void)
{
	hw_sleep();
}
