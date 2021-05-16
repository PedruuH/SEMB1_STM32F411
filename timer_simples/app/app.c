/*
 * app.c
 *
 *  Created on: Apr 30, 2021
 *      Author: pedro
 */

#include <stdint.h>
#include "hw.h"

void app_init(void)
{
	hw_timer_start(HW_TIM1);
}

void app_loop(void)
{
	hw_sleep();
}
