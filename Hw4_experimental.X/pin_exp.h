#ifndef PIN_EXPANDER_H
#define PIN_EXPANDER_H
#include "i2c_master_noint.h"
#include <xc.h>

unsigned char getExpander(unsigned char addr,unsigned char regist);
void setExpander(unsigned char addr, unsigned char data, unsigned char regist);