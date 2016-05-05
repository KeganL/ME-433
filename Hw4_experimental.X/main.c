#include "PIC32_INIT.h"

void initExpander() {
}

int main() {

    __builtin_disable_interrupts();

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;
    
    // do your TRIS and LAT commands here
    TRISAbits.TRISA4 = 0; // Set RA4 to output (green LED)
    TRISBbits.TRISB4 = 1; // Set RB4 to input (user button)
    LATAbits.LATA4 = 0; //Set green LED to 1 to start 
    //initSPI1();
    i2c_master_setup();
    
    
    __builtin_enable_interrupts();
    
    unsigned char data_read;
    

    init_exp();
    unsigned char data = 0b00000000;
    LATAbits.LATA4 = 0;
    setExpander(EXPADD, data,0x0A); // set G0 to high initially

    //write_exp(EXPADD, data,0x0A);
    //data_read = read_exp(EXPADD,0x09);
    //data_read = data_read >> 7;
    //data_read = data_read & 0b1;
    //if (data_read == 0){
    //    LATAbits.LATA4 = 1;
    //}
    //data = 0b00000000;
    //write_exp(EXPADD, data,0x0A);
    
    while(1){
        
        //LATAbits.LATA4 = 1;
        //write_exp(EXPADD, data,0x0A);
        //data_read = read_exp_pin(7);
        data_read = getExpander(EXPADD,0x09); /////
        data_read = data_read >> 7;
        data_read = data_read & 0b1;
        //data_read = 1;
        //LATAbits.LATA4 = 1; 
        if (data_read == 1){
            LATAbits.LATA4 = 1; 
//            //set_exp_pin(0,1);
//            
            data = 0b00000001;
            setExpander(EXPADD, data,0x0A); /////
//            LATAbits.LATA4 = 1;
        }
        else if (data_read == 0){
//            LATAbits.LATA4 = 0; 
            data = 0b00000000;
            setExpander(EXPADD,data,0x0A); /////
//            //set_exp_pin(0,0);
            LATAbits.LATA4 = 0;
//            
        }
    }


}
