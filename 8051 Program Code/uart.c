#include<reg51.h>
#define check 0

void Init_UART(void)
{
	SCON=0x50;
	TMOD=0x20;
	TH1=253;//9600@11.0592MHz
	#if check
		PCON|=1<<7;//SMOD=1
	#endif
	TR1=1;
}

void TxChar_UART(char ch)
{
	SBUF=ch;
	while(TI==0);
	TI=0;
}
/*void TxStr_UART(char *p)
{
	while(*p)
		TxChar_UART(*p++);	
}
void n_line()  //---Function for new line in Proteius Virtual Terminal
{
	TxChar_UART('\r');
	TxChar_UART('\n');
}*/
