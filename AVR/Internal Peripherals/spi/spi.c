
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

// ===============================================================================

#ifdef SPI_USE_CS_FUNCTION_CALLBACK

static void (*_cs_set_on)()  = NULL;
static void (*_cs_set_off)() = NULL;

void SPI_Set_CS_CallBack_Functions(void (*cs_on_callback)(), void (*cs_off_callback)())
{
	_cs_set_on  = cs_on_callback;
	_cs_set_off = cs_off_callback;
}

void SPI_Call_CS_ON()
{
	_cs_set_on();
}

void SPI_Call_CS_OFF()
{
	_cs_set_off();
}

#endif
