#include "SPI.h"

void SPI1_init(){
    //assign pins
    //ANSELBbits.ANSB14 = 0; //B14 to be used for SCK1
    //ANSELBbits.ANSB15 = 0; //B15 to be used for CS
    TRISBbits.TRISB15 = 0; //set CS as output
    SDI1Rbits.SDI1R = 0b0100; //assign SDI to RPB8
    RPB13Rbits.RPB13R = 0b0011; //assign SDO to RPB13
    CS = 1; //chip select set high
    
    //SPI
    SPI1CON = 0;
    SPI1CONbits.MSSEN = 0;
    SPI1CONbits.CKP = 0;
    SPI1CONbits.CKE = 1;
    SPI1CONbits.MSTEN = 1;
    SPI1CONbits.SMP = 1;
    SPI1STATbits.SPIROV = 0;
    SPI1BUF;
    SPI1BRG = 0x49;
    SPI1CONbits.ON = 1;
}

unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}

void setVoltage(unsigned char channel, unsigned char voltage){
    char byte1, byte2;
    byte1 = (channel << 7)|(0x7 << 4)|(voltage >> 4);
    byte2 = voltage << 4;
    CS = 0;
    spi_io(byte1);
    spi_io(byte2);
    CS = 1;
}