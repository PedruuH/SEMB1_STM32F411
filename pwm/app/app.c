/*
 * app.c
 *
 *  Created on: May 30, 2021
 *      Author: pedro
 */

#include <stdint.h>
#include <stdbool.h>
#include "app.h"
#include "hw.h"

void app_init(void)
{
	hw_pwm_init();
}

void app_loop(void)
{
	hw_sleep();
}
