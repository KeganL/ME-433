#ifndef PIC_INIT_H
#define PIC_INIT_H

#include <xc.h>           // processor SFR definitions
#include <sys/attribs.h>  // __ISR macro
#include "spi.h"
#include "i2c_master.h"
#include "PIN_EXP.h"
#include <math.h>
//
//// DEVCFG0
//#pragma config DEBUG = OFF // no debugging
//#pragma config JTAGEN = OFF // no jtag
//#pragma config ICESEL = ICS_PGx1 // use PGED1 and PGEC1
//#pragma config PWP = OFF // no write protect
//#pragma config BWP = OFF // no boot write protect
//#pragma config CP = OFF // no code protect
//
//// DEVCFG1
//#pragma config FNOSC = PRIPLL // use primary oscillator with pll
//#pragma config FSOSCEN = OFF // turn off secondary oscillator
//#pragma config IESO = OFF // no switching clocks
//#pragma config POSCMOD = HS // high speed crystal mode
//#pragma config OSCIOFNC = ON // free up secondary osc pins
//#pragma config FPBDIV = DIV_1 // divide CPU freq by 1 for peripheral bus clock
//#pragma config FCKSM = CSDCMD // do not enable clock switch
//#pragma config WDTPS = PS1048576 // slowest wdt
//#pragma config WINDIS = OFF // no wdt window
//#pragma config FWDTEN = OFF // wdt off by default
//#pragma config FWDTWINSZ = WINSZ_25 // wdt window at 25%
//
//// DEVCFG2 - get the CPU clock to 48MHz
//#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz
//#pragma config FPLLMUL = MUL_24 // multiply clock after FPLLIDIV
//#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz
//#pragma config UPLLIDIV = DIV_2 // divider for the 8MHz input clock, then multiply by 12 to get 48MHz for USB
//#pragma config UPLLEN = ON // USB clock on
//
//// DEVCFG3
//#pragma config USERID = 0 // some 16bit userid, doesn't matter what
//#pragma config PMDL1WAY = OFF // allow multiple reconfigurations
//#pragma config IOL1WAY = OFF // allow multiple reconfigurations
//#pragma config FUSBIDIO = ON // USB pins controlled by USB module
//#pragma config FVBUSONIO = ON // USB BUSON controlled by USB module


//***********************************************************************

// DEVCFG0
#pragma config DEBUG 		= 0b10	// no debugging
#pragma config JTAGEN 		= 0b0 	// no jtag
#pragma config ICESEL 		= 0b11 	// use PGED1 and PGEC1
#pragma config PWP 			= 0x3F  // no write protect
#pragma config BWP 			= 0b1 	// no boot write protect
#pragma config CP 			= 0b1 	// no code protect

// DEVCFG1
#pragma config FNOSC 		= 0b011	// use primary oscillator with pll
#pragma config FSOSCEN 		= 0b0 	// turn off secondary oscillator
#pragma config IESO 		= 0b0 	// no switching clocks
#pragma config POSCMOD 		= 0b10 	// high speed crystal mode
#pragma config OSCIOFNC 	= 0b1 	// free up secondary osc pins
#pragma config FPBDIV 		= 0b00 	// divide CPU freq by 1 for peripheral bus clock
#pragma config FCKSM 		= 0b11 	// do not enable clock switch
#pragma config WDTPS 		= 0b10100 	// slowest wdt
#pragma config WINDIS 		= 0b1 	// no wdt window
#pragma config FWDTEN 		= 0b0 	// wdt off by default
#pragma config FWDTWINSZ 	= 0b11 	// wdt window at 25%

// DEVCFG2 - get the CPU clock to 48MHz
#pragma config FPLLIDIV 	= 0b001	// divide input clock to be in range 4-5MHz
#pragma config FPLLMUL 		= 0b111	// multiply clock after FPLLIDIV
#pragma config FPLLODIV 	= 0b001	// divide clock after FPLLMUL to get 48MHz
#pragma config UPLLIDIV 	= 0b001	// divider for the 8MHz input clock, then multiply by 12 to get 48MHz for USB
#pragma config UPLLEN 		= 0b0 	// USB clock on

// DEVCFG3
#pragma config USERID 		= 0b0 	// some 16bit userid, doesn't matter what
#pragma config PMDL1WAY 	= 0b0 	// allow multiple reconfigurations
#pragma config IOL1WAY 		= 0b0 	// allow multiple reconfigurations
#pragma config FUSBIDIO 	= 0b1 	// USB pins controlled by USB module
#pragma config FVBUSONIO 	= 0b1 	// USB BUSON controlled by USB module

#endif