
#include "std_types.h"
#include "softwareDelay.h"
void SwDelay_ms(uint32 n)
{
	uint32 i;
	uint32 delay=n*380;
	for(i=0;i<delay;i++);
}

