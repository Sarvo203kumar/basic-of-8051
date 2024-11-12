#include<reg51.h>
sbit LED1 =  P0^0; 
sbit LED2 =  P0^1; 
sbit SW = P3^2;

void timer0_isr() interrupt 1
{
    TH0  = 0X4B;        
    TL0  = 0XFD;
    LED1 =!LED1;        
}

void main()
{
    TMOD = 0x01;      
    TH0 = 0X4B;        
    TL0 = 0XFD;
    TR0 = 1;          
    ET0 = 1;          
    EA = 1;           
    SW = 1;            
    while(1)
    {
        LED2= SW;      
    } 
}