

// ===============================================================================
//
// В данном примере демонстрируется работа с мьютексами и очередями задач.
//
// Здесь применён модуль UART, защищаемый мьютексом и очередь задач.
// Каждая из задач добавляет в очередь задание на отпраку своих данных,
// причём каждая из задач вызывается с разным интервалом.
//
// Для простоты понимания в код добавлено множество комментариев
//
// -------------------------------------------------------------------------------
//
// This example demonstrates working with mutexes and task queues.
//
// A UART module protected by a mutex and a task queue are used here.
// Each of the tasks adds a task to the queue to send its data,
// and each of the tasks is called at a different interval.
//
// A lot of comments have been added to the code for ease of understanding
//
// ===============================================================================


#include <avr/sleep.h>

#include "scheduler.h"
#include "scheduler_configuration.h"

#include "task_queue.h"

#include "uart.h"
#include "uart_async.h"


// создаём статическую переменную, хранящую очередь задач
// -------------------------------------------------------------------------------
// create a static variable that stores the task queue
static Task_Queue_t uart_queue;


// создаём статическую переменную, хранящую мьютекс для работы с модулем UART
// -------------------------------------------------------------------------------
// create a static variable that stores a mutex for working with the UART module
//
static Scheduler_Mutex_t uart_mutex;



// функции, реализующие работу с UART совместно с мьютексом
// -------------------------------------------------------------------------------
// functions that implement working with UART together with mutex
//
void Send_Msg_0()
{
	UART_Async_String_Transmit("Msg 0 was send!  ");
}

void Send_Msg_1()
{
	UART_Async_String_Transmit("Msg 1 was send!  ");
}

void Send_Msg_2()
{
	UART_Async_StringLn_Transmit("Msg 2 was send!");
}



// задачи, реализующие добавление соответствующих функций в очередь на исполнение
// -------------------------------------------------------------------------------
// tasks implementing the addition of appropriate functions to the queue for execution
//
void Task0()
{
	Task_Queue_Push(&uart_queue, Send_Msg_0);
}

void Task1()
{
	Task_Queue_Push(&uart_queue, Send_Msg_1);
}

void Task2()
{
	Task_Queue_Push(&uart_queue, Send_Msg_2);
}



// задача, реализующая управление потоком задач из очереди
// -------------------------------------------------------------------------------
// this is a task that implements control of the flow of tasks from the queue
//
void UART_Msg_Scheduler()
{
	if (Scheduler_Mutex_Is_Unlock(&uart_mutex))
	{
		Scheduler_Mutex_Set_Lock(&uart_mutex);
		
		void (*Target_Task)(void) = Task_Queue_Pop(&uart_queue);
		
		if (Target_Task != NULL)
		{
			Target_Task();
		}
		else
		{
			Scheduler_Mutex_Set_Unlock(&uart_mutex);
		}
	}
}



// колбэк, реализующий сброс мьютекса UART при завершении отправки данных
// -------------------------------------------------------------------------------
// this is a callback that implements the reset of the UART mutex at the end of sending data
//
void UART_Mutex_Unlock()
{
	Scheduler_Mutex_Set_Unlock(&uart_mutex);
}


int main(void)
{
	UART_Initialize(9600, true, false);
	UART_Async_Set_Transmittion_Enable(true);
	UART_Async_Set_Transmittion_Callback_Function(UART_Mutex_Unlock);
	
	
	// инициализация мьютекса UART
	// -------------------------------------------------------------------------------
	// initializing the UART mutex
	//
	uart_mutex = Scheduler_Create_Mutex();
	
	
	// инициализация статического массива задач и очереди на его основе
	// размер очереди - 3)
	// -------------------------------------------------------------------------------
	// initialization of a static array of tasks and a queue based
	// on it (queue size - 3)
	//
	static void (*uart_queue_buf[3])();
	
	uart_queue = Task_Queue_Create_Object(uart_queue_buf, 3);
	
	
	// при создании задачи указываем её номер, колбэк, статус и интервал выполнения
	// -------------------------------------------------------------------------------
	// when creating a task, we specify its number, callback, status and execution interval
	//
	Scheduler_Create_Task(0, Task0, SCHEDULER_TASK_IS_ACTIVE,  250);  // run every  250  ms
	Scheduler_Create_Task(1, Task1, SCHEDULER_TASK_IS_ACTIVE,  500);  // run every  500  ms
	Scheduler_Create_Task(2, Task2, SCHEDULER_TASK_IS_ACTIVE, 1000);  // run every 1000  ms
	
	
	// задача управления потоком задач из очереди должна выполняться
	// чаще задач, взаимодействующие с модулем UART! (в данном случае - 100 мс)
	// -------------------------------------------------------------------------------
	// the task of managing the flow of tasks from the queue should be performed
	// more often than tasks interacting with the UART module! (in this case - 100 ms)
	//
	Scheduler_Create_Task(3, UART_Msg_Scheduler, SCHEDULER_TASK_IS_ACTIVE, 100);  // run every 100  ms
	
	Scheduler_Tasks_Prepare();
	
	
	// Инициализация системного таймера и включение глобальных прерываний
	// -------------------------------------------------------------------------------
	// Initializing the system timer and enabling global interrupts
	//
	SYSTIMER_Initialize();


	// не забудьте включить глобальные прерывания
	// -------------------------------------------------------------------------------
	// don't forget to enable global interrupts
	//
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




