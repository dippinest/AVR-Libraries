
#include "delay.h"

#ifdef DELAY_MS_USE_YIELD

static void (*__delay_yield_ms)() = NULL;

void Delay_Ms_Set_Yield_CallBack_Function(void (*delay_yield_ms)())
{
	__delay_yield_ms = delay_yield_ms;
}

#endif



void Delay_Ms(uint16_t ms_delay)
{
	while(ms_delay)
	{
		--ms_delay;
		_delay_ms(1);
		
		
		#ifdef DELAY_MS_USE_YIELD
		
		if (__delay_yield_ms != NULL)
		{
			__delay_yield_ms();
		}
		
		#endif
	}
}

void Delay_Us(uint16_t us_delay)
{
	while(us_delay)
	{
		--us_delay;
		_delay_us(1);
	}
}



