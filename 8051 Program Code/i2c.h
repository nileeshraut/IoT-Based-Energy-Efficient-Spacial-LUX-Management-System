                  /* i2c.h */
#ifndef __I2C_H__
 #define __I2C_H__

#include "types.h"
void i2cStart(void);
void i2cRestart(void);
void i2cWrite(unsigned char);
void i2cAck(void);
void i2cNoAck(void);
void i2cStop(void);
unsigned char i2cRead(void);
unsigned int fun(void);
void i2cDevWrite(unsigned char,unsigned char,unsigned char);
unsigned char i2cDevRead(unsigned char,unsigned char);
//void i2cDevWrite2(unsigned char,u16,unsigned char);
//unsigned char i2cDevRead2(unsigned char,u16);

#endif
