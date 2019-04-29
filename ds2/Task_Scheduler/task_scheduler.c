/*******************************************************************************
* NAME: Task Scheduler                                                         *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  22.11.18                                                      *
*******************************************************************************/

#include <time.h> /*time_t, time()*/
#include <stdio.h> /*sizeof*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/
#include <unistd.h> /*sleep*/
#include "task_scheduler.h"
#include "task.h"
#include "priority_queue.h"
#include "uid.h"

#define NO_START_TIME 0

struct task_scheduler_s
{
	p_queue_t *pq;
	bool is_scheduler_stop;
};

bool ScheduledIsBefore(void *current_task, void *new_task)
{
	return (TaskGetStartTime(current_task) > TaskGetStartTime(new_task));
}

task_scheduler_t *TaskSchedulerCreate()
{
	task_scheduler_t *scheduler = malloc(sizeof(task_scheduler_t));
	if (NULL == scheduler)
	{
		return (NULL);
	}

	scheduler->pq = PQueueCreate(ScheduledIsBefore);
	if (NULL == scheduler->pq)
	{
	    free(scheduler);
	    return (NULL);
	}

	return (scheduler);
}

void TaskSchedulerDestroy(task_scheduler_t *scheduler)
{
	assert(scheduler != NULL);

	while(!TaskSchedulerIsEmpty(scheduler))
	{
		task_t *task = PQueueDequeue(scheduler->pq);
		TaskDestroy(task);
	}

	PQueueDestroy(scheduler->pq);
	free(scheduler);
}

unique_id_t TaskSchedulerAddTask(
	task_scheduler_t *scheduler,
	time_t start_time,
	size_t frequency,
	task_function_t task_func,
	destroy_task_function_t destroy_function,
	void *param)
{
	task_t *task = TaskCreate(
		start_time,
		frequency,
		task_func,
		destroy_function,
		param);

	if (NULL == task)
	{
		return (UIDGetBad());
	}

	assert(scheduler != NULL);

	if(MEMORY_ALLOCATION_FAIL == PQueueEnqueue(scheduler->pq, task))
	{
		return (UIDGetBad());
	}

	return (TaskGetUID(task));
}

bool TaskSchedulerMatchRemove(void *task, void *find_id)
{
	assert(task != NULL && find_id != NULL);
	return(UIDIsSame(TaskGetUID(task), *(unique_id_t *)find_id));
}


void TaskSchedulerRemoveTask(task_scheduler_t *scheduler, unique_id_t id)
{
	task_t *task = NULL;
	assert(scheduler != NULL);
	task = PQueueRemove(scheduler->pq, TaskSchedulerMatchRemove, &id);
	if(NULL != task)
	{
		TaskDestroy(task);
	}
}

bool TaskSchedulerIsEmpty(task_scheduler_t *scheduler)
{
	assert(scheduler != NULL);
	return(PQueueIsEmpty(scheduler->pq));
}

size_t TaskSchedulerCount(task_scheduler_t *scheduler)
{
	assert(scheduler != NULL);
	return(PQueueGetSize(scheduler->pq));
}


status TaskSchedulerStart(task_scheduler_t *scheduler)
{
	time_t tmp_time = NO_START_TIME;
	status stat = SUCCESS;
	scheduler->is_scheduler_stop = TRUE;

	while(scheduler->is_scheduler_stop != FALSE
	      && PQueueIsEmpty(scheduler->pq) == FALSE)
	{
		task_t *task = PQueuePeek(scheduler->pq);
		tmp_time = time(NULL);

		if (TaskGetStartTime(task) > tmp_time)
		{
			sleep(TaskGetStartTime(task) - tmp_time);
		}

		stat = TaskRun(task);

		if (STOP_TASK != stat && TaskGetFrequency(task))
		{
			if (stat != SUCCESS)
			{
				scheduler->is_scheduler_stop = FALSE;

				return (stat);
			}
			else if (PQueueEnqueue(scheduler->pq, task) == MEMORY_ALLOCATION_FAIL)
			{
				scheduler->is_scheduler_stop = FALSE;

				return (MEMORY_ALLOCATION_FAIL);
			}
		}
		else
		{
			TaskDestroy(task);
		}

		PQueueDequeue(scheduler->pq);
	}

	scheduler->is_scheduler_stop = FALSE;

	return(stat);
}

void TaskSchedulerStop(task_scheduler_t *scheduler)
{
	assert(scheduler != NULL);
	scheduler->is_scheduler_stop = FALSE;
}
