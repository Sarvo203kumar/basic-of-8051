
#define First_Line 0x80
#define Second_Line 0xc0
#define Curser_On  0x0f
#define Curser_Off 0x0c
#define Clear_Display 0x01
#define Data_Port P0

sbit Lcd_rs = P2^7;
sbit Lcd_rw = P2^6;
sbit Lcd_en = P2^5;

void Lcd8_Init();
void Lcd8_Command(unsigned char);
void Lcd8_Write(unsigned char,unsigned char);
void Lcd8_Display(unsigned char,const unsigned char*,unsigned int);
void Lcd8_Decimal2(unsigned char,unsigned char);
void Lcd8_Decimal3(unsigned char,unsigned char);
void Lcd8_Decimal4(unsigned char,unsigned int);
void Delay(unsigned int);

void Lcd8_Init()
{
	Lcd8_Command(0x38);		//to select function set
	Lcd8_Command(0x06);		//entry mode set
	Lcd8_Command(0x0c);		//display on
	Lcd8_Command(0x01);		//clear display
}

void Lcd8_Command(unsigned char com)
{
	Data_Port=com;
	Lcd_en=1;
	Lcd_rs=Lcd_rw=0;
	Delay(125);
	Lcd_en=0;
	Delay(125);
}

void Lcd8_Write(unsigned char com,unsigned char lr)
{
	Lcd8_Command(com);

	Data_Port=lr;			// Data 
	Lcd_en=Lcd_rs=1;
	Lcd_rw=0;
	Delay(125);
	Lcd_en=0;
	Delay(125);
}

void Lcd8_Display(unsigned char com,const unsigned char *word,unsigned int n)
{
	unsigned char Lcd_i;

	for(Lcd_i=0;Lcd_i<n;Lcd_i++)
	{ 
		Lcd8_Write(com+Lcd_i,word[Lcd_i]);
  	}
}

void Lcd8_Decimal2(unsigned char com,unsigned char val)
{
	unsigned int Lcd_hr,Lcd_t,Lcd_o;

	Lcd_hr=val%100;
	Lcd_t=Lcd_hr/10;
	Lcd_o=Lcd_hr%10;
	
	Lcd8_Write(com,Lcd_t+0x30);
	Lcd8_Write(com+1,Lcd_o+0x30);
}


void Lcd8_Decimal3(unsigned char com,unsigned char val)
{
	unsigned int Lcd_h,Lcd_hr,Lcd_t,Lcd_o;

	Lcd_h=val/100;
	Lcd_hr=val%100;
	Lcd_t=Lcd_hr/10;
	Lcd_o=Lcd_hr%10;
	
	Lcd8_Write(com,Lcd_h+0x30);
	Lcd8_Write(com+1,Lcd_t+0x30);
	Lcd8_Write(com+2,Lcd_o+0x30);
}

void Lcd8_Decimal4(unsigned char com,unsigned int val) 
{
	unsigned int Lcd_th,Lcd_thr,Lcd_h,Lcd_hr,Lcd_t,Lcd_o;

	val = val%10000;
	Lcd_th=val/1000;
	Lcd_thr=val%1000;
	Lcd_h=Lcd_thr/100;
	Lcd_hr=Lcd_thr%100;
	Lcd_t=Lcd_hr/10;
	Lcd_o=Lcd_hr%10;

	Lcd8_Write(com,Lcd_th+0x30);
	Lcd8_Write(com+1,Lcd_h+0x30);
	Lcd8_Write(com+2,Lcd_t+0x30);
	Lcd8_Write(com+3,Lcd_o+0x30);
}

void Delay(unsigned int del)
{
	while(del--);
}     
