#include "../include/test.h"
#include "../include/bit_array.h"

TestResult BitArrayIsOnTest();
TestResult BitArrayIsOffTest();
TestResult BitArraySetOnTest();
TestResult BitArraySetOffTest();
TestResult BitArrayFlipTest();
TestResult BitArrayRotateRightTest();
TestResult BitArrayRotateLeftTest();
TestResult BitArrayMirrorTest();
TestResult BitArrayCountOnTest();
TestResult BitArrayCountOffTest();
TestResult BitArrayMirrorLUTTest();
TestResult BitArrayCountOnLUTTest();
TestResult BitArrayCountOffLUTTest();

int main()
{
	RUN_TEST(BitArrayIsOnTest);
	RUN_TEST(BitArrayIsOffTest);
	RUN_TEST(BitArraySetOnTest);
	RUN_TEST(BitArraySetOffTest);
	RUN_TEST(BitArrayFlipTest);
	RUN_TEST(BitArrayRotateRightTest);
	RUN_TEST(BitArrayRotateLeftTest);
	RUN_TEST(BitArrayMirrorTest);
	RUN_TEST(BitArrayCountOnTest);
	RUN_TEST(BitArrayCountOffTest);
	RUN_TEST(BitArrayMirrorLUTTest);
	RUN_TEST(BitArrayCountOnLUTTest);
	RUN_TEST(BitArrayCountOffLUTTest);

	return (TEST_PASS);
}

TestResult BitArrayIsOnTest()
{
	REQUIRE(BitArrayIsOn(1, 0) == 1);
	REQUIRE(BitArrayIsOn(0, 0) == 0);
	REQUIRE(BitArrayIsOn(0xffffffffffffffff, 0) == 1);
	REQUIRE(BitArrayIsOn(0xffffffffffffffff, 63) == 1);
	REQUIRE(BitArrayIsOn(0xfffffffffffffffe, 0) == 0);
	REQUIRE(BitArrayIsOn(0x7fffffffffffffff, 63) == 0);

	return (TEST_PASS);
}

TestResult BitArrayIsOffTest()
{
	REQUIRE(BitArrayIsOff(1, 0) == 0);
	REQUIRE(BitArrayIsOff(0, 0) == 1);
	REQUIRE(BitArrayIsOff(0xffffffffffffffff, 0) == 0);
	REQUIRE(BitArrayIsOff(0xffffffffffffffff, 63) == 0);
	REQUIRE(BitArrayIsOff(0xfffffffffffffffe, 0) == 1);
	REQUIRE(BitArrayIsOff(0x7fffffffffffffff, 63) == 1);

	return (TEST_PASS);
}

TestResult BitArraySetOnTest()
{
	REQUIRE(BitArraySetOn(0, 0) == 1);
	REQUIRE(BitArraySetOn(1, 0) == 1);
	REQUIRE(BitArraySetOn(0xffffffffffffffff, 0) == 0xffffffffffffffff);
	REQUIRE(BitArraySetOn(0x7fffffffffffffff, 63) == 0xffffffffffffffff);
	REQUIRE(BitArraySetOn(0xfffffffffffffffe, 0) == 0xffffffffffffffff);
	REQUIRE(BitArraySetOn(0xffffffffffffff7f, 7) == 0xffffffffffffffff);

	return (TEST_PASS);
}

TestResult BitArraySetOffTest()
{
	REQUIRE(BitArraySetOff(1, 0) == 0);
	REQUIRE(BitArraySetOff(0, 0) == 0);
	REQUIRE(BitArraySetOff(0xffffffffffffffff, 0) == 0xfffffffffffffffe);
	REQUIRE(BitArraySetOff(0xffffffffffffffff, 63) == 0x7fffffffffffffff);
	REQUIRE(BitArraySetOff(0xfffffffffffffffe, 0) == 0xfffffffffffffffe);
	REQUIRE(BitArraySetOff(0xffffffffffffffff, 7) == 0xffffffffffffff7f);

	return (TEST_PASS);
}

TestResult BitArrayFlipTest()
{
	REQUIRE(BitArrayFlip(1, 0) == 0);
	REQUIRE(BitArrayFlip(0, 0) == 1);
	REQUIRE(BitArrayFlip(0xffffffffffffffff, 0) == 0xfffffffffffffffe);
	REQUIRE(BitArrayFlip(0xffffffffffffffff, 63) == 0x7fffffffffffffff);
	REQUIRE(BitArrayFlip(0xfffffffffffffffe, 0) == 0xffffffffffffffff);
	REQUIRE(BitArrayFlip(0xffffffffffffffff, 7) == 0xffffffffffffff7f);

	return (TEST_PASS);
}

TestResult BitArrayRotateRightTest()
{
	REQUIRE(BitArrayRotateRight(1, 1) == (unsigned long)1 << 63);
	REQUIRE(BitArrayRotateRight(1<<30, 31) == (unsigned long)1 << 63);
	REQUIRE(BitArrayRotateRight(0xf, 1) == 0x8000000000000007);
	REQUIRE(BitArrayRotateRight(0xf, 2) == 0xc000000000000003);

	return (TEST_PASS);
}

TestResult BitArrayRotateLeftTest()
{
	REQUIRE(BitArrayRotateLeft((unsigned long)1 << 63, 1) == 1);
	REQUIRE(BitArrayRotateLeft((unsigned long)1 << 63, 31) == 1<<30);
	REQUIRE(BitArrayRotateLeft(0x8000000000000007, 1) == 0xf);
	REQUIRE(BitArrayRotateLeft(0xc000000000000003, 2) == 0xf);

	return (TEST_PASS);
}

TestResult BitArrayMirrorTest()
{
	REQUIRE(BitArrayMirror(0xf) == 0xf000000000000000);
	REQUIRE(BitArrayMirror(0xf000000000000000) == 0xf);
	REQUIRE(BitArrayMirror(0) == 0);
	REQUIRE(BitArrayMirror(0xffffffffffffffff) == 0xffffffffffffffff);

	return (TEST_PASS);
}

TestResult BitArrayCountOnTest()
{
	REQUIRE(BitArrayCountOn(0xffffffffffffffff) == 64);

	return (TEST_PASS);
}

TestResult BitArrayCountOffTest()
{
	REQUIRE(BitArrayCountOff(0xffffffffffffffff) == 0);

	return (TEST_PASS);
}

TestResult BitArrayMirrorLUTTest()
{
	REQUIRE(BitArrayMirrorLUT(0xf) == 0xf000000000000000);
	REQUIRE(BitArrayMirrorLUT(0xf000000000000000) == 0xf);
	REQUIRE(BitArrayMirrorLUT(0) == 0);
	REQUIRE(BitArrayMirrorLUT(0xffffffffffffffff) == 0xffffffffffffffff);

	return (TEST_PASS);
}

TestResult BitArrayCountOnLUTTest()
{
	REQUIRE(BitArrayCountOnLUT(0xffffffffffffffff) == 64);

	return (TEST_PASS);
}

TestResult BitArrayCountOffLUTTest()
{
	REQUIRE(BitArrayCountOffLUT(0xffffffffffffffff) == 0);

	return (TEST_PASS);
}
