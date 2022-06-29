
#define  F_CPU 16000000UL

#include <avr/interrupt.h>
#include "uart.h"

#define BUF_SIZE 6
static char string_buffer[BUF_SIZE];

static void fsm(uint8_t byte)
{
	static uint8_t i = 0;
	
	string_buffer[i] = (char)byte;
	
	++i;
	
	if (i >= BUF_SIZE)
	{
		UART_Set_End_Of_Reception_Interrupt_Enable(false);
		
		UART_StringFmt_Transmit("your %d characters are: ", BUF_SIZE); UART_Data_Transmit(string_buffer, BUF_SIZE);
		
		i = 0;
		
		UART_Set_End_Of_Reception_Interrupt_Enable(true);
	}
}

ISR (USART_RXC_vect)
{
	fsm(UDR);
}

int main(void)
{
	UART_Initialize(9600, true, true);
	
	UART_StringFmt_Transmit("send any %d characters to the microcontroller...\r\n\r\n", BUF_SIZE);
	
	UART_Set_End_Of_Reception_Interrupt_Enable(true); sei();
	
	while (1)
	{
	}
}
