
#include <stdbool.h>

#define  F_CPU 16000000UL
#include <util/delay.h>

#include "uart.h"
#include "itoa.h"

static char string_buffer[32];

int main(void)
{
	UART_Initialize(9600, true, false);
	
	ITOA_Set_String_Buffer(string_buffer);
	
	int8_t i = 0;
	
	while (1)
	{
		UART_String_Transmit("Counter = "); UART_StringLn_Transmit( ITOA_Int8_To_String(++i, 4) ); // 4 = 3 digits + sign '-'
		_delay_ms(200);
	}
}
