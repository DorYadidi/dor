/*******************************************************************************
* NAME: binary sorted tree                                                     *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  11.12.18                                                      *
*******************************************************************************/

#include "test.h"
#include "stack.h"
#include <stdio.h>

void IntStackSort(stack_t *stack);
void IntStackSortInsert(stack_t *stack, int data);

TestResult TestStackSortInsert();
TestResult TestStackSort();

int main()
{
	RUN_TEST(TestStackSortInsert);
	RUN_TEST(TestStackSort);


	return (0);
}

void IntStackSort(stack_t *stack)
{
	int peek_data = 0;

	if (0 == StackGetSize(stack))
	{
		return;
	}

	peek_data = *(int *)StackPeek(stack);
	StackPop(stack);
	IntStackSort(stack);
	IntStackSortInsert(stack ,peek_data);
}

void IntStackSortInsert(stack_t *stack, int data)
{
	int peek_data = 0;

	if (0 == StackGetSize(stack) || data >= *(int *)StackPeek(stack))
	{
		StackPush(stack, &data);
	}
	else
	{
		peek_data = *(int *)StackPeek(stack);
		StackPop(stack);
		IntStackSortInsert(stack, data);
		StackPush(stack, &peek_data);
	}
}
/********************************TEST******************************************/
TestResult TestStackSort()
{
	int data1 = 4;
	int data2 = 12;
	int data3 = 1;
	int data4 = 13;
	int data5 = 132;
	int data6 = 65;

	stack_t *sorted_stack = StackCreate(6, sizeof(int));
	StackPush(sorted_stack, &data1);
	StackPush(sorted_stack, &data2);
	StackPush(sorted_stack, &data3);
	StackPush(sorted_stack, &data4);
	StackPush(sorted_stack, &data5);
	StackPush(sorted_stack, &data6);

	IntStackSort(sorted_stack);

	REQUIRE(StackGetSize(sorted_stack) == 6);
	REQUIRE(*(int *)StackPeek(sorted_stack) == data5);
	StackPop(sorted_stack);
	REQUIRE(*(int *)StackPeek(sorted_stack) == data6);
	StackPop(sorted_stack);
	REQUIRE(*(int *)StackPeek(sorted_stack) == data4);
	StackPop(sorted_stack);
	REQUIRE(*(int *)StackPeek(sorted_stack) == data2);
	StackPop(sorted_stack);
	REQUIRE(*(int *)StackPeek(sorted_stack) == data1);
	StackPop(sorted_stack);
	REQUIRE(*(int *)StackPeek(sorted_stack) == data3);
	StackPop(sorted_stack);

	StackDestroy(&sorted_stack);

	return (TEST_PASS);
}

TestResult TestStackSortInsert()
{
	int data1 = 1;
	int data2 = 2;
	int data3 = 10;
	int data4 = 12;
	int data5 = 14;
	int data6 = 3;

	stack_t *sorted_stack = StackCreate(6, sizeof(int));
	StackPush(sorted_stack, &data1);
	StackPush(sorted_stack, &data2);
	StackPush(sorted_stack, &data3);
	StackPush(sorted_stack, &data4);
	StackPush(sorted_stack, &data5);

	IntStackSortInsert(sorted_stack, data6);

	REQUIRE(StackGetSize(sorted_stack) == 6);
	REQUIRE(*(int *)StackPeek(sorted_stack) == data5);
	StackPop(sorted_stack);
	REQUIRE(*(int *)StackPeek(sorted_stack) == data4);
	StackPop(sorted_stack);
	REQUIRE(*(int *)StackPeek(sorted_stack) == data3);
	StackPop(sorted_stack);
	REQUIRE(*(int *)StackPeek(sorted_stack) == data6);
	StackPop(sorted_stack);
	REQUIRE(*(int *)StackPeek(sorted_stack) == data2);
	StackPop(sorted_stack);
	REQUIRE(*(int *)StackPeek(sorted_stack) == data1);
	StackPop(sorted_stack);

	StackDestroy(&sorted_stack);

	return (TEST_PASS);

}
