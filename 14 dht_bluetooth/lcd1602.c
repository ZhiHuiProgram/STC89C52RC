#include "intrins.h"
#include "reg52.h"
#include "lcd1602.h"
#include "delay.h"
#define lcddata P2
sbit RS=P0^7;
sbit RW=P0^6;
sbit EN=P0^5;
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