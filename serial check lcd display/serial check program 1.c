#include<AT89x52.h>
#include<Atmal_lcd.h>
#include<AT_serial.h>
sbit gsen = P1^0;
sbit buzzer = P1^1;
sbit value = P1^2;
sbit ir = P1^3;
bit t;
void serial_inti();
void mob_mes();
void mob_mess();

void main()
{
	gsen = buzzer = value = ir = 0;
	Lcd8_Init();
  Lcd8_Display(0x80,"  checking      ",16);
	Serial_Init(9600);
	serial_inti();
	Delay(65000);Delay(65000);
	
	while (1)
	{
		if ( gsen == 1)
		{
			buzzer == value == 1;
			Lcd8_Display(0x80,"  gas sensor    ",16);		
			Lcd8_Display(0xc0,"  detecting     ",16);
			mob_mes();	
		}
		if(ir == 1)
		{
			buzzer == value == 1;
			Lcd8_Display(0x80,"  ir  sensor    ",16);		
			Lcd8_Display(0xc0,"  detecting     ",16);
			mob_mess();
		}
		
		else 
		{
			buzzer == value == 0;
			
			Lcd8_Display(0x80,"    NO Sensor   ",16);
			Lcd8_Display(0xc0,"   detecting    ",16);
			
		}
	}
}
 void serial_inti()
 {
 
	Serial_Conout("SERIAL TEST",11);
	Serial_Out(0x0d);Serial_Out(0x0a);
	Delay(65000);Delay(65000);
	
 }
 
 void mob_mes()
 {
  Serial_Conout(" GAS SENSOR SENSED",18);
	Serial_Out(0x0d);Serial_Out(0x0a);
	Delay(65000);Delay(65000);
 }
  void mob_mess()
 {
  Serial_Conout(" IR SENSOR SENSED",17);
	Serial_Out(0x0d);Serial_Out(0x0a);
	Delay(65000);Delay(65000);
 }
