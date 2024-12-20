
#include "uart.h"
#include "uart_async.h"

FLASH(flash_str, char, "Hello, world!");

int main(void)
{
	UART_Initialize(9600, true, false);
	
	UART_Async_Set_Transmittion_Enable(true);
	
	
	sei();
	
	UART_Async_Flash_StringLn_Transmit(flash_str);
	
	while (1)
	{
	}
}
