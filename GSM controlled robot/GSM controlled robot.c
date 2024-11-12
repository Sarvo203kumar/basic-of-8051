
#include<reg51.h>
#include"lcd.h"
#include"uart.h"

#define robot P2

void main()
{
	unsigned char temp,i,j,k,l,m;
	unsigned char read[8],a[8]="forward ",b[8]="backward",c[8]="left    ",d[8]="right   ";
	lcd_init();
	uart_init();
	robot = 0;
	lcd_stringxy(0,0,"GSM Controlled");
	lcd_stringxy(1,0,"Robot");
	
	while(1)
	{
	
		j=0,l=0,m=0;
		while(rx_data()!=0x0d);
		
			while(rx_data()!=0x0a);
			
				if(rx_data()=='+')
				{
					if(rx_data()=='C')
					{
						if(rx_data()=='M')
						{
							if(rx_data()=='T')
							{
								if(rx_data()=='I')
								{
									while(rx_data()!=',');
									temp=rx_data();
									delay_ms(10);
									tx_string("at");
									tx_data(0x0d);
									tx_data(0x0a);
									tx_string("at+cmgf=1");
									tx_data(0x0d);
									tx_data(0x0a);
									tx_string("at+cmgr=");
									tx_data(temp);
									tx_data(0x0d);
									tx_data(0x0a);

									while(rx_data()!=0x0a);
									while(rx_data()!=0x0a);
									while(rx_data()!=0x0a);
									
									for(i=0;i<8;i++)
									{
										read[i]=rx_data();
									}
									lcd_cmd(0xc0);
									for(i=0;i<8;i++)
									{
										lcd_data(read[i]);
									}
									
									for(i=0;i<8;i++)
									{
										if(read[i]==a[i])
										j++;
										if(read[i]==b[i])
										k++;
										if(read[i]==c[i])
										l++;
										if(read[i]==d[i])
										m++;
									}
									
									if(j==8)
									{
										robot=0x0a;
									}
									if(k==8)
									{
										robot=0x05;
									}
									if(l==8)
									{
										robot=0x02;
									}
									if(m==8)
									{
										robot=0x08;
									}		
									
								}}}}}
		
}	}