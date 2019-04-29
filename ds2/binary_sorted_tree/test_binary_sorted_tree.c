/*******************************************************************************
* NAME: binary sorted tree                                                     *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  11.12.18                                                      *
*******************************************************************************/

#include <stdio.h> /*sizeof*/
#include "binary_sorted_tree.h"
#include "test.h"
#include "function_pointers.h"

TestResult TestBSTCreateAndSize();
TestResult TestBegin();
TestResult TestBSTInsert();
TestResult TestEnd();
TestResult TestFind();
TestResult TestForEach();
TestResult TestGetPrevious();
TestResult TestIsSameIterator();
TestResult TestRemove();


int CompareMinToMax(void *before, void *after);
status BSTPlusTwo(void *data, void *param);

int main()
{
	RUN_TEST(TestBSTCreateAndSize);
	RUN_TEST(TestBegin);
	RUN_TEST(TestBSTInsert);
	RUN_TEST(TestFind);
	RUN_TEST(TestEnd);
	RUN_TEST(TestIsSameIterator);
	RUN_TEST(TestGetPrevious);
	RUN_TEST(TestForEach);
	RUN_TEST(TestRemove);

	return (0);
}

int CompareMinToMax(const void *before, const void *after)
{

	return(*(int *)before - *(int *)after);
}

status BSTPlusTwo(void *data, void *param)
{
	*(int *)data += *(int *)param;

	return (SUCCESS);
}

TestResult TestBSTCreateAndSize()
{
	bst_t *bst = BSTCreate(CompareMinToMax);

	/*test: create + GetSize and ISEmpty*/
	REQUIRE("test GetSize" && 0 == BSTGetSize(bst));
	REQUIRE("test IsEmpty" && TRUE == BSTIsEmpty(bst));

	BSTDestroy(bst);

	return (TEST_PASS);
}

TestResult TestBegin()
{
	int key_1 = 1;
	int key_2 = 2;
	int key_3 = 3;
	int key_4 = 4;
	int key_5 = 5;
	int key_6 = 6;

	bst_iterator_t iter_1;

	bst_t *tree = BSTCreate(CompareMinToMax);
	REQUIRE(tree);

	BSTInsert(tree, &key_5);
	iter_1 = BSTBegin(tree);
	REQUIRE(5 == *(int *)BSTGetData(iter_1));

	BSTInsert(tree, &key_2);
	iter_1 = BSTBegin(tree);
	REQUIRE(2 == *(int *)BSTGetData(iter_1));

	BSTInsert(tree, &key_1);
	iter_1 = BSTBegin(tree);
	REQUIRE(1 == *(int *)BSTGetData(iter_1));

	BSTInsert(tree, &key_4);
	iter_1 = BSTBegin(tree);
	REQUIRE(1 == *(int *)BSTGetData(iter_1));

	REQUIRE("test GetSize" && 4 == BSTGetSize(tree));

	BSTInsert(tree, &key_6);
	iter_1 = BSTBegin(tree);
	REQUIRE(1 == *(int *)BSTGetData(iter_1));

	BSTInsert(tree, &key_3);
	iter_1 = BSTBegin(tree);
	REQUIRE(1 == *(int *)BSTGetData(iter_1));

	BSTDestroy(tree);

	return (TEST_PASS);
}

TestResult TestBSTInsert()/* GetSize */
{
	int key_1 = 1;
	int key_2 = 2;
	int key_3 = 3;
	int key_4 = 4;
	int key_5 = 5;
	int key_6 = 6;

	bst_t *tree = BSTCreate(CompareMinToMax);
	REQUIRE(tree);

	REQUIRE(0 == BSTGetSize(tree));

	BSTInsert(tree, &key_5); /* insert when empty         	|		  5		*/
	BSTInsert(tree, &key_2); /* insert to left of parent  	|	     / \	*/
	BSTInsert(tree, &key_1); /* insert to left of child   	|		2   6	*/
	BSTInsert(tree, &key_4); /* insert to right of child  	| 	   / \  	*/
	BSTInsert(tree, &key_6); /* insert to right of parent 	| 	  1   4 	*/
	BSTInsert(tree, &key_3); /*            	              	| 	     /		*/
                      		 /*            	              	| 	    3		*/
	REQUIRE(6 == BSTGetSize(tree));

	BSTDestroy(tree);
	tree = NULL;

	return (TEST_PASS);
}

