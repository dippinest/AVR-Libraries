#define  F_CPU 16000000UL
#include <util/delay.h>

#include "AVR/Internal Peripherals/uart/uart.h"
#include "Crossplatform/numconvert/itoa/itoa.h"

static char str_buf[32];

int main(void)
{
	UART_Initialize(9600, true, true, false, false, false, UART_NUM_OF_DATA_BITS_8, UART_NUM_OF_STOP_BITS_1, UART_PARITY_BIT_NONE);
	
	unsigned char i = 0;
	
	while (1)
	{
		UART_String_Transmit("Counter = "); UART_StringLn_Transmit(ITOA_UInt8_To_String(i++, 3, ' ', str_buf));
		_delay_ms(100);
	}
}
