/*******************************************************************************
* NAME: Task Scheduler                                                         *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  22.11.18                                                      *
*******************************************************************************/

#include <time.h>
#include "task.h"
#include "uid.h"
#include "test.h"


status TaskFunction1(void *param);
void DestroyTaskFunction1(void *param);
TestResult TestTask();

int main()
{
	RUN_TEST(TestTask);

	return (0);
}

status TaskFunction1(void *param)
{
	printf("%d\n", *(int *)param);
	return (SUCCESS);
}

void DestroyTaskFunction1(void *param)
{
	(void)(param);
}

TestResult TestTask()
{
	task_t *task;
	time_t time1 = time(NULL);
	size_t frequency = 1;
	int param = 5;

	/*Test Create*/
	task = TaskCreate(time1, frequency, TaskFunction1, DestroyTaskFunction1, &param);
	REQUIRE("test Create" && NULL != task);

	/*Test Get StartTime*/
	REQUIRE("GetStartTime" && TaskGetStartTime(task) == time1);

	/*Test GetFrequency*/
	REQUIRE("GetFrequency" && TaskGetFrequency(task) == frequency);

	/*Test TaskGetUID*/
	REQUIRE("TaskGetUID" && UIDIsBad(TaskGetUID(task)) == FALSE);

	/*Test TaskRun*/
	REQUIRE("TaskRun" && TaskRun(task) == SUCCESS);

	/*Test Destroy*/
	TaskDestroy(task);

	return (TEST_PASS);
}
