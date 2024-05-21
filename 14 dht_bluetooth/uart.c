#include "reg52.h"
#include <string.h>
#include <delay.h>
sbit relay = P1^0;
sbit led6 = P1^2;//D4 led
sbit led5 = P1^3;//D5 led
sfr AUXR = 0x8e;

char sbufarray[8];

int num= 8;
void uart_init(){
	AUXR = 0X01;
	SCON = 0x50;
	TMOD &= 0xf0;
	TMOD |= 0x20;
	TH1 = 0XFD;
	TH1 = 0XFD;
	TR1 = 1;
	EA = 1;
	ES = 1;
}
void sendbyte(char data1){
	SBUF = data1;
	while(!TI);
	TI = 0;
}
void sendstring(char *pp){
	while(*pp != '\0'){
		sendbyte(*pp);
		pp++;
	}
}
void INTR() interrupt 4{
	static int i=0;
	char cmd;
	if(RI == 1){
		RI = 0;
		cmd = SBUF;
		if(cmd == ':'){
			i=0;
		}
		sbufarray[i] = SBUF;
		i++;
		
		if(sbufarray[0]==':' && sbufarray[1]=='o' && sbufarray[2]=='p'){
			led5 = 0;
			relay = 0;
			Delay2000ms();
			memset(sbufarray,'\0',num);
		}
		if(sbufarray[0]==':' && sbufarray[1]=='c' && sbufarray[2]=='l'){
			led5 = 1;
			relay = 1;
			Delay2000ms();
			memset(sbufarray,'\0',num);
		}
	}
}
