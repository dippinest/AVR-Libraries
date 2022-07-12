
#include <util/delay.h>
#define F_CPU 16000000UL

#include "uart.h"
#include "itoa.h"
#include "softspi.h"
#include "max6675.h"

void CS_ON()
{
	PORTD &= ~(1 << 4);
}

void CS_OFF()
{
	PORTD |= (1 << 4);
}

static char buffer[16];

int main(void)
{
	UART_Initialize(9600, true, false);
	
	DDRD |= (1 << 4);
	
	SOFTSPI_Initialize();
	SOFTSPI_Set_CS_CallBack_Functions(CS_ON, CS_OFF);
	
	ITOA_Set_String_Buffer(buffer);
	
	while (1)
	{
		UART_StringFmt_Transmit("TEMP = %d *C\r\n", MAX6675_Get_Temperature_In_Celsius_Integer());
		_delay_ms(1000);
	}
}