TestResult TestEnd()
{
	int key_1 = 1;
	int key_2 = 2;
	int key_3 = 3;
	int key_4 = 4;
	int key_5 = 5;
	int key_6 = 6;

	bst_iterator_t iter_1;

	bst_t *tree = BSTCreate(CompareMinToMax);
	REQUIRE(tree);

	BSTInsert(tree, &key_5);
	iter_1 = BSTEnd(tree);
	iter_1 = BSTGetPrevious(iter_1);
	REQUIRE(5 == *(int *)BSTGetData(iter_1));

	BSTInsert(tree, &key_2);
	iter_1 = BSTEnd(tree);
	iter_1 = BSTGetPrevious(iter_1);
	REQUIRE(5 == *(int *)BSTGetData(iter_1));

	BSTInsert(tree, &key_1);
	iter_1 = BSTEnd(tree);
	iter_1 = BSTGetPrevious(iter_1);
	REQUIRE(5 == *(int *)BSTGetData(iter_1));

	BSTInsert(tree, &key_4);
	iter_1 = BSTEnd(tree);
	iter_1 = BSTGetPrevious(iter_1);
	REQUIRE(5 == *(int *)BSTGetData(iter_1));

	BSTInsert(tree, &key_6);
	iter_1 = BSTEnd(tree);
	iter_1 = BSTGetPrevious(iter_1);
	REQUIRE(6 == *(int *)BSTGetData(iter_1));

	BSTInsert(tree, &key_3);
	iter_1 = BSTEnd(tree);
	iter_1 = BSTGetPrevious(iter_1);
	REQUIRE(6 == *(int *)BSTGetData(iter_1));

	BSTDestroy(tree);
	tree = NULL;

	return (TEST_PASS);
}

TestResult TestFind()
{
	int key_1 = 1;
	int key_2 = 2;
	int key_3 = 3;
	int key_4 = 4;
	int key_5 = 5;
	int key_6 = 6;

	bst_iterator_t iter_1;

	bst_t *tree = BSTCreate(CompareMinToMax);
	REQUIRE(tree);

	BSTInsert(tree, &key_5);
	BSTInsert(tree, &key_2);
	BSTInsert(tree, &key_1);
	BSTInsert(tree, &key_4);
	BSTInsert(tree, &key_6);
	BSTInsert(tree, &key_3);

	iter_1 = BSTFind(tree, &key_1);
	REQUIRE(1 == *(int *)BSTGetData(iter_1));

	iter_1 = BSTFind(tree, &key_2);
	REQUIRE(2 == *(int *)BSTGetData(iter_1));

	iter_1 = BSTFind(tree, &key_3);
	REQUIRE(3 == *(int *)BSTGetData(iter_1));

	iter_1 = BSTFind(tree, &key_4);
	REQUIRE(4 == *(int *)BSTGetData(iter_1));

	iter_1 = BSTFind(tree, &key_5);
	REQUIRE(5 == *(int *)BSTGetData(iter_1));

	iter_1 = BSTFind(tree, &key_6);
	REQUIRE(6 == *(int *)BSTGetData(iter_1));

	BSTDestroy(tree);
	tree = NULL;

	return (TEST_PASS);
}


TestResult TestGetPrevious()
{
	int key_1 = 1;
	int key_2 = 2;
	int key_3 = 3;
	int key_4 = 4;
	int key_5 = 5;
	int key_6 = 6;

	bst_iterator_t iter_1;

	bst_t *tree = BSTCreate(CompareMinToMax);
	REQUIRE(tree);

	BSTInsert(tree, &key_5);
	BSTInsert(tree, &key_2);
	BSTInsert(tree, &key_1);
	BSTInsert(tree, &key_4);
	BSTInsert(tree, &key_6);
	BSTInsert(tree, &key_3);

	iter_1 = BSTEnd(tree);
	iter_1 = BSTGetPrevious(iter_1);
	REQUIRE(6 == *(int *)BSTGetData(iter_1));

	iter_1 = BSTGetPrevious(iter_1);
	REQUIRE(5 == *(int *)BSTGetData(iter_1));

	iter_1 = BSTGetPrevious(iter_1);
	REQUIRE(4 == *(int *)BSTGetData(iter_1));

	iter_1 = BSTGetPrevious(iter_1);
	REQUIRE(3 == *(int *)BSTGetData(iter_1));

	iter_1 = BSTGetPrevious(iter_1);
	REQUIRE(2 == *(int *)BSTGetData(iter_1));

	iter_1 = BSTGetPrevious(iter_1);
	REQUIRE(1 == *(int *)BSTGetData(iter_1));

	BSTDestroy(tree);
	tree = NULL;

	return (TEST_PASS);
}

