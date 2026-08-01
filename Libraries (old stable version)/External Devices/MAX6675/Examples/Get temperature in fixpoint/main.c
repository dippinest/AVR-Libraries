

#include <util/delay.h>

#include "uart.h"
#include "softspi.h"
#include "max6675.h"

#include "fixpoint.h"



// функции переключения вывода CS (Chip Select Pin)
//
// ===============================================================================
//
// CS output switching functions (Chip Select Pin)
//
void CS_Set_Active()
{
	PORTA &= ~(1 << 3);
}

void CS_Set_Inactive()
{
	PORTA |=  (1 << 3);
}



char string_buffer[16];


int main(void)
{
	DDRA |= (1 << 3);
	
	
	FIXPoint_Set_String_Buffer(string_buffer);
	
	UART_Initialize(9600, true, false);
	
	SOFTSPI_Initialize();
	SOFTSPI_Set_CS_Callback_Functions(CS_Set_Active, CS_Set_Inactive);
	
	
	// переменная со значением температуры
	//
	// ===============================================================================
	//
	// a variable with a temperature value
	//
	uint16_t temperature;
	
	while (1)
	{
		// если термопара исправна и подключена, выводим температуру
		// (иначе выводим сообщение об ошибке)
		//
		// ===============================================================================
		//
		// if the thermocouple is working properly and connected,
		// we display the temperature (otherwise we display an error message)
		//
		if (MAX6675_Get_Temperature_In_Celsius_Fixpoint_2Bit(&temperature))
		{
			UART_StringFmt_Transmit("Temperature = %s *C\r\n", FIXPoint_Int16FP_To_String(((int16_t)temperature * 25), 4, 2));
		}
		else
		{
			UART_StringFmt_Transmit("Error! The thermocouple is disconnected or faulty!\r\n");
		}
		
		_delay_ms(1000);
	}
}




