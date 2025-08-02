
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "initialize.h"
#include "radio.h"
#include "debugging.h"
#include "pwm.h"

uint8_t buff[255];

void main(){

  stdio_init_all(); sleep_ms(1000);
  init_pwm();
  if(init_board() > 0) printf("board init...\r\n");
  sleep_ms(1000);
  setModeReceive();
  
  for(;;){
    receive();
    sleep_ms(50);}}
