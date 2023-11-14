

// ===============================================================================
//
// Библиотека, реализующая простейший планировщик задач.
//
// Он позволяет реализовать псевдомногозадачность на одном ядре микроконтроллера:
// создавать задачи, управлять ими, вызывать их с определённым интервалом и т.д.
// Причём сами задачи могут также управлять друг другом: например, непосредственно
// вызывать их, изменять их состояние, менять их интервал и т.д.
// Это обеспечивает высокую гибкость кода.
//
// Максимальное количество задач для планировщика вы можете указать в
// конфигурационном файле scheduler.h (максимум - 256 задач)
//
// ВНИМАНИЕ! ЭТО НЕ ОПЕРАЦИОННАЯ СИСТЕМА! Планировщик лишь имитирует
// кооперативную ОС, но не является ей.
//
// -------------------------------------------------------------------------------
//
// Library that implements the simplest task scheduler.
//
// It allows you to implement pseudo-multitasking on a single microcontroller core:
// create tasks, manage them, call them at a certain interval, etc.
// Moreover, the tasks themselves can also control each other:
// for example, directly call them, change their state, change their interval, etc.
// This ensures high code flexibility.
//
// You can specify the maximum number of tasks for the scheduler
// in the scheduler.h configuration file (max - 256 tasks)
//
// Attention! THIS IS NOT AN OPERATING SYSTEM!
// The scheduler only simulates the cooperative OS, but is not it.
//
// ===============================================================================


#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "systimer.h"
#include "systimer_configuration.h"
#include "scheduler_configuration.h"

#define SCHEDULER_TASK_IS_ACTIVE  true
#define SCHEDULER_TASK_IS_STOPPED false


// ===============================================================================


typedef bool Scheduler_Mutex_t;

#define SCHEDULER_MUTEX_LOCK   true
#define SCHEDULER_MUTEX_UNLOCK false


// ===============================================================================


typedef uint8_t Scheduler_Task_Status_t;

#define SCHEDULER_TASK_STATUS_STOP   0
#define SCHEDULER_TASK_STATUS_RUN    1
#define SCHEDULER_TASK_STATUS_WAIT   2


// ===============================================================================


inline Scheduler_Mutex_t Scheduler_Create_Mutex()
{
	return (Scheduler_Mutex_t)SCHEDULER_MUTEX_UNLOCK;
}

inline void Scheduler_Mutex_Set_Lock(Scheduler_Mutex_t *mutex)
{
	*mutex = SCHEDULER_MUTEX_LOCK;
}

inline void Scheduler_Mutex_Set_Unlock(Scheduler_Mutex_t *mutex)
{
	*mutex = SCHEDULER_MUTEX_UNLOCK;
}

inline bool Scheduler_Mutex_Is_Unlock(Scheduler_Mutex_t *mutex)
{
	if (*mutex == SCHEDULER_MUTEX_UNLOCK)
	{
		return true;
	}
	
	return false;
}


// ===============================================================================


typedef struct
{
	void (*task_callback)();
	
	SYSTIMER_t task_interval;
	
	SYSTIMER_t task_initial_time;
	
	Scheduler_Task_Status_t  task_status;
	
} Scheduler_Task_t;


// ===============================================================================


Scheduler_Task_t *Scheduler_Get_Task_Queue();

Scheduler_Task_t *Scheduler_Get_Target_Task();

Scheduler_Task_t *Scheduler_Get_Next_Task();

uint8_t Scheduler_Get_Task_Counter();

void Scheduler_Create_Task(const uint8_t task_num, void (*task_callback_function)(), bool task_is_active, SYSTIMER_t task_interval);


// ===============================================================================


void Scheduler_Set_Task_Callback(uint8_t task_num, void (*task_callback_function)());

void Scheduler_Set_Task_Interval(uint8_t task_num, SYSTIMER_t task_interval);

void Scheduler_Set_Task_Status(uint8_t task_num, Scheduler_Task_Status_t task_status);

void *Scheduler_Get_Task_Callback(uint8_t task_num);

SYSTIMER_t Scheduler_Get_Task_Interval(uint8_t task_num);

Scheduler_Task_Status_t Scheduler_Get_Task_Status(uint8_t task_num);

void Scheduler_Task_Callback_Execute(uint8_t task_num);

void Scheduler_Set_Task_Active(const uint8_t task_num, bool task_is_active);

bool Scheduler_Task_Is_Active(const uint8_t task_num);


// ===============================================================================


void Scheduler_Tasks_Prepare();

void Scheduler_Run();


// ===============================================================================


// этот макрос упрощает работу с мьютексами
// -------------------------------------------------------------------------------
// this macro makes it easier to work with mutexes

#define SCHEDULER_USE_MUTEX(_MUTEX_, _IFCODE_, _ELSECODE_)  \
if (Scheduler_Mutex_Is_Unlock(&_MUTEX_))                    \
{                                                           \
	Scheduler_Mutex_Set_Lock(&_MUTEX_);                     \
	_IFCODE_;                                               \
}                                                           \
else                                                        \
{                                                           \
	_ELSECODE_;                                             \
}


#endif


