

#include <util/delay.h>

#include "uart.h"
#include "softspi.h"
#include "max6675.h"



// функции переключения вывода CS (Chip Select Pin)
//
// ===============================================================================
// CS output switching functions (Chip Select Pin)
//
void CS_High()
{
	PORTA &= ~(1 << 3);
}

void CS_Low()
{
	PORTA |=  (1 << 3);
}


int main(void)
{
	DDRA |= (1 << 3);
	
	
	UART_Initialize(9600, true, false);
	
	SOFTSPI_Initialize();
	SOFTSPI_Set_CS_Callback_Functions(CS_High, CS_Low);
	
	while (1)
	{
		UART_StringFmt_Transmit("TEMP = %d *C\r\n", MAX6675_Get_Temperature_In_Celsius_Integer()); _delay_ms(1000);
	}
}





