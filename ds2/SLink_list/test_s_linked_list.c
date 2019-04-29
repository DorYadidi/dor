#include "s_linked_list.h"
#include "test.h"
#include <string.h> /*strcmp*/
#include <stdlib.h> /*malloc, free*/

/*******************************************************************************
* NAME: Singly Linked List                                                     *
*                                                                              *
* PURPOSE: Singly Linked List                                                  *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  13.11.18                                                      *
*******************************************************************************/


typedef struct disneyland_s
{
	int id;

}disneyland_t;

TestResult Disneyland();
TestResult TestSLinkedList1(); /*check remove, loop and remove loop*/
TestResult TestSLinkedList2(); 	/*check Insert and InsertAfter*/
TestResult TestSLinkedList3(); /*check flip and insert after flip*/
TestResult TestSLinkedList4(); /*check Intersection*/
TestResult TestSLinkedList5(); /*check Intersection*/

status FindSettler(void *data, void *param);

int main()
{
	RUN_TEST(TestSLinkedList1);
	RUN_TEST(TestSLinkedList2);
	RUN_TEST(TestSLinkedList3);
	RUN_TEST(TestSLinkedList4);
	RUN_TEST(TestSLinkedList5);
	RUN_TEST(Disneyland);

	return 0;
}

TestResult TestSLinkedList1()
{
	int a = 4;
	int b = 5;

	sll_node_t *li = NULL;
	sll_node_t *li_2 = NULL;
	sll_node_t *li_3 = NULL;
	sll_node_t *li_4 = NULL;

	li = SLinkedListCreate(&a, NULL);
	li_2 = SLinkedListCreate(&b, NULL);
	li_3 = SLinkedListCreate(&a, NULL);
	li_4 = SLinkedListCreate(&b, NULL);

	SLinkedListInsertAfter(li,li_2);
	REQUIRE(SLinkedListGetSize(li) == 2);
	SLinkedListInsertAfter(li_2,li_3);
	REQUIRE(SLinkedListGetSize(li) == 3);/*check insert*/
	SLinkedListInsertAfter(li_3,li_4);
	REQUIRE(SLinkedListGetSize(li) == 4);

	li_4->next = li;
	REQUIRE(SLinkedListHasLoop(li) == TRUE); /*Check has loop*/
	li_4->next = NULL;
	REQUIRE(SLinkedListHasLoop(li) == FALSE); /*Check no loop*/

	SLinkedListDestroy(&li);
	return (TEST_PASS);
}

TestResult TestSLinkedList2()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;

	sll_node_t *head = NULL;
	sll_node_t *tmp1 = NULL;
	sll_node_t *tmp2 = NULL;
	sll_node_t *tmp3 = NULL;

	head = SLinkedListCreate(&a, NULL);
	tmp1 = SLinkedListCreate(&b, NULL);
	tmp2 = SLinkedListCreate(&c, NULL);
	tmp3 = SLinkedListCreate(&d, NULL);

	SLinkedListInsertAfter(head,tmp1);
	REQUIRE(head->next == tmp1);
	SLinkedListInsertAfter(tmp1,tmp3);
	REQUIRE(tmp1->next == tmp3);
	SLinkedListInsert(tmp3,tmp2);
	REQUIRE(tmp1->next == tmp3);
	REQUIRE(tmp3->data == &c);
	REQUIRE(tmp2->next == NULL);
	REQUIRE(tmp2->data == &d);

	SLinkedListDestroy(&head);
	return (TEST_PASS);
}

TestResult TestSLinkedList3()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;

	sll_node_t *head = NULL;
	sll_node_t *tmp1 = NULL;
	sll_node_t *tmp2 = NULL;
	sll_node_t *tmp3 = NULL;


	head = SLinkedListCreate(&a, NULL);
	tmp1 = SLinkedListCreate(&b, NULL);
	tmp2 = SLinkedListCreate(&c, NULL);
	tmp3 = SLinkedListCreate(&d, NULL);


	SLinkedListInsertAfter(head,tmp1);
	SLinkedListInsertAfter(tmp1,tmp3);
	SLinkedListInsert(tmp3,tmp2);
	REQUIRE(tmp3->data == &c);
	REQUIRE(tmp2->data == &d);
	REQUIRE(head->data == &a);
	REQUIRE(SLinkedListGetSize(head) == 4);
	head = SLinkedListFlip(head);
	REQUIRE(head->data == &d);
	REQUIRE(SLinkedListGetSize(head) == 4);

	SLinkedListDestroy(&head);

	return (TEST_PASS);
}

