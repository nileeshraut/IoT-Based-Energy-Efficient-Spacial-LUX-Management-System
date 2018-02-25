                     /* i2cB.c */
#include<reg51.h>
//#include "types.h"
#include "delay.h"
#include "i2c.h"
#include "defines.h"

void i2cStart(void)
{
  sda=1; 
  scl=1;
  sda=0;
}

void i2cWrite(u8 dat)
{
  u8 i;
  for(i=0;i<8;i++)
  {
	scl=0;
	sda=dat&(0x80>>i)?1:0;
	scl=1;
  }
}

void i2cAck(void)
{
  scl=0; 
  sda=1; 
  scl=1;
  //while(sda);
}

void i2cStop(void)
{
  scl=0; 
  sda=0; 
  scl=1;
  sda=1;
}

void i2cReStart(void)
{
  scl=0;
  sda=1; 
  scl=1;
  sda=0;
}

void i2cNoAck(void)
{
  scl=0; 
  sda=1; 
  scl=1;
}	

unsigned char i2cRead(void)
{
  u8 i;
  u8 buff=0;
  for(i=0;i<8;i++)
  {
	scl=0;
    scl=1;
    //delay_us(1);
    if(sda)
      buff|=0x80>>i;
  }
  return buff;
}

void i2cDevWrite(u8 slaveAddr,u8 buffAddr,u8 dat)
{
	i2cStart();
	i2cWrite(slaveAddr);
	i2cAck();
	i2cWrite(buffAddr);
	i2cAck();
	i2cWrite(dat);
	i2cAck();
  i2cStop();
	delay_ms(10);
}	

unsigned char i2cDevRead(u8 slaveAddr,u8 buffAddr)
{
	u8 buff;
  i2cStart();
	i2cWrite(slaveAddr);
	i2cAck();
	i2cWrite(buffAddr);
	i2cAck();
	i2cReStart();
	i2cWrite(slaveAddr|1);
	i2cAck();
	buff=i2cRead();
	i2cNoAck();
	i2cStop();
	return buff;
}

unsigned int fun(void)
{
	u16 data_from_slave;
	u8 msb,lsb;
	i2cStart();
	i2cWrite(0x46);
	i2cAck();

	i2cWrite(0x10);
	i2cAck();
 	i2cStop();
	delay_ms(180);

	
  	i2cStart();
	i2cWrite(0x47);
	i2cAck();
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        	i2cAck();
		
	msb=i2cRead(); //MS-Byte READ
	i2cNoAck();
	
//	data_from_slave |=i2cRead();
	lsb=i2cRead();
	i2cNoAck();
	i2cStop();
	data_from_slave=msb;
	data_from_slave <<=8;
	data_from_slave|=lsb;


	return data_from_slave;
	
}
