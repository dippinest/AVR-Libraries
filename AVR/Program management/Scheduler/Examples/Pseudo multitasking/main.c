
#include <avr/sleep.h>

#include "scheduler.h"
#include "scheduler_configuration.h"


// Задачи для переключения пинов порта (мигания соответствующими светодиодами)
// -------------------------------------------------------------------------------
// Tasks for switching port pins (flashing the corresponding LEDs)

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
	DDRB = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
	
	
	// При создании задачи указываем её номер, колбэк, статус и интервал выполнения
	// -------------------------------------------------------------------------------
	// When creating a task, we specify its number, callback, status and execution interval
	
	Scheduler_Create_Task(0, Task0, SCHEDULER_TASK_IS_ACTIVE, 100);  // run every 100  ms
	Scheduler_Create_Task(1, Task1, SCHEDULER_TASK_IS_ACTIVE, 250);  // run every 250  ms
	Scheduler_Create_Task(2, Task2, SCHEDULER_TASK_IS_ACTIVE, 500);  // run every 500  ms
	Scheduler_Create_Task(3, Task3, SCHEDULER_TASK_IS_ACTIVE, 1000); // run every 1000 ms
	
	
	Scheduler_Tasks_Prepare();
	
	
	// Инициализация системного таймера и включение глобальных прерываний
	// -------------------------------------------------------------------------------
	// Initializing the system timer and enabling global interrupts
	
	SYSTIMER_Initialize();
	
	sei();
	
	while (1)
	{
		Scheduler_Run();
		
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


