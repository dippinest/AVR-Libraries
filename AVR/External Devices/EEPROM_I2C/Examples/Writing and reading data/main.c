
#include "softi2c.h"
#include "eepromi2c.h"
#include "uart.h"

#define STR_SIZE 445

static char str[STR_SIZE] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";


// приёмный буфер размером в страницу EEPROM
// -------------------------------------------------------------------------------
// this is the receiving buffer is the size of an EEPROM page

static char buffer[STR_SIZE];


// я использую чип 24C128 с 128-ю килобитами памяти
// -------------------------------------------------------------------------------
// I use 24C128 chip (128 kbit)
#define EEPROM_CHIP_ADDR     EEPROMI2C_DEV_ADDR_A2F_A1F_A0F
#define EEPROM_PAGE_SIZE     EEPROMI2C_24C128_PAGE_SIZE
#define EEPROM_MAX_MEM_ADDR  EEPROMI2C_24C128_MAX_MEM_ADDR

int main(void)
{
	SOFTI2C_Initialize();
	
	
	EEPROMI2C_t eeprom = EEPROMI2C_Get_Memory_Chip_Object(EEPROM_CHIP_ADDR, EEPROM_MAX_MEM_ADDR, EEPROM_PAGE_SIZE);
	
	EEPROMI2C_Set_Target_Memory_Chip_Object(&eeprom);
	
	
	UART_Initialize(9600, true, false);


	// запись данных из массива str в EEPROM по адресу 0x0000 (закомментировано)
	// -------------------------------------------------------------------------------
	// writing data from the str array to EEPROM at 0x0000 (commented out)
	// EEPROMI2C_Write_Data(0x0000, str, STR_SIZE, 5);
	
	// чтение данных из EEPROM по адресу 0x0000 в массив buffer
	// -------------------------------------------------------------------------------
	// reading data from EEPROM at address 0x0000 to buffer array
	EEPROMI2C_Read_Data(0x0000, buffer, STR_SIZE, 5);
	
	
	UART_Data_Transmit(buffer, STR_SIZE);
	
	while (1)
	{
	}
}

