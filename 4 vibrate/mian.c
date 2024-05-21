#include"reg52.h"
#include"intrins.h"
sbit vibrate = P3^3;
sbit led5 = P3^7;
sbit led6 = P3^6;
sbit relay = P1^1;
void Delay2000ms();
void main(){
	while(1){
		if(vibrate == 0){
			led5 = 0;
			relay = 0;
			Delay2000ms();
		}else if(vibrate ==1){
			led5 = 1;
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
