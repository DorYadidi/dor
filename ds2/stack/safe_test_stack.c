#include "safe_stack.h"
#include "test.h"


TestResult TestSafeStack();

int main()
{
	RUN_TEST(TestSafeStack);


	return 0;
}

TestResult TestSafeStack()
{
	int a = 12;
	int b = 22;
	safe_stack_t *s = NULL;
	s = SafeStackCreate(5, sizeof(int));
	SafeStackPush(s, &a);
	SafeStackPush(s, &b);
	REQUIRE(SafeStackGetSize(s) == 2);
	SafeStackPop(s);
	REQUIRE(SafeStackGetSize(s) == 1);
	REQUIRE(SafeStackGetCapacity(s) == 5);
	REQUIRE(SafeStackGetElementSize(s) == 4);
	SafeStackPop(s);
	REQUIRE(SafeStackPeek(s) == NULL);
	SafeStackDestroy(&s);

	return (TEST_PASS);
}
