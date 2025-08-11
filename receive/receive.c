
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "initialize.h"
#include "radio.h"
#include "debugging.h"
#include "pwm.h"
#include "servo.h"

uint8_t buff[255];

void main(){

  stdio_init_all(); sleep_ms(1000);
  init_pwm();
  init_servo();
  if(init_board() > 0) printf("board init...\r\n");
  sleep_ms(1000);
  
  gpio_put(ANTENNA,1); // antenna high on receive only, low on transmit
                       // don't forget to change for transmit if using half duplex
  setModeReceive();
  
  for(;;){
    receive();
    sleep_ms(50);}}
