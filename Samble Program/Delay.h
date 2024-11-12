#ifndef _Delay_H
#define _Delay_H

/*
#include <intrins.h>

#ifndef TunedDelay
#define TunedDelay()\
{\
	_nop_();\
	_nop_();\
	_nop_();\
	_nop_();\
}
#endif
*/

#ifndef MSDelay
#define MSDelay(Data)\
{\
	unsigned int LocalVariable;\
	unsigned int CallVariable = Data;\
	while(CallVariable)\
	{\
		LocalVariable = 115;\
		while(LocalVariable > 0)\
		LocalVariable--;\
		CallVariable--;\
	}\
}
#endif


#ifndef USDelay
#define USDelay(Delay)\
{\
	unsigned int FDelay = ((Delay / 1.0850694) - 21);\
	TH0 = ((0xFFFF - FDelay) >> 8); TL0 = ((0xFFFF - FDelay) & 0xFF);\
	TMOD |= 0x01; ET0 = 0; TR0 = 1; while(!TF0); TR0 = 0; TF0 = 0;\
}
#endif


#ifndef USDelay
#define USDelay(Data)\
{\
	unsigned char LocalVariable = ((Data - 5) / 4);\
	while(--LocalVariable > 0) continue;\
}
#endif

#ifndef Delay
#define Delay(Data)\
{\
	unsigned char RoutineDelay;\
	unsigned char RequireDelay = Data;\
	do\
	{\
		RoutineDelay = 8;\
		do\
		{\
			MSDelay(125);\
		}\
		while(--RoutineDelay);\
	}\
	while(--RequireDelay);\
}
#endif
#endif
