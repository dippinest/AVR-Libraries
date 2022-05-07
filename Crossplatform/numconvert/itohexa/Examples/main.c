
#define  F_CPU 16000000UL
#include <util/delay.h>

#include "uart.h"
#include "itohexa.h"

static char str_buf[16];

int main(void)
{
	UART_Initialize(9600, true, false);
	
	ITOHEXA_Set_String_Buffer(str_buf);
	
	uint8_t i = 0;
	
	while (1)
	{
		UART_String_Transmit(ITOHEXA_8bitNum_To_HexString(i++, false)); UART_String_Transmit("; ");
		_delay_ms(200);
	}
}
