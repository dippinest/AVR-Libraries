
#include "uart0.h"

AVR_FLASH_DATA(flash_str,     char, "this string is in a flash memory");
AVR_FLASH_DATA(flash_fmt_str, char, "Math constant Pi ~ %.2f\r\n");

int main(void)
{
	UART0_Initialize(9600, true, false);
	
	UART0_Flash_StringLn_Transmit(flash_str);
	UART0_Flash_StringFmt_Transmit(flash_fmt_str, 3.14); // function not supported '%s' from flash!
	
	while (1)
	{
	}
}



