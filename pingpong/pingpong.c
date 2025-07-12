#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "pico/stdlib.h"

#include "initialize.h"
#include "radio.h"
#include "debugging.h"

uint8_t buff[255];

uint8_t ping[] = {'P','I','N','G','\0'};
uint8_t pong[] = {'P','O','N','G','\0'};

int bytesRead;

void main(){
stdio_init_all(); sleep_ms(3000);

if(init_board() > 0) printf("board init...\r\n");
sleep_ms(3000);

printf("sending ping...\r\n");
transmit(ping,sizeof(ping));
sleep_ms(100);

for(;;){
  setModeReceive();
  bytesRead = lora_receive_async(buff,sizeof(buff));
  if(bytesRead > -1) {
    if(strcmp((char *)buff,ping) == 0){
      printf("received ping sending pong\n");
      transmit(pong,sizeof(pong));
    } else if(strcmp((char *)buff,pong) == 0) {
      printf("received pong sending ping\n");
      transmit(ping,sizeof(ping));
    } else {
      printf("received neither ping or pong\n");
    }
    sleep_ms(2000);}}}

