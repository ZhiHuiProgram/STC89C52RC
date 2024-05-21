#include"reg52.h"
#include"intrins.h"
sbit vibrate = P3^2;

sbit D6       = P3^6;//?????(???),????led2??P3?IO???6?
sbit key3      = P2^1;
sbit trig     = P1^5;
sbit echo     = P1^6;
sbit sg90_con = P1^1;
sbit beep     = P2^0;
sbit remote_con = P2^6;

int steering_num=0;
int angle=0;
double distance;
double time;
char mark_vibrate = 0;
char angle_bak=2;

void Delay30ms();
void Delay15us();
void Delay2000ms();
void Delay150ms();
void Delay500ms();
void steering_engine();
void T0init();
void T1init();
double getdistance();
void startHC();
void int0_vibrate();

void main(){
	char n;
	double dis;
	T0init();
	T1init();
	angle = 2;      //?????0?,0.5ms,??1??0.5,???
	steering_num = 0;
	EX0 = 1;
	IT0 = 0;
	while(1){
		Delay30ms();
		dis = getdistance();
			if( remote_con == 1 ){
		
				angle = 4;
				D6 = 0;
				beep = 0;
				for(n=0;n<2;n++)
					Delay150ms();
				beep = 1;
				Delay2000ms();
				steering_num= 1;
				mark_vibrate =0; 
				angle_bak = angle;

		}else {
			angle = 2;
			steering_num= 0;
			D6 = 1; 
			angle_bak = angle;
			Delay30ms();
		}
		TH1 = 0;
		TL1 = 0;
	}
}
void int0_vibrate() interrupt 0
{
	mark_vibrate = 1;
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
void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void Delay150ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 2;
	j = 13;
	k = 237;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


