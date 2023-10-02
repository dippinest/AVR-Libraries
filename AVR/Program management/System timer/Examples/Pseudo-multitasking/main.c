

// Пример реализации псевдомногозадачности с помощью системного таймера
//
// Внимание! Выполняющиеся задачи не будут синхронизированны друг с другом.
// Чтобы избежать ошибок в синхронизации и доступа к общим ресурсам, используйте
// библиотеку Scheduller или полноценную ОСРВ (к примеру, FreeRTOS)
//
// -------------------------------------------------------------------------------
// An example of implementing pseudo-multitasking using a system timer
//
// Attention! Running tasks will not be synchronized with each other
// To avoid errors in synchronization and access to shared resources,
// use the Scheduler library or a full-fledged RTOS
// (for example, FreeRTOS)
//

#include <avr/sleep.h>

#include "uart.h"
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
	
	
	
	// переменные для хранения времени выполнения каждой задачи
	//
	// -------------------------------------------------------------------------------
	// variables for storing the execution time of each task
	//
	SYSTIMER_t timer0 = 0;
	SYSTIMER_t timer1 = 0;
	SYSTIMER_t timer2 = 0;
	SYSTIMER_t timer3 = 0;
	
	while (1)
	{
		SYSTIMER_Run_Task(&timer0, Task0, 100);  // run every 100  ticks
		SYSTIMER_Run_Task(&timer1, Task1, 200);  // run every 200  ticks
		SYSTIMER_Run_Task(&timer2, Task2, 500);  // run every 500  ticks
		SYSTIMER_Run_Task(&timer3, Task3, 1000); // run every 1000 ticks
		
		
		
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


