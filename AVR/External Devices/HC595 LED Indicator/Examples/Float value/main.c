
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

static float data = -7.00;

static char buf[8];


ISR(TIMER0_OVF_vect)
{
	HC595_LEDInd_Convert_Num_String_To_Symbols_Array(ITOA_Float_To_String(data, 2, 2), 4);
	HC595_LEDInd_Put_Symbols((uint8_t*)ITOA_Get_String_Buffer_Ptr(), 4);
}

int main(void)
{
	DDRD |= (1 << 4);
	
	
	ITOA_Set_String_Buffer(buf);
	
	SOFTSPI_Initialize();
	
	SOFTSPI_Set_CS_CallBack_Functions(CS_ON, CS_OFF);
	
	HC595_LEDInd_t indicator = HC595_LEDInd_Get_Device_Object();
	HC595_LEDInd_Set_Target_Device_Object(&indicator);
	
	
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


