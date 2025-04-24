
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

// приёмный буфер размером в страницу EEPROM
// -------------------------------------------------------------------------------
// this is the receiving buffer is the size of an EEPROM page

uint8_t buffer[EEPROM_PAGE_SIZE];


int main(void)
{
	SOFTI2C_Initialize();
	
	
	EEPROMI2C_t eeprom = EEPROMI2C_Create_Object(EEPROM_CHIP_ADDR, EEPROM_MAX_MEM_ADDR, EEPROM_PAGE_SIZE);
	
	EEPROMI2C_Set_Target_Object(&eeprom);
	
	
	UART_Initialize(9600, true, false);
	
	
	for (uint32_t i = 0; i < EEPROM_MAX_MEM_ADDR; i += EEPROM_PAGE_SIZE)
	{
		EEPROMI2C_Read_Data(i, buffer, EEPROM_PAGE_SIZE, 5);
		
		UART_Data_Transmit(buffer, EEPROM_PAGE_SIZE);
	}
	
	while (1)
	{
	}
}



