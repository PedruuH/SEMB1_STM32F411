/*
 * app.c
 *
 *  Created on: May 29, 2021
 *      Author: pedro
 */


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "app.h"
#include "hw.h"

#define DEBOUNCING_TIME_MS 150
#define PSSW_LENGTH 4
#define PASSWORD "AAAA" // "ABCD" "DBCD"
#define VEZES_PISCADO_TIMEOUT 2
#define TIMEOUT_LED_TIMER 200 //ou error
#define CORRECT_PSSW_TIMER_LED 2000
#define VEZES_PISCADO_ERROR 3

typedef enum sm_state_e
{
	RESET = 0,
	WAITING,
	TIMEOUT,
	PSSW_CORRECT,
	PSSW_ERROR,
	CHECK_PSSW
} sm_state_t;

typedef struct sm_state_var_s
{
	uint32_t posicao;
	sm_state_t state;
	char code[PSSW_LENGTH];
	uint32_t timeout_input_pssw;
	uint32_t timeout_led_timer;
	uint32_t vezes_piscado_timeout;
	uint32_t correct_pssw_timer_led;
	uint32_t error_led_time;
	uint32_t vezes_piscado_error;
} sm_state_var_t;


sm_state_var_t maquina;

void app_loop(void)
{
	hw_sleep();
}
void app_tick_1ms(void)
{
	machine_state();
}

void app_init(void)
{
	maquina.state = RESET;
//	hw_timer_start();

}

void machine_state(void)
{
	switch(maquina.state)
			{
				case RESET:
					maquina.posicao = 0;
					maquina.state = WAITING;
					maquina.timeout_input_pssw = 0;
					maquina.timeout_led_timer = 0;
					maquina.vezes_piscado_timeout = 0;
					maquina.error_led_time = 0;
					maquina.vezes_piscado_error = 0;
					break;

				case WAITING:
					maquina.timeout_input_pssw++;

					if(maquina.timeout_input_pssw >= 5000)
					{
						maquina.timeout_input_pssw = 0;
						maquina.state = TIMEOUT;
					}
					break;

				case CHECK_PSSW:
							if(strcmp(maquina.code, PASSWORD) == 0) {
								maquina.state = PSSW_CORRECT;
							} else {
								maquina.state = PSSW_ERROR;
							}

				case TIMEOUT:
					maquina.timeout_led_timer++;

					if(maquina.timeout_led_timer >= TIMEOUT_LED_TIMER)
					{
						hw_led_toggle();
						maquina.timeout_led_timer = 0;

						if(maquina.vezes_piscado_timeout <= VEZES_PISCADO_TIMEOUT)
						{
							maquina.vezes_piscado_timeout++;
						}
						else {
							maquina.vezes_piscado_timeout = 0;
							maquina.state = RESET;
						}
					}
					break;

				case PSSW_CORRECT:

					if(!hw_get_led_state()) {
						hw_led_toggle();
					} else {
						maquina.correct_pssw_timer_led++;

						if(maquina.correct_pssw_timer_led >= CORRECT_PSSW_TIMER_LED) {
							hw_led_toggle();
							maquina.correct_pssw_timer_led = 0;
							maquina.state = RESET;
						}
					}

					break;

				case PSSW_ERROR:
					maquina.error_led_time++;

					if(maquina.error_led_time >= TIMEOUT_LED_TIMER)
					{
						hw_led_toggle();
						maquina.error_led_time = 0;

						if(maquina.vezes_piscado_error <= VEZES_PISCADO_ERROR)
						{
							maquina.vezes_piscado_error++;
						}
						else {
							maquina.vezes_piscado_error = 0;
							maquina.state = RESET;
						}
					}

					break;


			}
}

void app_switch_interrupt(char digit)
{

	static uint32_t debouncing_time_ms = 0;

	if((hw_get_tick_ms() - debouncing_time_ms) >= DEBOUNCING_TIME_MS)
	{

		maquina.code[maquina.posicao] = digit;
		maquina.posicao += 1;

		if((maquina.posicao) == PSSW_LENGTH)
		{
			maquina.state = CHECK_PSSW;
		}

		maquina.timeout_input_pssw = 0;

		debouncing_time_ms = hw_get_tick_ms();
	}

}

