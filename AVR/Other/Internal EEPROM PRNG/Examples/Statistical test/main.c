
#include "uart.h"
#include "eeprom_rand.h"

int main(void)
{
	UART_Initialize(9600, true, false);
	
	
	// Инициализация ГПСЧ. Адрес начальной рабочей ячейки - 0x0000.
	// Диапазон рабочих адресов - от 0x0000 до 0x0020 (32 dec)
	// -------------------------------------------------------------------------------
	// Initialization of the PRNG. The address of the initial working cell is 0x0000.
	// The range of working addresses is from 0x0000 to 0x0020 (32 dec)
	EEPROM_RAND_Initialize(0x0000, 32);
	
	
	// Количество сгенерированных чисел
	// -------------------------------------------------------------------------------
	// Number of generated numbers
	#define NUM_OF_VAL 10000
	
	// генерирация 10.000 чисел в диапазоне от 0 до 256
	// -------------------------------------------------------------------------------
	// generating 10,000 numbers in the range from 0 to 256
	for (uint16_t i = 0; i < NUM_OF_VAL; ++i)
	{
		uint8_t val = EEPROM_RAND_Get_8Bit_Value();
		
		UART_StringFmt_Transmit("%i, ", val);
	}
	
	while (1)
	{
	}
}


