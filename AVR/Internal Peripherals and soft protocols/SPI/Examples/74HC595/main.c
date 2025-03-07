
#include <util/delay.h>
#include "spi.h"

// macro enabling latches that transmit data to the storage register
#define HC595_LATCHES \
PORTD |=  (1 << PORTD7);  \
PORTD &= ~(1 << PORTD7);

int main(void)
{
	DDRD |= (1 << PORTD7);
	
	SPI_Initialize(true, SPI_DEV_IS_MASTER, SPI_MODE_0, SPI_SPEED_FCPU_DIV_8);
	
	// implementation of running lights
	while (1)
	{
		for (int8_t i = 1; i < 8; ++i)
		{
			SPI_Send_Byte(~(1 << i)); HC595_LATCHES;
			_delay_ms(100);
		}
		for (int8_t i = 6; i >= 0; --i)
		{
			SPI_Send_Byte(~(1 << i)); HC595_LATCHES;
			_delay_ms(100);
		}
	}
}




