
#include "onewire.h"


#ifdef ONEWIRE_USE_MULTIPLE_INTERFACE

static volatile ONEWIRE_t *target_onewire_object = NULL;


ONEWIRE_t ONEWIRE_Create_Object(

uint8_t *data_ddr,
uint8_t *data_pinx,
uint8_t  data_pin
)
{
	ONEWIRE_t onewire;
	
	onewire.data_ddr  = data_ddr;
	onewire.data_pinx = data_pinx;
	onewire.data_pin  = data_pin;
	
	return onewire;
}

void ONEWIRE_Set_Target_Object(ONEWIRE_t *onewire)
{
	target_onewire_object = onewire;
}

volatile ONEWIRE_t *ONEWIRE_Get_Target_Object()
{
	return target_onewire_object;
}


// ===============================================================================


void ONEWIRE_Set_Low()
{
	*(target_onewire_object->data_ddr) |=  (1 << target_onewire_object->data_pin);
}

void ONEWIRE_Set_High()
{
	*(target_onewire_object->data_ddr) &= ~(1 << target_onewire_object->data_pin);
}

uint8_t ONEWIRE_Get_Level()
{
	return *(target_onewire_object->data_pinx) & (1 << target_onewire_object->data_pin);
}


#endif // ===============================================================================


uint8_t ONEWIRE_Reset()
{
	cli();
	
	ONEWIRE_Set_Low();
	_delay_us(640);
	
	ONEWIRE_Set_High();
	_delay_us(60);
	
	if (!ONEWIRE_Get_Level())
	{
		uint16_t timeout_counter = (uint16_t)(0.00024 / (1.0 / F_CPU));
		
		while(timeout_counter && !ONEWIRE_Get_Level())
		{
			--timeout_counter;
		}
		
		if (ONEWIRE_Get_Level())
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	
	sei();
	
	return 0;
}

void ONEWIRE_Send_Bit(uint8_t bit)
{
	ONEWIRE_Set_Low();
	
	if (bit)
	{
		_delay_us(5);
		ONEWIRE_Set_High();
		_delay_us(90);
	}
	else
	{
		_delay_us(90);
		ONEWIRE_Set_High();
		_delay_us(5);
	}
}

void ONEWIRE_Send_Byte(uint8_t data)
{
	cli();
	
	for (uint8_t i = 8; i; --i)
	{
		ONEWIRE_Send_Bit(data & 1);
		data >>= 1;
	}
	
	sei();
}

uint8_t ONEWIRE_Read_Bit()
{
	ONEWIRE_Set_Low();
	_delay_us(2);
	
	ONEWIRE_Set_High();
	_delay_us(8);
	
	uint8_t bit = ONEWIRE_Get_Level();
	_delay_us(80);
	
	return bit;
}

uint8_t ONEWIRE_Read_Byte()
{
	cli();
	
	uint8_t data = 0;
	
	for (uint8_t i = 8; i; --i)
	{
		data >>= 1;
		
		if (ONEWIRE_Read_Bit())
		{
			data |= 0x80;
		}
	}
	
	sei();
	
	return data;
}


// ===============================================================================


void ONEWIRE_Apply_By_Unique_ROM_ID(uint8_t *_8byte_unique_rom_id_buf)
{
	ONEWIRE_Send_Byte(0x55);
	
	for (uint8_t i = 0; i < 8; ++i)
	{
		ONEWIRE_Send_Byte(_8byte_unique_rom_id_buf[i]); // ONEWIRE_Send_Byte(*(_8byte_unique_rom_id_buf++));
	}
}

uint8_t ONEWIRE_Get_Unique_ROM_ID(uint8_t *_8byte_unique_rom_id_buf)
{
	if (ONEWIRE_Reset())
	{
		return 1;
	}
	
	ONEWIRE_Send_Byte(0x33);
	
	for (uint8_t i = 0; i < 8; ++i)
	{
		_8byte_unique_rom_id_buf[i] = ONEWIRE_Read_Byte(); // *(_8byte_unique_rom_id_buf++) = ONEWIRE_Read_Byte();
	}
	
	return 0;
}

uint8_t ONEWIRE_Get_CRC8(void *data, const uint8_t data_size)
{
	uint8_t crc8 = 0;
	
	for (uint8_t i = 0; i < data_size; ++i)
	{
		uint8_t b = ((uint8_t*)data)[i];
		
		for (uint8_t j = 8; j; --j)
		{
			crc8 = ((crc8 ^ b) & 1) ? (crc8 >> 1) ^ 0b10001100 : (crc8 >> 1);
			b >>= 1;
		}
	}
	
	return crc8;
}

bool ONEWIRE_Check_CRC8_From_Unique_ROM_ID(uint8_t *_8byte_unique_rom_id_buf)
{
	const uint8_t received_crc8 = _8byte_unique_rom_id_buf[7];
	
	return (received_crc8 == ONEWIRE_Get_CRC8(_8byte_unique_rom_id_buf, 7));
}



