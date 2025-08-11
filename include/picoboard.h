#ifndef _PICOBOARD_H_
#define _PICOBOARD_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "hardware/gpio.h"
#include "hardware/spi.h"

#define LED     25
#define CS      13
#define RESET   23
#define DIO_1   16
#define BUSY    18
#define ANTENNA 17

void init_pico();

#endif
