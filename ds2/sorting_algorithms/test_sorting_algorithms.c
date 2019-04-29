/*******************************************************************************
* NAME: Sorting Algorithms                                                     *
*                                                                              *
* AUTHOR: Dor Yadidi / Yaakov Sidikman                                         *
* DATE UPDATED:  30.12.18                                                      *
*******************************************************************************/

#include "test.h"
#include "sorting_algorithms.h"
#include <time.h> /*srand time()*/
#include <stdio.h> /*qsort printf*/
#include <sys/time.h>

#define DATA_SIZE 10000000
#define RANDOM_AGE 1000000

typedef struct age_int_s
{
	int age;

} age_int_t;

TestResult BubbleSortTest();
TestResult InsertionSortTest();
TestResult SelectionSortTest();
TestResult CountingSortTest();
TestResult RadixSortTest();
TestResult MergeSortTest();
TestResult QSortTest();
TestResult HeapSortTest();
TestResult QuickSortTest();
TestResult BSearchIterativeTest();
TestResult BSearchRecursiveTest();

static double msort_total;
static double hsort_total;
static double qsort_total;
static double quick_sort_total;

int main()
{
	int i = 0;
/*	RUN_TEST(BubbleSortTest);
	RUN_TEST(InsertionSortTest);
	RUN_TEST(SelectionSortTest);
	RUN_TEST(CountingSortTest);
	RUN_TEST(RadixSortTest);
	RUN_TEST(QuickSortTest);
	RUN_TEST(BSearchIterativeTest);
	RUN_TEST(BSearchRecursiveTest);
*/
	for ( ; i < 10; ++i)
	{
		RUN_TEST(QuickSortTest);
		RUN_TEST(MergeSortTest);
		RUN_TEST(HeapSortTest);
		RUN_TEST(QSortTest);
	}

	printf("\nQuickSort runtime: %f seconds \n", quick_sort_total / 10);
	printf("MergeSort runtime: %f seconds \n", msort_total / 10);
	printf("Heap Sort runtime: %f seconds \n", hsort_total / 10);
	printf("QuickSort runtime: %f seconds \n", qsort_total / 10);

	return (0);
}


age_int_t *CreateArrayOfAges()
{
	age_int_t *elements = malloc(DATA_SIZE * sizeof(age_int_t));

	size_t i = 0;
	srand(time(NULL));

	for ( ; i < DATA_SIZE; ++i)
	{
		elements[i].age = rand() % RANDOM_AGE;
	}

	return (elements);
}

int CompareMinToMax(const void *before, const void *after)
{

	return(((age_int_t *)before)->age - ((age_int_t *)after)->age);
}

bool IsSorted(void *elements, size_t element_size, size_t element_count,
              compare_function_t compare)
{
	size_t i = 0;
	for ( ; i < element_count - 1; i++)
	{
		if (compare(
			((char *)elements + (i * element_size)),
			((char *)elements + ((i + 1) * element_size))) > 0)
		{
			return (FALSE);
		}
	}

	return (TRUE);
}

static size_t KeyToNumAges(void *element, void *param)
{
	(void)param;

	return (size_t)(((age_int_t *)element)->age);
}
/*************************************************************************/

TestResult BubbleSortTest()
{
	age_int_t *elements = CreateArrayOfAges();
	BubbleSort(elements, sizeof(age_int_t), DATA_SIZE, CompareMinToMax);

	REQUIRE(IsSorted(elements, sizeof(age_int_t), DATA_SIZE, CompareMinToMax));
	free(elements);

	return (TEST_PASS);
}

TestResult InsertionSortTest()
{
	age_int_t *elements = CreateArrayOfAges();
	InsertionSort(elements, sizeof(age_int_t), DATA_SIZE, CompareMinToMax);

	REQUIRE(IsSorted(elements, sizeof(age_int_t), DATA_SIZE, CompareMinToMax));
	free(elements);

	return (TEST_PASS);
}

TestResult SelectionSortTest()
{
	age_int_t *elements = CreateArrayOfAges();
	SelectionSort(elements, sizeof(age_int_t), DATA_SIZE, CompareMinToMax);

	REQUIRE(IsSorted(elements, sizeof(age_int_t), DATA_SIZE, CompareMinToMax));
	free(elements);

	return (TEST_PASS);
}

