

#include <avr/interrupt.h>

#include <util/delay.h>

#include "softspi.h"
#include "tm74hc595.h"
#include "itoa.h"


// функция для работы "защёлки" регистра
//
// ===============================================================================
// function for register "latch" operation
//
void TM74HC595_Latches()
{
	PORTC |=  (1 << 3);
	
	asm("NOP");
	
	PORTC &= ~(1 << 3);
}





int16_t val = -200;

char string_buf[16];



// обработчик обновления таймера
// (для обслуживания динамической индикации таймера)
//
// ===============================================================================
// timer update handler
// (for maintenance of the dynamic timer display)
//
ISR(TIMER0_OVF_vect)
{
	TM74HC595_Put_Num_String(ITOA_Int16_To_String(val, 4), 4);
}


int main(void)
{
	DDRC |= (1 << 3);
	
	
	ITOA_Set_String_Buffer(string_buf);
	
	
	SOFTSPI_Initialize();
	
	
	TM74HC595_t tm74hc595 = TM74HC595_Create_Object(TM74HC595_Latches);

	TM74HC595_Set_Target_Object(&tm74hc595);
	

	
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
		++val; _delay_ms(200);
	}
}




