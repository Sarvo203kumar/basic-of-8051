#include<AT89x52.h>
sbit  gas=P1^0;
sbit  relay=P1^1;

void main()
{
	relay==0;
	while(1)
	{
		if(!gas)
		{
			relay=0;
		}
		else
		{
			relay=1;
	}
}
	}