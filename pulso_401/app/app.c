/*
 * app.c
 *
 *  Created on: Nov 15, 2020
 *      Author: marce
 */

#include <stdint.h>
#include <stdbool.h>
#include "app.h"
#include "hw.h"

#define APP_DEBOUCING_TIME_MS 50
#define MAX_BOX_CAPACITY 10

bool app_started = false;
volatile bool box_full = false;

void app_switch_interrupt(void)
{
	static uint32_t deboucing_time_ms = 0;

	if(!app_started)
		return;

	if((hw_tick_ms_get() - deboucing_time_ms) >= APP_DEBOUCING_TIME_MS)
	{
		box_full = false;
		hw_led_toggle();
		hw_start_timer();
		deboucing_time_ms = hw_tick_ms_get();
	}
}

void app_tick_1ms(void)
{
}

void app_init(void)
{
	hw_input_capture_init();

	app_started = true;
}

void app_loop(void)
{
	if(box_full)
		return;

	uint16_t cnt = hw_input_capture_get();

	if(cnt > MAX_BOX_CAPACITY)
	{
		box_full = true;
		hw_input_capture_set(0);
		hw_stop_timer();
		hw_led_toggle();
	}
}
