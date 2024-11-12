#include<AT89x51.h>
#include<Atal_lcd.h>
#include<Atmal_lcd.h>
sbit sw1 = P1^0;
sbit m1 = P2^0;
sbit m2 = P2^1;
sbit m3 = P2^2;
sbit m4 = P2^3;
sbit ala = P3^2; 
sbit pump = P1^3;
int i,j;
void delay(unsigned int dly);

void fire() interrupt 1
{
		if(ala == 1)
			{
				m1 = m2 = m3 = m4 = 0;
				pump = 1;
				delay(500);		
			}
			else 
			{
			pump = 0;
			}
		}
			
void main()
{
	m1 = m2 = m3 = m4 = 0;
	sw1 =0;
	pump = ala = 0;
	EA =1;
  EX0 =1;
	Lcd8_Init();
  Lcd8_Display(0x80,"  motor         ",16);
	Lcd8_Display(0xc0,"  controlling   ",16);
	Delay(65000);Delay(65000);
	while(sw1 ==1)
	{ 
			Lcd8_Display(0x80,"  motor         ",16);
			Lcd8_Display(0xc0,"  forward       ",16);
			m2 = m4 = 1;
			delay(100);
			m1 = m2 = m3 = m4 = 0;
			delay (100);
			Lcd8_Display(0x80,"  motor         ",16);
			Lcd8_Display(0xc0,"  reversing     ",16);
			m1 = m3 = 1;
			delay(100);
			m1 = m2 = m3 = m4 = 0;
			delay(100);
			Lcd8_Display(0x80,"  motor         ",16);
			Lcd8_Display(0xc0,"  right         ",16);
			m1 = 1;
			delay(100);
			m1 = m2 = m3 = m4 = 0;
			delay(100);
			Lcd8_Display(0x80,"  motor         ",16);
			Lcd8_Display(0xc0,"    left        ",16);
			m4= 1;
			delay(100);
			m1 = m2 = m3 = m4 = 0;
			delay(100);
			}
		}
void delay(unsigned int dly)
{
	unsigned int i,j;
	for (i=0;i<dly;i++)
	for (j=0;j<400;j++);
}