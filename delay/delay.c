#include<AT89x52.h>
void delay(unsigned int );
void main()
{
	while(1)
	{
		P2= 0xff;
		delay(500);
		
		P2= 0x00;
		delay(500);
	}
}
void delay(unsigned int dly)
{
	unsigned int i,j;
	for (i=0;i<dly;i++)
	for (j=0;j<400;j++);
}