#include<stdio.h>
#include "uart2.hpp"
#include "lpc17xx.hpp"
int main()
{
u2.init(115200);
LPC_PINCON->PINSEL1 |= (1 << 20);
while(1)
{
	int adc3 = 1023 - int(floor(adc0_get_reading(3))/4) ;
	if(adc3 > 0 && adc3 < 1023)
		adc3 = adc3 - 2;
	sprintf(str,"%d",adc3);
	int fd = atoi(str);
	printf("adc3 = %d\n ", fd);
	for(int i = 0; i < 20; i++)
		u2.putChar(str[i]);
}

return 0;
}