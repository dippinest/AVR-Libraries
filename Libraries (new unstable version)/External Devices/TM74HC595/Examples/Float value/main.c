

#include <avr/interrupt.h>

#include <util/delay.h>

#include "softspi.h"
#include "tm74hc595.h"
#include "ftoa.h"




// объект индикатора TM74HC595
//
// ===============================================================================
// TM74HC595 indicator object
//
TM74HC595_t tm74hc595;




// функция для работы "защёлки" регистра
//
// ===============================================================================
// function for register "latch" operation
//
void TM74HC595_Latches()
{
	PORTA |=  (1 << 4);
	
	asm("NOP");
	
	PORTA &= ~(1 << 4);
}





float val = -20;

char string_buf[8];



// обработчик обновления таймера
// (для обслуживания динамической индикации таймера)
//
// ===============================================================================
// timer update handler
// (for maintenance of the dynamic timer display)
//
ISR(TIMER0_OVF_vect)
{
	TM74HC595_Put_Num_String(&tm74hc595, FTOA_Float32_To_String(string_buf, val, 3, 1, '.'), 4);
}


int main(void)
{
	DDRA |= (1 << 4);
	
	
	SOFTSPI_Initialize();
	
	
	TM74HC595_Initialize_Object(&tm74hc595, TM74HC595_Latches);
	
	
	
	// 2 ms = 500 Hz (for F_CPU = 16 MHz)
	//
	TIMSK = (1 << TOIE0);
	TCNT0 = 255 - 250;
	TCCR0 = (1 << CS02);
	
	
	// не забудьте включить глобальные прерывания
	//
	// -------------------------------------------------------------------------------
	// don't forget to enable global interrupts
	//
	sei();
	
	
	while (1)
	{
		val += 0.1; _delay_ms(200);
	}
}




