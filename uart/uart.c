#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> //memset, strlen
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#include "initialize.h"
#include "radio.h"

char uart_buffer[100];
int bufferIndex = 0;
bool UART_TO_SEND = false;
uint8_t rxChar;

void on_uart_rx(){
  rxChar = uart_getc(uart1);//block until a character has been read
  if((rxChar != '\n') && (rxChar != '\r')){
    uart_buffer[bufferIndex++] = rxChar;
  } else {
    //process string
    uart_set_irq_enables(uart1,false,false);//disable uart interrupt
    uart_buffer[bufferIndex - 1] = '\0';
    UART_TO_SEND = true;}}


void main(){
stdio_init_all(); sleep_ms(2000);

if(init_board() > 0) printf("board init...\r\n");
sleep_ms(1000);
uart_init(uart1,115200);
gpio_set_function(TX_PIN, GPIO_FUNC_UART);
gpio_set_function(RX_PIN, GPIO_FUNC_UART);

uart_set_hw_flow(uart1,false,false);//no hardware flow control
uart_set_format(uart1,8,1,UART_PARITY_NONE);
uart_set_fifo_enabled(uart1,false);//turn off fifo
irq_set_exclusive_handler(UART1_IRQ,on_uart_rx);
irq_set_enabled(UART1_IRQ,true);
uart_set_irq_enables(uart1,true,false);//enable rx interrupt only

for(;;){
 if(UART_TO_SEND){
   transmit(uart_buffer,strlen(uart_buffer));
   sleep_ms(100);
   bufferIndex = 0;
   UART_TO_SEND = false;
   memset(uart_buffer,0x00,sizeof(uart_buffer));
   uart_set_irq_enables(uart1,true,false);
 }//enable rx interrupt after processing data
 sleep_ms(50);
}}

