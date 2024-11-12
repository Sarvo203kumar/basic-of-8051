#include<AT89x52.h>
#include<AT_serial.h>

void main();
{
	Serial_Init(9600);
	Receive(1);
}