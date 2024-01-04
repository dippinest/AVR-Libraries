
#include <avr/io.h>

#include "systimer.h"


int main(void)
{
	DDRB = (1 << 0);
	
	SYSTIMER_Initialize();
	
	
	sei();
	
	while (1)
	{	
		// задержка на 1000 тактов системного таймера (1000 мс)
		// -------------------------------------------------------------------------------
		// 1000 clock delay of the system timer (1000 ms)
		SYSTIMER_Delay(1000);
		
		// инвертируем значение порта PORT0
		// -------------------------------------------------------------------------------
		// invert the port value PORT0
		PORTB ^= (1 << 0);
	}
}




