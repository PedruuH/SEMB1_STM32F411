/*
 * app.c
 *
 *  Created on: Apr 22, 2021
 *      Author: pedro
 */

#include <stdint.h>

#include "app.h"
#include "hw.h"
void app_init (void)
{

}

void app_loop(void)
{
	hw_led_toggle(HW_LED_USER);
	hw_time_delay_ms(500);
}
