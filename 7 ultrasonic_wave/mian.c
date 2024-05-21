#include"reg52.h"
#include"intrins.h"
sbit D1 = P1^0;
sbit D2 = P1^1;
sbit D3 = P1^2;
sbit D4 = P1^3;
sbit D5 = P1^4;
sbit D6 = P1^5;
sbit D7 = P1^6;
sbit D8 = P1^7;
sbit trig = P2^5;
sbit echo = P2^6;
void Delay30ms();
void Delay15us();
void steering_engine();
void T0init(){
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TH0 =0;
	TL0 =0;
}
void startHC(){
	trig = 0;
	trig = 1;
	Delay15us();
	trig = 0;
}
void main(){
	int lednumber=0;
	double distance;
	double time;
	T0init();
	while(1){
		Delay30ms();
		startHC();
		while(echo == 0);
		TR0 = 1;
		while(echo == 1);
		TR0 = 0;
		time = (TL0+TH0*256)* 1.085;
		distance = time*0.017;
		lednumber = distance/10;
		if(lednumber<256){
			P1 = lednumber;
		}else {
			P1 = 0x00;
		}
		TH0 = 0;
		TL0 = 0;
	}
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
