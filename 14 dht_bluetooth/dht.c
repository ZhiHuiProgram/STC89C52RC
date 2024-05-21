#include "delay.h"
#include "reg52.h"
#include "dht.h"
sbit dht = P1^6;
char array[5];
char temperature[16];
char humidity[16];


char * read_data(){
	int i,j;
	char tmp;
	char flag;
	check_connect();
	for(i=0;i<5;i++){
		for(j=0;j<8;j++){
			while(!dht);
			Delay40us();
			if(dht == 1){
				flag=1;
				while(dht);
	//		}if(dht == 0){
			}else{
				flag=0;
			}
			tmp = tmp << 1;
			tmp |= flag;
		}
		array[i] = tmp;
	}
	return array;
}
char * dht_temp_show(char *array){
	temperature[0]='T';
	temperature[1]=':';
	temperature[2]=array[2]/10+0x30;
	temperature[3]=array[2]%10+0x30;
	temperature[4]='.';
	temperature[5]=array[3]/10+0x30;
	temperature[6]=array[3]%10+0x30;
	temperature[7]='C';
	return temperature;
}
char * dht_humi_show(char *array){
	humidity[0]='H';
	humidity[1]=':';
	humidity[2]=array[0]/10+0x30;
	humidity[3]=array[0]/10+0x30;
	humidity[4]='.';
	humidity[5]=array[1]/10+0x30;
	humidity[6]=array[1]/10+0x30;
	humidity[7]='%';
	return humidity;
}
void check_connect(){
	dht=1;
	dht = 0;
	Delay30ms();
	dht = 1;
//	Delay60us();
	while(dht);
	while(!dht);
	while(dht);

}