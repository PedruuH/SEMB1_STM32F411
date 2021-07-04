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

#define CAPACIDADE_CAIXA 7

bool caixa_cheia = false;

void app_init(void)
{
	hw_timer_start(HW_TIM1);
}

void app_loop(void)
{
	uint16_t contagem_obj = hw_get_TIM1_counter();

	if(contagem_obj >= CAPACIDADE_CAIXA)
	{
		hw_timer_stop(HW_TIM1);
		hw_led_toggle();
		hw_set_TIM_counterTOzero(HW_TIM1);
		caixa_cheia = true;
	}
}

void app_caixa_esvaziada(void)
{
	if(caixa_cheia)
	{
		hw_timer_start(HW_TIM1);
		hw_led_toggle();
		caixa_cheia = false;
	}
}
