
#include "eeprom.h"


void EEPROM_Write_Byte(uint16_t mem_addr, uint8_t b)
{
	while (EECR & (1 << EEWE));
	
	EEAR = mem_addr;
	EEDR = b;
	
	EECR |= (1 << EEMWE);
	EECR |= (1 << EEWE);
}

uint8_t EEPROM_Read_Byte(uint16_t mem_addr)
{
	while (EECR & (1<<EEWE));
	
	EEAR = mem_addr;
	
	EECR |= (1 << EERE);
	
	return EEDR;
}

void EEPROM_Write_Data(uint16_t mem_addr, void *data, uint16_t data_size)
{
	for (uint16_t i = 0; i < data_size; ++i)
	{
		EEPROM_Write_Byte((mem_addr + i), ((uint8_t*)data)[i]);
	}
}

void *EEPROM_Read_Data(uint16_t mem_addr, void *data, uint16_t data_size)
{
	for (uint16_t i = 0; i < data_size; ++i)
	{
		((uint8_t*)data)[i] = EEPROM_Read_Byte(mem_addr + i);
	}
	
	return data;
}


