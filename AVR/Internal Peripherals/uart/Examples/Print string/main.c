
#define  F_CPU 16000000UL
#include "uart.h"

int main(void)
{
	UART_Initialize(9600, true, false);
	
	UART_String_Transmit("Hello from UART!");
	
	while (1)
	{
	}
}
