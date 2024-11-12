#ifndef _DHT_H
#define _DHT_H

#ifndef _Delay_h
#include "Delay.h"
#endif

sbit DHTSensor = P3^4;

unsigned char GlobalArray[5] = "\x00\x00\x00\x00\x00";
unsigned char Temperature, Humidity;
unsigned char ResultA, ResultB;
unsigned char ArrayShift, RoutineShift;
unsigned int CheckSum;

char FetchDHT()
{
	ET2 = 0; //Disable PWM Interrupt
	
	DHTSensor = 1; MSDelay(200);
	DHTSensor = 0; MSDelay(20);
	DHTSensor = 1; USDelay(39);
	
	ResultA = 0; while(!DHTSensor && ++ResultA < 250);
	ResultB = 0; while(DHTSensor && ++ResultB < 250);
	
	for(ArrayShift = 0; ArrayShift < 5; ArrayShift++)
	{
		for(RoutineShift = 0x80; RoutineShift; RoutineShift >>= 1)
		{
			TL0 = 0; TR0 = 1;
			while(!DHTSensor && TL0 < 50);
			while(DHTSensor && TL0 < 120);
			TR0 = 0; 
			
			if(TL0 > 80) GlobalArray[ArrayShift] |= RoutineShift;
			else GlobalArray[ArrayShift] &=~ RoutineShift;
		}
	}
			
	CheckSum = GlobalArray[0] + GlobalArray[1] +
						 GlobalArray[2] + GlobalArray[3];
	
	if(GlobalArray[4] == CheckSum)
	{
		Humidity = GlobalArray[0];
		Temperature = GlobalArray[2];
	}
	
	TH0 = 0xFC;
	TL0 = 0x66;
	ET2 = 1; //Enable PWM Interrupt
	
	return '\0';
}
#endif

/*
char FetchDHT()
{
	EA = 0;
	ET0 = 0; //Disable Timer0 Interrupt
	
	DHTSensor = 1; MSDelay(200);
	DHTSensor = 0; MSDelay(20);
	DHTSensor = 1; USDelay(39);
	
	ResultA = 0; while(!DHTSensor && ++ResultA < 250);
	ResultB = 0; while(DHTSensor && ++ResultB < 250);
	
	for(ArrayShift = 0; ArrayShift < 5; ArrayShift++)
	{
		for(RoutineShift = 0x80; RoutineShift; RoutineShift >>= 1)
		{
			TL0 = 0; TR0 = 1;
			while(!DHTSensor && TL0 < 50);
			while(DHTSensor && TL0 < 120);
			TR0 = 0; 
			
			if(TL0 > 80) GlobalArray[ArrayShift] |= RoutineShift;
			else GlobalArray[ArrayShift] &=~ RoutineShift;
			
		}
	}
			
	CheckSum = GlobalArray[0] + GlobalArray[1] +
						 GlobalArray[2] + GlobalArray[3];
	
	if(GlobalArray[4] == CheckSum)
	{
		Humidity = GlobalArray[0];
		Temperature = GlobalArray[2];
	}
	
	TH0 = 0xFC;
	TL0 = 0x66;
	ET0  = 1;
	EA = 1;
	return 4;
}
#endif
*/