#include<regx52.h>
void transmit (unsigned  char s[]);
void main()
{
	SCON=0x50;
	TMOD=0x20;
	TH1=0xFD;
	TR1=1;
	SBUF=' ';
	while(TI==0);
	TI=0;
	transmit (" welcome ");
	transmit (" hai ");
	while(1);
	}
	void transmit (unsigned  char s[])
	{
		unsigned  char r;
	
		for (r=0;s[r]!='\0';r++)
		{
			SBUF=s[r];
			while(TI==0);
	    TI=0;
		}
	}