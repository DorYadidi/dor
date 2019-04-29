/*******************************************************************************
* NAME: Task Scheduler                                                         *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  22.11.18                                                      *
*******************************************************************************/
#include <stdio.h> 	/* sizeof */
#include <stdlib.h> /* size_t, malloc, free */
#include <string.h> /* strcmp */

#include "../include/test.h"
#include "../include/task.h"
#include "../include/task_scheduler.h"

#define ARRAY_SIZE 5

TestResult TaskCreateDestroyTest();
TestResult TaskGetStartTimeFrequencyUIDTest();
TestResult TaskRunTest();
TestResult TaskSchedulerCreateDestroyTest();
TestResult TaskSchedulerAddTaskTest();
TestResult TaskSchedulerOrderTest();
TestResult TaskSchedulerIsEmptyCountTest();
TestResult TaskSchedulerRemoveTaskTest();
TestResult TaskSchedulerStartTest();
TestResult TaskSchedulerStopTest();
TestResult TaskSchedulerTestFile();

static int array[ARRAY_SIZE];
static int counter = 0;

int main()
{
	RUN_TEST(TaskCreateDestroyTest);
	RUN_TEST(TaskGetStartTimeFrequencyUIDTest);
	RUN_TEST(TaskRunTest);

	RUN_TEST(TaskSchedulerCreateDestroyTest);
	RUN_TEST(TaskSchedulerAddTaskTest);
	RUN_TEST(TaskSchedulerOrderTest);
	RUN_TEST(TaskSchedulerIsEmptyCountTest);
	RUN_TEST(TaskSchedulerRemoveTaskTest);
	RUN_TEST(TaskSchedulerStartTest);
	RUN_TEST(TaskSchedulerStopTest);

	RUN_TEST(TaskSchedulerTestFile);

	return (0);
}
/***********************UtilityFunctions***************************************/

status UtilityTaskFunction(void *param)
{
	(void)param;
/*	printf("\nTaskFunction\n");*/
	return (SUCCESS);
}

status UtilityTaskFailFunction(void *param)
{
	(void)param;
/*	printf("\nTaskFunction\n");*/
	return (ACTION_FAIL);
}

status UtilityTaskFunctionAddToArray(void *param)
{
	if (NULL == param)
	{
		return (ACTION_FAIL);
	}

	array[*(int*)param] = counter;

	++counter;

	return (SUCCESS);
}

status UtilityTaskFunctionAddOne(void *param)
{
	if (NULL == param)
	{
		return (ACTION_FAIL);
	}

	*(int*)param += 1;

	return (SUCCESS);
}

status UtilityTaskStopFunction(void *param)
{
	TaskSchedulerStop((task_scheduler_t *)param);

	return (SUCCESS);
}

void UtilityDestroyFunction(void *param)
{
	(void)param;
/*	printf("\nDestroyFunction\n");*/
	return;
}

status TaskFunctionStopByFile(void *param)
{
	FILE *file = fopen("stop.txt", "a+");
	char tmp[5];

	if(!file)
	{
		return (STOP_TASK);
	}

	if (NULL == fgets(tmp, 5, file))
	{
		fclose(file);
		return (FAIL);
	}

	fclose(file);

	if(strcmp(tmp, "stop") == 0)
	{
		TaskSchedulerStop((task_scheduler_t *)(param));
	}

	return (SUCCESS);
}
/**************************TastTests*******************************************/

TestResult TaskCreateDestroyTest()
{
	task_t *task = NULL;
	task = TaskCreate(time(NULL), 0, UtilityTaskFunction,
							  UtilityDestroyFunction, NULL);

	REQUIRE(NULL != task);

	TaskDestroy(task);
	return (TEST_PASS);
}

TestResult TaskGetStartTimeFrequencyUIDTest()
{
	size_t frequency = 20;
	time_t t = time(NULL);

	task_t *task = TaskCreate(t, frequency, UtilityTaskFunction,
							  UtilityDestroyFunction, NULL);

	REQUIRE(t == TaskGetStartTime(task));
	REQUIRE(frequency == TaskGetFrequency(task));
	REQUIRE(FALSE == UIDIsBad(TaskGetUID(task)));
/*	printf("\n%s\n", UIDToString(TaskGetUID(task)));*/
	TaskDestroy(task);
	return (TEST_PASS);
}

