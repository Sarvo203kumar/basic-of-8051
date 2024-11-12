#include<reg51.h>
   sbit led = P2^1;
	 sbit led2 = P2^2;
   sbit Switch = P1^1;
	   
int main()
{
   led = 0;
	 led2 = 0;
   Switch = 1;
   while(1)
   {
   if(Switch == 0)
	   {
	   led = 0;
		 led2 = 1;
	   }
	 else
	   {
	   led = 1;
		 led2 = 0;
	   }
	   }
	   return 0;
	   }