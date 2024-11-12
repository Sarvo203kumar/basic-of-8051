void Serial_Init(unsigned long int);
void Serial_Out(unsigned char);
void Serial_Conout(const unsigned char *,unsigned char);
void Baudrate(unsigned long int);
void Receive(unsigned char);

void Serial_Init(unsigned long int baud)
{  
	EA=1;
	SCON = 0X50;
	TMOD = TMOD|0X21;
	Baudrate(baud);
	TR1 = 1;	
}

void Serial_Out(unsigned char val)
{
	SBUF =val;
	while(!TI);
	TI=0;
}

void Serial_Conout(const unsigned char *dat,unsigned char n)
{
	unsigned char ser_j;
	for(ser_j=0;ser_j<n;ser_j++)
	{
		Serial_Out(dat[ser_j]);
	}
}

void Baudrate(unsigned long int baud)
{
	if(baud==110) TH1=0x72;	 				  //1Mhz crystal
	else if(baud==2400) TH1=0xF4;			//11.0592Mhz crystal
	else if(baud==4800) TH1=0xFA;			//11.0592Mhz crystal
	else if(baud==9600) TH1=0XFD;	 		//11.0592Mhz crystal
	else if(baud==115200) TH1=0xFF;
}


void Receive(unsigned char rece)
{
	if(rece==1)
	{
		ES=1;		
	}
	else
	{
		ES=0;		
	}	
}
