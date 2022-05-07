
#define  F_CPU 16000000UL
#include <util/delay.h>

#include "uart.h"
#include "grayscode.h"

void print_bits(uint8_t val)
{
	for (int8_t i = 8; i >= 0; --i)
	{
		if (val & (1 << i))
		{
			UART_String_Transmit("1");
		}
		else
		{
			UART_String_Transmit("0");
		}
	}
}

int main(void)
{
	UART_Initialize(9600, true, false);
	
	uint8_t i = 0;
	
	while (1)
	{
		uint8_t i_grays = GRAYSCODE_UInt8_To_UInt8Grayscode(i);
		
		uint8_t i_new   = GRAYSCODE_UInt8Grayscode_To_UInt8(i_grays);
		
		UART_String_Transmit("i = ");         print_bits(i);
		UART_String_Transmit("; i_grays = "); print_bits(i_grays);
		UART_String_Transmit("; i_new = "); print_bits(i_new);
		
		UART_NEW_LINE;
		
		++i;
		
		_delay_ms(1000);
	}
}
