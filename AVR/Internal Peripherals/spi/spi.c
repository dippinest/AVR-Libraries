
#include "spi.h"

void SPI_Send_Byte(uint8_t byte)
{
	SPDR = byte;
	while (!(SPSR & (1 << SPIF)));
}

void SPI_Send_Data(void* data, uint16_t data_size)
{
	for (uint16_t i = 0; i < data_size; ++i)
	{
		SPDR = ((uint8_t*)data)[i];
		while (!(SPSR & (1 << SPIF)));
	}
}

uint8_t SPI_Get_Byte_With_Sending(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1 << SPIF)));
	
	return SPDR;
}
