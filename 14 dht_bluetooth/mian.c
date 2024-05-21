#include "reg52.h"
#include "intrins.h"
#include <string.h>
#include "delay.h"
#include "dht.h"
#include "lcd1602.h"
#include "uart.h"

sbit relay = P1^0;

int main(){
	char *array;
	char *humi;
	char *temp;
	char Tp=0x02;
	char Hp=0x02;
	uart_init();
	//lcd1602
	Delay2000ms();
	lcdinit();
	Delay15ms();
	while(1){
		Delay2000ms();
		lcdinit();
		array=read_data();
		humi=dht_humi_show(array);
		temp=dht_temp_show(array);
		
		writedataline(Tp,1,temp);
		writedataline(Hp,2,humi);
	//	writedataline(Tp,1,"hello");
//		writedataline(Hp,2,"world");
		if(array[0] > 50){
			relay = 0;
		}else{
			relay = 1;
		}
		sendstring(temp);
		sendstring("\r\n");
		sendstring(humi);
		sendstring("\r\n");
	}
}
/*	
		sendbyte(array[2]/10+0x30);
		sendbyte(array[2]%10+0x30);
		sendstring("\r\n");
		sendstring("H:");
		sendbyte(array[0]/10 + 0x30);//43 a 
		sendbyte(array[0]%10 + 0x30);
		sendbyte('.');
		sendbyte(array[1]/10 + 0x30);//43 a 
		sendbyte(array[1]%10 + 0x30);	
		sendstring("\r\n");	
		sendstring("T:");
		sendbyte(array[2]/10 + 0x30);//43 a 
		sendbyte(array[2]%10 + 0x30);	
		sendbyte('.');
		sendbyte(array[3]/10 + 0x30);//43 a 
		sendbyte(array[3]%10 + 0x30);			
		sendstring("\r\n");	
*/		








	
