#include<AT89x52.h>
#include"Atmal_lcd.h"
sbit r1=P1^0;
sbit r2=P1^1;
sbit r3=P1^2;
sbit r4=P1^3;
sbit c1=P1^4;
sbit c2=P1^5;
sbit c3=P1^6;

 void main()
{
	Lcd8_Init();
	
	Lcd8_Display(0x80,"  KEYPAD TEST   ",16);
  Delay(65000);Delay(65000);
	Lcd8_Command(0x01);	

while(1)
{
	r1=0;
	if(c1==0)
	{
	Lcd8_Display(0x80,"1",1);
  Delay(65000);Delay(65000);
	}
	if(c2==0)
	{
	Lcd8_Display(0x80," 2",2);
  Delay(65000);Delay(65000);
	}
	if(c3==0)
	{
	Lcd8_Display(0x80,"  3",3);
  Delay(65000);Delay(65000);
	}
	r1=1;r2=0;
	if(c1==0)
	{
	Lcd8_Display(0x80,"   4",4);
  Delay(65000);Delay(65000);
	}
	if(c2==0)
	{
	Lcd8_Display(0x80,"    5",5);
  Delay(65000);Delay(65000);
	}
	if(c3==0)
	{
	Lcd8_Display(0x80,"     6",6);
  Delay(65000);Delay(65000);
	}
	r2=1;r3=0;
	if(c1==0)
	{
	Lcd8_Display(0x80,"      7",7);
  Delay(65000);Delay(65000);
	}
	if(c2==0)
	{
	Lcd8_Display(0x80,"       8",8);
  Delay(65000);Delay(65000);
	}
	if(c3==0)
	{
	Lcd8_Display(0x80,"        9",9);
  Delay(65000);Delay(65000);
	}
	r3=1;r4=0;
	if(c1==0)
	{
	Lcd8_Display(0xc0," *",2);
  Delay(65000);Delay(65000);
	}
	if(c2==0)
	{
	Lcd8_Display(0xc0,"  0",3);
  Delay(65000);Delay(65000);
	}
	if(c3==0)
	{
	Lcd8_Display(0xc0,"   #",4);
  Delay(65000);Delay(65000);
	}
	r4=1;
}
}