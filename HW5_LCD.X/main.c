#include "PIC_INIT.h"
#include "ILI9163C.h"
#include "IMU.h"
#include "i2c_master.h"



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
    TRISAbits.TRISA4 = 0;
    TRISBbits.TRISB4 = 1;
    
    
    //initialize
    SPI1_init();
    LCD_init();
    i2c_master_setup();
    initIMU();
    
    if (WHOAMI() != 0b01101001) {
    LATAbits.LATA4 = 1;}
    
    __builtin_enable_interrupts();
    
    //text input
    LCD_clearScreen(BLACK);
    
//    int x = 28;
//    int y = 32;  
//    int xscale = 15;
//    int yscale = 10;
//    char data[100];
//    sprintf(data, "Hello world");
//    LCD_drawArray(x, y, RED, data);
//    sprintf(data, " %d", 1337);
//    LCD_drawArray(x + 55, y, GREEN, data);
//    sprintf(data, "!");
//    LCD_drawArray(x + 80, y, CYAN, data);
    
    char msg[100];
    int xscale = 15;
    int yscale = 10;
    int x = 3;
    int y = 10;
    
    sprintf(msg,"Accelerometer: ");
    LCD_drawArray(x, y, GREEN, msg);
    sprintf(msg,"X = ");
    LCD_drawArray(x, y + yscale, GREEN, msg);
    sprintf(msg,"Y = ");
    LCD_drawArray(x, y + 2*yscale, GREEN, msg);
    sprintf(msg,"Z = ");
    LCD_drawArray(x, y + 3*yscale, GREEN, msg);
    sprintf(msg,"Gyroscope: ");
    LCD_drawArray(x, y + 4*yscale, BLUE, msg);
    sprintf(msg,"X = ");
    LCD_drawArray(x, y + 5*yscale, BLUE, msg);
    sprintf(msg,"Y = ");
    LCD_drawArray(x, y + 6*yscale, BLUE, msg);
    sprintf(msg,"Z = ");
    LCD_drawArray(x, y + 7*yscale, BLUE, msg);
    sprintf(msg,"Temperature: ");
    LCD_drawArray(x, y + 8*yscale, RED, msg);
    sprintf(msg,"T = ");
    LCD_drawArray(x, y + 9*yscale, RED, msg);
    
    int length = 14;
    unsigned char IMU_data[length];
    short x_accel, y_accel, z_accel, x_gyro, y_gyro, z_gyro, temp;

        i2c_multi(IMU_ADDRESS, OUT_TEMP_L, IMU_data, length);
        x_accel = (IMU_data[1] << 8 )| IMU_data[0];
        y_accel = (IMU_data[3] << 8 )| IMU_data[2];
        z_accel = (IMU_data[5] << 8 )| IMU_data[4];
        x_gyro = (IMU_data[7] << 8 )| IMU_data[6]; 
        y_gyro = (IMU_data[9] << 8 )| IMU_data[8];
        z_gyro = (IMU_data[11] << 8 )| IMU_data[10];
        temp = (IMU_data[13] << 8 )| IMU_data[12];
     
        
    while(1){
        _CP0_SET_COUNT(0);
    
        sprintf(msg," %d",x_accel);
        LCD_drawArray(x + xscale, y + yscale, GREEN, msg);
        sprintf(msg," %d",y_accel);
        LCD_drawArray(x + xscale, y + 2*yscale, GREEN, msg);
        sprintf(msg," %d",z_accel);
        LCD_drawArray(x + xscale, y + 3*yscale, GREEN, msg);
        sprintf(msg," %d",x_gyro);
        LCD_drawArray(x + xscale, y + 5*yscale, BLUE, msg);
        sprintf(msg," %d",y_gyro);
        LCD_drawArray(x + xscale, y + 6*yscale, BLUE, msg);
        sprintf(msg," %d",z_gyro);
        LCD_drawArray(x + xscale, y + 7*yscale, BLUE, msg);
        sprintf(msg," %d",temp);
        LCD_drawArray(x + xscale, y + 9*yscale, RED, msg);
        
        while(_CP0_GET_COUNT() < 480000) { 
        ;   
        
        
        }

    }



}