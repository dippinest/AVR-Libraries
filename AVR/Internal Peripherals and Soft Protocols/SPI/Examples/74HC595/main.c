
#include <util/delay.h>
#include "spi.h"


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
	
	SPI_Initialize(true, SPI_DEV_IS_MASTER, SPI_MODE_0, SPI_SPEED_FCPU_DIV_8);

	
	while (1)
	{
		for (int8_t i = 1; i < 8; ++i)
		{
			SPI_Send_Byte( ~(1 << i) ); HHC595_Latches();
			_delay_ms(100);
		}
		for (int8_t i = 6; i >= 0; --i)
		{
			SPI_Send_Byte( ~(1 << i) ); HC595_Latches();
			_delay_ms(100);
		}
	}
}





