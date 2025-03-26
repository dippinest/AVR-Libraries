

#include <avr/interrupt.h>
#include <util/delay.h>

#include "softspi.h"
#include "tm74hc595.h"
#include "itoa.h"

void CS_ON()
{
	PORTC &= ~(1 << 3);
}

void CS_OFF()
{
	PORTC |=  (1 << 3);
}

static int16_t data = -50;

static char buf[8];


ISR(TIMER0_OVF_vect)
{
	TM74HC595_Put_Num_String(ITOA_Int16_To_String(data, 4), 4);
}

int main(void)
{
	DDRC |= (1 << 3);
	
	
	ITOA_Set_String_Buffer(buf);
	
	SOFTSPI_Initialize();
	SOFTSPI_Set_CS_CallBack_Functions(CS_OFF, CS_ON);
	
	TM74HC595_t tm74hc595 = TM74HC595_Create_Object();
	TM74HC595_Set_Target_Object(&tm74hc595);
	
	
	
	// 2 ms = 500 Hz (for F_CPU = 16 MHz)
	TIMSK = (1 << TOIE0);
	TCNT0 = 255 - 250;
	TCCR0 = (1 << CS02);
	
	sei();
	
	while (1)
	{
		++data;
		_delay_ms(200);
	}
}



