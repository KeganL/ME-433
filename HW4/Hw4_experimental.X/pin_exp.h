#ifndef PIN_EXP_H
#define PIN_EXP_H
#include <xc.h>

unsigned char getExpander(unsigned char addr,unsigned char regist);
void setExpander(unsigned char addr, unsigned char data, unsigned char regist);

#endif