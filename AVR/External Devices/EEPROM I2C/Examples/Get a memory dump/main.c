
#include "softi2c.h"
#include "eepromi2c.h"
#include "uart.h"

// я использую чип 24C128 с 128-ю килобитами памяти
// -------------------------------------------------------------------------------
// I use 24C128 chip (128 kbit)
#define EEPROM_CHIP_ADDR     EEPROMI2C_DEV_ADDR_A2F_A1F_A0F
#define EEPROM_PAGE_SIZE     EEPROMI2C_24C128_PAGE_SIZE
#define EEPROM_MAX_MEM_ADDR  EEPROMI2C_24C128_MAX_MEM_ADDR


// приёмный буфер размером в страницу EEPROM
// -------------------------------------------------------------------------------
// this is the receiving buffer is the size of an EEPROM page

#define BUFFER_SIZE EEPROM_PAGE_SIZE

uint8_t buffer[BUFFER_SIZE];


int main(void)
{
	SOFTI2C_Initialize();
	
	
	EEPROMI2C_t eeprom = EEPROMI2C_Create_Object(EEPROM_CHIP_ADDR, EEPROM_MAX_MEM_ADDR, EEPROM_PAGE_SIZE);
	
	EEPROMI2C_Set_Target_Object(&eeprom);
	
	
	UART_Initialize(9600, true, false);


	// заполнение байтом 0xAC всех ячейки данных FRAM
	// (последний аргумент '5' - время в мс между транзакциями)
	// -------------------------------------------------------------------------------
	// filling of all FRAM data cells with 0xAC byte
	// (the last argument '5' is the time in milliseconds between transactions)
	
	EEPROMI2C_Fill_Memory(0x0000, 0xAC, (EEPROM_MAX_MEM_ADDR + 1), 5);
	
	
	for (uint32_t i = 0; i <= EEPROM_MAX_MEM_ADDR; i += BUFFER_SIZE)
	{
		EEPROMI2C_Read_Data(i, buffer, BUFFER_SIZE, 5);
		
		UART_Data_Transmit(buffer, BUFFER_SIZE);
	}
	
	while (1)
	{
	}
}