TestResult TaskRunTest()
{
	size_t frequency = 20;
	time_t new_time = 20;
	task_t *task = TaskCreate(0, frequency, UtilityTaskFunction,
							  UtilityDestroyFunction, NULL);

	REQUIRE(SUCCESS == TaskRun(task));
	REQUIRE(new_time == TaskGetStartTime(task));
	TaskDestroy(task);

	task = TaskCreate(0, frequency, UtilityTaskFailFunction,
							  UtilityDestroyFunction, NULL);

	REQUIRE(SUCCESS != TaskRun(task));
	TaskDestroy(task);

	return (TEST_PASS);
}
/***********************TaskSchedulerTests*************************************/

unique_id_t *UtilityCreatePQ(task_scheduler_t *scheduler, int n,
							 task_function_t task_func, void *param,
							 size_t frequency)
{
	time_t t = time(NULL);
	unique_id_t* uid_array = malloc(n * sizeof(unique_id_t));
	int i = 0;

	for ( ; i < n ; ++i)
	{
		uid_array[i] = TaskSchedulerAddTask(scheduler, (t + i), frequency,
				       task_func, UtilityDestroyFunction, param);
	}

	return (uid_array);
}

TestResult TaskSchedulerCreateDestroyTest()
{
	task_scheduler_t *scheduler = NULL;
	scheduler = TaskSchedulerCreate();
	REQUIRE(NULL != scheduler);

	TaskSchedulerDestroy(scheduler);
	return (TEST_PASS);
}

TestResult TaskSchedulerAddTaskTest()
{
	size_t frequency = 20;
	time_t t = time(NULL);
	task_scheduler_t *scheduler = TaskSchedulerCreate();

	unique_id_t uid = TaskSchedulerAddTask(scheduler, t, frequency,
				      UtilityTaskFunction, UtilityDestroyFunction, NULL);

	REQUIRE(FALSE == UIDIsBad(uid));

	TaskSchedulerDestroy(scheduler);
	return (TEST_PASS);
}

TestResult TaskSchedulerOrderTest()
{
	int i = 0;
	int param[] ={0, 1, 2, 3, 4};
	time_t t = time(NULL);
	size_t frequency = 0;

	task_scheduler_t *scheduler = TaskSchedulerCreate();

	for ( ; i < ARRAY_SIZE ; ++i)
	{
		array[i] = 0;
	}

	TaskSchedulerAddTask(scheduler, t + 4, frequency,
	UtilityTaskFunctionAddToArray, UtilityDestroyFunction, &param[4]);

	TaskSchedulerAddTask(scheduler, t, frequency,
	UtilityTaskFunctionAddToArray, UtilityDestroyFunction, &param[0]);

	TaskSchedulerAddTask(scheduler, t + 2, frequency,
	UtilityTaskFunctionAddToArray, UtilityDestroyFunction, &param[2]);

	TaskSchedulerAddTask(scheduler, t + 1, frequency,
	UtilityTaskFunctionAddToArray, UtilityDestroyFunction, &param[1]);

	TaskSchedulerAddTask(scheduler, t + 3, frequency,
	UtilityTaskFunctionAddToArray, UtilityDestroyFunction, &param[3]);

	TaskSchedulerStart(scheduler);

	for (i = 0 ; i < ARRAY_SIZE ; ++i)
	{
		REQUIRE(i == array[i]);
	}

	TaskSchedulerDestroy(scheduler);
	return (TEST_PASS);
}

