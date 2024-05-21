#include"reg52.h"
#include"intrins.h"
sbit led1 = P1^0;//D4 led
sbit led2 = P1^1;//D5 led
sbit led3 = P1^2;
sbit led4 = P1^3;
sbit led5 = P1^4;
sbit led6 = P1^5;
sbit led7 = P1^6;
sbit led8 = P1^7;
int time=0;
void Delay1000ms();
void overtime() interrupt 1
{
	time++;
	TL0 = 0x00;
	TH0 = 0xDC;
	if(time == 100){
		time = 0;
		led1 = !led1;
		led2 = !led2;
		led3 = !led3;
		led4 = !led4;
				
	}
}
int main(){
	led1 = 0;
	led2 = 1;
	led3 = 0;
	led4 = 1;
	led5 = 0;
	led6 = 1;
	led7 = 0;
	led8 = 1;
	//1 初始化
	TMOD &= 0xf0;
	TMOD |= 0x01;
	//2 计算需要的时间
	TL0 = 0x00;
	TH0 = 0xDC;
	//3 开始运行
	TR0 = 1;
	TF0 = 0;
	//打开中断
	ET0 = 1;
	//打开总线
	EA = 1;
	while(1){
		led5 = 1;
		led6 = 0;
		led7 = 1;
		led8 = 0;
		Delay1000ms();
		led5 = 0;
		led6 = 1;
		led7 = 0;
		led8 = 1;
		Delay1000ms();
	}
}
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
