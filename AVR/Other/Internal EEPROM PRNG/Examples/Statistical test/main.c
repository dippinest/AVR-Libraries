
#include "uart.h"
#include "eeprom_rand.h"

int main(void)
{
	UART_Initialize(9600, true, false);
	
	
	#define NUM_OF_VAL 10000
	
	// генерирация 10.000 чисел в диапазоне от 0 до 256
	// -------------------------------------------------------------------------------
	// generating 10,000 numbers in the range from 0 to 256
	for (uint16_t i = 0; i < NUM_OF_VAL; ++i)
	{
		// Генерирация 8-ми битного псевдослучайного значения с использованием
		// диапазона рабочих адресов от 0x00 до 0x20. Основная ячейка - 0x00
		// -------------------------------------------------------------------------------
		// Generating an 8-bit pseudo-random value using a range of operating
		// addresses from 0x00 to 0x20. The main cell is 0x00
		uint8_t val = EEPROM_RAND_Get_8Bit_Value(0x00, 0x20);
		
		UART_StringFmt_Transmit("%i, ", val);
	}
	
	while (1)
	{
	}
}


