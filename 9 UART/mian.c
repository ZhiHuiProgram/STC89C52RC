#include"reg52.h"
#include"intrins.h"
#include<string.h>
#include<stdlib.h>

#define num 12
#define SIZE 12
sbit led6 = P3^6;//D4 led
sbit led5 = P3^7;//D5 led
sfr AUXR = 0x8e;
int mark=0;

char cmd;
char array[num];
char reset[]="AT+RST";
char uart[]="AT+UART=9600,8,1,0,0\r\n";
code char wifi[]="AT+CWJAP=\"YXS1017\",\"yuanxueshe1017\"\r\n";
code char tcp[]="AT+CIPSTART=\"TCP\",\"192.168.1.210\",8880\r\n";
char TCMS[]  = "AT+CIPMODE=1\r\n";
char SJCS[]  = "AT+CIPSEND\r\n";

void uart_init();
void Delay2000ms();
void Delay3ms();
void sendbyte(char data1);
void sendstring(char *pp);
void INTRinit();
void INTR();

//char cmd[SIZE];

void main(){
	uart_init();
	INTRinit();
	led6 = 1;
	mark = 0;
	Delay2000ms();
	while(1){
		led5 = 0;
		Delay2000ms();
	if(mark == 0){
		led6 = 0;
	//Delay2000ms();
		//sendstring(reset);
//		sendstring("fuck!\r\n");
		//Delay2000ms();
		//sendstring(uart);
		//Delay2000ms();
		sendstring(wifi);
		Delay2000ms();
			Delay2000ms();
					Delay2000ms();
		sendstring(tcp);
		Delay2000ms();
				Delay2000ms();
					Delay2000ms();
		sendstring(TCMS);
		Delay2000ms();
				Delay2000ms();
					Delay2000ms();
		sendstring(SJCS);
		Delay2000ms();
				Delay2000ms();
							Delay2000ms();
		led5 = 0;
		mark =1;
	}else{
		sendstring("fuck!\r\n");
				Delay2000ms();
	}
	}
}
void INTRinit(){
	EA = 1;
	ES = 1;
}

void INTR() interrupt 4{
	static int i=0;
	if(RI == 1){
		RI = 0;
		array[i] = SBUF;
		i++;
		cmd = SBUF;
		if(strstr(array,"open")){
			SBUF = 'A';
			memset(array,'\0',num);
		}else if(strstr(array,"close")){
			SBUF = 'B';
			memset(array,'\0',num);
		}
	}
}

void Delay2000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 15;
	j = 2;
	k = 235;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void Delay3ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 33;
	j = 66;
	do
	{
		while (--j);
	} while (--i);
}
void uart_init(){
	AUXR = 0X01;
	SCON = 0x50;
	TMOD &= 0x0f;
	TMOD |= 0x20;
	TH1 = 0XFD;
	TH1 = 0XFD;
	TR1 = 1;
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