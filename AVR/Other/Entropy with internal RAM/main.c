

// ===============================================================================
//
// Пример получения случайного значения для начальной инициализации ГПСЧ
// с помощью неинициализированной внутренней RAM памяти.
//
// Для различных реализаций ГПСЧ (генераторов псевдослучайных чисел) для их
// инициализации необходимо начальное значение, на основе которого в дальнейшем
// генерируется псевдослучайная последовательность. Очевидно, что такое начальное
// значение ГПСЧ при каждом запуске программы должно быть разным, иначе генерируемая
// последовательность будет каждый раз повторяться.
//
// Получить такое начальное значение можно из внешней периферии:
// АЦП, внешних устройств и т.д. Однако в некоторых ситуациях эти источники
// энтропии использовать затруднительно или вовсе невозможно (к примеру, в некоторых
// старых моделях микроконтроллеров отсутствует АЦП). В таком случае одним из решений
// может быть использование свойства внутренней RAM памяти при подаче питания.
// В момент подачи напряжения питания в ячейки RAM неинициализированны:
// в них находится "мусор", то есть случайные значения (этот эффект объясняется
// разбросом технологических параметров транзисторов ячеек памяти, тепловым шумом,
// остаточным зарядом и другими причинами).
// Используя эти значения, можно получить случайное значение для инициализации ГСПЧ.
//
// Внимание! Данный алгоритм работает ТОЛЬКО ПРИ ВКЛЮЧЕНИИ ПИТАНИЯ МК!
// При перезагрузке с помощью RESET или WDT алгоритм НЕ РАБОТАЕТ,
// поскольку значения в RAM сохраняются.
// Используйте этот алгоритм единожды при включении питания устройства!
//
// -------------------------------------------------------------------------------
//
// An example of obtaining a random value for initializing the PRNG using an external RC circuit.
//
// For various implementations of PRNGs (pseudorandom number generators) to
// initialize them, an initial value is needed, based on which a pseudorandom
// sequence is subsequently generated.
// Obviously, this initial value of the RNG must be different each time
// the program is started, otherwise the generated sequence will be repeated each time.
//
// You can get this initial value from external peripherals: ADCs, external devices, etc.
// However, in some situations it is difficult or impossible to use these sources of entropy
// (for example, some older models of microcontrollers lack an ADC). In this case,
// one solution may be to use the internal RAM memory property when power is applied.
// When the power supply voltage is applied to RAM cells, they are uninitialized:
// they contain "garbage", that is, random values (this effect is explained by the spread
// of technological parameters of memory cell transistors, thermal noise, residual charge,
// and other reasons).
// Using these values, you can get a random value to initialize the RNG.
//
// Attention! This algorithm ONLY works WHEN THE MK IS POWERED ON!
// When rebooting using RESET or WDT, the algorithm DOES NOT WORK because
// the values in RAM are saved.
// Use this algorithm once when the device is powered on!
//
// ===============================================================================




#include <stdint.h>
#include <stdlib.h>

#include <util/delay.h>

#include "uart.h"



// функции для получения энтропийного (случайного значения) 16 и 32 бит
//
// -------------------------------------------------------------------------------
// functions for obtaining an entropy (random value) of 16 and 32 bits
//
uint16_t Get_16bit_Entropy_From_Internal_RAM()
{
	extern uint16_t __bss_end;
	
	volatile uint16_t rnd_data = 0;
	volatile uint16_t *ptr = &__bss_end;
	
	
	for (uint8_t i = 0; i < 64; ++i)
	{
		rnd_data ^= ptr[i];
	}
	
	return rnd_data;
}

uint32_t Get_32bit_Entropy_From_Internal_RAM()
{
	extern uint16_t __bss_end;
	
	volatile uint32_t rnd_data = 0;
	volatile uint16_t *ptr = &__bss_end;
	
	
	for (uint8_t i = 0; i < 32; ++i)
	{
		rnd_data ^= ptr[i];
	}
	
	return rnd_data;
}


int main(void)
{
	UART_Initialize(9600, true, false);
	
	
	// ВНИМАНИЕ! Функция работает ЕДИНОЖДЫ ПРИ ВКЛЮЧЕНИИ ПИТАНИЯ!
	//
	// -------------------------------------------------------------------------------
	// ATTENTION! The function works ONCE WHEN THE POWER IS TURNED ON!
	//
	const uint32_t random_value_with_int_ram = Get_32bit_Entropy_From_Internal_RAM();
	
	UART_StringFmt_Transmit("Random value: %d\r\n\r\n", random_value_with_int_ram);
	
	
	
	// Используйте полученную энтропию для инициализации любого ГСПЧ
	//
	// -------------------------------------------------------------------------------
	// Use the resulting entropy to initialize the any PRNG
	//
	srand(random_value_with_int_ram);
	
	
	
	while (1)
	{
		UART_StringFmt_Transmit("Rand value = %d\r\n", rand()); _delay_ms(1000);
	}
}




