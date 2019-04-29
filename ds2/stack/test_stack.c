#include "stack.h"
#include "test.h"

enum {FALSE, TRUE};

struct stack_s
{
	void * stack_array;
	size_t capacity;
	size_t element_size;
	char * top;
};

TestResult TestStackCreateDestroyGet();
TestResult TestStackPushPopPeek();

int main()
{
	RUN_TEST(TestStackCreateDestroyGet);
	RUN_TEST(TestStackPushPopPeek);

	return (0);
}

TestResult TestStackPushPopPeek()
{
	int test = 1;
	void *test_element = "good";
	stack_t **free_test;

	while (test == 1)
	{
		stack_t *test_stack = StackCreate(3, sizeof(char));
		REQUIRE(StackGetSize(test_stack) == 0);
		StackPush(test_stack, test_element);
		StackPush(test_stack, test_element);
		StackPush(test_stack, test_element);
		REQUIRE(StackGetSize(test_stack) == 3);
		REQUIRE(*(char*)StackPeek(test_stack) == 'g');
		StackPop(test_stack);
		REQUIRE(StackGetSize(test_stack) == 2);

		free_test = &test_stack;
		StackDestroy(free_test);
		REQUIRE(test_stack == NULL);

		++test;
	}

	while (test == 2)
	{
		stack_t *test_stack = StackCreate(3, sizeof(int));
		StackPush(test_stack, test_element);
		REQUIRE(StackGetSize(test_stack) == 1);
		REQUIRE(*(char*)StackPeek(test_stack) == 'g');
		StackPop(test_stack);
		REQUIRE(StackGetSize(test_stack) == 0);

		free_test = &test_stack;
		StackDestroy(free_test);
		REQUIRE(test_stack == NULL);

		++test;
	}

	return (TEST_PASS);
}

TestResult TestStackCreateDestroyGet()
{
	stack_t **free_test;
	stack_t *test_stack = StackCreate(3, sizeof(char));

	REQUIRE(StackGetSize(test_stack) == 0);
	REQUIRE(StackGetCapacity(test_stack) == 3);
	REQUIRE(StackGetElementSize(test_stack) == sizeof(char));

	free_test = &test_stack;
	StackDestroy(free_test);
	REQUIRE(test_stack == NULL);

	return (TEST_PASS);
}
