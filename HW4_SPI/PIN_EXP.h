#ifndef PIN_EXPANDER_H
#define PIN_EXPANDER_H
#include "i2c_master.h"
#include <xc.h>

// MCP23008 ADDRESSES AND VALUES
#define IODIR   (char) 0x00
#define GPIO    (char) 0x09
#define OLAT    (char) 0x0A
#define GP0     (char) 1<<0
#define GP1     (char) 1<<1
#define GP2     (char) 1<<2
#define GP3     (char) 1<<3
#define GP4     (char) 1<<4
#define GP5     (char) 1<<5
#define GP6     (char) 1<<6
#define GP7     (char) 1<<7

void initExpander(void);
unsigned char getExpander(unsigned char addr, unsigned char reg);
void setExpander(unsigned char addr, unsigned char data, unsigned char reg);

#endif