 #include"reg52.h"
 sbit key1 = P2^1;
 sbit led1 = P3^6;
 sbit led2 = P3^7;
  void Delay200ms();
 void main()
 {
 	while(1){
 	led1 = 0;
	led2 = 1;
	Delay200ms();
	led1 = 1;
	led2 = 0;
	Delay200ms();
	}
 }
void Delay200ms()		//@11.0592MHz
{
	unsigned char i, j, k;

//	_nop_();
	i = 2;
	j = 103;
	k = 147;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
