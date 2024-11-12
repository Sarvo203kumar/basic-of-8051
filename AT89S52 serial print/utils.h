#ifndef _UTILS_H
#define _UTILS_H

#include "intrins.h"

#ifndef FCPU 
#define FCPU 11059200UL
#endif

#ifndef ClockConfig
#define ClockConfig
#define onemachinecycle 1.0850F
#define machinecycleus  0.92F
#endif

#ifndef tuneddelay
#define tuneddelay()\
{\
	_nop_();\
	_nop_();\
	_nop_();\
	_nop_();\
	_nop_();\
}
#endif

#define delay_us(Delay)\
{\
	unsigned char LocalVariable = ((Delay - 5) / 4);\
	while(--LocalVariable > 0) continue;\
}

#define delay_ms(Delay)\
{\
	unsigned int LocalVariable;\
	unsigned int CallVariable = Delay;\
	while(CallVariable)\
	{\
		LocalVariable = 115;\
		while(LocalVariable > 0)\
		LocalVariable--;\
		CallVariable--;\
	}\
}

typedef enum
{
	BIN = 2,
	OCT = 8,
	DEC = 10,
	HEX = 16
}
ATMEL_NUMERIC_BASE;

#define true 1
#define false 0
#define null '\0'

#define True true
#define False false
#define Null null

#define enable true
#define disable false
	
//extern long mapvalue(long value, long startmin, long startmax,long endmin, long endmax);
//extern double power(double base, int exponent);
extern int dtoa(unsigned long data1, unsigned char *array, int length, int base);
//extern int ftostra(float data1, int postfix, int prefix, unsigned char *array);
//extern char splitstring(unsigned char*, unsigned char*, const char*, unsigned char);
#endif 