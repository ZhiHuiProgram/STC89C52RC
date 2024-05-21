#include"reg52.h"
#include"intrins.h"
#include<string.h>
#include<stdlib.h>

#define num 12
sbit led6 = P3^6;//D4 led
sbit led5 = P3^7;//D5 led
sfr AUXR = 0x8e;
int mark=0;


char array[num];
char send_ok=0;
char wifi_connect=0;
char reset[]="AT+RST";
char uart[]="AT+UART=9600,8,1,0,0\r\n";
code char wifi[]="AT+CWJAP=\"YXS1017\",\"yuanxueshe1017\"\r\n";
code char tcp[]="AT+CIPSTART=\"TCP\",\"192.168.1.210\",8880\r\n";
char TCMS[]  = "AT+CIPMODE=1\r\n";
char SJCS[]  = "AT+CIPSEND\r\n";

void uart_init();
void Delay2000ms();
void Delay3ms();
void Delay1000ms();
void sendbyte(char data1);
void sendstring(char *pp);
void INTRinit();
void INTR();


void main(){
	uart_init();
	INTRinit();
	Delay2000ms();
	
	sendstring(wifi);
	while(!send_ok);
	send_ok=0;
	
	sendstring(tcp);
	while(!send_ok);
	send_ok=0;
	
	sendstring(TCMS);
	while(!send_ok);
	send_ok=0;
	
	sendstring(SJCS);

	Delay2000ms();
	while(1){
		sendstring("fuck!\r\n");
				Delay2000ms();
	}
}

void INTRinit(){
	EA = 1;
	ES = 1;
}

void INTR() interrupt 4{
	static char i=0;
	char test;
	if(RI == 1){
		RI = 0;
		test = SBUF;
		if(test == 'W' || test == 'O' || test =='L' || test == 'F'){
			i=0;
		}
		array[i] = test;
		i++;
		if(array[0] == 'W' && array[5] == 'C')
		{
			wifi_connect=1;
			memset(array,'\0',num);
		}
		if(array[0] == 'O' && array[1] == 'K')
		{
			send_ok=1;
			memset(array,'\0',num);
		}
		if(array[0] == 'L' && array[1] == '1')
		{
			led5=0;
			memset(array,'\0',num);
		}
		if(array[0] == 'L' && array[1] == '0')
		{
			led5=1;
			memset(array,'\0',num);
		}
		if(array[0] == 'F' && array[3] == 'A')
		{
			for(i;i<5;i++){
				led6=0;
				Delay1000ms();
				led6=1;
				Delay1000ms();
			}
			sendstring(reset);
			memset(array,'\0',num);
		}
		if(i == num){
			i=0;
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
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
