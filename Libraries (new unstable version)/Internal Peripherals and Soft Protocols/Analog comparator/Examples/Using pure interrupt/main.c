
#include <avr/interrupt.h>

#include "anacomp.h"

#define LED_ON  (PORTC &= ~(1 << 5))
#define LED_OFF (PORTC |=  (1 << 5))


ISR(ANA_COMP_vect)
{
	ANACOMP_Set_Interrupt_Enable(false);
	
	if (ANACOMP_Get_State() == ANACOMP_STATE_IS_HIGH)
	{
		LED_ON;
	}
	else
	{
		LED_OFF;
	}
	
	ANACOMP_Set_Interrupt_Enable(true);
}

int main(void)
{
	ANACOMP_Set_Enable(true);
	ANACOMP_Set_Interrupt_Enable(true);
	ANACOMP_Direct_Input_Set_Connect(ANACOMP_DIRECT_INPUT_IS_CONNECTED_TO_INTERNAL_VOLTAGE_SOURCE);
	ANACOMP_Set_Interrupt_Type(ANACOMP_INTERRUPT_TYPE_ANY_CHANGE);
	
	DDRC |= (1 << 5);

	
	sei();
	
	while (1)
	{
	}
}

