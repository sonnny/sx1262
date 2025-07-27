

#include "pico/stdlib.h"
#include "radio.h"
#include "debugging.h"

void busyWait(){while(gpio_get(BUSY));}

void standBy(){ 
  gpio_put(CS,0);
  spi_write_blocking(spi1,SETSTDBY_RC,sizeof(SETSTDBY_RC));
  gpio_put(CS,1);
  busyWait();}

void clearIrq(){
  gpio_put(CS,0);
  spi_write_blocking(spi1,CLEARIRQ,sizeof(CLEARIRQ));
  gpio_put(CS,1); busyWait();
}

uint8_t checkIrq(){
  uint8_t buff[10];
  
  if(gpio_get(DIO_1) == 0) return NOIRQ;
  
  gpio_put(CS,0);
  spi_write_read_blocking(spi1,GETIRQSTATUS,buff,sizeof(GETIRQSTATUS));
  gpio_put(CS,1);
  
  if(buff[3] == TRANSMITCOMPLETED) return TRANSMITCOMPLETED;
  
  if(buff[3] == PACKETRECEIVED) return PACKETRECEIVED;
  
  if(buff[3] == PREAMBLEDETECTED) return PREAMBLEDETECTED;
  
  return buff[3];
}



void transmit(uint8_t *data, int dataLen){

  uint8_t buff[32];

//printf("transmitting...\r\n");

  standBy();
  
  gpio_put(CS,0);
  spi_write_blocking(spi1,SETTXPACKETPARAM,sizeof(SETTXPACKETPARAM));
  gpio_put(CS,1);
  busyWait();  
  
  buff[0] = 0x0E;//write buffer opcode
  buff[1] = NOP;
  
  gpio_put(CS,0);
  spi_write_blocking(spi1,buff,2);
  
  //write data to transmit
  spi_write_blocking(spi1,data,dataLen);
  gpio_put(CS,1);
  busyWait();
  
  gpio_put(CS,0);
  spi_write_blocking(spi1,SETTX,sizeof(SETTX));
  gpio_put(CS,1);
  busyWait();

}

void setModeReceive(){
  gpio_put(CS,0);
  spi_write_blocking(spi1,SETRXPACKETPARAM,sizeof(SETRXPACKETPARAM));
  gpio_put(CS,1); busyWait();
  
  gpio_put(CS,0);
  spi_write_blocking(spi1,SETRX,sizeof(SETRX));
  gpio_put(CS,1); busyWait();

}

//receivve function
//process received data in this fuction
//do not pass to main
void receive(){
uint8_t rx_buffer_status[4];
uint8_t data[255];
 
if (getIrqLsb() & PACKETRECEIVED){
  clearIrq();
  
  gpio_put(CS,0); spi_write_read_blocking(spi1,GETRXBUFFERSTATUS,rx_buffer_status,sizeof(GETRXBUFFERSTATUS));
  gpio_put(CS,1); busyWait();
  
  uint8_t length = rx_buffer_status[2];
  uint8_t offset = rx_buffer_status[3];

  if(length > 0){
    rx_buffer_status[0] = OPCODE_READBUFFER;
    rx_buffer_status[1] = offset;
    rx_buffer_status[2] = NOP;
    gpio_put(CS,0);
    spi_write_blocking(spi1,rx_buffer_status,3);
    spi_read_blocking(spi1,NOP,data,length);
    gpio_put(CS,1); busyWait();
    
    if(length > 0){
      printf("data: %s\r\n",(char *) data);
    }
  }
} else printf("no packet received\r\n");

sleep_ms(900);
  
}
