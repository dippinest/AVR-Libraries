

// Пример замера времени выполнения участка кода с помощью системного таймера
//
// -------------------------------------------------------------------------------
// Example of measuring the execution time of a section of code using a system timer

#include "uart.h"
#include "systimer.h"

int main(void)
{
	UART_Initialize(9600, true, false);
	
	SYSTIMER_Initialize();
	
	
	// обязательно включите глобальные прерывания
	// -------------------------------------------------------------------------------
	// be sure to enable global interrupts
	sei();
	
	
	SYSTIMER_t start = SYSTIMER_Get_Value();
	
	
	// имитация долгих и сложных вычислений
	// -------------------------------------------------------------------------------
	// simulation of long and complex calculations
	//
	for (uint32_t i = 0; i < 1000000UL; ++i)
	{
		asm("nop");
	}
	
	SYSTIMER_t stop = SYSTIMER_Get_Value();
	
	
	UART_StringFmt_Transmit("Execution time = %d ticks\r\n", (stop - start));
	
	while (1)
	{
	}
}



