#include <AT89x52.h>
#include <intrins.h>
#include <string.h>

#include "utils.h"
#include "lcd.h"

sbit rs = P3^5;
sbit en = P3^4;
sbit d4 = P1^4;
sbit d5 = P1^5;
sbit d6 = P1^6;
sbit d7 = P1^7;

void lcd_initialize()
{
	rs = 1;
	en = 1;
	d4 = 1;
	d5 = 1;
	d6 = 1;
	d7 = 1;
	delay_ms(250);
	
	lcd_command(0x03); delay_ms(5);
	lcd_command(0x03); delay_ms(5);
	lcd_command(0x03); delay_us(150);
	
	lcd_command(return_home); delay_us(150);
	lcd_command(four_bit | two_line | char_set1); delay_us(150);
	lcd_command(display_on | cursor_off | blink_off); delay_us(150);
	lcd_command(shift_disable | cur_increment); delay_us(150);
	lcd_function(clear_display);
}

void lcd_command(unsigned char command)
{
	rs = 0;
	lcd_allort(command & 0xF0); lcd_enable();
	lcd_allort((command << 4) & 0xF0); lcd_enable();
}

void lcd_function(unsigned char command)
{
	lcd_command(command);
	delay_ms(50);
}

void lcd_write(unsigned char command, unsigned char data1)
{
	lcd_command(command);
	rs = 1;
	lcd_allort(data1 & 0xF0); lcd_enable();
	lcd_allort((data1 << 4) & 0xF0); lcd_enable();
}

void lcd_writeln(unsigned char command, const char *data1,
unsigned char length)
{
	while(length --> 0)
	lcd_write(command++, (*data1 ?*data1++ :' '));
}

void lcd_disp(unsigned char command, const char *data1)
{
	while(*data1)
	lcd_write(command++, *data1++);
}

#if 0
void lcd_decimal(unsigned char command, unsigned long data1, int length, int base)
{
	unsigned char localarray[10];
	dtoa(data1, (char*)localarray, length, base);
	lcd_disp(command, (char*)localarray);
}
#endif 

#if 0
void lcd_float(unsigned char command, float data1, int postfix, int prefix)
{
	unsigned char localarray[10];
	ftostra(data1, postfix, prefix, (char*)localarray);
	lcd_disp(command, (char*)localarray);
}
#endif

#if 0
void lcd_custom(unsigned char location, const char *data1)
{
	unsigned char localvariable = 0;
	location *= 8;
	for(localvariable = 0; localvariable < 8; localvariable++)
	lcd_write((cgram_address + location + localvariable), data1[localvariable]);
}

void lcd_char(unsigned char command, unsigned char location, const char *data1)
{
	lcd_custom(location, data1);
	lcd_write(command, location);
}
#endif

void lcd_allort(unsigned char data1)
{
	if(data1 & 0x10) d4 = 1; else d4 = 0;
	if(data1 & 0x20) d5 = 1; else d5 = 0;
	if(data1 & 0x40) d6 = 1; else d6 = 0;
	if(data1 & 0x80) d7 = 1; else d7 = 0;
}	

void lcd_enable(void)
{
	en = 0; _nop_(); _nop_();
	en = 1; _nop_(); _nop_();
	en = 0; delay_us(100);
}	