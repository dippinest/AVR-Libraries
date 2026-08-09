

#include "systimer.h"



// переменная для хранения системного времени
// -------------------------------------------------------------------------------
// variable for storing the system time
//
volatile SYSTIMER_t __SYSTIMER = 0;


SYSTIMER_t SYSTIMER_Get_Value()
{
	cli();

	SYSTIMER_t current_value = __SYSTIMER;

	sei();

	
	return current_value;
}



// ===============================================================================



void SYSTIMER_Delay(SYSTIMER_t ticks)
{
	const SYSTIMER_t target_time = __SYSTIMER;
	
	while((__SYSTIMER - target_time) < ticks)
	{
		asm("nop");
	}
}



// ===============================================================================



void SYSTIMER_Initialize_Task_Params(SYSTIMER_Task_Params_t *task_params, SYSTIMER_t interval)
{
	(*task_params).timer    = __SYSTIMER;
	(*task_params).interval = interval;
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
ISR(SYSTIMER_VECTOR_INTERRUPT)
{
	cli();
	
	++__SYSTIMER;
	
	sei();
}




