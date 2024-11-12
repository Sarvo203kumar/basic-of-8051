#include<AT89x51.h>
#include"Atmal_lcd.h"
sbit switch1=P3^0;
sbit switch2=P3^1;
sbit digit1=P2^0;
sbit digit2=P2^1;
int x=0,y,z;
void main()
{
	//unsigned char disp [10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
	switch1=1;
	switch2=1;
	digit1=1;
	digit2=1;
	
	
	Lcd8_Init();
	Lcd8_Display(0x80,"  COUNTER       ",16);
  Delay(65000);Delay(65000);
	Lcd8_Command(0x01);	

	while(1)
	{
		if(switch1==0)
	{
		x++;
		Delay(65000);
	}
	else if(switch2==0)
	{
		x--;
		Delay(65000);
	}
		y=x/10;
	digit1=0;
	Delay(10);
	digit1=1;
		Lcd8_Display(0x80,"COUNT           ",16);
		Lcd8_Decimal3(0xcd,y);
		Delay(10);
		
	z=x%10;
	Lcd8_Decimal3(0xc9,z);
	digit2=0;
	Delay(10);
	digit2=1;
	}
}