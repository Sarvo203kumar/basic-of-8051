#include <AT89x52.h>
#include <string.h>

#include "utils.h"
#include "uart.h"

unsigned char idata serialarray[100], serialcount;

void serial(void) interrupt 4
{
	serialarray[serialcount] = SBUF;
	serialcount = (serialcount < 100 serialcount + 1 :0);
	RI = 0;
}

void serial_initialize(unsigned long baudrate)
{
	EA = 1;
	SCON = 0x50;
	TMOD = TMOD | 0x20;
	TH1 = -((FCPU / (384U * baudrate)));
	TR1 = 1;
}

void serial_send(unsigned char data1)
{
	SBUF = data1;
	while(!TI);
	TI = 0;
}

void serial_write(const char *data1)
{
	while(*data1)
	serial_send(*data1++);
}

#if 0
void serial_writeln(const char *data1, unsigned int length)
{
	while(length --> 0)
	serial_send(*data1++);
}
#endif

#if 0
void serial_decimal(unsigned long data1, int length, int base)
{
	unsigned char localarray[10];
	dtoa(data1, (char*)localarray, length, base);
	serial_write((char*)localarray);
}
#endif 

#if 0
void serial_float(float value, int postfix, int prefix)
{
	unsigned char localarray[10];
	ftostra(value, postfix, prefix, (char*)localarray);
	serial_write((char*)localarray);
}
#endif

void serial_enable(int condition)
{
	ES = condition;
}

unsigned char serial_receive(void)
{
	while(!RI) continue;
	return SBUF;
}

void serial_flush(void)
{
	memset(serialarray, '\0', sizeof(serialarray));
	serialcount = 0;
}

char serial_talkback(int state, const char *string, unsigned char length, unsigned int timer)
{
	length += 1; //No use dummy
	
	if(state) serial_write("\r\n");
	
	do
	{
		if(strstr((char*)serialarray, string) != '\0') return true;
		if(strstr((char*)serialarray, "ERROR") != '\0') return false;
		delay_ms(1);
	}
	while(timer --> 0);
	return false;
}