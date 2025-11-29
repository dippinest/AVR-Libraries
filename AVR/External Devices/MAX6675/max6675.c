

#include "max6675.h"



#if defined (MAX6675_USE_SOFTSPI) && defined (MAX6675_USE_CS_CALLBACKS)


static uint16_t _MAX6675_Get_Data()
{
	uint16_t data = 0;
	
	
	SOFTSPI_CS_High();
	
	data = SOFTSPI_Get_Byte();
	
	data <<= 8;
	
	data |= SOFTSPI_Get_Byte();
	
	SOFTSPI_CS_Low();
	
	
	return data;
}


#elif defined (MAX6675_USE_SOFTSPI) && !defined (MAX6675_USE_CS_CALLBACKS)


static uint16_t _MAX6675_Get_Data()
{
	uint16_t data = 0;


	data = SOFTSPI_Get_Byte();
	
	data <<= 8;
	
	data |= SOFTSPI_Get_Byte();
	
	
	return data;
}


#elif !defined (MAX6675_USE_SOFTSPI) && defined (MAX6675_USE_CS_CALLBACKS)


static uint16_t _MAX6675_Get_Data()
{
	uint16_t data = 0;
	
	
	SPI_CS_High();
	
	data = SPI_Get_Byte(0x00);
	
	data <<= 8;
	
	data |= SPI_Get_Byte(0x00);
	
	SPI_CS_Low();
	
	
	return data;
}


#elif !defined (MAX6675_USE_SOFTSPI) && !defined (MAX6675_USE_CS_CALLBACKS)


static uint16_t _MAX6675_Get_Data()
{
	uint16_t data = 0;
	
	
	data = SPI_Get_Byte(0x00);
	
	data <<= 8;
	
	data |= SPI_Get_Byte(0x00);
	
	
	return data;
}


#endif


float MAX6675_Get_Temperature_In_Celsius_Float()
{
	return (_MAX6675_Get_Data() >> 3) * 0.25;
}

uint16_t MAX6675_Get_Temperature_In_Celsius_Integer()
{
	return _MAX6675_Get_Data() >> 5;
}

uint16_t MAX6675_Get_Temperature_In_Celsius_Fixpoint_2Bit()
{
	return _MAX6675_Get_Data() >> 3;
}





