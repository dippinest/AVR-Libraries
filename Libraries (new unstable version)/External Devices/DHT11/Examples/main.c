
#include "dht11.h"
#include "uart.h"


DHT11_Data_t dht11;


int main(void)
{
	UART_Initialize(9600, true, false);
	
	while (1)
	{
		// перед началом преобразования необходима подготовка.
		// Процедура инициализации является достаточно длительной
		// по времени (~20 мс), поэтому она вынесена отдельно для того,
		// чтобы у Вас юыла возможность реализовать её по-другому
		// (например, её неблокирующую реализацию)
		//
		// -------------------------------------------------------------------------------
		// Initialization is required before starting the conversion.
		// The preparing procedure is quite time-consuming (~20 ms),
		// so it is rendered separately so that you have the opportunity
		// to implement it in a different way
		// (for example, it is non-blocking implementation)
		//
		DHT11_Convert_Prepare();
		
		
		// при ошибке конвертации выводим ошибку
		//
		// -------------------------------------------------------------------------------
		// if there is a conversion error, an error is displayed
		//
		if (DHT11_Start_Convert(&dht11))
		{
			DEBUGPRINTLN("Error.");
		}
		else
		{
			UART_StringFmt_Transmit("Temp = %d *C\r\n", DHT11_Get_Integer_Temperature(&dht11));
			UART_StringFmt_Transmit("Hum  = %d  %%\r\n", DHT11_Get_Integer_Humidity(&dht11));
		}
		
		UART_NEW_LINE;
		
		_delay_ms(3000);
	}
}



