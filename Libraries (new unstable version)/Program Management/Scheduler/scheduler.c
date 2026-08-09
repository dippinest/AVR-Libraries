
#include "scheduler.h"


static Scheduler_Task_t _Tasks[SCHEDULER_MAX_TASK_NUM];

static Scheduler_Task_t *_target_task = NULL;

static volatile uint8_t _tasks_counter = 0;

extern volatile SYSTIMER_t __SYSTIMER;


// ===============================================================================


Scheduler_Task_t *Scheduler_Get_Task_Queue()
{
	return _Tasks;
}

Scheduler_Task_t *Scheduler_Get_Target_Task()
{
	return &_Tasks[_tasks_counter];
}

Scheduler_Task_t *Scheduler_Get_Next_Task()
{
	return &_Tasks[(_tasks_counter + 1) % SCHEDULER_MAX_TASK_NUM];
}

uint8_t Scheduler_Get_Task_Counter()
{
	return _tasks_counter;
}


void Scheduler_Create_Task(const uint8_t task_num, void (*task_callback_function)(), bool task_is_active, SYSTIMER_t task_interval)
{
	Scheduler_Task_t task;
	
	task.task_callback     = task_callback_function;
	task.task_interval     = task_interval;
	
	if(task_is_active)
	{
		task.task_status = SCHEDULER_TASK_STATUS_WAIT;
	}
	else
	{
		task.task_status = SCHEDULER_TASK_STATUS_STOP;
	}
	
	_Tasks[task_num] = task;
}


// ===============================================================================


void Scheduler_Set_Task_Callback(uint8_t task_num, void (*task_callback_function)())
{
	_Tasks[task_num].task_callback = task_callback_function;
}

void Scheduler_Set_Task_Interval(uint8_t task_num, SYSTIMER_t task_interval)
{
	_Tasks[task_num].task_interval = task_interval;
}

void Scheduler_Set_Task_Status(uint8_t task_num, Scheduler_Task_Status_t task_status)
{
	_Tasks[task_num].task_status = task_status;
}

void *Scheduler_Get_Task_Callback(uint8_t task_num)
{
	return _Tasks[task_num].task_callback;
}

SYSTIMER_t Scheduler_Get_Task_Interval(uint8_t task_num)
{
	return _Tasks[task_num].task_interval;
}

Scheduler_Task_Status_t Scheduler_Get_Task_Status(uint8_t task_num)
{
	return _Tasks[task_num].task_status;
}


// ===============================================================================


void Scheduler_Task_Callback_Execute(uint8_t task_num)
{
	if (_Tasks[task_num].task_callback != NULL)
	{
		_Tasks[task_num].task_callback();
	}
}

void Scheduler_Set_Task_Active(const uint8_t task_num, bool task_is_active)
{
	if (task_is_active)
	{
		_Tasks[task_num].task_status = SCHEDULER_TASK_STATUS_WAIT;
	}
	else
	{
		_Tasks[task_num].task_status = SCHEDULER_TASK_STATUS_STOP;
	}
}

bool Scheduler_Task_Is_Active(const uint8_t task_num)
{
	if (_Tasks[task_num].task_status == SCHEDULER_TASK_STATUS_STOP)
	{
		return false;
	}
	
	return true;
}


// ===============================================================================


void Scheduler_Tasks_Prepare()
{
	SYSTIMER_t target_time = __SYSTIMER;
	
	for (uint8_t i = 0; i < SCHEDULER_MAX_TASK_NUM; ++i)
	{
		_Tasks[i].task_initial_time = target_time;
	}
}

void Scheduler_Run()
{	
	for (_tasks_counter = 0; _tasks_counter < SCHEDULER_MAX_TASK_NUM; ++_tasks_counter)
	{
		_target_task = &(_Tasks[_tasks_counter]);
		
		if (_target_task->task_status == SCHEDULER_TASK_STATUS_STOP || _target_task->task_callback == NULL)
		{
			continue;
		}
		
		if (_target_task->task_status == SCHEDULER_TASK_STATUS_WAIT)
		{
			if ((__SYSTIMER - _target_task->task_initial_time) >= _target_task->task_interval)
			{
				_target_task->task_initial_time = __SYSTIMER;
				
				_target_task->task_status = SCHEDULER_TASK_STATUS_RUN;
				_target_task->task_callback();
				_target_task->task_status = SCHEDULER_TASK_STATUS_WAIT;
			}
		}
	}
}


