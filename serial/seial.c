#include<AT89x52.h>
#include"Atmal_lcd.h"
#include"AT_serial.h"
#define gas P1_0 

void serial_inti();
void mob_mess();

 bit t;
void main()
{
	
	 Lcd8_Init();
	 Delay(65000);
	 Lcd8_Display(0x80,"ALHOCOL DETECTNG",16);
	 Lcd8_Display(0xc0," FOR POLICE     ",16);
	 Serial_Init(9600);
	 Delay(65000); Delay(65000);
	 serial_inti();
	 Delay(65000); Delay(65000);
	 Lcd8_Command(0x01);
	 
  while(1)
  {
  
  if(!gas)
  {
  
  Lcd8_Display(0xc0,"  ALHOCOL SENSED",16);
  if(!t){t=1;mob_mess();}
  }
  else
  {
  t=0;
  Lcd8_Display(0xc0,"   NOT SENSING  ",16);
	SBUF =Receive;
	Serial_Conout(SBUF);
	//Lcd8_Decimal2(0x84,SBUF , 3);
  }
  
  }

 }
 void serial_inti()
 {
 
	Serial_Conout("SERIAL TEST",11);
	Serial_Out(0x0d);Serial_Out(0x0a);
	Delay(65000);Delay(65000);
	
 }
 
 void mob_mess()
 {
  Serial_Conout("ALHOCOL SENSED",14);
	Serial_Out(0x0d);Serial_Out(0x0a);
	Delay(65000);Delay(65000);
 }
										 

  