

#include <util/delay.h>

#include <stdint.h>
#include <stdlib.h>

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
	
	// Генерирация 16-ми битного псевдослучайного сида (семени) для стандартного ГПСЧ
	// -------------------------------------------------------------------------------
	// Generation of a 16-bit pseudorandom seed for the standard rand() PRNG
	srand(EEPROM_RAND_Get_16Bit_Value());
	
	while (1)
	{
		// Генерирация 8-ми битного псевдослучайного значения с использованием
		// стандартной функции rand()
		// -------------------------------------------------------------------------------
		// Generating an 8-bit pseudorandom value using the standard rand() function
		uint8_t seed = (uint8_t)rand();
		
		UART_Byte_Transmit(seed); _delay_ms(100);
	}
}





