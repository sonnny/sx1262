#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "initialize.h"
#include "radio.h"
#include "ws2812.h"

#define GREEN    0x10000000
#define LEDOFF  0x00000000

uint8_t ascii = 0x21;

uint8_t payload[] = {0x41,0x42,0x43,0x44,0x45,0x46,0x00};//null terminated

void main(){
stdio_init_all(); sleep_ms(3000);
ws2812_init();

if(init_board() > 0) printf("board init...\r\n");
sleep_ms(3000);

printf("transmitting...\r\n");

for(;;){
  ws2812_display(GREEN);
  transmit(payload,sizeof(payload));
  if(ascii > 0x7D) ascii = 0x21;
  payload[5] = ascii++;
  sleep_ms(500);
  ws2812_display(LEDOFF);
  sleep_ms(500);}}
