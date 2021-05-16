/*
 * app.c
 *
 *  Created on: Nov 15, 2020
 *      Author: marce
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "cbf.h"
#include "shell.h"
#include "app.h"
#include "hw.h"

#define APP_DEBOUCING_TIME_MS 50
#define APP_UART_BUFFER_MAX   64

static bool app_started = false;

void app_switch_interrupt(void)
{
	static uint32_t deboucing_time_ms = 0;

	if(!app_started)
		return;

	if((hw_tick_ms_get() - deboucing_time_ms) >= APP_DEBOUCING_TIME_MS)
	{
		deboucing_time_ms = hw_tick_ms_get();
	}
}

void app_tick_1ms(void)
{
	if(!app_started)
		return;
}

void app_init(void)
{
	shell_init();
	app_started = true;
}

void app_loop(void)
{
}
