/*************************************************************************
* NAME: Hash Table                                                       *
*                                                                        *
* AUTHOR: Yaakov Sidikman                                                *
* DATE UPDATED:  26.12.18                                                *
*************************************************************************/
#include <stdlib.h> /*rand , time, srand */
#include <time.h>
#include "test.h"
#include "hash_table.h"

status ActionFunction(void *data, void *param)
{
	*(int*)param += *(int*)data;
	return (SUCCESS);
}

size_t HashFunction(const void *data)
{
	int key = *(int*)data % 10;
	return (key);
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
			data[i] = rand() % data_points + 1;
		}
	}

	return (data);
}
/******************************************************************************/

TestResult TestBasicFunctions();
TestResult TestInsert();
TestResult TestRemove();
TestResult TestForEach();
TestResult TestFind();
/*TestResult TestStatistics();*/
/*TestResult TestCache();*/

int main()
{
	RUN_TEST(TestBasicFunctions);
	RUN_TEST(TestInsert);
	RUN_TEST(TestRemove);
	RUN_TEST(TestForEach);
	RUN_TEST(TestFind);
/*	RUN_TEST(TestStatistics);
	RUN_TEST(TestCache);*/

	return (0);
}

TestResult TestBasicFunctions()
{
	size_t number_of_keys = 10;
	hash_table_t *table = HashCreate(HashFunction, MatchFunction,
									 number_of_keys);
	REQUIRE(table);
	REQUIRE(0 == HashCount(table));
	REQUIRE(TRUE == HashIsEmpty(table));

	HashDestroy(table);
	table = NULL;

	return (TEST_PASS);
}

TestResult TestInsert()
{
	size_t data_points = 100;
	size_t number_of_keys = 10;
	hash_table_t *table = HashCreate(HashFunction, MatchFunction,
									 number_of_keys);
	int *data = int_data(data_points);
	size_t i = 0;

	for (i = 0; i < data_points; ++i)
	{
		HashInsert(table, &data[i]);
	}

	REQUIRE(data_points == HashCount(table));
	REQUIRE(FALSE == HashIsEmpty(table));

	HashDestroy(table);
	table = NULL;
	free(data);
	data = NULL;

	return (TEST_PASS);
}

TestResult TestFind()
{
	size_t data_points = 100;
	size_t number_of_keys = 10;
	hash_table_t *table = HashCreate(HashFunction, MatchFunction,
									 number_of_keys);
	int *data = int_data(data_points);
	size_t i = 0;

	for (i = 0; i < data_points; ++i)
	{
		HashInsert(table, &data[i]);
	}

	for (i = 0; i < data_points; ++i)
	{
		REQUIRE(*(int*)HashFind(table, &data[i]) == data[i]);
	}

	HashDestroy(table);
	table = NULL;
	free(data);
	data = NULL;

	return (TEST_PASS);
}

TestResult TestRemove()
{
	size_t data_points = 100;
	size_t number_of_keys = 10;
	hash_table_t *table = HashCreate(HashFunction, MatchFunction,
									 number_of_keys);
	int *data = int_data(data_points);
	size_t i = 0;

	for (i = 0; i < data_points; ++i)
	{
		HashInsert(table, &data[i]);
	}

	REQUIRE(data_points == HashCount(table));
	REQUIRE(FALSE == HashIsEmpty(table));

	for (i = 0; i < data_points; ++i)
	{
		HashRemove(table, &data[i]);
	}

	REQUIRE(0 == HashCount(table));
	REQUIRE(TRUE == HashIsEmpty(table));

	for (i = 0; i < data_points; ++i)
	{
		REQUIRE(NULL == HashFind(table, &data[i]));
	}

	HashDestroy(table);
	table = NULL;
	free(data);
	data = NULL;

	return (TEST_PASS);
}

TestResult TestForEach()
{
	size_t test_result = 0;
	size_t data_sum = 0;
	size_t data_points = 100;
	size_t number_of_keys = 10;
	hash_table_t *table = HashCreate(HashFunction, MatchFunction,
									 number_of_keys);
	int *data = int_data(data_points);
	size_t i = 0;

	for (i = 0; i < data_points; ++i)
	{
		HashInsert(table, &data[i]);
		data_sum += data[i];
	}

	REQUIRE(SUCCESS == HashForEach(table, ActionFunction, &test_result));
	REQUIRE(data_sum == test_result);

	HashDestroy(table);
	table = NULL;
	free(data);
	data = NULL;

	return (TEST_PASS);
}
