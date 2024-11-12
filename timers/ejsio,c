#include<AT89x52.h>
sbit led = P0^0;
sbit sw  = P0^1;

void main()
{  
	sw =0;
  TMOD = 0x01;
	
  if ( sw == 1)
		{
			led = 1;
			TR0 = 1;
			TH0 = 0xC9;
			TL0 = 0x87;
				
			TF0 = 0;
	
			while (TF0 == 0);
				{
					TR0 =0;
					TF0 =0;
				}
			led = 0;
			}
	else
   {
			led = 0;

		}
}	