#ifndef SERVO_H
#define SERVO_H

#include <stdio.h>
#include "hardware/pwm.h"
#include "pico/stdlib.h"

#define SERVO1 4
#define CHANNEL 2
#define PWM_FREQ 50
#define MIN_PULSE_WIDTH_US 1000
#define MAX_PULSE_WIDTH_US 2000
#define PULSE_RANGE_US (MAX_PULSE_WIDTH_US - MIN_PULSE_WIDTH_US)

void init_servo();
void servo_center();
void servo_left();
void servo_right();

#endif
