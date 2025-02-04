

// Пример реализации псевдомногозадачности с помощью системного таймера
//
// Внимание! Выполняющиеся задачи не будут синхронизированны друг с другом.
// Чтобы избежать ошибок в синхронизации и доступа к общим ресурсам, используйте
// полноценную ОСРВ (к примеру, FreeRTOS) или библиотеку scheduler.h
//
// -------------------------------------------------------------------------------
// An example of implementing pseudo-multitasking using a system timer
//
// Attention! Running tasks will not be synchronized with each other
// To avoid errors in synchronization and access to shared resources,
// use the full-fledged RTOS (for example, FreeRTOS) or the scheduler.h library
//

#include <avr/sleep.h>


#include "systimer.h"


// отдельные задачи для управления пинами GPIO
//
// -------------------------------------------------------------------------------
// separate tasks for managing GPIO pins
//
void Task0()
{
	PORTB ^= (1 << 0);
}

void Task1()
{
	PORTB ^= (1 << 1);
}

void Task2()
{
	PORTB ^= (1 << 2);
}

void Task3()
{
	PORTB ^= (1 << 3);
}


int main(void)
{
	DDRB  = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
	
	
	SYSTIMER_Initialize();
	
	
	// обязательно включите глобальные прерывания
	// -------------------------------------------------------------------------------
	// be sure to enable global interrupts
	sei();
	
	
	
	// переменные для хранения параметров выполнения каждой задачи
	//
	// -------------------------------------------------------------------------------
	// variables for storing the execution params of each task
	//
	SYSTIMER_Task_Params_t tparams0 = SYSTIMER_Create_Task_Params(100);
	SYSTIMER_Task_Params_t tparams1 = SYSTIMER_Create_Task_Params(200);
	SYSTIMER_Task_Params_t tparams2 = SYSTIMER_Create_Task_Params(500);
	SYSTIMER_Task_Params_t tparams3 = SYSTIMER_Create_Task_Params(1000);
	
	while (1)
	{
		SYSTIMER_Run_Task(&tparams0, Task0);  // run every 100  ticks
		SYSTIMER_Run_Task(&tparams1, Task1);  // run every 200  ticks
		SYSTIMER_Run_Task(&tparams2, Task2);  // run every 500  ticks
		SYSTIMER_Run_Task(&tparams3, Task3);  // run every 1000 ticks
		
		
		
		// при желании после отработки всех задач вы можете
		// усыпить процессор с целью экономии энергии
		//
		// -------------------------------------------------------------------------------
		// if desired, after working out all the tasks,
		// you can put the processor to sleep in order to save energy
		//
		sleep_enable();
		sleep_cpu();
	}
}


