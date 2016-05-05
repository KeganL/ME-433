#include "PIN_EXP.h"
void initExpander(void)
{
    setExpander(SLAVE_ADDRESS,0xF0,0x00); 
    setExpander(SLAVE_ADDRESS,0x00,0x0A); 
    //i2c_master_setup();
    //i2c_master_write(IODIR,IO_dir);
}
void setExpander(unsigned char addr, unsigned char data, unsigned char reg)
{
    i2c_master_start();
    i2c_master_send(addr<<1|0);
    i2c_master_send(reg);
    i2c_master_send(data);
    i2c_master_stop();
}
unsigned char getExpander(unsigned char addr, unsigned char reg)
{
    unsigned char readval;
    i2c_master_start();
    i2c_master_send(addr<<1|0);
    i2c_master_send(reg);
    i2c_master_restart();
    i2c_master_send(addr<<1|1);
    
    //LATAbits.LATA4 = 1;
    readval = i2c_master_recv();
    //LATAbits.LATA4 = 1;
    i2c_master_ack(1);
    i2c_master_stop();
    return readval;
}