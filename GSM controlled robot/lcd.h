
//NOTES:

//1: This code may be distributed and modified freely .
//2: External Crystal of 11.0592 MHz is assumed.
//3. 16x2 lcd Modules is being operated in Nibble Mode.
//4: Connections to the lcd are assumed as followed:

//		RS		-> P1.0
//		RW		-> P1.1	
//		E		  -> P1.2
//		D4,D5,D6,D7	-> P1.4,P1.5,P1.6,P1.7


#define lcd_DATA P1

sbit lcd_rs = P1^0; 

sbit lcd_rw = P1^1;  			//Must Always be low to allow data to be sent to lcd

sbit lcd_en = P1^2;

void delay_ms(unsigned int n)
{
int i,j;
for(i=0;i<n;i++)
for(j=0;j<124;j++);
}

void lcd_enable()
{
	lcd_en = 1;		//High to low transition
	delay_ms(5);
	lcd_en = 0;		
}

void lcd_cmd(unsigned char cmd)
{
    lcd_rs = 0;			//cmd Mode
    lcd_DATA = ((cmd & 0xF0)|0x04);
    lcd_enable();
    lcd_DATA = (((cmd<<4) & 0xF0)|0x04);
    lcd_enable();
		delay_ms(5);
}

void lcd_data(unsigned char ascii)
{
    lcd_rs = 1;			//Data Mode
    lcd_DATA = ((ascii & 0xF0)|0x05);
    lcd_enable();
    lcd_DATA = (((ascii<<4) & 0xF0)|0x05);
    lcd_enable();
		delay_ms(5);
}

void lcd_init()
{
	
	lcd_cmd(0x02);		//Enable 4 bit mode
	  
	lcd_cmd(0x28);		//Set interface 4 bit 2 line

	lcd_cmd(0x08);		//Enable display/cursor
	
	lcd_cmd(0x06);		//Set cursor move, Move cursor right
	
	lcd_cmd(0X0C);		//Turn on display
	
}

void lcd_gotoxy(unsigned char row,unsigned char column)			//move cursor to the specified position
{
   if(row==0)
    {
	 lcd_cmd(0x80+column);
	}
   else if(row==1)
	{
	 lcd_cmd(0xC0+column);	
	}	
}
void lcd_number(int val,unsigned int field_length)			// Function to display number 
{
	char str[5]={0,0,0,0,0};
	int i=4,j=0;
	while(val)
	{
	str[i]=val%10;
	val=val/10;
	i--;
	}
	if(field_length==-1)
		while(str[j]==0) j++;
	else
		j=5-field_length;

	if(val<0) lcd_data('-');
	for(i=j;i<5;i++)
	{
	lcd_data(48+str[i]);
	}
}

void lcd_string(unsigned char *str)
{
	
		
		while(*str!='\0')	//Till null character is encountered
		{
			lcd_data(*str);
			str++;
		}
}

void lcd_stringxy(unsigned char row, unsigned char col, unsigned char *lcd_string)
{
	lcd_gotoxy(row,col);
	while (*lcd_string) 
	{
		lcd_data(*lcd_string++);
	}
}
void lcd_numberxy(unsigned char row, unsigned char col,int val,unsigned int field_length)
{
	char str[5]={0,0,0,0,0};
	int i=4,j=0;

	lcd_gotoxy(row,col);

	while(val)
	{
	str[i]=val%10;
	val=val/10;
	i--;
	}
	if(field_length==-1)
		while(str[j]==0) j++;
	else
		j=5-field_length;

	if(val<0) lcd_data('-');
	for(i=j;i<5;i++)
	{
	lcd_data(48+str[i]);
	}
}

