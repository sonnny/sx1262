#ifndef _RADIO_H_
#define _RADIO_H_

#include <stdio.h>

#include "picoboard.h"
#include "config.h"

void setModeReceive();

void receive();

void transmit(uint8_t *data, int dataLen);

uint8_t checkIrq();

void clearIrq();

//testing purposes
uint8_t getIrqLsb();
uint8_t getIrqMsb();

#endif
