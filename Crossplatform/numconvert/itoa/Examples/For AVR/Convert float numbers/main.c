
// This example demonstrates the saving of program memory
// when using the "ITOA_Float_To_String" function instead
// of "printf" ("sprintf") type functions. In the first case,
// with the value of the optimization flag -Os (optimization
// by code size, gcc-avr compiler), the code volume is 2066 bytes,
// while the similar code with the "sprintf" function takes 3540 bytes.
// Memory savings are (3540 - 2066) = 1474 bytes

#define F_CPU 16000000UL
#include <util/delay.h>
//#include <stdio.h>

#include "itoa.h"
#include "uart.h"

static char buffer[32];

int main(void)
{
	UART_Initialize(9600, true, false);
	
	ITOA_Set_String_Buffer(buffer);
	
	while (1)
	{
		//sprintf(buffer, "%.4f", 1234.4567); UART_StringLn_Transmit(buffer);
		
		UART_StringLn_Transmit(ITOA_Float_To_String(1234.4567, 5, 4)); // 5 int sign = 4 digits + sign '-'
		_delay_ms(1000);
	}
}
