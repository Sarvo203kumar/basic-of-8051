#include<reg51.h>
#include<AT89s52.h>
void main()
{
	unsigned char seg [10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
	unsigned char x;
	unsigned int i;
	P0=0x00;
	while(1)
	{
		for (x=0;x<10;x++)
		{
			P0=seg[x];
			for(i=0;i<60000;i++);
		}
	}
}