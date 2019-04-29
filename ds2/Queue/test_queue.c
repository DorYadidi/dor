#include "queue.h"
#include "test.h"
#include "s_linked_list.h"

#include <stdlib.h> /*malloc, free*/

TestResult TestQueue1();
TestResult TestQueue2();

int main()
{
	RUN_TEST(TestQueue1);
	RUN_TEST(TestQueue2);

	return (0);
}

TestResult TestQueue1()
{
	int a = 5;
	int b = 4;
	queue_t *q = QueueCreate();
	REQUIRE(QueueEnqueue(q, &a) == SUCCESS);
	REQUIRE(*(int *)QueuePeek(q) == 5);
	REQUIRE(QueueGetSize(q) == 1);
	REQUIRE(QueueEnqueue(q, &b) == SUCCESS);
	REQUIRE(QueueGetSize(q) == 2);
	REQUIRE(QueueIsEmpty(q) == FALSE);
	REQUIRE(*(int *)QueueDequeue(q) == 5);
	REQUIRE(QueueGetSize(q) == 1);
	REQUIRE(*(int *)QueueDequeue(q) == 4);
	REQUIRE(QueueGetSize(q) == 0);
	REQUIRE(QueueIsEmpty(q) == TRUE);
	REQUIRE(QueueEnqueue(q, &a) == SUCCESS);
	REQUIRE(QueueGetSize(q) == 1);

	QueueDestroy(&q);

	return (TEST_PASS);
}

TestResult TestQueue2()
{
	int a = 5;
	int b = 4;
	int c = 10;
	int d = 11;
	int f = 12;
	queue_t *q = QueueCreate();
	queue_t *q2 = QueueCreate();
	REQUIRE(QueueEnqueue(q, &a) == SUCCESS);
	REQUIRE(QueueEnqueue(q, &b) == SUCCESS);
	REQUIRE(QueueEnqueue(q2, &c) == SUCCESS);
	REQUIRE(QueueEnqueue(q2, &d) == SUCCESS);
	REQUIRE(QueueEnqueue(q2, &f) == SUCCESS);
	REQUIRE(*(int *)QueuePeek(q2) == 10);
	QueueAppend(q, q2);
	free(q2);
	q2 = NULL;
	REQUIRE(QueueGetSize(q) == 5);
	REQUIRE(*(int *)QueueDequeue(q) == 5);
	REQUIRE(*(int *)QueueDequeue(q) == 4);
	REQUIRE(*(int *)QueueDequeue(q) == 10);
	REQUIRE(*(int *)QueueDequeue(q) == 11);
	REQUIRE(*(int *)QueueDequeue(q) == 12);
	REQUIRE(QueueIsEmpty(q) == TRUE);

	QueueDestroy(&q);
	return (TEST_PASS);
}
