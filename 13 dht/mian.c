#include "reg52.h"
#include "intrins.h"
#include <string.h>
#define lcddata P2
sbit led6 = P1^5;//D4 led
sbit led5 = P1^7;//D5 led
sbit dht = P1^6;
sbit RS=P0^7;
sbit RW=P0^6;
sbit EN=P0^5;
sbit relay = P1^0;
sfr AUXR = 0x8e;

//dht11
char array[5];
char temperature[16];
char humidity[16];
void dht11show();
//dht11
void check_connect();
void read_data();
void Delay2000ms();
void Delay60us();
void Delay20ms();
void Delay30ms();
void Delay1000ms();
void Delay40us();
void uart_init();
void sendstring(char *pp);
void sendbyte(char data1);
//lcd1602
void Delay15ms();
void Delay5ms();
void write_data(char cmd);
void write_command(char cmd);
void lcdinit();
void check_busy();
void writedataline(char position , char array , char latter[]);

int main(){
	char Tp=0x02;
	char Hp=0x02;
	uart_init();
	//lcd1602
	Delay2000ms();
	lcdinit();
	Delay15ms();
	while(1){
		Delay1000ms();
		lcdinit();
		read_data();
		dht11show();
		writedataline(Tp,1,temperature);
		writedataline(Hp,2,humidity);
	//	writedataline(Tp,1,"hello");
//		writedataline(Hp,2,"world");
		if(array[0] > 50){
			relay = 0;
		}else{
			relay = 1;
		}
	}
}
/*	
		sendbyte(array[2]/10+0x30);
		sendbyte(array[2]%10+0x30);
		sendstring("\r\n");
		sendstring("H:");
		sendbyte(array[0]/10 + 0x30);//43 a 
		sendbyte(array[0]%10 + 0x30);
		sendbyte('.');
		sendbyte(array[1]/10 + 0x30);//43 a 
		sendbyte(array[1]%10 + 0x30);	
		sendstring("\r\n");	
		sendstring("T:");
		sendbyte(array[2]/10 + 0x30);//43 a 
		sendbyte(array[2]%10 + 0x30);	
		sendbyte('.');
		sendbyte(array[3]/10 + 0x30);//43 a 
		sendbyte(array[3]%10 + 0x30);			
		sendstring("\r\n");	
*/		

void check_connect(){
	dht=1;
	dht = 0;
	Delay30ms();
	dht = 1;
//	Delay60us();
	while(dht);
	while(!dht);
	while(dht);

}
void read_data(){
	int i,j;
	char tmp;
	char flag;
	check_connect();
	for(i=0;i<5;i++){
		for(j=0;j<8;j++){
			while(!dht);
			Delay40us();
			if(dht == 1){
				flag=1;
				while(dht);
	//		}if(dht == 0){
			}else{
				flag=0;
			}
			tmp = tmp << 1;
			tmp |= flag;
		}
		array[i] = tmp;
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
void Delay20ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 36;
	j = 217;
	do
	{
		while (--j);
	} while (--i);
}
void Delay60us()		//@11.0592MHz
{
	unsigned char i;

	i = 25;
	while (--i);
}
void Delay40us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 15;
	while (--i);
}
void uart_init(){
	AUXR = 0X01;
	SCON = 0x40;
	TMOD &= 0xf0;
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
void dht11show(){
	temperature[0]='T';
	temperature[1]=':';
	temperature[2]=array[2]/10+0x30;
	temperature[3]=array[2]%10+0x30;
	temperature[4]='.';
	temperature[5]=array[3]/10+0x30;
	temperature[6]=array[3]%10+0x30;
	temperature[7]='C';
	humidity[0]='H';
	humidity[1]=':';
	humidity[2]=array[0]/10+0x30;
	humidity[3]=array[0]/10+0x30;
	humidity[4]='.';
	humidity[5]=array[1]/10+0x30;
	humidity[6]=array[1]/10+0x30;
	humidity[7]='%';
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
void Delay30ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 54;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}
void writedataline(char position , char array , char latter[]){
	char arrays;
	int i = 0;
	switch(array){
		case 1:
			arrays = position+0x80;
			write_command(arrays);
			while(*latter){
				write_data(*latter);
				latter++;
			}
			break;
		case 2:
			arrays = position+0x40+0x80;
			write_command(arrays);
/*		while(i<len){
			write_data(latter[i]);
		}*/
			while(*latter){
				write_data(*latter);
				latter++;
			}
			break;
	}
}
void write_data(char cmd){
	check_busy();
	RS =1;
	RW = 0;
	
		EN = 0;
	_nop_();
	lcddata = cmd;
		_nop_();
	EN = 1;
	_nop_();
	_nop_();
	EN = 0;
	_nop_();
}
void write_command(char cmd){
	check_busy();
	RS =0;
	RW = 0;
	
	EN = 0;
	_nop_();
	lcddata = cmd;
		_nop_();
	EN = 1;
	_nop_();
	_nop_();
	EN = 0;
	_nop_();
}
void lcdinit(){
	Delay15ms();
	write_command(0x38);
	Delay5ms();
	write_command(0x38);
	Delay5ms();
	write_command(0x38);
	Delay5ms();
	write_command(0x38);
	write_command(0x08);
	write_command(0x01);
	write_command(0x06);
	write_command(0x0c);
	
}
void check_busy(){
	char tmp = 0x80;
	lcddata = 0x80;
//	while(read_command(tmp) & 0x80);
	while(tmp & 0x80){
		RS =0;
		RW = 1;
	
		EN = 0;
		_nop_();

		EN = 1;
		_nop_();
		_nop_();
		tmp = lcddata;
		EN = 0;
		_nop_();
	}
}
void Delay15ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 27;
	j = 226;
	do
	{
		while (--j);
	} while (--i);
}
void Delay5ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 9;
	j = 244;
	do
	{
		while (--j);
	} while (--i);
}
	
