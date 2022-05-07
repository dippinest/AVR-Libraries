
#define  F_CPU 16000000UL
#include <util/delay.h>

#include "uart.h"
#include "bcdcode.h"

int main(void)
{
	UART_Initialize(9600, true, false);
	
	uint8_t i = 0, bcd;
	
	while (1)
	{
		bcd = BCDCODE_UInt8_To_UInt8BCD(i);
		UART_StringFmt_Transmit("Counter: 0x%X (%d); BCD code: 0x%X; normal code: 0x%X\r\n", i, i, bcd, BCDCODE_UInt8BCD_To_UInt8(bcd));
		++i;
		
		_delay_ms(200);
	}
}
