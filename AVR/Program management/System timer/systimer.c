
#include "systimer.h"


volatile SYSTIMER_t __SYSTIMER = 0;

SYSTIMER_t SYSTIMER_Get_Value()
{
	return __SYSTIMER;
}


// ===============================================================================


void SYSTIMER_Delay(SYSTIMER_t ticks)
{
	const SYSTIMER_t tagret_time = __SYSTIMER;
	
	while((__SYSTIMER - tagret_time) < ticks)
	{
		asm("nop");
	}
}


// ===============================================================================


SYSTIMER_Task_Params_t SYSTIMER_Get_Task_Params(SYSTIMER_t interval)
{
	SYSTIMER_Task_Params_t params;
	
	params.timer    = __SYSTIMER;
	params.interval = interval;
	
	return params;
}

void SYSTIMER_Run_Task(SYSTIMER_Task_Params_t *task_params, void (*task)())
{
	if ((__SYSTIMER - task_params->timer) > task_params->interval)
	{
		task_params->timer = __SYSTIMER;
		task();
	}
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


