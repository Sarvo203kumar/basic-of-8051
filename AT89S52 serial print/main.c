#include <at89x52.h>
#include <string.h>

#include "gpio.h"
#include "utils.h"
#include "lcd.h"
#include "uart.h"

#ifndef lcdpinconfig
#define lcdpinconfig
#define rs	P35
#define en	P34
#define d4	P14
#define d5	P15
#define d6	P16
#define d7	P17
#endif 

#ifndef uartpinconfig
#define uartpinconfig
#define uarttransmitter P31
#define uartreceiver    P30
#define uartbaudrate	9600
#endif 

int main()
{
	lcd_initialize();
	lcd_disp(0x80," ATMEL UART LCD ");
	lcd_disp(0xC0,"  INTERFACING   ");
	delay_ms(2500); lcd_function(clear_display);

	serial_initialize(uartbaudrate);
	serial_enable(true);
	serial_flush();

	serial_write("Try to send charactor i'll show it on lcd\r\n\r\n");
	serialcount = 0;

	while(1)
	{ 
		if(serialcount <= 16) lcd_writeln(0x80, &serialarray[0], serialcount);
		else lcd_writeln(0xC0, &serialarray[16], serialcount - 16);

		if(serialcount > 32)
		{
			serial_write("I've filled buffer...\r\n");
			serial_write("I am resetting myself...\r\n\r\n");
			serial_flush();
			lcd_function(clear_display);
		}
	}
}