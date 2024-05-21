#include"reg52.h"
#include"intrins.h"

sbit sg90_con = P1^7;
int time=0;
int angle=0;
void Delay1000ms();
void Delay300ms();
void T0init();

int main(){
	void Delay300ms();
	T0init();
	while(1){
		angle = 2;
		Delay1000ms();
		angle = 4;
		Delay1000ms();
		angle = 6;
		Delay1000ms();
		angle = 4;
		Delay1000ms();
		angle = 2;
		Delay1000ms();
	}
}
void T0init(){
	//1 初始化
	TMOD &= 0xf0;
	TMOD |= 0x01;
	//2 计算需要的时间
	TL0 = 0x33;
	TH0 = 0xFE;
	//3 开始运行
	TR0 = 1;
	TF0 = 0;
	//打开中断
	ET0 = 1;
	//打开总线
	EA = 1;
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
void Delay300ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 3;
	j = 26;
	k = 223;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void overtime() interrupt 1
{
	time++;
	TL0 = 0x33;
	TH0 = 0xFE;
	if(time == 1){
		sg90_con = 1;
	}
	if(time == angle){
		sg90_con = 0;
	}
		
	if(time == 40){
		time = 0;
		sg90_con = 0;
				
	}
}