TestResult CountingSortTest()
{
	age_int_t *elements = CreateArrayOfAges();
	CountingSort(elements, sizeof(age_int_t), DATA_SIZE, KeyToNumAges, NULL,
	             RANDOM_AGE + 1);

	REQUIRE(IsSorted(elements, sizeof(age_int_t), DATA_SIZE, CompareMinToMax));
	free(elements);

	return (TEST_PASS);
}

TestResult RadixSortTest()
{

	age_int_t *elements = CreateArrayOfAges();
	RadixSort(elements, sizeof(age_int_t), DATA_SIZE, KeyToNumAges, NULL,
	         sizeof(int));

	REQUIRE(IsSorted(elements, sizeof(age_int_t), DATA_SIZE, CompareMinToMax));

	free(elements);

	return (TEST_PASS);
}

TestResult MergeSortTest()
{
	age_int_t *elements = CreateArrayOfAges();
	struct timeval stop, start;

	gettimeofday(&start, NULL);
	MergeSort(elements, sizeof(age_int_t), DATA_SIZE, CompareMinToMax);
	gettimeofday(&stop, NULL);
	msort_total += (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

	REQUIRE(IsSorted(elements, sizeof(age_int_t), DATA_SIZE, CompareMinToMax));
	free(elements);

	return (TEST_PASS);
}

TestResult QSortTest()
{
	age_int_t *elements = CreateArrayOfAges();
	struct timeval stop, start;

	gettimeofday(&start, NULL);
	qsort(elements, DATA_SIZE, sizeof(age_int_t), CompareMinToMax);
	gettimeofday(&stop, NULL);
	qsort_total += (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

	REQUIRE(IsSorted(elements, sizeof(age_int_t), DATA_SIZE, CompareMinToMax));
	free(elements);

	return (TEST_PASS);
}

TestResult HeapSortTest()
{
	age_int_t *elements = CreateArrayOfAges();
	struct timeval stop, start;

	gettimeofday(&start, NULL);
	HeapSort(elements,sizeof(age_int_t), DATA_SIZE, CompareMinToMax);
	gettimeofday(&stop, NULL);
	hsort_total += (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

	REQUIRE(IsSorted(elements, sizeof(age_int_t), DATA_SIZE, CompareMinToMax));
	free(elements);

	return (TEST_PASS);
}

TestResult QuickSortTest()
{
	age_int_t *elements = CreateArrayOfAges();
	struct timeval stop, start;

	gettimeofday(&start, NULL);
	QuickSort(elements, sizeof(age_int_t), DATA_SIZE, CompareMinToMax);
	gettimeofday(&stop, NULL);
	quick_sort_total += (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

	REQUIRE(IsSorted(elements, sizeof(age_int_t), DATA_SIZE, CompareMinToMax));
	free(elements);

	return (TEST_PASS);
}

/*****************************************************************************/
TestResult BSearchIterativeTest()
{
	int array[] = {2, 5, 6, 8, 9, 10};
	int array_size = 6;
	int *data = BSearchIterative(array, array_size, 5);
	REQUIRE(*data == 5);
	data = BSearchIterative(array, array_size, 2);
	REQUIRE(*data == 2);
	data = BSearchIterative(array, array_size, 10);
	REQUIRE(*data == 10);
	data = BSearchIterative(array, array_size, 333);
	REQUIRE(data == NULL);


	return (TEST_PASS);
}

TestResult BSearchRecursiveTest()
{
	int array[] = {2, 5, 6, 8, 9, 10};
	int array_size = 6;
	int *data = BSearchRecursive(array, array_size, 5);
	REQUIRE(*data == 5);
	data = BSearchRecursive(array, array_size, 2);
	REQUIRE(*data == 2);
	data = BSearchRecursive(array, array_size, 10);
	REQUIRE(*data == 10);
	data = BSearchRecursive(array, array_size, 333);
	REQUIRE(data == NULL);

	return (TEST_PASS);
}
