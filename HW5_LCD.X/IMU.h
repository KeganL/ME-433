#ifndef IMU_H
#define IMU_H

// control reg
#define CTRL1_XL 0x10 
#define CTRL2_G 0x11 
#define CTRL3_C 0x12

// output reg
#define OUT_TEMP_L 0x20
#define OUTX_L_XL 0x28


void initIMU(void);
unsigned char WHOAMI(void);


#endif
