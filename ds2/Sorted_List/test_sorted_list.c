#include "test.h"
#include "d_linked_list.h"
#include "sorted_list.h"
#include "function_pointers.h"
#include <stdio.h>

TestResult TestSortedList1();
bool IsBeforMin (void *current_data, void *new_data);

int main()
{
	RUN_TEST(TestSortedList1);

	return (0);
}

bool IsBeforMin (void *current_data, void *new_data)
{
	if (*(int *)new_data < *(int *)current_data)
	{
		return (TRUE);
	}

	return (FALSE);
}

TestResult TestSortedList1()
{
	int a = 1;
	int b = 4;
	int c = 11;
	int d = 5;
	int e = 13;
	int f = 11;
	sorted_iterator_t iterator;
	sorted_list_t *sorted = SortedListCreate(IsBeforMin);
	sorted_list_t *src = SortedListCreate(IsBeforMin);

	/*test: create + GetSize and ISEmpty*/
	REQUIRE("test Create" && sorted != NULL);
	REQUIRE("test GetSize" && 0 == SortedListGetSize(sorted));
	REQUIRE("test IsEmpty" && TRUE == SortedListIsEmpty(sorted));

	/*test INSERT*/
	iterator = SortedListInsert(sorted, &b);
	REQUIRE("test GetSize" && 1 == SortedListGetSize(sorted));
	SortedListInsert(sorted, &c);
	REQUIRE("test GetSize" && 2 == SortedListGetSize(sorted));
	REQUIRE("test IsEmpty" && FALSE == SortedListIsEmpty(sorted));
	REQUIRE("test Insert" && b == *(int*)SortedListGetData(iterator));
	iterator = SortedListGetNext(iterator);
	REQUIRE("test Insert" && c == *(int*)SortedListGetData(iterator));
	SortedListInsert(sorted, &a);
	iterator = SortedListGetPrevious(iterator);
	iterator = SortedListGetPrevious(iterator);
	REQUIRE("test Insert" && a == *(int*)SortedListGetData(iterator));

	/*test PopFront+PopBack+Erase*/
	SortedListErase(iterator);
	SortedListPopFront(sorted);
	SortedListPopBack(sorted);
	REQUIRE("test GetSize" && 0 == SortedListGetSize(sorted));
	REQUIRE("test IsEmpty" && TRUE == SortedListIsEmpty(sorted));

	/*test Merge*/
	iterator = SortedListInsert(sorted, &c);
	SortedListInsert(sorted, &a);
	SortedListInsert(sorted, &b);
	REQUIRE("test GetSize" && 3 == SortedListGetSize(sorted));
	SortedListInsert(src, &d);
	SortedListInsert(src, &e);
	SortedListInsert(src, &f);
	REQUIRE("test GetSize" && 3 == SortedListGetSize(src));
	SortedListMerge(sorted, src);
	REQUIRE("test Insert" && c == *(int*)SortedListGetData(iterator));
	iterator = SortedListGetNext(iterator);
	REQUIRE("test Insert" && f == *(int*)SortedListGetData(iterator));
	iterator = SortedListGetNext(iterator);
	REQUIRE("test Insert" && e == *(int*)SortedListGetData(iterator));
	iterator = SortedListGetPrevious(iterator);
	iterator = SortedListGetPrevious(iterator);
	iterator = SortedListGetPrevious(iterator);
	REQUIRE("test Insert" && d == *(int*)SortedListGetData(iterator));
	iterator = SortedListGetPrevious(iterator);
	REQUIRE("test Insert" && b == *(int*)SortedListGetData(iterator));
	iterator = SortedListGetPrevious(iterator);
	REQUIRE("test Insert" && a == *(int*)SortedListGetData(iterator));

	/*test Destroy*/
	SortedListDestroy(sorted);
	SortedListDestroy(src);

	return (TEST_PASS);
}
