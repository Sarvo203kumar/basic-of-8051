#include<AT89x52.h>
#include"smcl_lcd8.h"
#include"AT_serial.h"
#define gas P1_0
#define relay P1_1
#define set P1_2
#define mov P1_3
#define inc P1_4
#define dec P1_5
#define ent P1_6 
unsigned int i=0,r=0,j;
unsigned char a[20],b[20];
void mob_inti();
void mob_mess();
void keypad();
 bit t;
void main()
{
	
	 Lcd8_Init();relay=0;
	 Delay(65000);
	 Lcd8_Display(0x80,"ALHOCOL DETECTNG",16);
	 Lcd8_Display(0xc0,"FOR POLICE      ",16);
	 Serial_Init(9600);
	 Delay(65000); Delay(65000);
	 Delay(65000); Delay(65000);
	 mob_inti();
	 Delay(65000); Delay(65000);
	 Lcd8_Display(0xc0,"                ",16);
	 
  while(1)
  {
  
  if(!gas)
  {
  relay=1;
  Lcd8_Display(0xc0,"  ALHOCOL SENSED",16);
		
 if(!t)
{
	
t=1;
mob_mess();

}
  }
  else
  {
  t=0;relay=0;
  Lcd8_Display(0xc0,"                ",16);
  }
  if(!set)
{
	while(!set)
Delay(2000);
Lcd8_Command(0x01);
keypad();	

}
  }

 }
 void mob_inti()
 {
 
	Serial_Conout("AT",2);
	Serial_Out(0x0d);Serial_Out(0x0a);
	Delay(65000);Delay(65000);
	Serial_Conout("AT+CMGF=1",9);
	Serial_Out(0x0d);Serial_Out(0x0a);
	Delay(65000);Delay(65000);
	
	
 }
 void keypad()
 {
 Lcd8_Display(0x80," SET MOB NO:    ",16);
 Delay(5000);
 Lcd8_Command(0x0e);
 while(ent)
 {
 Lcd8_Command(0xc0+r);
 if(!mov){while(!mov);Delay(5000);r++;if(r>9)r=0;}
 if(!set){while(!set);Delay(5000);r--;if(r<0)r=9;}
 if(!inc){while(!inc);Delay(5000);i++;if(i>9)i=0;a[r]=i+0x30;Lcd8_Write(0xc0+r,a[r]);}
  if(!dec){while(!dec);Delay(5000);i--;if(i<0)i=9;a[r]=i+0x30;Lcd8_Write(0xc0+r,a[r]);}
 }
 Lcd8_Command(0x0c);Lcd8_Command(0x01);Lcd8_Display(0x80,"ALHOCOL DETECTNG",16);
 }
 void mob_mess()
 {
 Delay(5000);
 Serial_Conout("ATD",3);
 for(j=0;j<10;j++)
 Serial_Out(a[j]);
 Serial_Out(';');
 Serial_Out(0x0d);Serial_Out(0x0a);
 Delay(65000); Delay(65000); Delay(65000);
  Delay(65000); Delay(65000); Delay(65000);
  Delay(65000); Delay(65000); Delay(65000);
  Serial_Conout("ATH",3);Serial_Out(0x0d);Serial_Out(0x0a);
  Delay(65000); Delay(65000); Delay(65000);
  Serial_Conout("AT+CMGS=",8);
  Serial_Out('"');
   for(j=0;j<10;j++)
 Serial_Out(a[j]);
   Serial_Out('"');
    Serial_Out(0x0d);Serial_Out(0x0a);
 Delay(65000); Delay(65000);
 Serial_Conout("ALHOCOL SENSED",15);
 Serial_Out(0x1a);
 Delay(65000); Delay(65000); Delay(65000);

 }
										 

  