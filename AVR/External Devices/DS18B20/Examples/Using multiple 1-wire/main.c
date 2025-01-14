
#include <util/delay.h>

#include "uart.h"
#include "onewire.h"
#include "ds18b20.h"


int main(void)
{
	UART_Initialize(9600, true, false);
	
	ONEWIRE_t onewire_1 = ONEWIRE_Get_Object(T(DDRA), T(PINA), 0);
	ONEWIRE_t onewire_2 = ONEWIRE_Get_Object(T(DDRA), T(PINA), 1);
	
	
	ONEWIRE_Set_Target_Object(&onewire_1);
	DS18B20_Set_Resolution(DS18B20_12BIT_RESOLUTION);
	
	ONEWIRE_Set_Target_Object(&onewire_2);
	DS18B20_Set_Resolution(DS18B20_12BIT_RESOLUTION);
	
	while (1)
	{
		ONEWIRE_Set_Target_Object(&onewire_1);
		DS18B20_Start_Convert();
		
		ONEWIRE_Set_Target_Object(&onewire_2);
		DS18B20_Start_Convert();
		
		
		_delay_ms(DS18B20_12BIT_RESOLUTION_CONVERT_TIMEOUT_MS);
		
		
		ONEWIRE_Set_Target_Object(&onewire_1);
		UART_StringFmt_Transmit("1 DS18B20 Temp = %d *C\r\n", DS18B20_Get_Integer_Temperature());
		
		ONEWIRE_Set_Target_Object(&onewire_2);
		UART_StringFmt_Transmit("2 DS18B20 Temp = %d *C\r\n", DS18B20_Get_Integer_Temperature());
		
		UART_NEW_LINE;
	}
}


