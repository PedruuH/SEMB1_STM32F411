/*
 * app.h
 *
 *  Created on: May 14, 2021
 *      Author: pedro
 */

#ifndef APP_H_
#define APP_H_

void app_init(void);
void app_loop(void);
void app_average_adc_value(uint16_t *adc_raw_val, uint16_t *adc_avg_val_1, uint16_t *adc_avg_val_2, uint16_t *media_final);
void app_convert_adc_digital_to_voltage_int(uint16_t adc_avg, uint16_t *adc_voltage_digital);
void app_set_adc_finished(void);

#endif /* APP_H_ */
