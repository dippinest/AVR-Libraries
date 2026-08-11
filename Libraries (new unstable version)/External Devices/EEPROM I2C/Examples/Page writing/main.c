

#include "softi2c.h"
#include "eepromi2c.h"
#include "uart.h"



static char data[] = "This is a data from to EEPROM";

#define DATA_SIZE (sizeof(data) / sizeof(char))




// я использую чип 24C64 с 64-ю килобитами памяти
// -------------------------------------------------------------------------------
// I use 24C128 chip (64 kbit)
//
#define EEPROM_CHIP_ADDR     EEPROMI2C_DEV_ADDR_A2F_A1F_A0F
#define EEPROM_PAGE_SIZE     EEPROMI2C_24C64_PAGE_SIZE
#define EEPROM_MAX_MEM_ADDR  EEPROMI2C_24C64_MAX_MEM_ADDR



// объект внешней микросхемы памяти EEPROMI2C
//
// ===============================================================================
// the object of the external EEPROMI2C memory chip
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


	// запись данных из массива str в EEPROM по адресу 0x0000 (закомментировано)
	// -------------------------------------------------------------------------------
	// writing data from the str array to EEPROM at 0x0000 (commented out)
	// EEPROMI2C_Write_Page(&eepromi2c, 0x0000, data, DATA_SIZE);
	
	
	// задержка 5 мс между транзакциями чтения страниц
	// -------------------------------------------------------------------------------
	// 5 ms delay between page read transactions
	EEPROMI2C_Operation_Delay_Ms(5);
	
	
	// чтение данных из EEPROM по адресу 0x0000 в массив buffer
	// -------------------------------------------------------------------------------
	// reading data from EEPROM at address 0x0000 to buffer array
	EEPROMI2C_Read_Page(&eepromi2c, 0x0000, buffer, DATA_SIZE);
	
	
	UART_Data_Transmit(buffer, DATA_SIZE);
	
	while (1)
	{
	}
}





