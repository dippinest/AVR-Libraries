
#include "eeprom.h"


void EEPROM_Write_Byte(uint16_t mem_addr, uint8_t byte)
{
	while (SPMCR & (1 << SPMEN));
	while (EECR & (1 << EEWE));
	
	EEAR = mem_addr;
	EEDR = byte;
	
	cli();
	EECR |= (1 << EEMWE);
	EECR |= (1 << EEWE);
	sei();
}

uint8_t EEPROM_Read_Byte(uint16_t mem_addr)
{
	while (SPMCR & (1 << SPMEN));
	while (EECR & (1 << EEWE));
	
	EEAR  = mem_addr;
	EECR |= (1 << EERE);
	
	return EEDR;
}

void EEPROM_Write_Data(uint16_t mem_addr, void *data, uint16_t data_size)
{
	for (uint16_t i = mem_addr; i < (mem_addr + data_size); ++i)
	{
		EEPROM_Write_Byte(i, ((uint8_t*)data)[i]);
	}
}

void *EEPROM_Read_Data(uint16_t mem_addr, void *data, uint16_t data_size)
{
	for (uint16_t i = mem_addr; i < (mem_addr + data_size); ++i)
	{
		((uint8_t*)data)[i] = EEPROM_Read_Byte(i);
	}
	
	return data;
}




/*


void EEPROM_Write_Byte(uint16_t mem_addr, uint8_t byte)
{
	EEAR = mem_addr;
	EEDR = byte;
	
	cli();
	EECR |= (1 << EEMWE);
	EECR |= (1 << EEWE);
	sei();
	
	while (SPMCR & (1 << SPMEN));
	while (EECR & (1 << EEWE));
}

uint8_t EEPROM_Read_Byte(uint16_t mem_addr)
{
	EEAR  = mem_addr;
	EECR |= (1 << EERE);
	
	while (SPMCR & (1 << SPMEN));
	while (EECR & (1 << EEWE));
	
	return EEDR;
}

void EEPROM_Write_Data(uint16_t mem_addr, void *data, uint16_t data_size)
{
	for (uint16_t i = mem_addr; i < (mem_addr + data_size); ++i)
	{
		EEPROM_Write_Byte(i, ((uint8_t*)data)[i]);
	}
}

void *EEPROM_Read_Data(uint16_t mem_addr, void *data, uint16_t data_size)
{
	for (uint16_t i = mem_addr; i < (mem_addr + data_size); ++i)
	{
		((uint8_t*)data)[i] = EEPROM_Read_Byte(i);
	}
	
	return data;
}


*/

