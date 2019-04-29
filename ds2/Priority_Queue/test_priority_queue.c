/*******************************************************************************
* NAME: Priority Queue                                                         *
*                                                                              *
* PURPOSE:                                                                     *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  14.11.18                                                      *
*******************************************************************************/

#include "priority_queue.h"
#include "sorted_list.h"
#include "test.h"
#include <stdio.h>

TestResult TestPQueue();
bool HasPriorityMin(void *current_data, void *new_data);

int main()
{
	RUN_TEST(TestPQueue);

	return (0);
}

bool IsBeforMin (void *current_data, void *new_data)
{
	if (*(int *)new_data < *(int *)current_data)
	{
		return (TRUE);
	}

	return (FALSE);
}

bool FindToRemove(void *data, void *param);

TestResult TestPQueue()
{
	int a = 1;
	int b = 4;
	int c = 11;
	int d = 5;

	p_queue_t *queue = PQueueCreate(IsBeforMin);

	/*test: create + GetSize and ISEmpty*/
	REQUIRE("test Create" && queue != NULL);
	REQUIRE("test GetSize" && 0 == PQueueGetSize(queue));
	REQUIRE("test IsEmpty" && TRUE == PQueueIsEmpty(queue));

	/*test INSERT*/
	PQueueEnqueue(queue, &b);
	REQUIRE("test GetSize" && 1 == PQueueGetSize(queue));
	PQueueEnqueue(queue, &a);
	PQueueEnqueue(queue, &c);
	PQueueEnqueue(queue, &d);
	REQUIRE("test GetSize" && 4 == PQueueGetSize(queue));
	REQUIRE("test IsEmpty" && FALSE == PQueueIsEmpty(queue));
	REQUIRE("test PQueuePeek" && a == *(int*)PQueuePeek(queue));
	REQUIRE("test PQueueDequeue" && a == *(int*)PQueueDequeue(queue));
	REQUIRE("test GetSize" && 3 == PQueueGetSize(queue));
	REQUIRE("test PQueueDequeue" && b == *(int*)PQueueDequeue(queue));
	REQUIRE("test PQueuePeek" && d == *(int*)PQueuePeek(queue));
	REQUIRE("test PQueueDequeue" && d == *(int*)PQueueDequeue(queue));
	REQUIRE("test PQueueDequeue" && c == *(int*)PQueueDequeue(queue));
	REQUIRE("test GetSize" && 0 == PQueueGetSize(queue));
	REQUIRE("test IsEmpty" && TRUE == PQueueIsEmpty(queue));

	/*Remove*/
	PQueueEnqueue(queue, &b);
	REQUIRE("test GetSize" && 1 == PQueueGetSize(queue));
	PQueueEnqueue(queue, &a);
	PQueueEnqueue(queue, &c);
	PQueueEnqueue(queue, &d);
	REQUIRE("test GetSize" && 4 == PQueueGetSize(queue));
	PQueueRemove(queue, FindToRemove, &a);
	REQUIRE("test GetSize" && 3 == PQueueGetSize(queue));
	REQUIRE("test PQueueDequeue" && b == *(int*)PQueueDequeue(queue));
	PQueueRemove(queue, FindToRemove, &c);
	REQUIRE("test PQueueDequeue" && d == *(int*)PQueueDequeue(queue));
	REQUIRE("test GetSize" && 0 == PQueueGetSize(queue));
	REQUIRE("test IsEmpty" && TRUE == PQueueIsEmpty(queue));


	/*Destroy*/
	PQueueDestroy(queue);

	return (TEST_PASS);
}

bool FindToRemove(void *data, void *param)
{
	if(*(int *)data == *(int *)param)
	{
		return (TRUE);
	}

	return (FALSE);
}
