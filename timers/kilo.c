#include<AT89x52.h>
sbit led = P0^0;
void time()
{
	TH0 = 0xF8;
	TL0 = 0xCC;
	TR0 =1;
	
	while (TF0 == 0);
	{
		TR0 =0;
		TF0 =0;
	}
}
void main()
{
  TMOD = 0x02;
	led = 0;
	time();
	led = 1;
	time();
}	