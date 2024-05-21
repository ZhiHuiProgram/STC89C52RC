#include"reg52.h"
#include"intrins.h"
void Delay100ms();
sbit ledD5 = P3^7;
sbit ledD6 = P3^6;
sbit key1 = P2^1;
sbit key2 = P2^0;
void main(){
	ledD5 = 1;
	ledD6 = 0;
	while (1){
		Delay100ms();
		if(key1 == 0){
			ledD5 = !ledD5;
			ledD6 = !ledD6;
		}else if (key2 == 0){
			ledD5 = 1;
			ledD6 = 0;
		}
	}

}
void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}