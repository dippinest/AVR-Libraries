
#include <avr/io.h>
#include <stdint.h>

#include "delay.h"


int main(void)
{
	// настраиваем пин 0 порта PORTB на выход
	// -------------------------------------------------------------------------------
	// configure the pin 0 of the PORTB port to the output
	DDRB  = (1 << 0);
	PORTB = (1 << 1);
	
	while (1)
	{
		uint8_t i = 25;
		
		while (i)
		{
			PORTB ^= (1 << 0);
			
			// изменяем состояние пина с возрастающей скоростью благодаря функции Delay_Ms
			// -------------------------------------------------------------------------------
			// changing the pin state with increasing speed thanks to the Delay_Ms function
			Delay_Ms(i * 10);
			
			--i;
		}
	}
}


