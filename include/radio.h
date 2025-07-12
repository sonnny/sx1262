#ifndef _RADIO_H_
#define _RADIO_H_

#include "picoboard.h"
#include "config.h"

void setModeReceive();

int lora_receive_async(uint8_t [], int);

void transmit(uint8_t *data, int dataLen);

//testing purposes
uint8_t getIrqLsb();
uint8_t getIrqMsb();

#endif
