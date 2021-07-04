/*
 * hw.h
 *
 *  Created on: May 14, 2021
 *      Author: pedro
 */
#ifndef HW_H_
#define HW_H_

typedef struct
{
  uint32_t Channel;
  uint32_t Rank;
  uint32_t SamplingTime;
  uint32_t Offset;

}ADC_Channelconfig ;

void hw_timer_start(void);
void hw_sleep(void);
void hw_led_toggle(void);
void hw_convert_adc_digital_to_voltage_int(void);
void ADC_Select_CH3 (void);
void ADC_Select_CH4 (void);
void hw_ADC_start(uint16_t *values, uint32_t size);
void hw_ADC_stop(void);
void hw_set_timer_led(uint16_t media_final);
void hw_delay(uint32_t time);

#endif /* HW_H_ */

