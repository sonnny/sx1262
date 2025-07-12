

#include "initialize.h"

int init_board(){

init_pico();

gpio_put(RESET,0); sleep_ms(100);
gpio_put(RESET,1); sleep_ms(100);
gpio_put(RESET,0); sleep_ms(100);
gpio_put(RESET,1); sleep_ms(100);
  
//SetDIO2AsRfSwitchCtrl
gpio_put(CS,0);
spi_write_blocking(spi1,SETSWITCHDIO2,sizeof(SETSWITCHDIO2));
gpio_put(CS,1); sleep_ms(100);

//setfrequency 915mHz
gpio_put(CS,0);
spi_write_blocking(spi1,SETFREQ915,sizeof(SETFREQ915));
gpio_put(CS,1); sleep_ms(100);

//setpackettype
gpio_put(CS,0);
spi_write_blocking(spi1,SETPACKETTYPE,sizeof(SETPACKETTYPE));
gpio_put(CS,1); sleep_ms(100);

//stoptimeonpreamble
gpio_put(CS,0);
spi_write_blocking(spi1,STOPTIMEONPREAMBLE,sizeof(STOPTIMEONPREAMBLE));
gpio_put(CS,1); sleep_ms(100);

//setmodulation
gpio_put(CS,0);
spi_write_blocking(spi1,SETMODULATION,sizeof(SETMODULATION));
gpio_put(CS,1); sleep_ms(100);

//setpaconfig
gpio_put(CS,0);
spi_write_blocking(spi1,SETPACONFIG,sizeof(SETPACONFIG));
gpio_put(CS,1); sleep_ms(100);

//settxparams
gpio_put(CS,0);
spi_write_blocking(spi1,SETTXPARAMS22,sizeof(SETTXPARAMS22));
gpio_put(CS,1); sleep_ms(100);

//setlorasymbnumtimeout
gpio_put(CS,0);
spi_write_blocking(spi1,SETSYMBOLTIMEOUT, sizeof(SETSYMBOLTIMEOUT));
gpio_put(CS,1); sleep_ms(100);

//setdioirqparams
gpio_put(CS,0);
spi_write_blocking(spi1,SETDIOIRQ, sizeof(SETDIOIRQ));
gpio_put(CS,1); sleep_ms(100);

return 1;

}




