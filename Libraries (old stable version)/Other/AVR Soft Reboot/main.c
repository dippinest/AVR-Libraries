
#include <avr/io.h>
#include <avr/interrupt.h>

#include <avr/wdt.h>

// функция программной перезагрузки микроконтроллера на основе watchdog таймера
//
// -------------------------------------------------------------------------------
// function of software restart of the microcontroller based on the watchdog timer
//
void Soft_Reboot()
{
	// отключаем все прерывания
	//
	// -------------------------------------------------------------------------------
	// disabling all interrupts
	//
	cli();
	
	// устанавливаем значение WDT на минимально возможный период
	// (в данном случае - 15 мс)
	//
	// -------------------------------------------------------------------------------
	// setting the WDT value to the minimum possible period
	// (in this case - 15 ms)
	//
	wdt_enable(WDTO_15MS);

	// в этом месте микроконтроллер будет перезагружен через 15 мс
	//
	// -------------------------------------------------------------------------------
	// at this point the microcontroller will reboot after 15 ms
	//
	while(1);
}



#include <util/delay.h>

int main(void)
{
	// мигание светодиодом для наглядности
	//
	// -------------------------------------------------------------------------------
	// LED flashing for clarity
	//
	DDRD = (1 << 7);
	
	PORTD |= (1 << 7);  _delay_ms(500);
	PORTD &= ~(1 << 7); _delay_ms(500);
	
	
	// вызов функции программной перезагрузки микроконтроллера
	//
	// -------------------------------------------------------------------------------
	// calling the microcontroller's software reboot function
	//
	Soft_Reboot();
	






	// до бесконечного цикла программа НИКОГДА НЕ ДОЙДЁТ!
	//
	// -------------------------------------------------------------------------------
	// the program WILL NEVER REACH an infinite loop!
	//
	while (1)
	{
	}
}







