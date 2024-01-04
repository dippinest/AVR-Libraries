
#include "eeprom.h"


void EEPROM_Write_Byte(uint16_t mem_addr, uint8_t byte)
{
	eeprom_write_byte((void*)mem_addr, byte);
}

uint8_t EEPROM_Read_Byte(uint16_t mem_addr)
{
	return eeprom_read_byte((void*)mem_addr);
}

void EEPROM_Write_Data(uint16_t mem_addr, void *data, uint16_t data_size)
{
	eeprom_write_block(data, (void*)mem_addr, data_size);
}

void *EEPROM_Read_Data(uint16_t mem_addr, void *data, uint16_t data_size)
{
	eeprom_read_block(data, (void*)mem_addr, data_size);
	
	return data;
}


