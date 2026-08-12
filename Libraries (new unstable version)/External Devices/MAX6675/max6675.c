

#include "max6675.h"



// ===============================================================================

#ifdef MAX7219_USE_SOFTSPI


#include "softspi.h"

#define _SPI_Get_Byte         SOFTSPI_Get_Byte
#define _SPI_CS_Set_Active    SOFTSPI_CS_Set_Active
#define _SPI_CS_Set_Inactive  SOFTSPI_CS_Set_Inactive


#else


#include "spi.h"

#define _SPI_Get_Byte         SPI_Get_Byte
#define _SPI_CS_Set_Active    SPI_CS_Set_Active
#define _SPI_CS_Set_Inactive  SPI_CS_Set_Inactive

#endif

// ===============================================================================




#ifdef MAX6675_USE_CS_CALLBACKS



static uint16_t _MAX6675_Get_Data()
{
	uint16_t data = 0;
	
	
	_SPI_CS_Set_Active();
	
	data = _SPI_Get_Byte(0x00);
	
	data <<= 8;
	
	data |= _SPI_Get_Byte(0x00);
	
	_SPI_CS_Set_Inactive();
	
	
	return data;
}



#else


static uint16_t _MAX6675_Get_Data()
{
	uint16_t data = 0;
	
	
	data = _SPI_Get_Byte(0x00);
	
	data <<= 8;
	
	data |= _SPI_Get_Byte(0x00);
	
	
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




