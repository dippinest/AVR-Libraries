
#include "uart0.h"


#define BUFFER_SIZE 16

uint8_t uart0_buffer[BUFFER_SIZE];


#define TERMINATOR_SYMBOL '@'


int main(void)
{
	UART0_Initialize(9600, true, true);
	
	while (1)
	{
		UART0_Data_Transmit(uart0_buffer, UART0_Data_Receive_Before_Terminator(uart0_buffer, TERMINATOR_SYMBOL, BUFFER_SIZE));
	}
}


