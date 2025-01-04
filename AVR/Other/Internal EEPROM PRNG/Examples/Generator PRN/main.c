

#include <util/delay.h>

#include <stdint.h>

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
	
	while (1)
	{
		// Генерация 8-ми битного псевдослучайного значения
		// -------------------------------------------------------------------------------
		// Generating an 8-bit pseudo-random value
		uint8_t seed = EEPROM_RAND_Get_8Bit_Value();
		
		UART_Byte_Transmit(seed); _delay_ms(100);
	}
}



