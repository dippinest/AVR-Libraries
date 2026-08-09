

#include "task_queue.h"




void Task_Queue_Initialize_Object(Task_Queue_t *task_queue, void (**tasks_buffer)(), uint16_t buffer_size)
{
	(*task_queue).tasks_buffer = tasks_buffer;

	(*task_queue).first        = 0;
	(*task_queue).last         = 0;
	(*task_queue).size         = buffer_size;
	
	(*task_queue).is_empty     = true;
	
	for (uint16_t i = 0; i < (*task_queue).size; ++i)
	{
		(*task_queue).tasks_buffer[i] = NULL;
	}
}



Task_Queue_t *Task_Queue_Create_Object_To_Dynamic_Memory(uint16_t buffer_size)
{
	Task_Queue_t *task_queue = (Task_Queue_t*)malloc(sizeof(Task_Queue_t));
	
	if (task_queue == NULL)
	{
		return NULL;
	}
	
	task_queue->tasks_buffer = malloc(sizeof(void*));
	
	if (task_queue->tasks_buffer == NULL)
	{
		free(task_queue);
		
		return NULL;
	}

	task_queue->first        = 0;
	task_queue->last         = 0;
	task_queue->size         = buffer_size;
	
	task_queue->is_empty     = true;
	
	for (uint16_t i = 0; i < task_queue->size; ++i)
	{
		task_queue->tasks_buffer[i] = NULL;
	}

	return task_queue;
}



void Task_Queue_Delete_Object_From_Dynamic_Memory(Task_Queue_t* task_queue)
{
	if (task_queue == NULL)
	{
		return;
	}
	
	if (task_queue->tasks_buffer != NULL)
	{
		free(task_queue->tasks_buffer);
	}
	
	free(task_queue);
	
	task_queue = NULL;
}



// ===============================================================================





void *Task_Queue_Push(Task_Queue_t* task_queue, void (*task)())
{
	if (!task_queue->is_empty && (task_queue->last == task_queue->first))
	{
		return NULL;
	}

	task_queue->tasks_buffer[task_queue->last] = task;

	task_queue->is_empty = false;

	task_queue->last++;


	if (task_queue->last == task_queue->size)
	{
		task_queue->last = 0;
	}

	return task;
}



void *Task_Queue_Pop(Task_Queue_t* task_queue)
{
	if (task_queue->is_empty)
	{
		return NULL;
	}
	
	void (*task)(void) = task_queue->tasks_buffer[task_queue->first];

	task_queue->first++;

	if (task_queue->first == task_queue->size)
	{
		task_queue->first = 0;
	}

	if (task_queue->first == task_queue->last)
	{
		task_queue->is_empty = true;
	}

	return task;
}



void *Task_Queue_Get_First(Task_Queue_t* task_queue)
{
	if (task_queue->is_empty)
	{
		return NULL;
	}

	return task_queue->tasks_buffer[task_queue->first];
}



bool  Task_Queue_Is_Empty(Task_Queue_t* task_queue)
{
	if (task_queue->is_empty)
	{
		return true;
	}

	return false;
}










