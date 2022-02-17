#define F_CPU 16000000UL
#include <util/delay.h>

#include "uart.h"

int main(void)
{
	UART_Initialize(9600, true, false, false, false, false, UART_NUM_OF_DATA_BITS_8, UART_NUM_OF_STOP_BITS_1, UART_PARITY_BIT_NONE);
	
	while (1)
	{
		UART_StringLn_Transmit("Hello from UART!");
		_delay_ms(1000);
	}
}