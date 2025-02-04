
#include "softi2c.h"
#include "frami2c.h"

#include "uart.h"

#define STR_SIZE 445

static char str[STR_SIZE] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

static char buffer[STR_SIZE];


int main(void)
{
	SOFTI2C_Initialize();
	
	
	FRAMI2C_t fram = FRAMI2C_Create_Object(FRAMI2C_DEV_ADDR_A2F_A1F_A0F, FM24C256_MAX_MEM_ADDR);
	
	FRAMI2C_Set_Target_Object(&fram);
	
	
	UART_Initialize(9600, true, false);
	
	
	// запись данных из массива str в FRAM по адресу 0x0000 (закомментировано)
	// -------------------------------------------------------------------------------
	// writing data from the str array to FRAM at 0x0000 (commented out)
	// FRAMI2C_Write_Data(0x0000, str, STR_SIZE);
	
	// чтение данных из FRAM по адресу 0x0000 в массив buffer
	// -------------------------------------------------------------------------------
	// reading data from FRAM at address 0x0000 to buffer array
	FRAMI2C_Read_Data(0x0000, buffer, STR_SIZE);
	
	
	UART_Data_Transmit(buffer, STR_SIZE);
	
	while (1)
	{
	}
}



