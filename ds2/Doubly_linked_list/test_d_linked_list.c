#include <stdlib.h> /* free */

#include "d_linked_list.h"
#include "test.h"
#include "function_pointers.h"

TestResult TestDLinkedList1();
status PrintSLL(void *head, void *param);

int main()
{
	RUN_TEST(TestDLinkedList1);

	return (0);
}

TestResult TestDLinkedList1()
{
	int a = 1;
	int b = 2;
	int c = 3;
	dll_iterator_t iterator;
	dll_iterator_t iterator2;
	dll_iterator_t iterator3;
	d_linked_list_t *dll = DLinkedListCreate();
	d_linked_list_t *splice = DLinkedListCreate();

	/*test: create + GetSize and ISEmpty*/
	REQUIRE("test Create" && dll != NULL);
	REQUIRE("test GetSize" && 0 == DLinkedListGetSize(dll));
	REQUIRE("test IsEmpty" && TRUE == DLinkedListIsEmpty(dll));

	/*test: PushFront + GetData*/
	DLinkedListPushFront(dll, &a);
	DLinkedListPushFront(dll, &b);
	REQUIRE("test GetSize" && 2 == DLinkedListGetSize(dll));
	iterator = DLinkedListPushFront(dll, &c);
	REQUIRE("test GetSize" && 3 == DLinkedListGetSize(dll));
	REQUIRE("test GetData" && *(int *)DLinkedListGetData(iterator) == c);
	REQUIRE("test is IsEmpty" && FALSE == DLinkedListIsEmpty(dll));

	/* test PopFront*/
	DLinkedListPopFront(dll);
	DLinkedListPopFront(dll);
	DLinkedListPopFront(dll);
	REQUIRE("test PopFront" && 0 == DLinkedListGetSize(dll));
	REQUIRE("test PopFront" && TRUE == DLinkedListIsEmpty(dll));

	/* test PushBack*/
	DLinkedListPushBack(dll, &c);
	DLinkedListPushBack(dll, &b);
	REQUIRE("test PushBack" && 2 == DLinkedListGetSize(dll));
	iterator = DLinkedListPushBack(dll, &a);
	REQUIRE("test GetData" && *(int *)DLinkedListGetData(iterator) == a);

	/* test PopBack*/
	DLinkedListPopBack(dll);
	DLinkedListPopBack(dll);
	DLinkedListPopBack(dll);
	REQUIRE("test PopBack" && 0 == DLinkedListGetSize(dll));
	REQUIRE("test PopBack" && TRUE == DLinkedListIsEmpty(dll));

	/* test begin & end */
	DLinkedListPushFront(dll, &a);
	DLinkedListPushFront(dll, &b);
	iterator = DLinkedListBegin(dll);
	REQUIRE("test Begin" && b == *(int*)DLinkedListGetData(iterator));
	iterator = DLinkedListEnd(dll);
	iterator =DLinkedListGetPrevious(iterator);;
	REQUIRE("test End" && a == *(int*)DLinkedListGetData(iterator));
	DLinkedListPopBack(dll);
	DLinkedListPopBack(dll);
	REQUIRE("test PopBack" && TRUE == DLinkedListIsEmpty(dll));

	/*test Insert + GetNext + GetPrevious*/
	iterator = DLinkedListPushFront(dll, &a);
	DLinkedListInsert(iterator, &b);
	DLinkedListInsert(iterator, &c);
	REQUIRE("test Insert" && 3 == DLinkedListGetSize(dll));
	REQUIRE("test Insert" && *(int *)DLinkedListGetData(iterator) == a);
	iterator = DLinkedListGetPrevious(iterator);
	REQUIRE("test GetPrevious" && *(int *)DLinkedListGetData(iterator) == c);
	iterator = DLinkedListGetNext(iterator);
	REQUIRE("test GetNext" && *(int *)DLinkedListGetData(iterator) == a);
	DLinkedListPopBack(dll);
	DLinkedListPopBack(dll);
	DLinkedListPopBack(dll);
	REQUIRE("test PopBack" && TRUE == DLinkedListIsEmpty(dll));

	/* test InsertAfter + Erase */
	iterator = DLinkedListPushFront(dll, &a);
	DLinkedListInsertAfter(iterator, &b);
	DLinkedListInsertAfter(iterator, &c);
	REQUIRE("test InsertAfter" && 3 == DLinkedListGetSize(dll));
	REQUIRE("test InsertAfter" && *(int *)DLinkedListGetData(iterator) == a);
	iterator = DLinkedListGetNext(iterator);
	REQUIRE("test InsertAfter" && *(int *)DLinkedListGetData(iterator) == c);
	iterator = DLinkedListGetNext(iterator);
	REQUIRE("test InsertAfter" && *(int *)DLinkedListGetData(iterator) == b);
	DLinkedListErase(iterator);
	REQUIRE("test Erase" && 2 == DLinkedListGetSize(dll));
	DLinkedListPopBack(dll);
	DLinkedListPopBack(dll);
	REQUIRE("test PopBack" && TRUE == DLinkedListIsEmpty(dll));

	/* test Splice */
	iterator = DLinkedListPushBack(dll, &a);
	DLinkedListPushBack(dll , &b);
	DLinkedListPushBack(dll, &c);
	DLinkedListPushBack(splice, &b);
	iterator2 = DLinkedListPushBack(splice, &a);
	DLinkedListPushBack(splice, &a);
	iterator3 = DLinkedListPushBack(splice, &c);
	DLinkedListPushBack(splice, &c);
	DLinkedListPushBack(splice, &c);
	DLinkedListSplice(iterator, iterator2, iterator3);
	REQUIRE("test Splice" && 5 == DLinkedListGetSize(dll));
	REQUIRE("test InsertAfter" && *(int *)DLinkedListGetData(iterator) == a);
	iterator = DLinkedListGetPrevious(iterator);
	REQUIRE("test InsertAfter" && *(int *)DLinkedListGetData(iterator) == a);
	iterator = DLinkedListGetPrevious(iterator);
	REQUIRE("test InsertAfter" && *(int *)DLinkedListGetData(iterator) == a);

	/* test Destroy*/
	DLinkedListDestroy(dll);
	DLinkedListDestroy(splice);

	return (TEST_PASS);
}
