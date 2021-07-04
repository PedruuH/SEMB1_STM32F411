/*
 * app.c
 *
 *  Created on: May 14, 2021
 *      Author: pedro
 */

#include <stdint.h>
#include "hw.h"

void app_init(void)
{

	hw_timer_start();

}

void app_loop(void)
{
	hw_sleep();
}

