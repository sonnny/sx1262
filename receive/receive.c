
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "initialize.h"
#include "radio.h"
#include "debugging.h"

uint8_t buff[255];

void main(){

  stdio_init_all(); sleep_ms(3000);
  if(init_board() > 0) printf("board init...\r\n");
  sleep_ms(3000);
  init_board();     sleep_ms(3000);
  setModeReceive();
  
  for(;;){
    receive();}}
