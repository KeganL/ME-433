#include "PIC_INIT.h"
#define PI (double) 3.14159
#define clockfreq (int) 48000000
#define A_ticks (int) clockfreq/10/256
#define B_ticks (int) clockfreq/5/256

int main(){
    int count = 0, i = 0;
    unsigned char Aamp = 0, Bamp = 0; 
    unsigned char sine[A_ticks];
    for(;i<A_ticks;i++){
        //sine[i] = ((255)/2*sin(((double)(2*PI*count))/((double)256)*2))+(128/2);
        sine[i] = ((255)/2*sin(((double)(2*PI*count))/((double)256)*2))+(128);
        count++;
    }
    count = 0;


    __builtin_disable_interrupts();
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);
    BMXCONbits.BMXWSDRM = 0x0;
    INTCONbits.MVEC = 0x1;
    DDPCONbits.JTAGEN = 0;
    TRISAbits.TRISA4 = 0; // RA4 is output
    TRISBbits.TRISB4 = 1; // RB4 is input
    LATAbits.LATA4 = 0; // LED is off
    WDTCONbits.ON = 0;
    SPI1_init();
    __builtin_enable_interrupts();

    while (1) {
        _CP0_SET_COUNT(0); // set core timer to 0
        setVoltage(ChA, Aamp);
        setVoltage(ChB, Bamp);
        Aamp = sine[count];
        count++;
        Bamp++;
        while(_CP0_GET_COUNT()<(B_ticks/2)){;}
    }
}

