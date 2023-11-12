
#include "delay.h"

#ifdef DELAY_USE_YIELD_MS

static void (*__delay_yield_ms)() = NULL;

void Delay_Ms_Set_Yield_CallBack_Function(void (*delay_yield_ms)())
{
	__delay_yield_ms = delay_yield_ms;
}

#endif


#ifdef DELAY_USE_YIELD_US

static void (*__delay_yield_us)() = NULL;

void Delay_Mu_Set_Yield_CallBack_Function(void (*delay_yield_us)())
{
	__delay_yield_us = delay_yield_us;
}

#endif



void Delay_Ms(uint16_t ms_delay)
{
	while(ms_delay)
	{
		--ms_delay;
		_delay_ms(1);
		
		
		#ifdef DELAY_USE_YIELD_MS
		
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
		
		
		#ifdef DELAY_USE_YIELD_US
		
		if (__delay_yield_us != NULL)
		{
			__delay_yield_us();
		}
		
		#endif
	}
}