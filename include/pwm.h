#ifndef PWM_H
#define PWM_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

void init_pwm();
void forward_slow();
void forward(int speed);
void stop();
void reverse();

#endif
