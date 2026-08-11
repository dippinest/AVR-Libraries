

#include "softi2c.h"
#include "eepromi2c.h"
#include "uart.h"



// я использую чип 24C64 с 64-ю килобитами памяти
// -------------------------------------------------------------------------------
// I use 24C128 chip (64 kbit)
//
#define EEPROM_CHIP_ADDR     EEPROMI2C_DEV_ADDR_A2F_A1F_A0F
#define EEPROM_PAGE_SIZE     EEPROMI2C_24C64_PAGE_SIZE
#define EEPROM_MAX_MEM_ADDR  EEPROMI2C_24C64_MAX_MEM_ADDR



// объект индикатора EEPROMI2C
//
// ===============================================================================
// EEPROMI2C indicator object
//
EEPROMI2C_t eepromi2c;


// приёмный буфер размером в страницу EEPROM
// -------------------------------------------------------------------------------
// this is the receiving buffer is the size of an EEPROM page
//
uint8_t buffer[EEPROM_PAGE_SIZE];


int main(void)
{
	SOFTI2C_Initialize();
	
	
	EEPROMI2C_Initialize_Object(&eepromi2c, EEPROM_CHIP_ADDR, EEPROM_MAX_MEM_ADDR, EEPROM_PAGE_SIZE);
	
	
	UART_Initialize(9600, true, false);
	
	
	for (uint32_t i = 0; i < EEPROM_MAX_MEM_ADDR; i += EEPROM_PAGE_SIZE)
	{
		EEPROMI2C_Read_Data(&eepromi2c, i, buffer, EEPROM_PAGE_SIZE, 5);
		
		UART_Data_Transmit(buffer, EEPROM_PAGE_SIZE);
	}
	
	while (1)
	{
	}
}






