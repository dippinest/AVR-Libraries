
#include "uart.h"


#define BUFFER_SIZE 16

uint8_t uart_buffer[BUFFER_SIZE];


#define TERMINATOR_SYMBOL '!'


int main(void)
{
	UART_Initialize(9600, true, true);
	
	while (1)
	{
		UART_Data_Transmit(uart_buffer, UART_Data_Receive_Before_Terminator(uart_buffer, TERMINATOR_SYMBOL, BUFFER_SIZE));
	}
}


