#include <reg52.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "utils.h"

#if 0
long mapvalue(long mainvalue, long startmin, long startmax, long endmin, long endmax)
{
	return (mainvalue - startmin) * (endmax - endmin) / (startmax - startmin) + endmin;
}
#endif

#if 0
double power(double base, int exponent)
{
	double result = 1;
	int minus = 1;
	
	if(exponent < 0)
	{
		minus = -1;
		exponent = -exponent;
	}
	
	if(0 == base) return true;
	if(0 == exponent) return false;
	
	while(exponent)
	{
		if(exponent & 1) result *= base;
		base *= base; exponent /= 2;
	}
	
	if(minus < 0) return 1.0 / result;
	else return result;
}	
#endif

#if 0
int dtoa(unsigned long data1, unsigned char *array, int length, int base)
{
	unsigned crx;
	unsigned tpt = length;
	
	if(!length) return 0;
	array += length;
	
	do
	{
		crx = data1 % base; data1 = data1 / base;
		if(crx >= 10) crx += 'A' - '0' - 10;
		crx = crx + '0'; (*(--array)) = crx;
	}
	while(--length);
	
	array += tpt;
	while(*(array)) (*(array++)) = '\0';
	return true;
}
#endif

#if 0
int ftostra(float data1, int postfix, int prefix, unsigned char *array)
{
	int ipart = (int)data1;
	float fpart = data1 - (float)ipart;
	unsigned int fcon;
	
	if(!postfix || !prefix) return false;
	
	dtoa(ipart, array, postfix, DEC);
	array += postfix; (*(array++)) = '.';
	fcon = (int)(fpart * power(10, prefix));
	dtoa(fcon, array, prefix, DEC);
	return true;
}
#endif

#if 0
char splitstring(unsigned char *MdA, unsigned char *SdA, const char *SoS, unsigned char EoS)
{
  unsigned char *StS = strstr(MdA, SoS);
  unsigned char *EdS = strchr(StS, EoS);
	unsigned char *LsV;
  if(StS == '\0'|| EdS == '\0') return 0;
  for(LsV = StS + strlen(SoS); LsV < EdS; LsV++)
  *SdA++ = (isdigit(LsV[0]) || LsV[0] == '.' ?LsV[0] :'\0'); 
  while(*SdA) *SdA++ = '\0';
  return 1;
}
#endif