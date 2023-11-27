
#include "ds18b20.h"

// ===============================================================================

#ifdef DS18B20_USE_MULTIPLE_SENSORS

static uint8_t *target_ds18b20_address = NULL;

// ===============================================================================

void DS18B20_Set_Target_DS18B20_Address(uint8_t *ds18b20_address)
{
	target_ds18b20_address = ds18b20_address;
}

uint8_t *DS18B20_Get_Target_DS18B20_Address()
{
	return target_ds18b20_address;
}

static void _DS18B20_Contact_To_Address()
{
	ONEWIRE_Reset();
	ONEWIRE_Send_Byte(0x55);
	
	for (uint8_t i = 0; i < 8; ++i)
	{
		ONEWIRE_Send_Byte(target_ds18b20_address[i]);
	}
}

// ===============================================================================

void DS18B20_Set_Resolution(uint8_t resolution)
{
	_DS18B20_Contact_To_Address();
	ONEWIRE_Send_Byte(0x4E);
	
	ONEWIRE_Send_Byte(0x00);
	ONEWIRE_Send_Byte(0x00);
	ONEWIRE_Send_Byte(resolution);
}

void DS18B20_Set_Resolution_With_Skip_ROM(uint8_t resolution)
{
	ONEWIRE_Reset();
	ONEWIRE_Send_Byte(0xCC);
	ONEWIRE_Send_Byte(0x4E);
	
	ONEWIRE_Send_Byte(0x00);
	ONEWIRE_Send_Byte(0x00);
	ONEWIRE_Send_Byte(resolution);
}

uint8_t *DS18B20_Get_Scratchpad(uint8_t *scrathpad_buffer)
{
	_DS18B20_Contact_To_Address();
	ONEWIRE_Send_Byte(0xBE);
	
	for (uint8_t i = 0; i < 9; ++i)
	{
		scrathpad_buffer[i] = ONEWIRE_Read_Byte();
	}
	
	return scrathpad_buffer;
}

void DS18B20_Start_Convert()
{
	_DS18B20_Contact_To_Address();
	ONEWIRE_Send_Byte(0x44);
}

void DS18B20_Start_Convert_With_Skip_ROM()
{
	ONEWIRE_Reset();
	ONEWIRE_Send_Byte(0xCC);
	ONEWIRE_Send_Byte(0x44);
}

int8_t DS18B20_Get_Integer_Temperature()
{
	_DS18B20_Contact_To_Address();
	ONEWIRE_Send_Byte(0xBE);
	
	uint8_t lsb = ONEWIRE_Read_Byte();
	uint8_t msb = ONEWIRE_Read_Byte();
	
	int16_t t_raw = ((msb << 8) | lsb);
	
	int8_t temperature = t_raw >> 4;
	
	return temperature;
}

float DS18B20_Get_Float_Temperature()
{
	_DS18B20_Contact_To_Address();
	ONEWIRE_Send_Byte(0xBE);
	
	uint8_t lsb = ONEWIRE_Read_Byte();
	uint8_t msb = ONEWIRE_Read_Byte();
	
	int16_t t_raw = ((msb << 8) | lsb);
	
	return t_raw * 0.0625;
}

float DS18B20_Get_Float_Temperature_With_Increased_Accuracy()
{
	uint8_t scratchpad[9];
	
	DS18B20_Get_Scratchpad(scratchpad);
	
	uint8_t lsb          = scratchpad[0];
	uint8_t msb          = scratchpad[1];
	uint8_t count_remain = scratchpad[6];
	uint8_t count_per_c  = scratchpad[7];
	
	int16_t temp_raw = (msb << 8) | lsb;
	
	return (temp_raw * 0.0625) - 0.25 + ((count_per_c - count_remain) / count_per_c);
}

bool DS18B20_Get_Power_Supply()
{
	_DS18B20_Contact_To_Address();
	ONEWIRE_Send_Byte(0xB4);
	
	return ONEWIRE_Get_Level();
}

#else // ===============================================================================

void DS18B20_Set_Resolution(uint8_t resolution)
{
	ONEWIRE_Reset();
	ONEWIRE_Send_Byte(0xCC);
	ONEWIRE_Send_Byte(0x4E);
	
	ONEWIRE_Send_Byte(0x00);
	ONEWIRE_Send_Byte(0x00);
	ONEWIRE_Send_Byte(resolution);
}

uint8_t *DS18B20_Get_Scratchpad(uint8_t *scrathpad_buffer)
{
	ONEWIRE_Reset();
	ONEWIRE_Send_Byte(0xCC);
	ONEWIRE_Send_Byte(0xBE);
	
	for (uint8_t i = 0; i < 9; ++i)
	{
		scrathpad_buffer[i] = ONEWIRE_Read_Byte();
	}
	
	return scrathpad_buffer;
}

void DS18B20_Start_Convert()
{
	ONEWIRE_Reset();
	ONEWIRE_Send_Byte(0xCC);
	ONEWIRE_Send_Byte(0x44);
}

int8_t DS18B20_Get_Integer_Temperature()
{
	ONEWIRE_Reset();
	ONEWIRE_Send_Byte(0xCC);
	ONEWIRE_Send_Byte(0xBE);
	
	uint8_t lsb = ONEWIRE_Read_Byte();
	uint8_t msb = ONEWIRE_Read_Byte();
	
	int16_t t_raw = ((msb << 8) | lsb);
	
	int8_t temperature = t_raw >> 4;
	
	return temperature;
}

float DS18B20_Get_Float_Temperature()
{
	ONEWIRE_Reset();
	ONEWIRE_Send_Byte(0xCC);
	ONEWIRE_Send_Byte(0xBE);
	
	uint8_t lsb = ONEWIRE_Read_Byte();
	uint8_t msb = ONEWIRE_Read_Byte();
	
	int16_t t_raw = ((msb << 8) | lsb);
	
	return t_raw * 0.0625;
}

float DS18B20_Get_Float_Temperature_With_Increased_Accuracy()
{
	uint8_t scratchpad[9];
	
	DS18B20_Get_Scratchpad(scratchpad);
	
	uint8_t lsb          = scratchpad[0];
	uint8_t msb          = scratchpad[1];
	uint8_t count_remain = scratchpad[6];
	uint8_t count_per_c  = scratchpad[7];
	
	int16_t temp_raw = (msb << 8) | lsb;
	
	return (temp_raw * 0.0625) - 0.25 + ((count_per_c - count_remain) / count_per_c);
}

bool DS18B20_Get_Power_Supply()
{
	ONEWIRE_Reset();
	ONEWIRE_Send_Byte(0xCC);
	ONEWIRE_Send_Byte(0xB4);
	
	return ONEWIRE_Get_Level();
}

#endif


