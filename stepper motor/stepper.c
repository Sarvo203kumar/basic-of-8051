#include<AT89x52.h>
sbit I1=P1^0;
sbit I2=P1^1;
sbit I3=P1^2;
sbit I4=P1^3;

void main()
{
	unsigned int i;
	I1=I2=I3=I4=0;
	while(1)
	{
		I1=1;
		I2=I3=I4=0;
		for(i=0;i<30000;i++);
		I2=1;
		I1=I3=I4=0;
		for(i=0;i<30000;i++);
		I3=1;
		I1=I2=I4=0;
		for(i=0;i<30000;i++);
		I4=1;
		I1=I2=I3=0;
		for(i=0;i<30000;i++);
	}
}