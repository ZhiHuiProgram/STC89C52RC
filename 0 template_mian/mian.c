#include"reg52.h"
#include"intrins.h"
sbit led6 = P3^6;//D4 led
sbit led5 = P3^7;//D5 led
void Delay2000ms()	;
int main(){
		
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
