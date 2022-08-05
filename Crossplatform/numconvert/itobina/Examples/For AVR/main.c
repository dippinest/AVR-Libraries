
#define F_CPU 16000000UL
#include <util/delay.h>

#include "uart.h"
#include "itobina.h"

static char buf[16];

int main(void)
{
	UART_Initialize(9600, true, false);
	ITOBINA_Set_String_Buffer(buf);
	
	uint8_t val = 0;
	
	while (1)
	{
		UART_StringFmt_Transmit("val = %d -> 0b%s\r\n", val, ITOBINA_8bitNum_To_BinString(val));
		
		++val;
		_delay_ms(500);
	}
}
