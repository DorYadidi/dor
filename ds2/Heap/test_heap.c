/*************************************************************************
* NAME: Heap                                                             *
*                                                                        *
* AUTHOR: Yaakov Sidikman                                                *
* DATE UPDATED:  27.12.18                                                *
*************************************************************************/

#include <stdlib.h> /*rand , time, srand */
#include <string.h>
#include <time.h>
#include "test.h"
#include "heap.h"

static int Compare(const void *x, const void *y)
{
	return (*(int *)x - *(int *)y);
}

bool MatchFunction(void *data, void *param)
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
TestResult TestPush();
TestResult TestPop();
TestResult TestRemove();

int main()
{
	RUN_TEST(TestBasicFunctions);
	RUN_TEST(TestPush);
	RUN_TEST(TestPop);
	RUN_TEST(TestRemove);

	return (0);
}

TestResult TestBasicFunctions()
{
	heap_t *heap = HeapCreate(Compare);
	REQUIRE(heap);
	REQUIRE(0 == HeapCount(heap));
	REQUIRE(TRUE == HeapIsEmpty(heap));

	HeapDestroy(heap);
	heap = NULL;

	return (TEST_PASS);
}

TestResult TestPush()
{
	size_t data_points = 1000;
	heap_t *heap = HeapCreate(Compare);
	int *data = int_data(data_points);
	size_t i = 0;

	for (i = 0; i < data_points; ++i)
	{
		HeapPush(heap, &data[i]);
	}
	REQUIRE(data_points == HeapCount(heap));
	REQUIRE(FALSE == HeapIsEmpty(heap));

	HeapDestroy(heap);
	heap = NULL;
	free(data);
	data = NULL;

	return (TEST_PASS);
}

TestResult TestPop()
{
	size_t data_points = 1000;
	heap_t *heap = HeapCreate(Compare);
	int *test_data = int_data(data_points);
	int *sort_data = malloc(data_points * sizeof(int));
	size_t i = 0;

	memcpy(sort_data, test_data, data_points * sizeof(int));
	qsort(sort_data, data_points, sizeof(int), Compare);

	for (i = 0; i < data_points; ++i)
	{
		HeapPush(heap, &test_data[i]);
	}

	for (i = 0; i < data_points - 1; ++i)
	{
		REQUIRE(sort_data[data_points -1 -i] == *(int*)HeapPeek(heap));
		HeapPop(heap);
	}

	HeapPop(heap);
	REQUIRE(0 == HeapCount(heap));
	REQUIRE(TRUE == HeapIsEmpty(heap));

	HeapDestroy(heap);
	heap = NULL;
	free(test_data);
	free(sort_data);
	test_data = NULL;
	sort_data = NULL;

	return (TEST_PASS);
}

TestResult TestRemove()
{
	size_t data_points = 100;
	heap_t *heap = HeapCreate(Compare);
	int *test_data = int_data(data_points);
	int *sort_data = malloc(data_points * sizeof(int));
	size_t i = 0;

	memcpy(sort_data, test_data, (data_points - 2) * sizeof(int));
	qsort(sort_data, (data_points - 2), sizeof(int), Compare);

	for (i = 0; i < data_points; ++i)
	{
		HeapPush(heap, &test_data[i]);
	}

	REQUIRE(test_data[data_points - 1] ==
		*(int*)HeapRemove(heap, MatchFunction, &test_data[data_points - 1]));
	REQUIRE(test_data[data_points - 2] ==
		*(int*)HeapRemove(heap, MatchFunction, &test_data[data_points - 2]));
	REQUIRE(data_points - 2 == HeapCount(heap));

	for (i = 0; i < data_points - 3; ++i)
	{
		REQUIRE(sort_data[data_points -3 -i] == *(int*)HeapPeek(heap));
		HeapPop(heap);
	}

	HeapPop(heap);
	REQUIRE(0 == HeapCount(heap));
	REQUIRE(TRUE == HeapIsEmpty(heap));

	HeapDestroy(heap);
	heap = NULL;
	free(test_data);
	free(sort_data);
	test_data = NULL;
	sort_data = NULL;

	return (TEST_PASS);
}
