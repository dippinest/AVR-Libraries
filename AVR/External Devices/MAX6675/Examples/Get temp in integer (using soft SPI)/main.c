
// ATN! to run the example, be sure to uncomment out the
// MAX6675_USE_SPI_CS_CALLBACKS macro in the max6675_configuration.h file!

#include <util/delay.h>

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
