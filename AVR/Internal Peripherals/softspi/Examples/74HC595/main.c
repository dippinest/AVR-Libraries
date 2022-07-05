
#define F_CPU 16000000UL

#include <util/delay.h>
#include "softspi.h"

// macro enabling latches that transmit data to the storage register
#define HC595_LATCHES         \
	PORTD |=  (1 << PORTD7);  \
	PORTD &= ~(1 << PORTD7);

int main(void)
{
	DDRD |= (1 << PORTD7);
	
	SOFTSPI_Initialize();
	
	// implementation of running lights
	while (1)
	{
		for (int8_t i = 1; i < 8; ++i)
		{
			SOFTSPI_Send_Byte(~(1 << i)); HC595_LATCHES;
			_delay_ms(100);
		}
		for (int8_t i = 6; i >= 0; --i)
		{
			SOFTSPI_Send_Byte(~(1 << i)); HC595_LATCHES;
			_delay_ms(100);
		}
	}
}
