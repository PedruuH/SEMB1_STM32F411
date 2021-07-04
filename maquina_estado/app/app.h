/*
 * app.h
 *
 *  Created on: May 29, 2021
 *      Author: pedro
 */

#ifndef APP_H_
#define APP_H_

void app_init(void);
void app_loop(void);
void app_tick_1ms(void);
void app_switch_interrupt(char pin);
void machine_state(void);
void password_correct(void);


#endif /* APP_H_ */
