#include<reg51.h>
#include<string.h>
sbit Load =P1^0;

void main()
{
	unsigned char res;
	char a[20];char b[20];
	int i,j=0;
	Load=0;
	SCON =0x50;
	TMOD=0x20;
	TH1 =0;
	TR1=1;
	while(1)
	{
		while(RI==0);
    RI=0;
	  a[j]=SBUF;
  	P1=a[j];
	  j++;
}
	if(strcmp(a,"start")==0)
	{
		P2=0x0f;
		Load =1;
		}
	else if(strcmp(b,"stop")==0)
		{
		P2=0xf0;
	  Load=0;
	}
		
}
  i=strlen(a);
  j=0;

while(i>0)
{
	SBUF=a[j];
  j++;
  i--;

}

		