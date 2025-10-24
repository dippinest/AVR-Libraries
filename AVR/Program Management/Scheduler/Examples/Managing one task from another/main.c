
#include <avr/sleep.h>

#include "scheduler.h"
#include "scheduler_configuration.h"


// Задача для переключения пина порта (мигания светодиодом)
// -------------------------------------------------------------------------------
// Task for switching port pin (flashing the LED)

void Task0()
{
	PORTB ^= (1 << 0);
}


// Задача, управляющая состояние задачи Task0
// -------------------------------------------------------------------------------
// This task manages the state of the Task0 task

void Task1()
{
	// При каждом вызове этой задачи будем переключать
	// состояние активности задачи Task0
	// -------------------------------------------------------------------------------
	// Each time this task is called,
	// we will switch the activity state of the Task0 task
	
	bool task0_is_active = Scheduler_Task_Is_Active(0);
	
	task0_is_active = !task0_is_active;
	
	Scheduler_Set_Task_Active(0, task0_is_active);
}


int main(void)
{
	DDRB = (1 << 0);
	
	
	// При создании задачи указываем её номер, колбэк, статус и интервал выполнения
	// -------------------------------------------------------------------------------
	// When creating a task, we specify its number, callback, status and execution interval
	
	Scheduler_Create_Task(0, Task0, SCHEDULER_TASK_IS_ACTIVE,  50);  // run every  50  ms
	Scheduler_Create_Task(1, Task1, SCHEDULER_TASK_IS_ACTIVE, 500);  // run every 500  ms
	
	
	Scheduler_Tasks_Prepare();
	
	
	// Инициализация системного таймера и включение глобальных прерываний
	// -------------------------------------------------------------------------------
	// Initializing the system timer and enabling global interrupts
	
	SYSTIMER_Initialize();
	sei();
	
	while (1)
	{
		// в бесконечном цикле запускаем обработчик планировщика задач
		// -------------------------------------------------------------------------------
		// in an endless loop, we run the task scheduler handler
		//
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



