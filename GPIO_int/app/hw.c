/*
 * hw.c
 *
 *  Created on: Apr 30, 2021
 *      Author: pedro
 */
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"
bool pin0 , pin1 = false;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if (GPIO_Pin == GPIO_PIN_0)
	{
		pin0 = true;
	}
	if (GPIO_Pin == GPIO_PIN_1)
	{
		pin1 = true;
	}
	app_interrupt(pin0,pin1);
}

void hw_sleep(void)
{
	__WFI();
}

void hw_led_toggle(void)
{
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}
