#define  F_CPU 16000000UL
#include <util/delay.h>

#include "AVR/Internal Peripherals/uart/uart.h"
#include "Crossplatform/numconvert/itohexa/itohexa.h"

static char str_buf[8];

int main(void)
{
	UART_Initialize(9600, true, true, false, false, false, UART_NUM_OF_DATA_BITS_8, UART_NUM_OF_STOP_BITS_1, UART_PARITY_BIT_NONE);
	
	unsigned char i = 0;
	
	while (1)
	{
		UART_String_Transmit("Counter = 0x"); UART_StringLn_Transmit(ITOHEXA_8bitNum_To_Hex_String(i++, false, str_buf));
		_delay_ms(200);
	}
}
