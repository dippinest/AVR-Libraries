
#include "dht22.h"
#include "uart.h"


DHT22_Data_t dht22;


int main(void)
{
	UART_Initialize(9600, true, false);
	
	while (1)
	{
		DHT22_Convert_Prepare();
		
		
		// при ошибке конвертации выводим ошибку
		//
		// -------------------------------------------------------------------------------
		// if there is a conversion error, an error is displayed
		//
		if (DHT22_Start_Convert(&dht22))
		{
			DEBUGPRINTLN("Error.");
		}
		else
		{
			UART_StringFmt_Transmit("Temp = %d *C\r\n", DHT22_Get_Integer_Temperature(&dht22));
			UART_StringFmt_Transmit("Hum  = %d  %%\r\n", DHT22_Get_Integer_Humidity(&dht22));
		}
		
		UART_NEW_LINE;
		
		_delay_ms(3000);
	}
}



