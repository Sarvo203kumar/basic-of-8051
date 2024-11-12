#include<reg51.h>

sbit led=P1^0; 

void delay()
{
int count=0;
 while(count!=500)
  {
   TMOD=0x01;  
   TH0=0xF8;   
   TL0=0xCC;  
   TR0=1;     
   while(!TF0);   
   TR0 = 0;      
   TF0 = 0;      
   count++;
  }

}

void main()
{
while(1)     
{
led=1;    
delay();  
led=0;  
delay();  
}
}  