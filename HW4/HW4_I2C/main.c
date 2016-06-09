#include "PIC_INIT.h"

int main(){
    //setup I2C
    __builtin_disable_interrupts();
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    BMXCONbits.BMXWSDRM = 0x0;
    INTCONbits.MVEC = 0x1;
    DDPCONbits.JTAGEN = 0;
    TRISAbits.TRISA4 = 0; // RA4 is output
    TRISBbits.TRISB4 = 1; // RB4 is input
    LATAbits.LATA4 = 0;			// LED is off
    WDTCONbits.ON = 0;
    i2c_master_setup();
    __builtin_enable_interrupts();     
    
    unsigned char data_read;
    initExpander();
    unsigned char data = 0b00000000;
    //LATAbits.LATA4 = 0;
    setExpander(SLAVE_ADDRESS, data,0x0A); // set G0 to high
    

    while (1) {   
        data_read = getExpander(SLAVE_ADDRESS, 0x09); /////
        data_read = data_read >> 7;
        data_read = data_read & 0b1;

        if (data_read == 1) {
            //LATAbits.LATA4 = 1;
            data = 0b00000001;
            setExpander(SLAVE_ADDRESS, data, 0x0A); /////

        } else if (data_read == 0) {
            data = 0b00000000;
            setExpander(SLAVE_ADDRESS, data, 0x0A); /////
            //LATAbits.LATA4 = 0;
            //            
        }
    }
}

