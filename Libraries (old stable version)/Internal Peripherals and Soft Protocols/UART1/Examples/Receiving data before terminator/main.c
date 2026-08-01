
#include "uart1.h"


#define BUFFER_SIZE 16

uint8_t uart1_buffer[BUFFER_SIZE];


#define TERMINATOR_SYMBOL '@'


int main(void)
{
	UART1_Initialize(9600, true, true);
	
	while (1)
	{
		UART1_Data_Transmit(uart1_buffer, UART1_Data_Receive_Before_Terminator(uart1_buffer, TERMINATOR_SYMBOL, BUFFER_SIZE));
	}
}


