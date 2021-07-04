/*
 * app.c
 *
 *  Created on: May 30, 2021
 *      Author: windysson
 */


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "app.h"
#include "hw.h"

#define VN_APP_DEBOUNCING_TIME_MS 200
#define VN_DIGITS 5
#define PASSWORD "CDBBA"

typedef enum sm_state_e
{
	SM_RESET = 0,
	SM_WAITING,
	SM_TIMEOUT,
	SM_CORRECT_PASSWORD,
	SM_ERROR_PASSWORD,
	SM_CHECKING
} sm_state_t;

typedef struct sm_state_var_s
{
	uint32_t pos;
	sm_state_t state;
	char code[VN_DIGITS];
	uint32_t led_time_cnt_ms;
	uint32_t led_time_cnt_correct_ms;
	uint32_t led_time_cnt_timeout_ms;
	uint32_t timeout_showed;
	uint32_t led_time_cnt_error_ms;
	uint32_t error_showed;
} sm_state_var_t;


volatile uint32_t led_time_ms = 1000;
volatile sm_state_var_t st;

bool app_started = false;

void app_switch_interrupt(char digit)
{

	static uint32_t debouncing_time_ms = 0;

	if(!app_started)
		return;

	if((hw_get_tick_ms() - debouncing_time_ms) >= VN_APP_DEBOUNCING_TIME_MS)
	{

		st.code[st.pos] = digit;
		st.pos = st.pos + 1;

		if((st.pos) == VN_DIGITS)
		{
			st.state = SM_CHECKING;
		}

		st.led_time_cnt_ms = 0;

		debouncing_time_ms = hw_get_tick_ms();
	}

}

void app_tick_1ms(void)
{

	if(!app_started)
		return;

	switch(st.state)
	{
		case SM_RESET:
			st.pos = 0;
			st.state = SM_WAITING;
			st.led_time_cnt_ms = 0;
			st.led_time_cnt_timeout_ms = 0;
			st.timeout_showed = 0;
			st.led_time_cnt_error_ms = 0;
			st.error_showed = 0;
			break;

		case SM_WAITING:
			st.led_time_cnt_ms++;

			if(st.led_time_cnt_ms >= 5000)
			{
				st.led_time_cnt_ms = 0;
				st.state = SM_TIMEOUT;
			}
			break;

		case SM_TIMEOUT:
			st.led_time_cnt_timeout_ms++;

			if(st.led_time_cnt_timeout_ms >= 200)
			{
				hw_led_toggle();
				st.led_time_cnt_timeout_ms = 0;

				if(st.timeout_showed <= 2)
				{
					st.timeout_showed++;
				}
				else {
					st.timeout_showed = 0;
					st.state = SM_RESET;
				}
			}
			break;

		case SM_CORRECT_PASSWORD:

			if(hw_led_state_get() == false) {
				hw_led_toggle();
			} else {
				st.led_time_cnt_correct_ms++;

				if(st.led_time_cnt_correct_ms >= 2000) {
					hw_led_toggle();
					st.led_time_cnt_correct_ms = 0;
					st.state = SM_RESET;
				}
			}

			break;

		case SM_ERROR_PASSWORD:
			st.led_time_cnt_error_ms++;

			if(st.led_time_cnt_error_ms >= 200)
			{
				hw_led_toggle();
				st.led_time_cnt_error_ms = 0;

				if(st.error_showed <= 4)
				{
					st.error_showed++;
				}
				else {
					st.error_showed = 0;
					st.state = SM_RESET;
				}
			}

			break;

		case SM_CHECKING:
			if(strcmp(st.code, PASSWORD) == 0) {
				st.state = SM_CORRECT_PASSWORD;
			} else {
				st.state = SM_ERROR_PASSWORD;
			}
	}

}

void app_init(void)
{
	app_started = true;
	st.state = SM_RESET;

}


void app_loop(void)
{
	hw_cpu_sleep();
}