TestResult TestSLinkedList4()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;

	sll_node_t *head = NULL;
	sll_node_t *tmp1 = NULL;
	sll_node_t *tmp2 = NULL;
	sll_node_t *tmp3 = NULL;
	sll_node_t *head2 = NULL;
	sll_node_t *head3 = NULL;

	head = SLinkedListCreate(&a, NULL);
	tmp1 = SLinkedListCreate(&b, NULL);
	tmp2 = SLinkedListCreate(&c, NULL);
	tmp3 = SLinkedListCreate(&d, NULL);


	SLinkedListInsertAfter(head,tmp1);
	tmp2 = SLinkedListInsertAfter(tmp1,tmp2);
	SLinkedListInsertAfter(tmp2,tmp3);
	REQUIRE(tmp2->next == tmp3);
	REQUIRE(tmp3->data == &d);
	REQUIRE(tmp2->data == &c);
	REQUIRE(head->data == &a);
	REQUIRE(SLinkedListGetSize(head) == 4);


	head3 = SLinkedListCreate(&a, NULL);
	REQUIRE(SLinkedListIntersection(head, head3) == NULL);

	head2 = SLinkedListCreate(&a, tmp2);
	REQUIRE(tmp2->next == tmp3);
	REQUIRE(head2->next == tmp2);
	REQUIRE(tmp1->next == tmp2);
	REQUIRE(SLinkedListIntersection(head, head2) == tmp2);

	SLinkedListDestroy(&head);
	free(head2);
	SLinkedListDestroy(&head3);
	return (TEST_PASS);
}

status PrintLinkedList(void *data, void *param)
{
	(void)(param);
	printf("%d\n", *(int *)data);

	return (SUCCESS);
}

TestResult TestSLinkedList5()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;

	sll_node_t *head = NULL;
	sll_node_t *tmp1 = NULL;
	sll_node_t *tmp2 = NULL;
	sll_node_t *tmp3 = NULL;


	head = SLinkedListCreate(&a, NULL);
	tmp1 = SLinkedListCreate(&b, NULL);
	tmp2 = SLinkedListCreate(&c, NULL);
	tmp3 = SLinkedListCreate(&d, NULL);


	SLinkedListInsertAfter(head,tmp1);
	SLinkedListInsertAfter(tmp1,tmp3);
	SLinkedListInsert(tmp3,tmp2);
	SLinkedListForEach(head,PrintLinkedList, NULL);

	SLinkedListDestroy(&head);
	return (TEST_PASS);
}

status FindSettler(void *data, void *result)
{
	*(int *)result = *(int *)result ^ ((disneyland_t *)data)->id;
	return (SUCCESS);
}

TestResult Disneyland()
{
	disneyland_t a = {1};
	disneyland_t b = {2};
	disneyland_t c = {3};
	disneyland_t d = {4};
	disneyland_t e = {1};
	disneyland_t f = {2};
	disneyland_t g = {4};
	int result = 0;

	sll_node_t *head = NULL;
	sll_node_t *tmp1 = NULL;
	sll_node_t *tmp2 = NULL;
	sll_node_t *tmp3 = NULL;
	sll_node_t *tmp4 = NULL;
	sll_node_t *tmp5 = NULL;
	sll_node_t *tmp6 = NULL;

	head = SLinkedListCreate(&a, NULL);
	tmp1 = SLinkedListCreate(&b, NULL);
	tmp2 = SLinkedListCreate(&c, NULL);
	tmp3 = SLinkedListCreate(&d, NULL);
	tmp4 = SLinkedListCreate(&e, NULL);
	tmp5 = SLinkedListCreate(&f, NULL);
	tmp6 = SLinkedListCreate(&g, NULL);

	SLinkedListInsertAfter(head,tmp1);
	SLinkedListInsertAfter(tmp1,tmp2);
	SLinkedListInsertAfter(tmp2,tmp3);
	SLinkedListInsertAfter(tmp3,tmp4);
	SLinkedListInsertAfter(tmp4,tmp5);
	SLinkedListInsertAfter(tmp5,tmp6);

	SLinkedListForEach(head, FindSettler, &result);
	REQUIRE(3 == result);
	SLinkedListDestroy(&head);

	return (TEST_PASS);
}
