#include"reg52.h"
#include"intrins.h"
#include<string.h>
#define lcddata P2

sbit RS=P0^7;
sbit RW=P0^6;
sbit EN=P0^5;


void Delay15ms();
void Delay5ms();
void write_data(char cmd);
void write_command(char cmd);
void lcdinit();
void check_busy();
void writedataline(char position , char array , char latter[]);

void main(){
	char position = 0x80+0x05;
	char latter[] ="wozhen" ;

	lcdinit();
	Delay15ms();
	writedataline(position , 2,latter);
	writedataline(position , 1,latter);
//	write_command(position);
//	write_data(latter);
//	WriteCommandLCD(position);
//	WriteDataLCD(latter);
	
}
void writedataline(char position , char array , char latter[]){
	char arrays;
	int i = 0;
	switch(array){
		case 1:
			write_command(position);
			while(*latter){
				write_data(*latter);
				latter++;
			}
			break;
		case 2:
			arrays = position+0x40;
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
