#include<AT89x51.h>
#include"Atmal_lcd.h"
void main()
{
	unsigned char v1,v3,v4;
	unsigned int v2;
	
	TMOD=0X60;
	TL1=0X00;
	TR1=1;
	
	Lcd8_Init();
	Lcd8_Display(0x80,"  COUNTER       ",16);
  Delay(65000);Delay(65000);
	Lcd8_Command(0x01);	

	while(1)
	{
		v1=TL1;
		v3=v1/10;
		v4=v1%10;
		Lcd8_Display(0x80,"COUNT           ",16);
		Lcd8_Decimal3(0xcd,v3);
		for(v2=0;v2<500;v2++);
		Lcd8_Decimal3(0xc9,v4);
		for(v2=0;v2<500;v2++);
	}
}