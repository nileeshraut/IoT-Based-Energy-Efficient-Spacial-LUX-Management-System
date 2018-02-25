				/* defines.h */

#ifndef __DEFINES_H__
#define __DEFINES_H__

#include<reg51.h>
/*LCD Port Pins*/
#define lcd_data P0
sbit rs=P3^4;
sbit rw=P3^5;
sbit en=P3^6;

/*LED1:- BULB Based On Environment Condition*/
sbit LED1=P1^0;

/*I2C SCL and SDA*/
sbit scl=P2^1;
sbit sda=P2^0;


/* spi defines for MCP3204 :CHANGE AS PER NEED*/
sbit clk=P2^3;
sbit Dout=P2^4;
sbit Din=P2^5;
sbit cs=P2^6;

#endif
