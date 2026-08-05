
#include "uart1.h"
#include "uart1_async.h"

AVR_FLASH_DATA(flash_str, char, "Hello, world!");

int main(void)
{
	UART1_Initialize(9600, true, false);
	
	UART1_Async_Set_Transmittion_Enable(true);
	
	
	sei();
	
	UART1_Async_Flash_StringLn_Transmit(flash_str);
	
	while (1)
	{
	}
}



