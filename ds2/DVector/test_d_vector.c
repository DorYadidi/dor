/*******************************************************************************
* NAME:    test_d_vector                                                       *
*                                                                              *
* PURPOSE: tests for the dynamic vector   	              							       *
*                                                                              *
* AUTHOR: itamar persi                                                         *
* DATE UPDATED:  06.11.18                                                      *
*******************************************************************************/
#include <stdio.h>
#include "test.h"
#include "d_vector.h"

TestResult DVectorTestPushPop(void);
TestResult DVectorTestReserve(void);

int main()
{
	RUN_TEST (DVectorTestPushPop);
	RUN_TEST (DVectorTestReserve);

	return 0;
}

TestResult DVectorTestPushPop(void)
{
	int i = 0;
	int a = 4;
	int b = 5;

	d_vector_t *s = DVectorCreate(100, sizeof(int));
	d_vector_t *s2;

	REQUIRE(100 == DVectorGetCapacity(s));
	REQUIRE(sizeof(int) == DVectorGetElementSize(s));
	REQUIRE(0 == DVectorGetSize(s));
	REQUIRE(DVectorGetItem(s, 0) == NULL);

	DVectorPush(s, &a);
	REQUIRE(100 == DVectorGetCapacity(s));
	REQUIRE(sizeof(int) == DVectorGetElementSize(s));
	REQUIRE(1 == DVectorGetSize(s));
	REQUIRE(*(int *)DVectorGetItem(s, 0) == a);

	DVectorPush(s, &b);
	REQUIRE(100 == DVectorGetCapacity(s));
	REQUIRE(sizeof(int) == DVectorGetElementSize(s));
	REQUIRE(2 == DVectorGetSize(s));
	REQUIRE(*(int *)DVectorGetItem(s, 0) == a);
	REQUIRE(*(int *)DVectorGetItem(s, 1) == b);

	DVectorPop(s);
	REQUIRE(100 == DVectorGetCapacity(s));
	REQUIRE(sizeof(int) == DVectorGetElementSize(s));
	REQUIRE(1 == DVectorGetSize(s));
	REQUIRE(*(int *)DVectorGetItem(s, 0) == a);

	DVectorPop(s);
	REQUIRE(100 == DVectorGetCapacity(s));
	REQUIRE(sizeof(int) == DVectorGetElementSize(s));
	REQUIRE(0 == DVectorGetSize(s));


	for(i = 0; i < 55 ; ++i)
	{
		DVectorPush(s, &a);
	}

	for(i = 0; i < 55 ; ++i)
	{
		DVectorPop(s);
/*	printf("%lu, %lu, %lu\n", DVectorGetElementSize(s), DVectorGetCapacity(s), DVectorGetSize(s));*/
	}
/*	printf("%lu, %lu, %lu\n", DVectorGetElementSize(s), DVectorGetCapacity(s), DVectorGetSize(s));*/
/*	printf("%p\n", DVectorGetItem(s, 0));*/
	REQUIRE(0 == DVectorGetSize(s));
	REQUIRE(DVectorGetItem(s, 0) == NULL);

	DVectorDestroy(&s);

/*	printf("%lu, %lu, %lu\n", StackGetElementSize(s), StackGetCapacity(s), StackGetSize(s));*/
/*	printf("%p\n", StackPeek(s));*/



	s2 = DVectorCreate(5, sizeof(int));

	REQUIRE(5 == DVectorGetCapacity(s2));
	REQUIRE(0 == DVectorGetSize(s2));

	DVectorPush(s2, &a);
	REQUIRE(5 == DVectorGetCapacity(s2));
	REQUIRE(1 == DVectorGetSize(s2));

	DVectorPush(s2, &b);
	REQUIRE(5 == DVectorGetCapacity(s2));
	REQUIRE(2 == DVectorGetSize(s2));

	DVectorPush(s2, &b);
	REQUIRE(5 == DVectorGetCapacity(s2));
	REQUIRE(3 == DVectorGetSize(s2));

	DVectorPop(s2);
	REQUIRE(5 == DVectorGetCapacity(s2));
	REQUIRE(2 == DVectorGetSize(s2));

	DVectorPop(s2);
	REQUIRE(2 == DVectorGetCapacity(s2));
	REQUIRE(1 == DVectorGetSize(s2));

	DVectorDestroy(&s2);

	return (TEST_PASS);
}

TestResult DVectorTestReserve(void)
{
	int i = 0;
	int a = 4;
/*	int b = 5;*/

	d_vector_t *s = DVectorCreate(100, sizeof(int));

	for(i = 0; i < 105 ; ++i)
	{
		DVectorPush(s, &a);
	}

	REQUIRE(*(int *)DVectorGetItem(s, 104) == a);
	REQUIRE(105 == DVectorGetSize(s));
	REQUIRE(200 == DVectorGetCapacity(s));

		for(i = 0; i < 105 ; ++i)
	{
		DVectorPush(s, &a);
	}

	REQUIRE(*(int *)DVectorGetItem(s, 204) == a);
	REQUIRE(210 == DVectorGetSize(s));
	REQUIRE(400 == DVectorGetCapacity(s));

	for(i = 0; i < 111 ; ++i)
	{
		DVectorPop(s);
	}

	REQUIRE(99 == DVectorGetSize(s));
	REQUIRE(200 == DVectorGetCapacity(s));
	REQUIRE(DVectorGetItem(s, 204) == NULL);

	for(i = 0; i < 50 ; ++i)
	{
		DVectorPop(s);
	}

	REQUIRE(49 == DVectorGetSize(s));
	REQUIRE(100 == DVectorGetCapacity(s));
	REQUIRE(*(int *)DVectorGetItem(s, 48) == a);
	REQUIRE(DVectorGetItem(s, 49) == NULL);


	DVectorReserve(s, 51);
	REQUIRE(49 == DVectorGetSize(s));
	REQUIRE(100 == DVectorGetCapacity(s));

	DVectorReserve(s, 101);
	REQUIRE(49 == DVectorGetSize(s));
	REQUIRE(101 == DVectorGetCapacity(s));
	REQUIRE(*(int *)DVectorGetItem(s, 48) == a);
	REQUIRE(DVectorGetItem(s, 49) == NULL);

	DVectorDestroy(&s);
	return (TEST_PASS);
}
/******************************************************************************/
/******************************************************************************/