TestResult TestForEach()
{
	int key_1 = 1;
	int key_2 = 2;
	int key_3 = 3;
	int key_4 = 4;
	int key_5 = 5;
	int key_6 = 6;

	int param = 2;

	bst_iterator_t iter_1;

	bst_t *tree = BSTCreate(CompareMinToMax);
	REQUIRE(tree);

	BSTInsert(tree, &key_5);
	BSTInsert(tree, &key_2);
	BSTInsert(tree, &key_1);
	BSTInsert(tree, &key_4);
	BSTInsert(tree, &key_6);
	BSTInsert(tree, &key_3);

	BSTForEach(tree, BSTPlusTwo, &param);

	iter_1 = BSTBegin(tree);
	REQUIRE(1 + param == *(int *)BSTGetData(iter_1));

	iter_1 = BSTGetNext(iter_1);
	REQUIRE(2 + param == *(int *)BSTGetData(iter_1));

	iter_1 = BSTGetNext(iter_1);
	REQUIRE(3 + param == *(int *)BSTGetData(iter_1));

	iter_1 = BSTGetNext(iter_1);
	REQUIRE(4 + param == *(int *)BSTGetData(iter_1));

	iter_1 = BSTGetNext(iter_1);
	REQUIRE(5 + param == *(int *)BSTGetData(iter_1));

	iter_1 = BSTGetNext(iter_1);
	REQUIRE(6 + param == *(int *)BSTGetData(iter_1));

	BSTDestroy(tree);
	tree = NULL;

	return (TEST_PASS);
}

TestResult TestIsSameIterator()
{
	int key_1 = 1;
	int key_2 = 2;

	bst_iterator_t iter_1;
	bst_iterator_t iter_2;
	bst_iterator_t iter_3;

	bst_t *tree = BSTCreate(CompareMinToMax);
	REQUIRE(tree);

	BSTInsert(tree, &key_1);
	BSTInsert(tree, &key_2);

	iter_1 = BSTBegin(tree);
	iter_2 = iter_1;
	iter_3 = BSTEnd(tree);

	REQUIRE(TRUE == BSTIsSameIterator(iter_1, iter_2));
	REQUIRE(FALSE == BSTIsSameIterator(iter_1, iter_3));

	BSTDestroy(tree);
	tree = NULL;

	return (TEST_PASS);
}


TestResult TestRemove()
{
	int key_1 = 1;
	int key_2 = 2;
	int key_3 = 3;
	int key_4 = 4;
	int key_5 = 5;
	int key_6 = 6;

	bst_iterator_t iter_1;

	bst_t *tree = BSTCreate(CompareMinToMax);
	REQUIRE(tree);

	BSTInsert(tree, &key_5);
	BSTInsert(tree, &key_2);
	BSTInsert(tree, &key_1);
	BSTInsert(tree, &key_4);
	BSTInsert(tree, &key_6);
	BSTInsert(tree, &key_3);

	iter_1 = BSTBegin(tree);
	REQUIRE(1 == *(int *)BSTGetData(iter_1));
	iter_1 = BSTGetNext(iter_1);
	REQUIRE(2 == *(int *)BSTGetData(iter_1));
	iter_1 = BSTGetNext(iter_1);
	REQUIRE(3 == *(int *)BSTGetData(iter_1));
	iter_1 = BSTGetNext(iter_1);
	REQUIRE(4 == *(int *)BSTGetData(iter_1));
	iter_1 = BSTGetNext(iter_1);
	REQUIRE(5 == *(int *)BSTGetData(iter_1));
	iter_1 = BSTGetNext(iter_1);
	REQUIRE(6 == *(int *)BSTGetData(iter_1));
	iter_1 = BSTGetNext(iter_1);

	iter_1 = BSTFind(tree, &key_2);
	BSTRemove(iter_1);
	REQUIRE("right child has left child" && 5 == BSTGetSize(tree));
	iter_1 = BSTBegin(tree);
	REQUIRE(1 == *(int *)BSTGetData(iter_1));
	iter_1 = BSTGetNext(iter_1);
	REQUIRE(3 == *(int *)BSTGetData(iter_1));
	iter_1 = BSTGetNext(iter_1);
	REQUIRE(4 == *(int *)BSTGetData(iter_1));
	iter_1 = BSTGetNext(iter_1);
	REQUIRE(5 == *(int *)BSTGetData(iter_1));
	iter_1 = BSTGetNext(iter_1);
	REQUIRE(6 == *(int *)BSTGetData(iter_1));
	iter_1 = BSTGetNext(iter_1);


	iter_1 = BSTFind(tree, &key_4);
	BSTRemove(iter_1);
	REQUIRE("only has left child" && 4 == BSTGetSize(tree));

	iter_1 = BSTFind(tree, &key_6);
	BSTRemove(iter_1);
	REQUIRE("no children" && 3 == BSTGetSize(tree));

	iter_1 = BSTFind(tree, &key_1);
	BSTRemove(iter_1);
	iter_1 = BSTFind(tree, &key_3);
	BSTRemove(iter_1);
	iter_1 = BSTFind(tree, &key_5);
	BSTRemove(iter_1);
	REQUIRE("last node" && 0 == BSTGetSize(tree));

	BSTDestroy(tree);
	tree = NULL;

	return (TEST_PASS);
}
