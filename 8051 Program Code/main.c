#include "uart.h"
//#include "lcd.h"
#include "delay.h"
#include "mcp3204.h"
#include "types.h"
#include "i2c.h"
#include "defines.h"
#include "clock.h"
//#include <stdio.h>//-----LDR


main()
{
	unsigned int light_Status;
//------LDR VARIABLES----------//
	float f;	//---Value Read From LDR
//	char buf[10];//----LDR:Storing String For Sending Through UART


//-----RTC VARIABLES---------//
	unsigned char hr=0x00, min=0x00, sec=0x00,day=0x00,date=0x00,month=0x00,year=0x00;
	i2cDevWrite(0xd0,0x08,sec);
	i2cDevWrite(0xd0,0x09,min);
	i2cDevWrite(0xd0,0x0a,hr);
	i2cDevWrite(0xd0,0x0b,day);
	i2cDevWrite(0xd0,0x0c,date);
	i2cDevWrite(0xd0,0x0d,month);
	i2cDevWrite(0xd0,0x0e,year);
	Init_UART();
	LED1=0;
	while(1)
	{
		f=Read1_ADC_MCP3204(2);
		//TxStr_UART("LDR");
		//sprintf(buf, "%.2f", f);//Converting FLOAT to String and Storing it in "buf"
		//TxStr_UART(buf);	
		if(f>4.0)
		{
			LED1=1;//Active High LED
			light_Status=fun();
			if(light_Status>=3500)	
			{
				TxChar_UART('1');
				clock_start();
				RTC_display();
			}
			else
			{
				TxChar_UART('0');RTC_display();
				//TxStr_UART("WARNING!!!LIGHT NOT WORKING");
				//TxChar_UART('\r');
				//TxChar_UART('\n');
			}
			
		}
		else
		{
			LED1=0;//Active High LED
			TxChar_UART('2');//DAYYYYYYY
			clock_stop();
			RTC_display();
			//RTC_display();
			//TxStr_UART("!!! LIGHT IS OFF !!!");
		}//else
	delay_ms(500);	 
	}//while

}//main


