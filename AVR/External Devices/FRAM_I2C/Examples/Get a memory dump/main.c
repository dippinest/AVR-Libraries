
#include "softi2c.h"
#include "frami2c.h"

#include "uart.h"

#define BUFFER_SIZE 128

uint8_t buffer[BUFFER_SIZE];


int main(void)
{
	SOFTI2C_Initialize();
	
	
	FRAMI2C_t fram = FRAMI2C_Get_Memory_Chip_Object(FRAMI2C_DEV_ADDR_A2F_A1F_A0F, FM24C256_MAX_MEM_ADDR);
	
	FRAMI2C_Set_Target_Memory_Chip_Object(&fram);
	
	
	UART_Initialize(9600, true, false);
	
	
	// заполнение байтом 0xAC всех ячейки данных FRAM
	// -------------------------------------------------------------------------------
	// filling of all FRAM data cells with 0xAC byte
	EEPROMI2C_Fill_All_Memory(0x0000, 0xAC, (fram.max_mem_addr + 1));
	
	
	for (uint32_t i = 0; i < fram.max_mem_addr; i += BUFFER_SIZE)
	{
		FRAMI2C_Read_Data(i, buffer, BUFFER_SIZE);
		
		UART_Data_Transmit(buffer, BUFFER_SIZE);
	}
	
	while (1)
	{
	}
}

