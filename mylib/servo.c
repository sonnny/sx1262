#include "servo.h"

float pulse_width_us;
uint32_t zero_duty;
uint32_t ninety_duty;
uint32_t one80_duty;

void init_servo(){
  gpio_set_function(SERVO1, GPIO_FUNC_PWM);
  float clock_div = 125000000.0f / (PWM_FREQ * 10000); // 250 Example clock divider
  pwm_set_clkdiv(CHANNEL, clock_div);
  pwm_set_wrap(CHANNEL, 10000); // Example wrap value
  pwm_set_enabled(CHANNEL, true);
    
  //zero duty
  pulse_width_us = MIN_PULSE_WIDTH_US;
  zero_duty = (uint32_t)(pulse_width_us * 10000 / (1000000.0f/PWM_FREQ));

  //ninety_duty
  pulse_width_us = MIN_PULSE_WIDTH_US + (PULSE_RANGE_US/2.0f);
  ninety_duty = (uint32_t)(pulse_width_us * 10000 / (1000000.0f/PWM_FREQ)); 
    
  //one80_duty
  pulse_width_us = MAX_PULSE_WIDTH_US;
  one80_duty = (uint32_t)(pulse_width_us * 10000 / (1000000.0f/PWM_FREQ));  
}

void servo_center(){ pwm_set_chan_level(CHANNEL,PWM_CHAN_A,ninety_duty);}

void servo_left(){ pwm_set_chan_level(CHANNEL,PWM_CHAN_A,zero_duty);}

void servo_right(){ pwm_set_chan_level(CHANNEL,PWM_CHAN_A,one80_duty);}
