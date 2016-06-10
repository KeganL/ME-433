#include "PIC_INIT.h"
#include "ILI9163C.h"



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
    
    
    //text input
    LCD_clearScreen(BLACK);
    
    int x = 28;
    int y = 32;
    
    int xscale = 15;
    int yscale = 10;
    char data[100];
    sprintf(data, "Hello world");
    LCD_drawArray(x, y, RED, data);
    sprintf(data, " %d", 1337);
    LCD_drawArray(x + 55, y, GREEN, data);
    sprintf(data, "!");
    LCD_drawArray(x + 80, y, CYAN, data);
    
    
    
}