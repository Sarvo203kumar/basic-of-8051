#ifndef _UART_H
#define _UART_H

#include <string.h>

#ifndef SpeedCalculation
#define SpeedCalculation
#define Crystal 11059200UL
#define BaudRate 9600
#define RegValue (256 - ((Crystal)/(unsigned long)32 * 12 * BaudRate))
#endif

#ifndef SerialRoutines
#define SerialRoutines
char * utoa(char*, unsigned , int);
void Serial_Initialize();
void Serial_Send(unsigned char);
void Serial_Write(const char*);
void Serial_Decimal(unsigned int, char);
void Serial_Enable(char);
#endif

/*
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
*/


void Serial_Initialize()
{
	SCON = (1 << 6); //8Bit UART Determined By Timer1
	TMOD |= (1 << 5); //8Bit Auto Reload Setting
  TH1 = 0xFD; //Apply Calculated Value 0xFD
	TR1 = 1; //Activate Timer1
}

void Serial_Send(unsigned char SingleData)
{
	SBUF = SingleData;
	while(TI == 0);
	TI = 0;
}

void Serial_Write(const char *SendData)
{
	while(*SendData) Serial_Send(*SendData++);
}

void Serial_Decimal(unsigned int DecimalValue, char Length)
{
	unsigned char LocalVariable[6];
	unsigned char Centering;
	utoa((char*)LocalVariable, DecimalValue, 10);
	Centering = strlen((char*)LocalVariable);
	while(Centering != Length--) Serial_Send(0x30);
	Serial_Write((char*)LocalVariable);
}

void Serial_Enable(char Condition)
{
	if(Condition) SCON |= (1 << 4);
	else SCON &=~ (1 << 4);
}
#endif