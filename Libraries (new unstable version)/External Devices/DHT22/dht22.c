
#include "dht22.h"


void DHT22_Convert_Prepare()
{
	ONEWIRE_Set_Low();
	_delay_ms(2);
	
	ONEWIRE_Set_High();
	_delay_us(40);
}


uint8_t DHT22_Start_Convert(DHT22_Data_t *dht22)
{
	cli();
	
	if (ONEWIRE_Get_Level() == ONEWIRE_LEVEL_IS_HIGH)
	{
		sei();
		return 1;
	}
	
	_delay_us(80);
	
	if (ONEWIRE_Get_Level() == ONEWIRE_LEVEL_IS_LOW)
	{
		sei();
		return 1;
	}
	
	while (ONEWIRE_Get_Level() == ONEWIRE_LEVEL_IS_HIGH);
	
	for (uint8_t i = 0; i < 5; ++i)
	{
		dht22->dht22_40bit_data_buffer[i] = 0;
		
		for (uint8_t j = 0; j < 8; ++j)
		{
			while (ONEWIRE_Get_Level() == ONEWIRE_LEVEL_IS_LOW);
			
			_delay_us(30);
			
			if (ONEWIRE_Get_Level() == ONEWIRE_LEVEL_IS_HIGH)
			{
				dht22->dht22_40bit_data_buffer[i] |= (1 << (7 - j));
			}
			
			while (ONEWIRE_Get_Level() == ONEWIRE_LEVEL_IS_HIGH);
		}
	}
	
	uint8_t crc = dht22->dht22_40bit_data_buffer[0] + dht22->dht22_40bit_data_buffer[1] +
	dht22->dht22_40bit_data_buffer[2] + dht22->dht22_40bit_data_buffer[3];
	
	if (crc != dht22->dht22_40bit_data_buffer[4])
	{
		sei();
		return 1;
	}
	
	sei();
	
	return 0;
}


// ===============================================================================


int8_t DHT22_Get_Integer_Temperature(DHT22_Data_t *dht22)
{
	int16_t temperature =
		(dht22->dht22_40bit_data_buffer[2] << 8) | (dht22->dht22_40bit_data_buffer[3]);
		
	return (int8_t)(temperature / 10);
}


int8_t DHT22_Get_Integer_Humidity(DHT22_Data_t *dht22)
{
	int16_t humidity =
		(dht22->dht22_40bit_data_buffer[0] << 8) | (dht22->dht22_40bit_data_buffer[1]);
	
	return (int8_t)(humidity / 10);
}


float DHT22_Get_Float_Temperature(DHT22_Data_t *dht22)
{
	int16_t raw_temperature_data =
		(dht22->dht22_40bit_data_buffer[2] << 8) | (dht22->dht22_40bit_data_buffer[3]);
	
	return (float)(raw_temperature_data) / 10;
}


float DHT22_Get_Float_Humidity(DHT22_Data_t *dht22)
{
	int16_t raw_humidity_data =
		(dht22->dht22_40bit_data_buffer[0] << 8) | (dht22->dht22_40bit_data_buffer[1]);
	
	return (float)(raw_humidity_data) / 10;
}


int16_t DHT22_Get_FIXPoint_1_Fractional_Digit_Temperature(DHT22_Data_t *dht22)
{
	int16_t raw_temperature_data =
		(dht22->dht22_40bit_data_buffer[2] << 8) | (dht22->dht22_40bit_data_buffer[3]);
		
	return raw_temperature_data;
}


int16_t DHT22_Get_FIXPoint_1_Fractional_Digit_Humidity(DHT22_Data_t *dht22)
{
	int16_t raw_humidity_data =
		(dht22->dht22_40bit_data_buffer[0] << 8) | (dht22->dht22_40bit_data_buffer[1]);
	
	return raw_humidity_data;
}







