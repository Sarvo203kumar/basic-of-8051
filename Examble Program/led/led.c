 #include<reg51.h>
 #define LEDs P1
 sbit led=P2^7;
 void main()
 {
 while(1)
 {
 LEDs=0;
 led=0;
 LEDs=1;
 led=1;
 }
 }