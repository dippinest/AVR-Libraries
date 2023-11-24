
#include "uart.h"
#include "eeprom.h"


#define STR_SIZE 90

static char str[] = "Beatae plane aures, quae non vocem foris sonantem, sed intus auscultant veritatem docentem";


// приёмный буфер размером в страницу EEPROM
// -------------------------------------------------------------------------------
// this is the receiving buffer is the size of an EEPROM page

static char buffer[STR_SIZE];

int main(void)
{
	sei();
	
	UART_Initialize(9600, true, false);


	// запись данных из массива str в EEPROM по адресу 0x0000 (закомментировано)
	// -------------------------------------------------------------------------------
	// writing data from the str array to EEPROM at 0x0000 (commented out)
	// EEPROM_Write_Data(0x0000, str, STR_SIZE);
	
	// чтение данных из EEPROM по адресу 0x0000 в массив buffer
	// -------------------------------------------------------------------------------
	// reading data from EEPROM at address 0x0000 to buffer array
	EEPROM_Read_Data(0x0000, buffer, STR_SIZE);
	
	
	UART_Data_Transmit(buffer, STR_SIZE);
	
	while (1)
	{
	}
}


