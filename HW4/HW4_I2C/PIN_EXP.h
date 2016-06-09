#ifndef PIN_EXPANDER_H
#define PIN_EXPANDER_H
#include <xc.h>


void initExpander(void);
unsigned char getExpander(unsigned char addr, unsigned char reg);
void setExpander(unsigned char addr, unsigned char data, unsigned char reg);

#endif