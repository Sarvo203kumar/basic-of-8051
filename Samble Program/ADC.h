#ifndef _ADC_H
#define _ADC_H

#ifndef _Delay_H
#include "Delay.h"
#endif

#ifndef SPIConfig
#define SPIConfig
#define SPIPort P2
#define ChipSelect 6
#define DataOutput 5
#define DataInput 4
#define SerialClock 3
#endif

#ifndef SPIPinConfig
#define SPIPinConfig

#define SerialClockLow() SPIPort &=~ (1 << SerialClock)
#define SerialClockHigh() SPIPort |= (1 << SerialClock)

#define ChipSelectLow() SPIPort &=~ (1 << ChipSelect)
#define ChipSelectHigh() SPIPort |= (1 << ChipSelect)

#define DataOutputLow() SPIPort &=~ (1 << DataOutput)
#define DataOutputHigh() SPIPort |= (1 << DataOutput)

#define DataInputLow() SPIPort &=~ (1 << DataInput)
#define DataInputHigh() SPIPort |= (1 << DataInput)

#define SPIDataLineIn (SPIPort & (1 << DataInput) ?1 :0)
#endif

#ifndef SPIRoutines
#define SPIRoutines
unsigned int Read_ADC(char);
unsigned char SPI_Read();
unsigned char SPI_RW(unsigned char);
void SPI_Write(unsigned char);
void SPI_Initialize();
#endif

void SPI_Write(unsigned char WriteData)
{
	unsigned char Shifting;
	for(Shifting = 0x80; Shifting; Shifting >>= 1)
	{
		if(Shifting & WriteData) DataOutputHigh();
		if(!(Shifting & WriteData)) DataOutputLow();
		SerialClockHigh(); TunedDelay();
		SerialClockLow(); TunedDelay();
	}
}

unsigned char SPI_Read()
{
	unsigned char ReturnVariable, Shifting;
	for(Shifting = 0x80; Shifting; Shifting >>= 1)
	{
		if(SPIDataLineIn) ReturnVariable |= Shifting;
		else ReturnVariable &=~ Shifting;
		SerialClockHigh(); TunedDelay();
		SerialClockLow(); TunedDelay();
	}
	return ReturnVariable;
}

unsigned char SPI_RW(unsigned char WriteData)
{
	unsigned char ReturnVariable, Shifting;
	for(Shifting = 0x80; Shifting; Shifting >>= 1)
	{
		if(Shifting & WriteData) DataOutputHigh();
		if(!(Shifting & WriteData)) DataOutputLow();
		SerialClockHigh(); TunedDelay();
		if(SPIDataLineIn) ReturnVariable |= Shifting;
		else ReturnVariable &=~ Shifting;
		SerialClockLow(); TunedDelay();
	}
	return ReturnVariable;
}

unsigned int Read_ADC(char Channel)
{
	unsigned char HigherByte, LowerByte;
	ChipSelectLow();
	SPI_Write((1 << 2)|(1 << 1)|((Channel & 0x04) << 0));
	HigherByte = SPI_RW(((Channel & 0x02) << 7) | ((Channel & 0x01) << 6));
	LowerByte = SPI_Read();
	ChipSelectHigh();
	return (((HigherByte << 8)|LowerByte) & 0xFFF);
}

void SPI_Initialize()
{
	ChipSelectHigh();
	DataOutputHigh();
	SerialClockLow();
}
#endif