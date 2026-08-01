

#include "max6675.h"



#if defined (MAX6675_USE_SOFTSPI) && defined (MAX6675_USE_CS_CALLBACKS)


#include "softspi.h"



static uint16_t _MAX6675_Get_Data()
{
	uint16_t data = 0;
	
	
	SOFTSPI_CS_Set_Active();
	
	data = SOFTSPI_Get_Byte();
	
	data <<= 8;
	
	data |= SOFTSPI_Get_Byte();
	
	SOFTSPI_CS_Set_Inactive();
	
	
	return data;
}


#elif defined (MAX6675_USE_SOFTSPI) && !defined (MAX6675_USE_CS_CALLBACKS)


#include "softspi.h"



static uint16_t _MAX6675_Get_Data()
{
	uint16_t data = 0;


	data = SOFTSPI_Get_Byte();
	
	data <<= 8;
	
	data |= SOFTSPI_Get_Byte();
	
	
	return data;
}


#elif !defined (MAX6675_USE_SOFTSPI) && defined (MAX6675_USE_CS_CALLBACKS)


#include "spi.h"



static uint16_t _MAX6675_Get_Data()
{
	uint16_t data = 0;
	
	
	SPI_CS_Set_Active();
	
	data = SPI_Get_Byte(0x00);
	
	data <<= 8;
	
	data |= SPI_Get_Byte(0x00);
	
	SPI_CS_Set_Inactive();
	
	
	return data;
}


#elif !defined (MAX6675_USE_SOFTSPI) && !defined (MAX6675_USE_CS_CALLBACKS)


#include "spi.h"



static uint16_t _MAX6675_Get_Data()
{
	uint16_t data = 0;
	
	
	data = SPI_Get_Byte(0x00);
	
	data <<= 8;
	
	data |= SPI_Get_Byte(0x00);
	
	
	return data;
}


#endif


bool MAX6675_Get_Temperature_In_Celsius_Float(float *temperature)
{
	bool is_working_properly = true;
	
	const uint16_t data = _MAX6675_Get_Data();
	
	
	if (data & (1 << 2))
	{
		is_working_properly = false;
	}
	else
	{
		*temperature = (data >> 3) * 0.25;
	}
	
	
	return is_working_properly;
}

bool MAX6675_Get_Temperature_In_Celsius_Integer(uint16_t *temperature)
{
	bool is_working_properly = true;
	
	const uint16_t data = _MAX6675_Get_Data();
	
	
	if (data & (1 << 2))
	{
		is_working_properly = false;
	}
	else
	{
		*temperature = data >> 5;
	}
	
	
	return is_working_properly;
}

bool MAX6675_Get_Temperature_In_Celsius_Fixpoint_2Bit(uint16_t *temperature)
{
	bool is_working_properly = true;
	
	const uint16_t data = _MAX6675_Get_Data();
	
	
	if (data & (1 << 2))
	{
		is_working_properly = false;
	}
	else
	{
		*temperature = data >> 3;
	}
	
	
	return is_working_properly;
}




