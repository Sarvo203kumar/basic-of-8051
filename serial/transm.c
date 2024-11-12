#include<AT89x52.h>
#include<AT_serial.h>


void main()
{
	Serial_Init(9600);
	Serial_Conout(" welcome ",9);
	Serial_Conout(" bro ",5);
	Serial_Out(0x09);Serial_Out(0X05);
}
	