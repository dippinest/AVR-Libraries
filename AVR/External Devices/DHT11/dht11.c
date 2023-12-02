
#include "dht11.h"


void DHT11_Convert_Prepare()
{
	ONEWIRE_Set_Low();
	_delay_ms(18);
	
	ONEWIRE_Set_High();
	_delay_us(40);
}

uint8_t DHT11_Start_Convert(DHT11_Data_t *dht11)
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
		dht11->dht11_40bit_data_buffer[i] = 0;
		
		for (uint8_t j = 0; j < 8; ++j)
		{
			while (ONEWIRE_Get_Level() == ONEWIRE_LEVEL_IS_LOW);
			
			_delay_us(30);
			
			if (ONEWIRE_Get_Level() == ONEWIRE_LEVEL_IS_HIGH)
			{
				dht11->dht11_40bit_data_buffer[i] |= (1 << (7 - j));
			}
			
			while (ONEWIRE_Get_Level() == ONEWIRE_LEVEL_IS_HIGH);
		}
	}
	
	uint8_t crc = dht11->dht11_40bit_data_buffer[0] + dht11->dht11_40bit_data_buffer[1] +
	dht11->dht11_40bit_data_buffer[2] + dht11->dht11_40bit_data_buffer[3];
	
	if (crc != dht11->dht11_40bit_data_buffer[4])
	{
		sei();
		return 1;
	}
	
	sei();
	
	return 0;
}


int8_t DHT11_Get_Temperature(DHT11_Data_t *dht11)
{
	return dht11->dht11_40bit_data_buffer[2];
}


int8_t DHT11_Get_Humidity(DHT11_Data_t *dht11)
{
	return dht11->dht11_40bit_data_buffer[0];
}



