#include <AT89X52.h>

#include "DHT.h"
#include "Delay.h"
#include "LCD.h"
#include "UART.h"
#include "ADC.h"
#include "MsDelay.h"

#ifndef BuiltInLed
#define BuiltInLed
#define LedPort P0
#define LedPin 0
#endif

#ifndef PWMConfig
#define PWMConfig
#define PWMPort P2
#define PWMPin 7
#define PWMInLine (PWMPort & (1 << PWMPin) ?1 :0)
#define PWMHigh() PWMPort |= (1 << PWMPin)
#define PWMLow() PWMPort &=~ (1 << PWMPin)
#endif

unsigned int TimerTicks, LightIntensity, PulseWidth;
unsigned int TempVar;
unsigned char ProcVar;

/*
void PulseWidthModulation(unsigned char PulseData)
{
	unsigned int RequirePulseData;
//	TR2 = 0; //Disable Timer While Uploading New Values
	T2CON &=~ (1 << 1); //Disable Counter and Activate Timer
	T2MOD |= (1 << 1); //Enable Pin Output For Timer 2
	RequirePulseData = PulseData * 256; //Convert 8 to 16Bit
	RCAP2H = ((RequirePulseData >> 8) & 0xFF); //Load Higher 8 bit Value
	RCAP2L = RequirePulseData & 0xFF; //Load Lower 8 Bit Value
	TR2 = 1;
}
*/

void Timer2_ISR() interrupt 5
{
	TR2 = 0; //Disable Timer While Updating Values
	
	if(PWMInLine)
	{
		PWMLow();
		TempVar = (255 - PulseWidth);
		TH2 = 0xFF - (TempVar >> 8) & 0xFF;
		TL2 = 0xFF - (TempVar & 0xFF);
	}
	else
	{
		PWMHigh();
		TempVar = PulseWidth * 1;
		TH2 = 0xFF - (TempVar >> 8) & 0xFF;
		TL2 = 0xFF - (TempVar & 0xFF);
	}
	
	TF2 = 0;
	TR2 = 1;
	return ;
}
		
void Timer0_ISR() interrupt 1
{
	TimerTicks++;
	TH0 = 0xFC;
	TL0 = 0x63; // (3 Instruction Cycles used to load value)
	TF0 = 0;
	return ;
}

void main()
{
	PWMPort &=~ (1 << PWMPin);
	LedPort &=~ (1 << LedPin);
	
	LCD_Initialize();
	Serial_Initialize();
	SPI_Initialize();
	LCD_BackLight(1);
	Serial_Enable(0);
	
	LCD_Disp(0x80,"UNIVERSAL BOARD ");
	LCD_Disp(0xC0,"   AT89S52      ");
	Delay(1); LCDClear();
	
	Serial_Write("Universal Board\r\n");
	Serial_Write("    AT89S52    \r\n");
	
	TMOD |= (1 << 0); //Timer 0 16Bit Mode
	TH0 = 0xFC; TL0 = 0x66; // 12/11059200 -> 1.0850 1000/1.0850 -> 920.8 -> 65535-921 -> 64614
	EA = 1; //Enable Global Interrupt
	ET0 = 1; //Enable Timer Interrupt
	TR0 = 1; //Run Timer 0
	
	T2CON = 0x00; //Timer 2 16 Bit Mode (Default)
	T2MOD = 0x00; //No Output & No Counter
	TH2 = 0x00; //Load Null For PWM
	TL2 = 0x00; //Load Null For PWM
	ET2 = 1; //Enable Timer 2 Interrupt
	TR2 = 1; //Run Timer 2
	
	while(1)
	{
		LightIntensity = Read_ADC(0);
		PulseWidth = LightIntensity / 16;
//		PulseWidthModulation(PulseWidth);
		
		LCD_Disp(0x80,"TEM:"); LCD_Decimal(0x84, Temperature, 3);
		LCD_Disp(0x88,"HUM:"); LCD_Decimal(0x8C, Humidity, 3);
		LCD_Disp(0xC0,"LDR:"); LCD_Decimal(0xC4, LightIntensity, 4);
		LCD_Disp(0xC9,"PWM:"); LCD_Decimal(0xCD, PulseWidth, 3);
		
		if(TimerTicks > 1499)
		{
			LedPort |= (1 << LedPin); TR0 = 0; FetchDHT();
			Serial_Write("Temperature:"); Serial_Decimal(Temperature, 3); Serial_Write("\r\n");
			Serial_Write("   Humidity:"); Serial_Decimal(Humidity, 3); Serial_Write("\r\n");
			Serial_Write("  Intensity:"); Serial_Decimal(LightIntensity, 4); Serial_Write("\r\n");
			Serial_Write("Pulse Width:"); Serial_Decimal(PulseWidth, 3); Serial_Write("\r\n");
			LedPort &=~(1 << LedPin); TimerTicks = 0; TR0 = 1;
		}
	}
}