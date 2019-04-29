#pragma once

#include "uid.h"
#include "enum_rd58.h"
#include "function_pointers.h"

/*******************************************************************************
* NAME: Task Scheduler                                                         *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  22.11.18                                                      *
*******************************************************************************/

#ifndef __TASK_SCHEDULER_H__
#define __TASK_SCHEDULER_H__

typedef struct task_scheduler_s task_scheduler_t;

/******************************************************************************/

task_scheduler_t *TaskSchedulerCreate();
/*******************************************************************************
* Creates task scheduler                                                       *
*                                                                              *
* Parameters:                                                                  *
*  none                                                                        *
*                                                                              *
* Returns:                                                                     *
*  pointer to new task scheduler, NULL if failed                               *
*******************************************************************************/

void TaskSchedulerDestroy(task_scheduler_t *scheduler);
/*******************************************************************************
* Frees all memory allocated to task scheduler                                 *
*                                                                              *
* Parameters:                                                                  *
*  scheduler  - pointer to task scheduler                                      *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

unique_id_t TaskSchedulerAddTask(
	task_scheduler_t *scheduler,
	time_t start_time,
	size_t frequency,
	task_function_t task_func,
	destroy_task_function_t destroy_function,
	void *param
);
/*******************************************************************************
* Sets task in task scheduler                                                  *
*                                                                              *
* Parameters:                                                                  *
*  start_time - time after which task will be run                              *
*  frequency  - time between executions of repeated task                       *
*  task_func  - task function to be executed                                   *
*  destroy    - function to be called by task if task needs to be destroyed    *
*  param      - task function parameter                                        *
*                                                                              *
* Returns:                                                                     *
*  unique_id_t of new task, undefined if failed to set task                    *
*******************************************************************************/

void TaskSchedulerRemoveTask(task_scheduler_t *scheduler, unique_id_t id);
/*******************************************************************************
* Removes a task from the task scheduler                                       *
*                                                                              *
* Parameters:                                                                  *
*  scheduler  - pointer to task scheduler                                      *
*  id - unique id of the task to be removed                                    *
*                                                                              *
* Returns:                                                                     *
*  none                                                    	                    *
*******************************************************************************/

bool TaskSchedulerIsEmpty(task_scheduler_t *scheduler);
/*******************************************************************************
* Returns TRUE if the scheduler is empty                                       *
*                                                                              *
* Parameters:                                                                  *
*  scheduler  - pointer to task scheduler                                      *
*                                                                              *
* Returns:                                                                     *
*  TRUE - scheduler is empty                                                   *
*  FALSE - scheduler is not empty                                              *
*******************************************************************************/

size_t TaskSchedulerCount(task_scheduler_t *scheduler);
/*******************************************************************************
* Counts the number pf tasks in the scheduler. Includes running task           *
*                                                                              *
* Parameters:                                                                  *
*  scheduler  - pointer to task scheduler                                      *
*                                                                              *
* Returns:                                                                     *
*  number of tasks queued in scheduler                                         *
*******************************************************************************/

status TaskSchedulerStart(task_scheduler_t *scheduler);
/*******************************************************************************
* Starts the scheduler                                                         *
*                                                                              *
* Parameters:                                                                  *
*  scheduler  - pointer to task scheduler                                      *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

void TaskSchedulerStop(task_scheduler_t *scheduler);
/*******************************************************************************
* Sets exit time from scheduler                                                *
*                                                                              *
* Parameters:                                                                  *
*  scheduler  - pointer to task scheduler                                      *
*                                                                              *
* Returns:                                                                     *
*  unique id of Exit task                                                      *
*******************************************************************************/

#endif
