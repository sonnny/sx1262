
#include "radio.h"

void busyWait(){while(gpio_get(BUSY));}

void standBy(){ 
  gpio_put(CS,0);
  spi_write_blocking(spi1,SETSTDBY_RC,sizeof(SETSTDBY_RC));
  gpio_put(CS,1);
  busyWait();}

void transmit(uint8_t *data, int dataLen){

  uint8_t buff[32];

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

int lora_receive_async(uint8_t* receivedData, int dataLength){

  uint8_t buff[32];
  uint8_t payloadLength;
  uint8_t startAddress;
  
  //testing if DIO_1 vs irq status on receiving packet
  //seems depending on the speed of transmitting
  //testing DIO_1 is better with avoiding duplicate packets
  
  //testing receiving packet
  //one is check irq status register for packet received
 
  //check irq status for received packet
  //we received multiple times sometimes same packet twice or 3 times
  //gpio_put(CS,0);
  //spi_write_read_blocking(spi1,GETIRQSTATUS,buff,sizeof(GETIRQSTATUS));
  //gpio_put(CS,1); busyWait();
  //if(!buff[3] & PACKETRECEIVED) return -1;
  
  //testing receiving packet
  //one is check DIO_1 pin
  
  if(gpio_get(DIO_1) == 0){return -1;}//no received data
  
  gpio_put(CS,0);
  spi_write_blocking(spi1,CLEARIRQ,sizeof(CLEARIRQ));
  gpio_put(CS,1); busyWait();
  
  //find buffer received data length
  //find buffer offset address of received data
  gpio_put(CS,0);
  spi_write_read_blocking(spi1,GETRXBUFFERSTATUS,buff,sizeof(GETRXBUFFERSTATUS));
  gpio_put(CS,1); busyWait();
  
  payloadLength = buff[2];
  startAddress  = buff[3];
  
  buff[0] = OPCODE_READBUFFER;
  buff[1] = startAddress;
  buff[2] = NOP;
  
  gpio_put(CS,0);
  spi_write_blocking(spi1,buff,3);
  spi_read_blocking(spi1,NOP,receivedData,payloadLength);
  gpio_put(CS,1); busyWait();
  return payloadLength;
  
}
