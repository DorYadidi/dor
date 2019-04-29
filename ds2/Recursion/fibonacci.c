/*******************************************************************************
* NAME: binary sorted tree                                                     *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  11.12.18                                                      *
*******************************************************************************/

#include "test.h"
#include <stdio.h>

TestResult TestFibonacci();
size_t IterativeFibonacci(int n);
size_t RecursionFibonacci(int n);

int main ()
{
	RUN_TEST(TestFibonacci);

	return (0);
}

size_t IterativeFibonacci(int n)
{
	int prev = 0, current = 1;
	int i = 0;

	for (i = 2; i <= n; ++i)
	{
		current = prev + current;
		prev = current - prev;
	}
	return (current);

}

size_t RecursionFibonacci(int n)
{
	if (1 >= n)
	{
		return (n);
	}

	return (RecursionFibonacci(n-1) + RecursionFibonacci(n-2));
}

/**********************************TEST*********************************************/
TestResult TestFibonacci()
{
	int n = 10;
	printf ("\nIterative %lu\n", IterativeFibonacci(n));
	printf ("Recursion %lu\n", RecursionFibonacci(n));

	REQUIRE(IterativeFibonacci(n) == RecursionFibonacci(n));

	return (TEST_PASS);
}
