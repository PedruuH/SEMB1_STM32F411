/*
 * app.h
 *
 *  Created on: Apr 30, 2021
 *      Author: pedro
 */

#ifndef APP_H_
#define APP_H_

void app_init(void);
void app_loop(void);
void app_interrupt(bool,bool);
void app_tick_1ms(void);

#endif /* APP_H_ */
