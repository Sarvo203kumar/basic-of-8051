#ifndef _UART_H
#define _UART_H

extern unsigned char idata serialarray[100], serialcount;

extern void serial_initialize(unsigned long);
extern void serial_send(unsigned char);
extern void serial_write(const char*);
//extern void serial_writeln(const char*, unsigned int);
//extern unsigned char serial_receive(void);
//extern void serial_decimal(unsigned long, int, int);
//extern void serial_float(float, int, int);
extern void serial_enable(int);
extern void serial_flush(void);
extern char serial_talkback(int, const char*, unsigned char, unsigned int);
#endif