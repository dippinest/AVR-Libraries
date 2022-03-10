#include "AVR/Internal Peripherals/uart/uart.h"

int main(void)
{
	UART_Initialize(9600, true, false, false, false, false, UART_NUM_OF_DATA_BITS_8, UART_NUM_OF_STOP_BITS_1, UART_PARITY_BIT_NONE);
	
	UART_String_Transmit("Hello from AVR UART!");
	
	while (1)
	{
	}
}
