#include <reg51.h>
#include "types.h"
#include "defines.h"


float Read1_ADC_MCP3204(u8 channelNo)
{
  u16 adc_val=0;
  float temp;
  bit d0,d1;
  s8 i;
	
  d0=channelNo&1;
  d1=(channelNo>>1)&1;

  cs=clk=Din=Dout=1;
  cs=0;
//MASTER TO SLAVE     
  //7 clk pulse to sample analog signal,& issue NULL bit
  clk=0; clk=1;
  clk=0; clk=1;
  clk=0; clk=1;
  
  Din=d1;
  clk=0; clk=1;

  Din=d0;
  clk=0; clk=1;
	
	clk=0; clk=1;
  clk=0; clk=1;


//SLAVE TO MASTER
  //read 12 bit converted value MSB first
  for(i=11;i>=0;i--)
  {
	  clk=0;
	  if(Dout)
	    adc_val|=(1<<i); //1 by 1 bit is receiving and thus by shifting we are storing it
	  clk=1;
   }
   cs=1;

   temp=((adc_val*5.0)/4096);
   return temp;
}
