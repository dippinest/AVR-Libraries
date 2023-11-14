
#include "queue.h"


Task_Queue_t Task_Queue_Create(void (**tasks_buffer)(), uint16_t buffer_size)
{
	Task_Queue_t queue;
	
	queue.tasks_buffer = tasks_buffer;

	queue.first        = 0;
	queue.last         = 0;
	queue.size         = buffer_size;
	
	queue.is_empty     = true;
	
	for (uint16_t i = 0; i < queue.size; ++i)
	{
		queue.tasks_buffer[i] = NULL;
	}

	return queue;
}

Task_Queue_t *Task_Queue_Create_To_Dynamic_Memory(uint16_t buffer_size)
{
	Task_Queue_t *queue = (Task_Queue_t*)malloc(sizeof(Task_Queue_t));
	
	if (queue == NULL)
	{
		return NULL;
	}
	
	queue->tasks_buffer = malloc(sizeof(void*));
	
	if (queue->tasks_buffer == NULL)
	{
		free(queue);
		
		return NULL;
	}

	queue->first        = 0;
	queue->last         = 0;
	queue->size         = buffer_size;
	
	queue->is_empty     = true;
	
	for (uint16_t i = 0; i < queue->size; ++i)
	{
		queue->tasks_buffer[i] = NULL;
	}

	return queue;
}

void Task_Queue_Delete_From_Dynamic_Memory(Task_Queue_t* queue)
{
	if (queue == NULL)
	{
		return;
	}
	
	if (queue->tasks_buffer != NULL)
	{
		free(queue->tasks_buffer);
	}
	
	free(queue);
	
	queue = NULL;
}


// ===============================================================================


void *Task_Queue_Push(Task_Queue_t* queue, void (*task)())
{
	if (!queue->is_empty && (queue->last == queue->first))
	{
		return NULL;
	}

	queue->tasks_buffer[queue->last] = task;

	queue->is_empty = false;

	queue->last++;


	if (queue->last == queue->size)
	{
		queue->last = 0;
	}

	return task;
}

void *Task_Queue_Pop(Task_Queue_t* queue)
{
	if (queue->is_empty)
	{
		return NULL;
	}
	
	void (*task)(void) = queue->tasks_buffer[queue->first];

	queue->first++;

	if (queue->first == queue->size)
	{
		queue->first = 0;
	}

	if (queue->first == queue->last)
	{
		queue->is_empty = true;
	}

	return task;
}

void *Task_Queue_Get_First(Task_Queue_t* queue)
{
	if (queue->is_empty)
	{
		return NULL;
	}

	return queue->tasks_buffer[queue->first];
}

bool  Task_Queue_Is_Empty(Task_Queue_t* queue)
{
	if (queue->is_empty)
	{
		return true;
	}

	return false;
}

