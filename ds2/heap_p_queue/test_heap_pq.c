/*************************************************************************
* NAME: Heap Priority Queue                                              *
*                                                                        *
* AUTHOR: Yaakov Sidikman                                                *
* DATE UPDATED:  30.12.18                                                *
*************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <time.h>
#include "heap_pq.h"
#include "test.h"

static int Compare(const void *x, const void *y)
{
	return (*(int *)x - *(int *)y);
}

static bool match(void *data, void *param)
{
	return (*(int*)data == *(int*)param);
}

static int *int_data(size_t data_points)
{
	size_t i = 0;
	int *data = malloc(data_points * sizeof(int));
	srand(time(NULL));

	if (data)
	{
		for (i = 0; i <data_points; ++i)
		{
			data[i] = (rand() % data_points) + 1;
		}
	}

	return (data);
}

/******************************************************************************/

TestResult TestBasicFunctions();
TestResult TestEnqueue();
TestResult TestDequeue();
TestResult TestRemove();

int main()
{
	RUN_TEST(TestBasicFunctions);
	RUN_TEST(TestEnqueue);
	RUN_TEST(TestDequeue);
	RUN_TEST(TestRemove);

	return (0);
}

TestResult TestBasicFunctions()
{
	heap_p_queue_t *heap = HeapPQueueCreate(Compare);
	REQUIRE(heap);
	REQUIRE(0 == HeapPQueueGetSize(heap));
	REQUIRE(TRUE == HeapPQueueIsEmpty(heap));

	HeapPQueueDestroy(heap);
	heap = NULL;

	return (TEST_PASS);
}

TestResult TestEnqueue()
{
	size_t data_points = 1000;
	heap_p_queue_t *heap = HeapPQueueCreate(Compare);
	int *data = int_data(data_points);
	size_t i = 0;

	for (i = 0; i < data_points; ++i)
	{
		HeapPQueueEnqueue(heap, &data[i]);
	}
	REQUIRE(data_points == HeapPQueueGetSize(heap));
	REQUIRE(FALSE == HeapPQueueIsEmpty(heap));

	HeapPQueueDestroy(heap);
	heap = NULL;
	free(data);
	data = NULL;

	return (TEST_PASS);
}

TestResult TestDequeue()
{
	size_t data_points = 1000;
	heap_p_queue_t *heap = HeapPQueueCreate(Compare);
	int *data = int_data(data_points);
	int last_peek = 0;
	int curr_peek = 0;
	size_t i = 0;

	for (i = 0; i < data_points; ++i)
	{
		HeapPQueueEnqueue(heap, &data[i]);
	}

	for (i = 0; i < data_points - 1; ++i)
	{
		last_peek = *(int*)HeapPQueuePeek(heap);
		HeapPQueueDequeue(heap);
		curr_peek = *(int*)HeapPQueuePeek(heap);
		REQUIRE(0 <= last_peek - curr_peek);
	}

	HeapPQueueDequeue(heap);
	REQUIRE(0 == HeapPQueueGetSize(heap));
	REQUIRE(TRUE == HeapPQueueIsEmpty(heap));

	HeapPQueueDestroy(heap);
	heap = NULL;
	free(data);
	data = NULL;

	return (TEST_PASS);
}

TestResult TestRemove()
{
	size_t data_points = 1000;
	heap_p_queue_t *heap = HeapPQueueCreate(Compare);
	int *data = int_data(data_points);
	int last_peek = 0;
	int curr_peek = 0;
	size_t i = 0;

	for (i = 0; i < data_points; ++i)
	{
		HeapPQueueEnqueue(heap, &data[i]);
	}

	REQUIRE(data[45] == *(int*)HeapPQueueRemove(heap, match, &data[45]));
	REQUIRE(data[27] == *(int*)HeapPQueueRemove(heap, match, &data[27]));
	REQUIRE(data_points - 2 == HeapPQueueGetSize(heap));

	for (i = 0; i < data_points - 3; ++i)
	{
		last_peek = *(int*)HeapPQueuePeek(heap);
		HeapPQueueDequeue(heap);
		curr_peek = *(int*)HeapPQueuePeek(heap);
		REQUIRE(0 <= last_peek - curr_peek);
	}

	HeapPQueueDequeue(heap);
	REQUIRE(0 == HeapPQueueGetSize(heap));
	REQUIRE(TRUE == HeapPQueueIsEmpty(heap));

	HeapPQueueDestroy(heap);
	heap = NULL;
	free(data);
	data = NULL;

	return (TEST_PASS);
}
