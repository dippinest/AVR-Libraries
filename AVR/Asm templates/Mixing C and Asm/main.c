
// Это пример совместного использования языка ассемблера в проекте на языке Си.
// В этом примере на языке ассемблера реализуются функции записи битовой маски
// в байт по указателю (в том числе и в порт).
//
// -------------------------------------------------------------------------------
// This is an example of sharing assembly language in a C project. In this example,
// the functions of writing a bit mask to a byte by pointer (including to the port)
// are implemented in assembly language.
//
// ===============================================================================

#include <avr/io.h>

#include <util/delay.h>
#define F_CPU 16000000UL

#include "asmroutine.h"

int main(void)
{
	DDRD |= (1 << 5) | (1 << 7);
	
	while (1)
	{
		Set_BitMask(&PORTD, (1 << 5) | (1 << 7));   _delay_ms(100);
		
		Reset_BitMask(&PORTD, (1 << 5) | (1 << 7)); _delay_ms(100);
	}
}
