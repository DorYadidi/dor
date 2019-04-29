#include <errno.h>

#include "c_buffer.h"
#include "test.h"

enum {FALSE, TRUE};

struct c_buffer_s
{
	char *base;
	char *top;
	char *read;
	char *write;
};

TestResult TestCBuffer();

int main()
{
	RUN_TEST(TestCBuffer);

	return (0);
}

TestResult TestCBuffer()
{
	char *test_src = "how do you do";
	char test_dest[50];
	c_buffer_t **free_test;

	/* test Create & GetSize */
	c_buffer_t *test_buffer = CBufferCreate(20);
	REQUIRE(CBufferGetSize(test_buffer) == 0);

	/* test GetCapacity */
	REQUIRE(CBufferGetCapacity(test_buffer) == 20);

	/* test Write */
	REQUIRE(CBufferWrite(test_buffer, test_src, 14) == 14);
	REQUIRE(CBufferGetSize(test_buffer) == 14);
	REQUIRE(CBufferWrite(test_buffer, test_src, 10) == 6);

	/* test Read */

	REQUIRE(CBufferRead(test_buffer, test_dest, 14) == 14);
	REQUIRE(CBufferGetSize(test_buffer) == 6);
	printf("%s\n", test_dest);
	REQUIRE(*test_src == *test_dest);
	REQUIRE(CBufferRead(test_buffer, test_dest, 14) == 6);

	/* test Clear */
	CBufferClear(test_buffer);
	REQUIRE(CBufferGetCapacity(test_buffer) == 20);
	REQUIRE(CBufferGetSize(test_buffer) == 0);

	/* test Write at full */
	REQUIRE(CBufferWrite(test_buffer, test_src, 14) == 14);
	REQUIRE(CBufferWrite(test_buffer, test_src, 10) == 6);
	REQUIRE(CBufferWrite(test_buffer, test_src, 10) == -1);
	REQUIRE(errno == ENOBUFS);

	/* test Read empty */
	REQUIRE(CBufferRead(test_buffer, test_dest, 20) == 20);
	REQUIRE(CBufferRead(test_buffer, test_dest, 20) == -1);
	REQUIRE(errno == ENODATA);

	free_test = &test_buffer;
	CBufferDestroy(free_test);
	REQUIRE(test_buffer == NULL);

	return (TEST_PASS);
}
