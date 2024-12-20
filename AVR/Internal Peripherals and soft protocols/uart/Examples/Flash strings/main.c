
#include "uart.h"

FLASH(flash_str,     char, "this string is in a flash memory");
FLASH(flash_fmt_str, char, "Math constant Pi ~ %.2f\r\n");

int main(void)
{
	UART_Initialize(9600, true, false);
	
	UART_Flash_StringLn_Transmit(flash_str);
	UART_Flash_StringFmt_Transmit(flash_fmt_str, 3.14); // function not supported '%s' from flash!
	
	while (1)
	{
	}
}
