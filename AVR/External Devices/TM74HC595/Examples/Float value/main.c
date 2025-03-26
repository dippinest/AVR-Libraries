


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

static float data = -7.00;

static char buf[8];


ISR(TIMER0_OVF_vect)
{
	TM74HC595_Convert_Num_String_To_Symbols_Array(ITOA_Float_To_String(data, 2, 2), 4);
	TM74HC595_Put_Symbols((uint8_t*)ITOA_Get_String_Buffer_Ptr(), 4);
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
		data += 0.01;
		_delay_ms(200);
	}
}







