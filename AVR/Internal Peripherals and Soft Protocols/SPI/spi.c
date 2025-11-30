
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

static void (*_cs_set_active)()   = NULL;
static void (*_cs_set_inactive)() = NULL;

void SPI_Set_CS_Callback_Functions(void (*cs_active_callback)(), void (*cs_inactive_callback)())
{
	_cs_set_active   = cs_active_callback;
	_cs_set_inactive = cs_inactive_callback;
}

void SPI_CS_Set_Active()
{
	if (_cs_set_active != NULL)
	{
		_cs_set_active();
	}
}

void SPI_CS_Set_Inactive()
{
	if (_cs_set_inactive != NULL)
	{
		_cs_set_inactive();
	}
}




