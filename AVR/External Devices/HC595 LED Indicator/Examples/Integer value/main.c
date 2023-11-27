

#include <avr/interrupt.h>
#include <util/delay.h>

#include "softspi.h"
#include "hc595_ledind.h"
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
	HC595_LEDInd_Put_Num_String(ITOA_Int16_To_String(data, 4), 4);
}

int main(void)
{
	DDRD |= (1 << 4);
	
	ITOA_Set_String_Buffer(buf);
	
	SOFTSPI_Initialize();
	SOFTSPI_Set_CS_CallBack_Functions(CS_OFF, CS_ON);
	
	HC595_LEDInd_t indicator = HC595_LEDInd_Get_Device_Object();
	HC595_LEDInd_Set_Target_Device_Object(&indicator);
	
	
	
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


