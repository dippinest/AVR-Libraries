#include <avr/interrupt.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#include "uart.h"

static void fsm(uint8_t byte)
{
	static uint8_t i = 0;
	
	UART_StringFmt_Transmit("A receive UART interrupt was triggered! Byte UDR (char) = \"%c\"; i = %d\r\n", (char)byte, i++);
}

ISR (USART_RXC_vect)
{
	fsm(UDR);
}

int main(void)
{
	sei();
	
	UART_Initialize(9600, true, true, false, false, true, UART_NUM_OF_DATA_BITS_8, UART_NUM_OF_STOP_BITS_1, UART_PARITY_BIT_NONE);
	
	while (1)
	{
	}
}
