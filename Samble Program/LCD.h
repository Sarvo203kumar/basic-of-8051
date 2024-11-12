#ifndef _LCD_H
#define _LCD_H

#ifndef _Delay_H
#include "Delay.h"
#endif

#include <string.h>

#ifndef LCDConfig
#define LCDConfig
#define LCDPort P3
#define LCDData 2
#define LCDClock 3
#endif

#ifndef LCDPinConfig
#define LCDPinConfig

#define LCDClockHigh() LCDPort |= (1 << LCDClock)
#define LCDClockLow() LCDPort &=~ (1 << LCDClock)

#define LCDDataHigh() LCDPort |= (1 << LCDData)
#define LCDDataLow() LCDPort &=~ (1 << LCDData)

#define LCDDataLineIn (LCDPort & (1 << LCDData) ?1 :0)
#endif

#ifndef LCDClear
#define LCDClear()\
{\
	LCD_Command(0x01);\
	MSDelay(20);\
}
#endif

#ifndef LCDRoutines
#define LCDRoutines
char * utoa(char*, unsigned, int);
void LCD_Initialize();
void LCD_Command(unsigned char);
void LCD_Write(unsigned char, unsigned char);
void LCD_Disp(unsigned char, const char*);
void LCD_Decimal(unsigned char, unsigned int, char);
void LCD_BackLight(char);
void LCD_Allort(unsigned char);
#endif

#ifndef I2CRoutines
#define I2CRoutines
void I2C_Start();
void I2C_Stop();
void I2C_Clock();
void I2C_Write(unsigned char);
#endif

char BackLight, RegisterSelect;

char * utoa(char *Buffer, unsigned Value, int Base)
{
	unsigned v;
	char c;
	v = Value;
	do
	{
		v /= Base;
		Buffer++;
	}while(v != 0);
	*Buffer-- = 0;
	do
	{
		c = Value % Base;
		Value /= Base;
		if(c >= 10) c += 'A' - '0' - 10;
		c += '0';
		*Buffer-- = c;
	}while(Value != 0);
	return Buffer;
}

void LCD_Initialize()
{
	LCDClockHigh();
	LCDDataHigh();
	
	MSDelay(200);
	LCD_Command(0x03);
	MSDelay(5);
	LCD_Command(0x03);
	MSDelay(5);
	LCD_Command(0x03);
	USDelay(150);
	LCD_Command(0x02);
	USDelay(150);
	LCD_Command(0x28);
	MSDelay(5);
	LCD_Command(0x28);
	MSDelay(5);
	LCD_Command(0x28);
	USDelay(150);
	LCD_Command(0x06);
	USDelay(150);
	LCD_Command(0x0C);
	USDelay(150);
	LCDClear();
}

void LCD_Command(unsigned char CommandData)
{
	RegisterSelect = 0;
	LCD_Allort(CommandData & 0xF0);
	LCD_Allort((CommandData << 4) & 0xF0);
}

void LCD_Write(unsigned char CommandData, unsigned char DisplayData)
{
	LCD_Command(CommandData);
	RegisterSelect = 1;
	LCD_Allort(DisplayData & 0xF0);
	LCD_Allort((DisplayData << 4) & 0xF0);
}

void LCD_Disp(unsigned char DisplayAddress, const char *DisplayData)
{
	while(*DisplayData) LCD_Write(DisplayAddress++, *DisplayData++);
}

void LCD_Decimal(unsigned char DisplayAddress, unsigned int DecimalValue, char Length)\
{
	unsigned char Centering;
	unsigned char LocalVariable[6];
	utoa((char*)LocalVariable, DecimalValue, 10);
	Centering = strlen((char*)LocalVariable);
	while(Centering != Length--) LCD_Write(DisplayAddress++, 0x30);
	LCD_Disp(DisplayAddress, (char*)LocalVariable);
}

void LCD_BackLight(char Data)
{
	BackLight = (Data ?1 :0);
}

void LCD_Allort(char Address)
{
	I2C_Start();
	I2C_Write(0x4E);
	I2C_Write(Address | (0 << 2) | (BackLight << 3) | (RegisterSelect << 0));
	I2C_Write(Address | (1 << 2) | (BackLight << 3) | (RegisterSelect << 0));
	I2C_Write(Address | (0 << 2) | (BackLight << 3) | (RegisterSelect << 0));
	I2C_Stop();
}

void I2C_Start()
{
	LCDClockHigh(); LCDDataHigh();
	TunedDelay(); LCDDataLow();
	TunedDelay(); LCDClockLow();
}

void I2C_Stop()
{
	LCDClockHigh(); LCDDataLow();
	TunedDelay(); LCDDataHigh();
	TunedDelay();
}

void I2C_Clock()
{
	_nop_(); LCDClockHigh();
	TunedDelay(); LCDClockLow();
	TunedDelay(); _nop_();
}

void I2C_Write(unsigned char Data)
{
	unsigned char Shifting;
	for(Shifting = 0x80; Shifting; Shifting >>= 1)
	{
		if(Shifting & Data) LCDDataHigh();
		if(!(Shifting & Data)) LCDDataLow();
		I2C_Clock();
	}
	LCDDataLow(); I2C_Clock();
}
#endif