
#include "uart.h"
#include "uart_async.h"

const char _F[] PROGMEM = "ПРИВЕТ, МИР!";

int main(void)
{
	UART_Initialize(9600, true, false);
	
	sei();
	UART_Async_Set_Transmittion_Enable(true);
	
	UART_Async_Flash_StringLn_Transmit(_F);
	
	while (1)
	{
	}
}
