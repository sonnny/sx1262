
#include "picoboard.h"

void init_pico(){

spi_init(spi1,5000*1000);
spi_set_format(spi1,8,SPI_CPOL_0,SPI_CPHA_0,SPI_MSB_FIRST);
gpio_set_function(14,GPIO_FUNC_SPI);
gpio_set_function(15,GPIO_FUNC_SPI);
gpio_set_function(24,GPIO_FUNC_SPI);

gpio_init(LED);   gpio_set_dir(LED,GPIO_OUT);   gpio_put(LED,0);
gpio_init(CS);    gpio_set_dir(CS,GPIO_OUT);    gpio_put(CS,1);
gpio_init(RESET); gpio_set_dir(RESET,GPIO_OUT); gpio_put(RESET,1);

gpio_init(DIO_1); gpio_set_dir(DIO_1,GPIO_IN);
gpio_init(BUSY);  gpio_set_dir(BUSY, GPIO_IN);

}
