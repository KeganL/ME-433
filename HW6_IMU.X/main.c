#include "PIC_INIT.h"
#include "IMU.h"


#define CS LatBbits.LatB15

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
    TRISAbits.TRISA4 = 0; //choose ra4 to be output pin (led)
    TRISBbits.TRISB4 = 1;
    LATAbits.LATA4 = 0;

    //oc pins
    RPA0Rbits.RPA0R = 0b0101; // use A0 pin for OC1
    RPA1Rbits.RPA1R = 0b0101; // use A1 pin for OC2

    i2c_master_setup();

    // initialize IMU
    initIMU();
//    if (WHOAMI() != 0b01101001) {
//        LATAbits.LATA4 = 1;
//    }

    // Set up Peripheral Timer2, OC1 and OC2
    T2CONbits.TCKPS = 0b011; // Timer2 prescaler N = 8
    PR2 = 5999; // Frequency = 1kHz
    TMR2 = 0; // Timer2 initial count 0;

    OC1CONbits.OCM = 0b110; // PWM mode without fault pin
    OC1CONbits.OCTSEL = 0; // Use Timer2 for comparison
    OC1RS = 3000; // Duty cycle 50%
    OC1R = 3000;

    OC2CONbits.OCM = 0b110; // PWM mode without fault pin
    OC2CONbits.OCTSEL = 0; // Use Timer2 for comparison
    OC2RS = 3000; // Duty cycle 50%
    OC2R = 3000;

    T2CONbits.ON = 1; // Turn on Timer2
    OC1CONbits.ON = 1; // Turn on Output Control 1
    OC2CONbits.ON = 1; // Turn on Output Control 2

    __builtin_enable_interrupts();

    char length = 6;
    unsigned char accel_data[length];
    short x_accel, y_accel;

    while (1) {

        _CP0_SET_COUNT(0);

        i2c_multi(IMU_ADDRESS, OUTX_L_XL, accel_data, length);
        x_accel = (accel_data[1] << 8) | accel_data[0];
        y_accel = (accel_data[3] << 8) | accel_data[2];
        
        if (x_accel > 10){
            LATAbits.LATA4 = 1;
        }
        else{
            LATAbits.LATA4 = 0;
        }

        OC1RS = x_accel * 3000 / 16384 + 2999;
        OC2RS = y_accel * 3000 / 16384 + 2999;

        while (_CP0_GET_COUNT() < 480000) {
            ; // Wait for 20 ms
        }


    }
}