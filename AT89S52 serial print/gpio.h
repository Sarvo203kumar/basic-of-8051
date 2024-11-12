#ifndef _GPIO_H
#define _GPIO_H

typedef enum
{
	P00, P01, P02, P03, P04, P05, P06, P07,
	P10, P11, P12, P13, P14, P15, P16, P17,
	P20, P21, P22, P23, P24, P25, P26, P27,
	P30, P31, P32, P33, P34, P35, P36, P37
}
ATMEL_PORT_GPIO_PINS;

static void gpio_set_output(ATMEL_PORT_GPIO_PINS pin)
{
	switch(pin >> 3)
	{
		case 0: P0 &=~ (1 << (pin & 0x07)); break;
		case 1: P1 &=~ (1 << (pin & 0x07)); break;
		case 2: P2 &=~ (1 << (pin & 0x07)); break;
		case 3: P3 &=~ (1 << (pin & 0x07)); break;
		default: break;
	}
}

static void gpio_set_input(unsigned char pin)
{
	switch(pin >> 3)
	{
		case 0: P0 |= (1 << (pin & 0x07)); break;
		case 1: P1 |= (1 << (pin & 0x07)); break;
		case 2: P2 |= (1 << (pin & 0x07)); break;
		case 3: P3 |= (1 << (pin & 0x07)); break;
		default: break;
	}
}

static void gpio_set_toggle(unsigned char pin)
{
	switch(pin >> 3)
	{
		case 0: P0 ^= (1 << (pin & 0x07)); break;
		case 1: P1 ^= (1 << (pin & 0x07)); break;
		case 2: P2 ^= (1 << (pin & 0x07)); break;
		case 3: P3 ^= (1 << (pin & 0x07)); break;
		default: break;
	}
}

static void gpio_put_high(unsigned char pin)
{
	switch(pin >> 3)
	{
		case 0: P0 |= (1 << (pin & 0x07)); break;
		case 1: P1 |= (1 << (pin & 0x07)); break;
		case 2: P2 |= (1 << (pin & 0x07)); break;
		case 3: P3 |= (1 << (pin & 0x07)); break;
		default: break;
	}
}

static void gpio_put_low(unsigned char pin)
{
	switch(pin >> 3)
	{
		case 0: P0 &=~ (1 << (pin & 0x07)); break;
		case 1: P1 &=~ (1 << (pin & 0x07)); break;
		case 2: P2 &=~ (1 << (pin & 0x07)); break;
		case 3: P3 &=~ (1 << (pin & 0x07)); break;
		default: break;
	}
}

static void gpio_put_toggle(unsigned char pin)
{
	switch(pin >> 3)
	{
		case 0: P0 ^= (1 << (pin & 0x07)); break;
		case 1: P1 ^= (1 << (pin & 0x07)); break;
		case 2: P2 ^= (1 << (pin & 0x07)); break;
		case 3: P3 ^= (1 << (pin & 0x07)); break;
		default: break;
	}
}

static unsigned char gpio_get(unsigned char pin)
{
	unsigned char Result;
	switch(pin >> 3)
	{
		case 0: Result = (P0 & (1 << (pin & 0x07))); break;
		case 1: Result = (P1 & (1 << (pin & 0x07))); break;
		case 2: Result = (P2 & (1 << (pin & 0x07))); break;
		case 3: Result = (P3 & (1 << (pin & 0x07))); break;
		default: break;
	}
	return Result;
}
#endif