
#include "softi2c.h"
#include "eepromi2c.h"
#include "uart.h"

static char data[] = "This is a data for writing to EEPROM";

#define DATA_SIZE (sizeof(data) / sizeof(char))


// приёмный буфер размером в страницу EEPROM
// -------------------------------------------------------------------------------
// this is the receiving buffer is the size of an EEPROM page

uint8_t buffer[DATA_SIZE];


// я использую чип 24C128 с 128-ю килобитами памяти
// -------------------------------------------------------------------------------
// I use 24C128 chip (128 kbit)
#define EEPROM_CHIP_ADDR     EEPROMI2C_DEV_ADDR_A2F_A1F_A0F
#define EEPROM_PAGE_SIZE     EEPROMI2C_24C128_PAGE_SIZE
#define EEPROM_MAX_MEM_ADDR  EEPROMI2C_24C128_MAX_MEM_ADDR

int main(void)
{
	SOFTI2C_Initialize();
	
	
	EEPROMI2C_t eeprom = EEPROMI2C_Get_Device_Object(EEPROM_CHIP_ADDR, EEPROM_MAX_MEM_ADDR, EEPROM_PAGE_SIZE);
	
	EEPROMI2C_Set_Target_Device_Object(&eeprom);
	
	
	UART_Initialize(9600, true, false);


	// запись данных из массива str в EEPROM по адресу 0x0000 (закомментировано)
	// -------------------------------------------------------------------------------
	// writing data from the str array to EEPROM at 0x0000 (commented out)
	// EEPROMI2C_Write_Page(0x0000, data, DATA_SIZE);
	
	
	// задержка 5 мс между транзакциями чтения страниц
	// -------------------------------------------------------------------------------
	// 5 ms delay between page read transactions
	EEPROMI2C_Operation_Delay_Ms(5);
	
	
	// чтение данных из EEPROM по адресу 0x0000 в массив buffer
	// -------------------------------------------------------------------------------
	// reading data from EEPROM at address 0x0000 to buffer array
	EEPROMI2C_Read_Page(0x0000, buffer, DATA_SIZE);
	
	
	UART_Data_Transmit(buffer, DATA_SIZE);
	
	while (1)
	{
	}
}



