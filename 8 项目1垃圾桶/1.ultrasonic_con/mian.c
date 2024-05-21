#include"reg52.h"
#include"intrins.h"
int steering_num=0;
int angle=0;
double distance;
double time;
sbit sg90_con = P3^1;
sbit D6 = P1^6;
sbit trig = P2^5;
sbit echo = P2^6;
void Delay30ms();
void Delay15us();
void Delay2000ms();
void steering_engine();
void T0init();
void T1init();
double getdistance();
void startHC();
void main(){
	double dis;
	T0init();
	T1init();
	while(1){
		Delay30ms();
		dis = getdistance();
		if(dis >=20){
			angle = 2;
			steering_num= 0;
			D6 = 1;
		}else if(dis <20){
			angle = 5;
			D6 = 0;
			Delay2000ms();
			steering_num= 1;
		}
		TH1 = 0;
		TL1 = 0;
	}
}
void startHC(){
	trig = 0;
	trig = 1;
	Delay15us();
	trig = 0;
}
double getdistance(){
		startHC();
		while(echo == 0);
		TR1 = 1;
		while(echo == 1);
		TR1 = 0;
		time = (TL1+TH1*256)* 1.085;
		distance = time*0.017;
		return distance;
}
void steering_engine() interrupt 1
{
	steering_num++;
	TL0 = 0x33;
	TH0 = 0xFE;
	if(steering_num == 1){
		sg90_con = 1;
	}
	if(steering_num == angle){
		sg90_con = 0;
	}
		
	if(steering_num == 40){
		steering_num = 0;
		sg90_con = 0;
				
	}
}
void T0init(){
	TMOD &= 0x0f;
	TMOD |= 0x10;
	TH1 =0;
	TL1 =0;
}
void T1init(){
	TMOD &= 0xf0;
	TMOD |= 0x01;
	//2 计算需要的时间
	TL0 = 0x33;
	TH0 = 0xFE;
	TR0 = 1;
	TF0 = 0;
	//打开中断
	ET0 = 1;
	//打开总线
	EA = 1;
}
void Delay15us()		//@11.0592MHz
{
	unsigned char i;

	i = 4;
	while (--i);
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

