#include<AT89x52.h>
#include"Atmal_lcd.h"

sbit Motor1  = P1^2;
sbit Motor2 = P1^3;
sbit  FORWARD=P1^0;
sbit  REVERSE=P1^1;

void main()
{
	 FORWARD=REVERSE=1;
	 FORWARD=REVERSE=0;
	 Motor1=Motor2=0;
	
	Lcd8_Init();
	Lcd8_Display(0x80,"  Motor control ",16);
 	Lcd8_Display(0xc0,"    System      ",16);
	Delay(65000);Delay(65000);

	while(1)
	{	
		if(!FORWARD  == 1)

		{
			 Motor1=1;
			 Motor2=0;
			Lcd8_Display(0x80,"     MOTOR      ",16);
			Lcd8_Display(0xc0,"    FORWARD     ",16);
			Delay(10000);
			
		}
		else if(!REVERSE == 1 )

		{
			 Motor1=0;
			 Motor2=1;
			Lcd8_Display(0x80,"******MOTOR******",16);
			Lcd8_Display(0xc0,"*****REVERSE****",16);
			Delay(10000);
			
		}
   else
	 {
		   Motor1=1;
			 Motor2=1;
			Lcd8_Display(0x80,"******MOTOR******",16);
			Lcd8_Display(0xc0,"******STOP*****",16);
			Delay(10000);
		 
	 }
		}
		}
	