#include <xc.h>
#include "i2c_master.h"
#define XYZ 2000 // I2CBRG = [1/(2*Fsck) - PGD]*Pblck - 2

unsigned char i2c_master_read(int pin) {
    unsigned char out = 0x01;
    unsigned char data;
    out = out<<pin;
    data = getExpander(SLAVE_ADDRESS,0x09);
    data = (data&out)>>pin;
    return data;
}

void i2c_master_write(int pin, int write) {
    unsigned char out = 0x01;
    LATAbits.LATA4 = 0; 
    unsigned char current = getExpander(SLAVE_ADDRESS,0x09);
    out = out << pin;
    if (write == 1){
        setExpander(SLAVE_ADDRESS,current|out,0x0A);
    }
    else if (write == 0){
        setExpander(SLAVE_ADDRESS,current&(~out),0x0A);
        LATAbits.LATA4 = 1;
    }

   
}

void i2c_master_setup(void) {
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    I2C2BRG = XYZ; // I2CBRG = [1/(2*Fsck) - PGD]*Pblck - 2
    // look up PGD for your PIC32
    I2C2CONbits.ON = 1; // turn on the I2C1 module
}

// Start a transmission on the I2C bus
void i2c_master_start(void) {
    I2C2CONbits.SEN = 1;            // send the start bit
    while(I2C2CONbits.SEN) { ; }    // wait for the start bit to be sent
}

void i2c_master_restart(void) {     
    I2C2CONbits.RSEN = 1;           // send a restart 
    while(I2C2CONbits.RSEN) { ; }   // wait for the restart to clear
}

void i2c_master_send(unsigned char byte) { // send a byte to slave
  I2C2TRN = byte;                   // if an address, bit 0 = 0 for write, 1 for read
  while(I2C2STATbits.TRSTAT) { ; }  // wait for the transmission to finish
  if(I2C2STATbits.ACKSTAT) {        // if this is high, slave has not acknowledged
    // ("I2C2 Master: failed to receive ACK\r\n");
  }
}

unsigned char i2c_master_recv(void) { // receive a byte from the slave
    I2C2CONbits.RCEN = 1;             // start receiving data
    while(!I2C2STATbits.RBF) { ; }    // wait to receive the data
    return I2C2RCV;                   // read and return the data
}

void i2c_master_ack(int val) {        // sends ACK = 0 (slave should send another byte)
                                      // or NACK = 1 (no more bytes requested from slave)
    I2C2CONbits.ACKDT = val;          // store ACK/NACK in ACKDT
    I2C2CONbits.ACKEN = 1;            // send ACKDT
    while(I2C2CONbits.ACKEN) { ; }    // wait for ACK/NACK to be sent
}

void i2c_master_stop(void) {          // send a STOP:
  I2C2CONbits.PEN = 1;                // comm is complete and master relinquishes bus
  while(I2C2CONbits.PEN) { ; }        // wait for STOP to complete
}