/*******************************************************************************
* NAME: binary sorted tree                                                     *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  11.12.18                                                      *
*******************************************************************************/

#include "test.h"
#include "s_linked_list.h"
#include <stdio.h>
#include <string.h>


sll_node_t *SLinkedListRecursionFlip(sll_node_t *head);
TestResult TestRecursionFlip();


int main ()
{
	RUN_TEST(TestRecursionFlip);

	return (0);
}

sll_node_t *SLinkedListRecursionFlip(sll_node_t *head)
{
	sll_node_t *end = head->next;
    if (NULL == end)
	{
       return (head);
   	}
    else
	{
		end = SLinkedListRecursionFlip(head->next);
	    head->next->next = head;
	    head->next  = NULL;

		return (end);
	}
}

TestResult TestRecursionFlip()
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
	REQUIRE(SLinkedListGetSize(head) == 4);
	head = SLinkedListRecursionFlip(head);
	REQUIRE(head->data == &d);
	REQUIRE(SLinkedListGetSize(head) == 4);

	SLinkedListDestroy(&head);

	return (TEST_PASS);
}
