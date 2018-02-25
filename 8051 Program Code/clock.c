#include "uart.h"
#include "i2c.h"
unsigned char hr=0x00, min=0x00, sec=0x00,day=0x00,date,month,year
	,clock_flag=1,i;

void Read_RTC_to_RAM(void) //Read from RTC Control Reg. & Store into RTC_RAM
{
	//---READ VALUES FROM RTC Control Register----//
			sec=i2cDevRead(0xd0,0x00);
			min=i2cDevRead(0xd0,0x01);	
			hr=i2cDevRead(0xd0,0x02);	
			day=i2cDevRead(0xd0,0x03);
			date=i2cDevRead(0xd0,0x04);
			month=i2cDevRead(0xd0,0x05);
			year=i2cDevRead(0xd0,0x06);
		
	//---STORE UPDATED VALUE TO RTC_RAM---//
			i2cDevWrite(0xd0,0x08,sec);
			i2cDevWrite(0xd0,0x09,min);
			i2cDevWrite(0xd0,0x0a,hr);
			i2cDevWrite(0xd0,0x0b,day);
			i2cDevWrite(0xd0,0x0c,date);
			i2cDevWrite(0xd0,0x0d,month);
			i2cDevWrite(0xd0,0x0e,year);
}


void clock_start(void)
{
	if(clock_flag==1)
	{
	//---READ VALUES FROM RTC_RAM(BUFFER)----//
			sec=i2cDevRead(0xd0,0x08);	
			min=i2cDevRead(0xd0,0x09);
			hr=i2cDevRead(0xd0,0x0a);
			day=i2cDevRead(0xd0,0x0b);
			date=i2cDevRead(0xd0,0x0c);
			month=i2cDevRead(0xd0,0x0d);
			year=i2cDevRead(0xd0,0x0e);
			
	//---UPDATE IT TO RTC Control REGISTER---//		
			i2cDevWrite(0xd0,0x00,sec);	
			i2cDevWrite(0xd0,0x01,min);
			i2cDevWrite(0xd0,0x02,hr);
			i2cDevWrite(0xd0,0x03,day);
			i2cDevWrite(0xd0,0x04,date);
			i2cDevWrite(0xd0,0x05,month);
			i2cDevWrite(0xd0,0x06,year);
	}
	Read_RTC_to_RAM();
	clock_flag=0;
}

void clock_stop(void)
{
	if(clock_flag==0)
	{
		Read_RTC_to_RAM();
	}
	clock_flag=1;
	return ;
}

void RTC_display(void)
{
			//TxStr_UART("LIGHT ON TIME:");
			hr=i2cDevRead(0xd0,0x0a);
			i=(hr/16)+48;
			TxChar_UART(i);
			i=(hr%16)+48;
			TxChar_UART(i);
			//TxChar_UART(':');

			min=i2cDevRead(0xd0,0x09);
			i=(min/16)+48;
			TxChar_UART(i);
			i=(min%16)+48;
			TxChar_UART(i);
			//TxChar_UART(':');

			sec=i2cDevRead(0xd0,0x08);
			i=(sec/16)+48;
			TxChar_UART(i);
			i=(sec%16)+48;
			TxChar_UART(i);
			TxChar_UART('$');
			//n_line();
			
		
}