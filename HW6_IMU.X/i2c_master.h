#ifndef I2C_MASTER_H
#define I2C_MASTER_H
#define IMU_ADDRESS (char) 0b1101011
#define SLV_ADDR (char) 0b0100000

// Header file for i2c_master.c
// helps implement use I2C2 as a master without using interrupts

void i2c_master_setup(void);              // set up I2C 1 as a master, at 100 kHz
void i2c_master_start(void);              // send a START signal
void i2c_master_restart(void);            // send a RESTART signal
void i2c_master_send(unsigned char byte); // send a byte (either an address or data)
unsigned char i2c_master_recv(void);      // receive a byte of data
void i2c_master_ack(int val);             // send an ACK (0) or NACK (1)
void i2c_master_stop(void);               // send a stop
void i2c_multi(char addr, char reg, unsigned char * data, char len );

#endif