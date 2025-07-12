
#include "debugging.h"

//debugging
//table 13-29
//getting hex 0x16 meaning:
//
// 0 - tx done, packet transmission completed
// 1 - rx done, packet received
// 1 - preamble detected
// 0 - sync valid word
//
// 1 - headervalid, valid header received
// 0 - header error
// 0 - crc error
// 0 - cad done
uint8_t getIrqLsb(){
  uint8_t buff[4];
  gpio_put(CS,0);
  spi_write_read_blocking(spi1,GETIRQSTATUS,buff,sizeof(GETIRQSTATUS));
  gpio_put(CS,1); busyWait();
  return buff[3];
}

uint8_t getIrqMsb(){
  uint8_t buff[4];
  gpio_put(CS,0);
  spi_write_read_blocking(spi1,GETIRQSTATUS,buff,sizeof(GETIRQSTATUS));
  gpio_put(CS,1); busyWait();
  return buff[2];
}
