
#include "eeprom.h"


void EEPROM_Write_Byte(uint16_t memory_addr, const uint8_t b)
{
	while (EECR & (1 << EEWE));
	
	EEAR = memory_addr;
	EEDR = b;
	
	EECR |= (1 << EEMWE);
	EECR |= (1 << EEWE);
}

uint8_t EEPROM_Read_Byte(uint16_t memory_addr)
{
	while (EECR & (1 << EEWE));
	
	EEAR = memory_addr;
	
	EECR |= (1 << EERE);
	
	return EEDR;
}

void EEPROM_Update_Byte(uint16_t memory_addr, const uint8_t b)
{
	uint8_t tmp = EEPROM_Read_Byte(memory_addr);
	
	if (tmp != b)
	{
		EEPROM_Write_Byte(memory_addr, b);
	}
}

void EEPROM_Write_Data(uint16_t memory_addr, const void *data, uint16_t data_size)
{
	for (uint16_t i = 0; i < data_size; ++i)
	{
		EEPROM_Write_Byte((memory_addr + i), ((uint8_t*)data)[i]);
	}
}

void *EEPROM_Read_Data(uint16_t memory_addr, void *data, uint16_t data_size)
{
	for (uint16_t i = 0; i < data_size; ++i)
	{
		((uint8_t*)data)[i] = EEPROM_Read_Byte(memory_addr + i);
	}
	
	return data;
}

void EEPROM_Update_Data(uint16_t memory_addr, const void *data, uint16_t data_size)
{
	uint8_t tmp;
	
	for (uint16_t i = 0; i < data_size; ++i)
	{
		tmp = EEPROM_Read_Byte((memory_addr + i));
		
		if (tmp != ((uint8_t*)data)[i])
		{
			EEPROM_Write_Byte((memory_addr + i), ((uint8_t*)data)[i]);
		}
	}
}


void EEPROM_Fill_Memory(uint16_t memory_addr, uint8_t val, uint32_t num)
{
	for (uint16_t i = memory_addr; i < num; ++i)
	{
		EEPROM_Write_Byte(i, val);
	}
}


