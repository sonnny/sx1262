#include "pwm.h"

void init_pwm(){
gpio_set_function(2,GPIO_FUNC_PWM);
gpio_set_function(3,GPIO_FUNC_PWM);
pwm_set_wrap(1,5000);
pwm_set_clkdiv(1,25.0f);
pwm_set_chan_level(1,PWM_CHAN_A,0);
pwm_set_chan_level(1,PWM_CHAN_B,0);
pwm_set_enabled(1,true);
}

void forward(int speed){
pwm_set_chan_level(1,PWM_CHAN_A,speed);
pwm_set_chan_level(1,PWM_CHAN_B,0);
}

void stop(){
pwm_set_chan_level(1,PWM_CHAN_A,0);
pwm_set_chan_level(1,PWM_CHAN_B,0);
}

void reverse(int speed){
pwm_set_chan_level(1,PWM_CHAN_A,0);
pwm_set_chan_level(1,PWM_CHAN_B,speed);
}


