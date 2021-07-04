

#ifndef HW_H_
#define HW_H_

typedef enum hw_tim_e
{
    HW_TIM2 = 0,
    HW_TIM3 = 1,
} hw_tim_t;

void hw_sleep(void);
void hw_pwm_init(void);
void hw_set_pwm_pulse(void);
void hw_timer_start(hw_tim_t tim_index);
void hw_tick_ms(void);


#endif /* HW_H_ */
