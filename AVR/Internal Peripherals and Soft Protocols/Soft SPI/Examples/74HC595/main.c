
#include <util/delay.h>

#include "softspi.h"


// функция для работы "защёлки" регистра
//
// ===============================================================================
// function for register "latch" operation
//
inline void HC595_Latches()
{
	PORTD |=  (1 << 7);
	
	asm("NOP");
	
	PORTD &= ~(1 << 7);
}

int main(void)
{
	DDRD |= (1 << 7);
	
	SOFTSPI_Initialize();
	

	while (1)
	{
		for (int8_t i = 1; i < 8; ++i)
		{
			SOFTSPI_Send_Byte( ~(1 << i) ); HC595_Latches();
			_delay_ms(100);
		}
		for (int8_t i = 6; i >= 0; --i)
		{
			SOFTSPI_Send_Byte( ~(1 << i) ); HC595_Latches();
			_delay_ms(100);
		}
	}
}

