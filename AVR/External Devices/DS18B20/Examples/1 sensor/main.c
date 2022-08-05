
#define F_CPU 16000000UL

#include <util/delay.h>

#include "uart.h"
#include "onewire.h"
#include "ds18b20.h"

int main(void)
{
	UART_Initialize(9600, true, false);
	
	DS18B20_Set_Resolution(DS18B20_12BIT_RESOLUTION);
	
	while (1)
	{
		DS18B20_Start_Convert(); _delay_ms(DS18B20_12BIT_RESOLUTION_CONVERT_TIMEOUT_MS);
		
		UART_StringFmt_Transmit("TEMP = %d *C\r\n", DS18B20_Get_Integer_Temperature());
	}
}
