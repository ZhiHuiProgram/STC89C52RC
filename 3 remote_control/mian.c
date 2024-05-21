#include"reg52.h"
#include"intrins.h"
//sbit led5 = P3^7;
//sbit led6 = P3^6;
sbit relay = P1^1;
sbit remote_D0 = P1^5;
sbit remote_D1 = P1^6;
sbit vibrate = P2^1;
void Delay2000ms();
void main(){
	int mark;
	while(1){
		if(remote_D0 == 1){
			mark = 0;
			relay = 0;
			Delay2000ms();
			relay = 1;
//			led5 = 0;
//			led6 = 1;
		}
		if(remote_D1 == 1){
//			led5 = 1;
//			led6 = 0;
      relay = 1; 
			mark = 1;
		}
		if( mark == 0){
			if( vibrate == 0){
				relay = 0;
				Delay2000ms();
			}
		//	Delay2000ms();
		}else if(mark == 1){
			relay = 1;
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
