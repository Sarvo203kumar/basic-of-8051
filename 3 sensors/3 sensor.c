#include<AT89x52.h>
#include"smcl_lcd8.h"
#include"AT_serial.h"

sbit  gas=P1^0;
sbit   ir=P1^1;
sbit fire=P1^2;
sbit   g1=P1^3;
sbit   i1=P1^4;
sbit   f1=P1^5;
 unsigned char a,b,i,rcv[5];

 void Serial(void) interrupt 4
 {
	if(RI)
	{
		rcv[i]=SBUF;
		if(rcv[0]=='*')i++;     
		else i=0;
		RI=0;
	}
  }
void main()
{
	Lcd8_Init();
	Serial_Init(9600);
	g1==1;i1==1;f1==1;
	Lcd8_Display(0x80,"  Home security ",16);
   	//Lcd8_Display(0xc0,"    System      ",16);
	 Delay(65000);Delay(65000);
	Lcd8_Command(0x01);	
	a==0,b==0; Receive(1);

	while(1)
	{	//Delay(1000);Lcd8_Command(0x01);
		 a++;		Lcd8_Decimal3(0xcd,b);Lcd8_Decimal3(0xc9,a);
	if(i>1)
			{
				Receive(0);
				
				if(rcv[1]=='1')			{Serial_Out('1');i=0;Lcd8_Decimal3(0x80,rcv);}			 //x && 
				else if(rcv[1]=='2')	{Serial_Out('2');i=0;Lcd8_Display(0x80,"******R 2*******",16);}
				else if(rcv[1]=='3')	{Serial_Out('3');i=0;Lcd8_Display(0x80,"******R 3*******",16);}
				else if(rcv[1]=='4')	{Serial_Out('4');i=0;Lcd8_Display(0x80,"******R 4*******",16);}
				else if(rcv[1]=='5')	
				i=0;Receive(1);	i=0;
			}	
		if(!gas)

		{
			Delay(1000);//Lcd8_Command(0x01);
			Lcd8_Display(0x80,"******GAS*******",16);
			Lcd8_Display(0xc0,"****DETECTED****",16);
			Delay(6000);Lcd8_Command(0x01);
		}
		if(!ir)
		{
				Delay(1000);//Lcd8_Command(0x01);
			Lcd8_Display(0x80,"******THEFT*****",16);
			Lcd8_Display(0xc0,"****DETECTED****",16);
				Delay(6000);//Lcd8_Command(0x01);
		}
		if(!fire)
		{
			 	Delay(1000);//Lcd8_Command(0x01);
			Lcd8_Display(0x80,"******FIRE******",16);
			Lcd8_Display(0xc0,"****DETECTED****",16);
			Delay(6000);Lcd8_Command(0x01);
		}
		//else {Lcd8_Display(0x80,"****************",16);
		    //	Lcd8_Display(0xc0,"****DETECTED****",16);}
	   if(a>20){a=0;b++;}
	   if(b>10)
		{Serial_Out('#');b=0;}
		

	//Serial_Out((speed%1000/100)+0x30);
	//Serial_Out((speed%100/10)+0x30);
	//Serial_Out((speed%10)+0x30);
	//enter();Delay(65000);

	//if(vib)			{Serial_Conout("*d",2);enter();}
	//else if(!vib)	{Lcd8_Display(0xc0,"ACCIDENT OCC",12);Serial_Conout("*c",2);enter();}
	}
}
							
