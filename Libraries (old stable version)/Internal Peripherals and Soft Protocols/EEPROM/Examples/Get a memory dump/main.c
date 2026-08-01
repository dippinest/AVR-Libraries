

#include "uart.h"
#include "eeprom.h"


// размер внешней EEPROM в байтах
//
// ===============================================================================
// internal EEPROM size in bytes
//
#define INTERNAL_EEPROM_SIZE 1024


int main(void)
{
	UART_Initialize(9600, true, false);

	for (uint16_t i = 0; i < INTERNAL_EEPROM_SIZE; ++i)
	{
		UART_Byte_Transmit( EEPROM_Read_Byte(i) );
	}
	
	
	while (1)
	{
	}
}




