
#include "uart.h"
#include "uart_non_blocking.h"

const char _F[] PROGMEM = "ПРИВЕТ, МИР!";

int main(void)
{
	UART_Initialize(9600, true, false);
	
	sei();
	UART_NB_Set_Transmittion_Enable(true);
	
	UART_NB_Flash_StringLn_Transmit(_F);
	
	while (1)
	{
	}
}
