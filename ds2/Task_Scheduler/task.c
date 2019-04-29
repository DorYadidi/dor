/*******************************************************************************
* NAME: Task                                                                   *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  22.11.18                                                      *
*******************************************************************************/

#include <time.h> /*time_t*/
#include <stdio.h>
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/
#include "task.h"
#include "uid.h"

struct task_s
{
	unique_id_t id;
	time_t start_time;
	size_t frequency;
	task_function_t task_function;
	destroy_task_function_t destroy_function;
	void *param;
};

task_t *TaskCreate(
	time_t start_time,
	size_t frequency,
	task_function_t task_function,
	destroy_task_function_t destroy_function,
	void *param)
{
	task_t *task = malloc(sizeof(task_t));
	if (NULL == task)
	{
		return (NULL);
	}

	task->id = UIDCreate();
	if (TRUE == UIDIsBad(task->id))
	{
		free(task);
		return (NULL);
	}

	task->start_time = start_time;
	task->frequency = frequency;
	task->task_function = task_function;
	task->destroy_function = destroy_function;
	task->param = param;

	return (task);
}

void TaskDestroy(task_t *task)
{
	assert(task != NULL);
	task->destroy_function(task->param);
	free(task);
}

time_t TaskGetStartTime(task_t *task)
{
	assert(task != NULL);
	return (task->start_time);
}

size_t TaskGetFrequency(task_t *task)
{
	assert(task != NULL);
	return (task->frequency);
}

unique_id_t TaskGetUID(task_t *task)
{
	assert(task != NULL);
	return (task->id);
}

status TaskRun(task_t *task)
{
	assert(task != NULL);
	task->start_time += task->frequency;

	return (task->task_function(task->param));
}
