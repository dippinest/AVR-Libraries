
#include <avr/interrupt.h>
#include <util/delay.h>

#include "softspi.h"
#include "hc595_led_indicator.h"
#include "itoa.h"

void CS_ON()
{
	PORTD &= ~(1 << 4);
}

void CS_OFF()
{
	PORTD |=  (1 << 4);
}

static int16_t data = -50;

static char buf[8];


ISR(TIMER0_OVF_vect)
{
	static uint8_t led_digits_counter = 0;
	HC595_LED_Indicator_Put_Num_String(ITOA_Int16_To_String(data, 4), 4, &led_digits_counter);
}

int main(void)
{
	ITOA_Set_String_Buffer(buf);
	
	DDRD |= (1 << 4);
	SOFTSPI_Initialize();
	
	SOFTSPI_Set_CS_CallBack_Functions(CS_ON, CS_OFF);
	
	// 2 ms = 500 Hz (for F_CPU = 16 MHz)
	TIMSK = (1 << TOIE0);
	TCNT0 = 255 - 250;
	TCCR0 = (1 << CS02);
	
	sei();
	
	while (1)
	{
		++data;
		_delay_ms(100);
	}
}


