

#include "softi2c.h"
#include "frami2c.h"

#include "uart.h"



#define BUFFER_SIZE 128

// приёмный буфер размером 128 байт
// -------------------------------------------------------------------------------
// 128 bytes receiving buffer
//
uint8_t buffer[BUFFER_SIZE];



// объект внешней микросхемы памяти FRAMI2C
//
// ===============================================================================
// the object of the external FRAMI2C memory chip
//
FRAMI2C_t frami2c;



int main(void)
{
	SOFTI2C_Initialize();
	
	
	FRAMI2C_Initialize_Object(&frami2c, FRAMI2C_DEV_ADDR_A2F_A1F_A0F, FM24C256_MAX_MEM_ADDR);
	
	
	UART_Initialize(9600, true, false);
	
	
	
	// заполнение байтом 0xAC всех ячейки данных FRAM
	// -------------------------------------------------------------------------------
	// filling of all FRAM data cells with 0xAC byte
	FRAMI2C_Fill_Memory(&frami2c, 0x0000, 0xAC, (frami2c.max_mem_addr + 1));
	
	
	for (uint32_t i = 0; i <= frami2c.max_mem_addr; i += BUFFER_SIZE)
	{
		FRAMI2C_Read_Data(&frami2c, i, buffer, BUFFER_SIZE);
		
		UART_Data_Transmit(buffer, BUFFER_SIZE);
	}
	
	while (1)
	{
	}
}





