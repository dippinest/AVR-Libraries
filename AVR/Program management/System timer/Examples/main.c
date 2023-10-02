

// Пример замера времени выполнения участка кода с помощью системного таймера
//
// -------------------------------------------------------------------------------
// Example of measuring the execution time of a section of code using a system timer


#include <util/delay.h>

#include "uart.h"
#include "systimer.h"


// вы можете непосредственно использовать переменную системного таймера
// __SYSTIMER, объявив её следующим образом, однако это опасно,
// так как ей случайно можно присвоить другое значение, нарушив работу
// других частей кода. Для безопасности вместо использования переменной
// __SYSTIMER используйте функцию SYSTIMER_Get_Value()
//
// -------------------------------------------------------------------------------
// you can directly use the system timer variable __SYSTIMER
// by declaring it as follows, however, this is dangerous, since it
// can accidentally be assigned a different value, disrupting the
// operation of other parts of the code. For security, instead of
// using the __SYSTIMER variable, use the
// SYSTIMER_Get_Value() function
//
extern volatile SYSTIMER_t __SYSTIMER;


int main(void)
{
	UART_Initialize(9600, true, false);
	
	SYSTIMER_Initialize();
	
	
	// обязательно включите глобальные прерывания
	// -------------------------------------------------------------------------------
	// be sure to enable global interrupts
	sei();
	
	
	SYSTIMER_t start = __SYSTIMER; // SYSTIMER_t start = SYSTIMER_Get_Value();
	
	
	// имитация долгих и сложных вычислений
	// -------------------------------------------------------------------------------
	// simulation of long and complex calculations
	//
	for (uint32_t i = 0; i < 1000000UL; ++i)
	{
		asm("nop");
	}
	
	SYSTIMER_t stop = __SYSTIMER; // SYSTIMER_t stop = SYSTIMER_Get_Value();
	
	
	UART_StringFmt_Transmit("Execution time = %d ticks\r\n", (stop - start));
	
	while (1)
	{
	}
}



