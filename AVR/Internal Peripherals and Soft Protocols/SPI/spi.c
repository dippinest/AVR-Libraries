
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

uint8_t SPI_Get_Byte(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1 << SPIF)));
	return SPDR;
}

// ===============================================================================

static void (*_cs_set_high)() = NULL;
static void (*_cs_set_low)()  = NULL;

void SPI_Set_CS_Callback_Functions(void (*cs_high_callback)(), void (*cs_low_callback)())
{
	_cs_set_high = cs_on_callback;
	_cs_set_low  = cs_off_callback;
}

void SPI_CS_High()
{
	_cs_set_high();
}

void SPI_CS_Low()
{
	_cs_set_low();
}



