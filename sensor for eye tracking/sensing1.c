#include<reg51.h>
#include<delay.h>
#include<Atmal_lcd.h>

sbit sens = P1^1;
sbit motor = P2^0;
sbit motor2 = P2^1;
sbit key = P2^2;


int main()
{
	motor=motor2 =0;
	key = sens=0;
	Lcd8_Init();
  Lcd8_Display(0x80,"     test       ",16);
	Lcd8_Display(0xc0,"                ",16);
	Delay(6500);
	while (key == 1)
	{
		
		if ( sens==1)
		{
			Delay_ms(10000);
			Lcd8_Display(0x80,"sensor sensing  ",16);
			Lcd8_Display(0xc0,"                ",16);
			motor =0;
		}
		else 
		{
			motor =1;
			Lcd8_Display(0x80," Motor Smoth    ",16);
			Lcd8_Display(0xc0,"   Running      ",16);
		}
	}}

