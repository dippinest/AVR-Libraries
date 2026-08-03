
#include "dht22.h"
#include "uart.h"
#include "fixpoint.h"


DHT22_Data_t dht22;

char string_buffer[16];


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
			UART_String_Transmit("Temp = ");
			
			UART_String_Transmit(
				FIXPoint_Int16FP_To_String(string_buffer, 2, DHT22_Get_FIXPoint_1_Fractional_Digit_Temperature(&dht22), 2, 1, ' ', '.')
			);
			
			UART_StringLn_Transmit(" *C");
			
			
			
			UART_String_Transmit("Hum  = ");
			
			UART_String_Transmit(
				FIXPoint_Int16FP_To_String(string_buffer, 2, DHT22_Get_FIXPoint_1_Fractional_Digit_Humidity(&dht22), 2, 1, ' ', '.')
			);
			
			UART_StringLn_Transmit(" %");
		}
		
		UART_NEW_LINE;
		
		
		_delay_ms(3000);
	}
}



