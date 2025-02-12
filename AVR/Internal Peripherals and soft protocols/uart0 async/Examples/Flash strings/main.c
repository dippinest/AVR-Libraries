
#include "uart0.h"
#include "uart0_async.h"

AVR_FLASH_DATA(flash_str, char, "Hello, world!");

int main(void)
{
	UART0_Initialize(9600, true, false);
	
	UART0_Async_Set_Transmittion_Enable(true);
	
	
	sei();
	
	UART0_Async_Flash_StringLn_Transmit(flash_str);
	
	while (1)
	{
	}
}



