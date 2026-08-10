

#include "softi2c.h"
#include "ds1307.h"
#include "uart.h"



int main(void)
{
	SOFTI2C_Initialize();
	
	UART_Initialize(9600, true, false);
	
	
	
	// запись данных во внутреннюю RAM (закомментировано)
	//
	// ===============================================================================
	// writing data to internal RAM (commented out)
	//
	//for (uint8_t i = 0; i <= DS1307_USER_RAM_MAX_ADDRESS; ++i)
	//{
	//	DS1307_Write_Byte_To_User_56Byte_RAM(i, i);
	//}
	
	
	
	// чтение данных из внутренней RAM
	//
	// ===============================================================================
	// reading data from internal RAM
	//
	for (uint8_t i = 0; i <= DS1307_USER_RAM_MAX_ADDRESS; ++i)
	{
		UART_Byte_Transmit
		(
			DS1307_Read_Byte_From_User_56Byte_RAM(i)
		);
	}
	
	
	
	while (1)
	{
	}
}





