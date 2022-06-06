
#include "max6675.h"

static uint16_t _MAX6675_Get_Data()
{
	uint16_t data = 0;
	
	#ifdef MAX6675_USE_SPI_CS_CALLBACKS
	SPI_Call_CS_ON();
	data = SPI_Get_Byte_With_Sending(0x00);
	data <<= 8;
	data |= SPI_Get_Byte_With_Sending(0x00);
	SPI_Call_CS_OFF();
	
	#else
	data = SPI_Get_Byte_With_Sending(0x00);
	data <<= 8;
	data |= SPI_Get_Byte_With_Sending(0x00);
	#endif
	
	return data;
}

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
