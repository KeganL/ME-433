#ifndef SPI_H
#define SPI_H
#include <xc.h>

#define ChA (unsigned char) 0
#define ChB (unsigned char) 1
#define CS LATBbits.LATB15


//protos
void SPI1_init();
void setVoltage (unsigned char channel, unsigned char voltage);
unsigned char spi_io(unsigned char write);

#endif