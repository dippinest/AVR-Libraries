
#include "systimer.h"


volatile SYSTIMER_t __SYSTIMER = 0;

SYSTIMER_t SYSTIMER_Get_Value()
{
	return __SYSTIMER;
}


// обработчик прерывания системного таймера
//
// -------------------------------------------------------------------------------
// system timer interrupt handler
//
ISR(TIMER0_COMP_vect)
{
	++__SYSTIMER;
}


