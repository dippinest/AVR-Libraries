
#include <avr/pgmspace.h>

#include "uart.h"

const char FLASH_STRING[] PROGMEM = "this string is in a flash memory";	
const char FLASH_FMT_STRING[] PROGMEM = "Math constant Pi ~ %.2f\r\n";

int main(void)
{
	UART_Initialize(9600, true, false);
	
	UART_Flash_StringLn_Transmit(FLASH_STRING);
	UART_Flash_StringFmt_Transmit(FLASH_FMT_STRING, 3.14); // function not supported '%s' from flash!
	
	while (1)
	{
	}
}