TestResult TaskSchedulerIsEmptyCountTest()
{
	size_t frequency = 20;
	time_t t = time(NULL);
	task_scheduler_t *scheduler = TaskSchedulerCreate();

	REQUIRE(TRUE == TaskSchedulerIsEmpty(scheduler));
	REQUIRE(0 == TaskSchedulerCount(scheduler));

	TaskSchedulerAddTask(scheduler, t, frequency,UtilityTaskFunction,
						 UtilityDestroyFunction,NULL);

	REQUIRE(FALSE == TaskSchedulerIsEmpty(scheduler));
	REQUIRE(1 == TaskSchedulerCount(scheduler));

	TaskSchedulerAddTask(scheduler, t, frequency,UtilityTaskFunction,
						 UtilityDestroyFunction,NULL);

	REQUIRE(FALSE == TaskSchedulerIsEmpty(scheduler));
	REQUIRE(2 == TaskSchedulerCount(scheduler));

	TaskSchedulerDestroy(scheduler);
	return (TEST_PASS);
}

TestResult TaskSchedulerRemoveTaskTest()
{
	size_t frequency = 20;
	int n = 10;
	task_scheduler_t *scheduler = TaskSchedulerCreate();
	unique_id_t* uid_array = UtilityCreatePQ(scheduler, n,
							 UtilityTaskFunction, NULL, frequency);

	REQUIRE(10 == TaskSchedulerCount(scheduler));
	TaskSchedulerRemoveTask(scheduler, uid_array[0]);
	REQUIRE(9 == TaskSchedulerCount(scheduler));
	TaskSchedulerRemoveTask(scheduler, uid_array[1]);
	REQUIRE(8 == TaskSchedulerCount(scheduler));

	free(uid_array);
	TaskSchedulerDestroy(scheduler);
	return (TEST_PASS);
}

TestResult TaskSchedulerStartTest()
{
	int param = 0;
	int n = 10;
	size_t frequency = 0;
	task_scheduler_t *scheduler = TaskSchedulerCreate();
	unique_id_t* uid_array = UtilityCreatePQ(scheduler, n,
							 UtilityTaskFunctionAddOne, &param, frequency);

	REQUIRE(SUCCESS == TaskSchedulerStart(scheduler));
	REQUIRE(n == param);

	free(uid_array);
	TaskSchedulerDestroy(scheduler);
	return (TEST_PASS);
}

TestResult TaskSchedulerStopTest()
{
	int param = 0;
	int n = 10;
	size_t frequency = 10;
	time_t stop_time = time(NULL) + 10;
	task_scheduler_t *scheduler = TaskSchedulerCreate();

	unique_id_t* uid_array = UtilityCreatePQ(scheduler, n,
							 UtilityTaskFunctionAddOne, &param, frequency);

 	TaskSchedulerAddTask(scheduler, stop_time, 0, UtilityTaskStopFunction,
 					 	 UtilityDestroyFunction, scheduler);

	REQUIRE(SUCCESS == TaskSchedulerStart(scheduler));

	free(uid_array);
	TaskSchedulerDestroy(scheduler);
	return (TEST_PASS);
}
/***********************StopProgramWithFile(dor)*******************************/

TestResult TaskSchedulerTestFile()
{
	time_t time1 = time(NULL) + 5;
	time_t time2 = time(NULL) + 2;
	time_t time3 = time(NULL);
	size_t frequency1 = 2;
	size_t frequency2 = 3;
	size_t frequency3 = 1;
	int param1 = 1;
	int param2 = 2;
	task_scheduler_t *scheduler = NULL;

	scheduler = TaskSchedulerCreate();
	TaskSchedulerAddTask(scheduler, time1, frequency1, UtilityTaskFunction,
						 UtilityDestroyFunction, &param1);
	TaskSchedulerAddTask(scheduler, time2, frequency2, UtilityTaskFunction,
						 UtilityDestroyFunction, &param2);
	TaskSchedulerAddTask(scheduler, time3, frequency3, TaskFunctionStopByFile,
						 UtilityDestroyFunction, scheduler);
	REQUIRE("test AddTask" && 3 == TaskSchedulerCount(scheduler));

	/*To stop user need to write to file stop.txt "stop" */
	TaskSchedulerStart(scheduler);

	TaskSchedulerDestroy(scheduler);
	return (TEST_PASS);
}
/******************************************************************************/
/******************************************************************************/
