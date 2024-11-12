#include<AT89x52.h>
#include<Atmal_lcd.h>
sbit gsen = P1^0;
sbit buzzer = P1^1;
sbit value = P1^2;
void main()
{
	gsen = buzzer = value = 0;
	Lcd8_Init();
  Lcd8_Display(0x80," Gas sensor     ",16);
	Lcd8_Display(0xc0,"    system      ",16);
	Delay(65000);Delay(65000);
	
	while (1)
	{
		if ( gsen == 1)
		{
			buzzer == value == 1;
			Lcd8_Display(0x80,"  gas sensor    ",16);		
			Lcd8_Display(0x80,"  detecting     ",16);
			Delay (65000);	
		}
		
		else 
		{
			buzzer == value == 0;
			
			Lcd8_Display(0x80,"    NO gas      ",16);
			Lcd8_Display(0x80,"   detecting    ",16);
			
		}
	}
}