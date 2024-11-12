#include<reg51.h>
#include<Atmal_lcd.h>
#include<string.h>
sbit  Led=P1^0;

void main()
{
	unsigned char res;
	char a[20]; int i,j=0;
	Led=0;
	Lcd8_Init();
	Lcd8_Display(0x80,"  SERIAL TEST   ",16);
  Delay(65000);Delay(65000);
	Lcd8_Command(0x01);	
	SCON=0x50;
	TMOD=0x20;
	TH1=-3;
	TR1=1;
	while(1)
	{
	while(strcmp(a,"hello")!=0)
	{
		while(RI==0);
    RI=0;
	  a[j]=SBUF;
  	P1=a[j];
	  j++;
}
	if(strcmp(a,"hello")==0)
	{
		P2=0x0f;
		Led=0;
		break;
		}
	else
		P2=0xf0;
	  Led=1;
}
  i=strlen(a);
  j=0;

while(i>0)
{
	SBUF=a[j];
  j++;
  i--;
while(T1==0);
  T1=0;
	Lcd8_Decimal3(0x80,a);
}
}


