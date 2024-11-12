#include<reg51.h>
#include<AT89a52.h>

 	 unsigned char seg [10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
		
	 unsigned int i;
   unsigned char x;
	



void main()
{    
	P0 = 0x00;
	
	while
		for (x=0;x<10;x++)
		{
			P0= seg [x];
			for (i=0; i<60000;i++);
    P1^1 = 0;
		P1^2 = 1;
		P1^3 = 0;
		for (x=0;x<10;x++)
		{
			P0= seg [x];
			for (i=0; i<60000;i++);
   
		for (x=0;x<10;x++)
		{
			P0= seg [x];
			for (i=0; i<60000;i++);
		}}}	