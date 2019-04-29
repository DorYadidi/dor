
#include <stdlib.h> /* rand */
#include <time.h>
#include "stack.h"
#include "test.h"
#include "avl_tree.h"
#include "d_linked_list.h"

#define SIZE_OF_DATA 5000

static int AvlTreeKeyCompare(const void *new_key, const void *node_key)
{
	return (*(int *)new_key - *(int *)node_key);
}

bool IsEvenNum(void *data, void *param)
{
	(void)(param);

	if(*(int *)data % 2 == 0)
	{
		return (TRUE);
	}

	return (FALSE);
}


static status TestPosition(void *current_data, void *param)
{
	status action_status = SUCCESS;
	stack_t *stack = (stack_t *)param;

	if(0 < StackGetSize(stack))
	{
		if (*(int*)StackPeek(stack) >= *(int*)current_data)
		{
			action_status = FAIL;
		}

		StackPop(stack);
	}

	StackPush(stack, current_data);

	return (action_status);
}

static status BreakSort(void *current_data, void *param)
{
	(void)param;

	if (0 == *(int*)current_data % 2)
	{
		*(int*)current_data /= 100;
	}
	else
	{
		*(int*)current_data *= 100;
	}

	return (SUCCESS);
}

static int *GenerateData(avl_tree_t *tree, int size_of_data)
{
	int *data = calloc(sizeof(int), size_of_data);
	int total_data = 0;
	int i = 0;
	int j = 0;

	if (NULL == data)
	{
		return (NULL);
	}

	srand(time(NULL));

	for (i = 0; i < SIZE_OF_DATA; ++i)
	{
		int data_point = rand();

		bool insert = TRUE;

		for (j = 0; j < total_data; ++j)
		{
			if (data[j] == data_point)
			{
				--i;
				--total_data;
				insert = FALSE;
			}
			else
			{
				data[i] = data_point;
			}
		}

		if (TRUE == insert)
		{
			AvlTreeInsert(tree, &data[i]);
			++total_data;
		}
	}

	return (data);
}

/******************************************************************************/

TestResult TestBasicFunctions();
TestResult TestForEach();
TestResult TestFind();
TestResult TestRemove();
TestResult TestBalance();
TestResult TestMultiFind();
/*TestResult TestMultiRemove();*/

int main()
{
	RUN_TEST(TestBasicFunctions);
	RUN_TEST(TestForEach);
	RUN_TEST(TestFind);
	RUN_TEST(TestRemove);
	RUN_TEST(TestBalance);
	RUN_TEST(TestMultiFind);
/*	RUN_TEST(TestMultiRemove);*/

	return (0);
}

TestResult TestBasicFunctions()
{
	int *data;
	avl_tree_t *tree = AvlTreeCreate(AvlTreeKeyCompare);
	REQUIRE(tree);
	REQUIRE(TRUE == AvlTreeIsEmpty(tree));
	REQUIRE(0 == AvlTreeCount(tree));

	data = GenerateData(tree, SIZE_OF_DATA);

	REQUIRE(FALSE == AvlTreeIsEmpty(tree));
	REQUIRE(SIZE_OF_DATA == AvlTreeCount(tree));

	AvlTreeDestroy(tree);
	tree = NULL;
	free(data);
	data = NULL;

	return (TEST_PASS);
}

TestResult TestForEach()
{
	int *data;
	avl_tree_t *tree = AvlTreeCreate(AvlTreeKeyCompare);
	stack_t *test_stack = StackCreate(2, sizeof(int));
	REQUIRE(tree);
	REQUIRE(test_stack);

	data = GenerateData(tree, SIZE_OF_DATA);
	REQUIRE(SUCCESS == AvlTreeForEach(tree, TestPosition, test_stack));
	printf("%lu\n", AvlTreeHeight(tree));

	AvlTreeForEach(tree, BreakSort, NULL);
	while (0 != StackGetSize(test_stack))
	{
		StackPop(test_stack);
	}
	REQUIRE(FAIL == AvlTreeForEach(tree, TestPosition, test_stack));

	free(data);
	data = NULL;
	AvlTreeDestroy(tree);
	tree = NULL;
	StackDestroy(&test_stack);
	test_stack = NULL;

	return (TEST_PASS);
}

TestResult TestFind()
{
	int key[] = {5, 2, 1, 4, 6, 3, 7};
	int i = 0;
	avl_tree_t *tree = AvlTreeCreate(AvlTreeKeyCompare);
	REQUIRE(tree);

	for (i = 0; i < 6; ++i)
	{
		AvlTreeInsert(tree, &key[i]);
	}

	for (i = 0; i < 6; ++i)
	{
		REQUIRE(key[i] == *(int*)AvlTreeFind(tree, &key[i]));
	}

	REQUIRE(NULL == AvlTreeFind(tree, &key[6]));

	AvlTreeDestroy(tree);
	tree = NULL;

	return (TEST_PASS);
}

TestResult TestRemove()
{
	size_t data[] = {6, 2, 7, 1, 5, 8, 4, 3};
	size_t data_count = 8;
	size_t key[] = {4 /*only left child*/,
				 7 /*only right child*/,
				 2 /*right child has left child */,
				 6 /*right child does not have left child */};
	size_t key_count = 4;
	size_t i = 0;
	avl_tree_t *tree = AvlTreeCreate(AvlTreeKeyCompare);
	stack_t *test_stack = StackCreate(2, sizeof(int));
	REQUIRE(tree);
	REQUIRE(test_stack);

	for (i = 0; i < data_count; ++i)
	{
		AvlTreeInsert(tree, &data[i]);
	}
	REQUIRE(data_count == AvlTreeCount(tree));
/*	REQUIRE(5 == AvlTreeHeight(tree));*/ /* no longer works now that it is balanced */

	for (i = 0; i < key_count; ++i)
	{
		AvlTreeRemove(tree, &key[i]);
		REQUIRE((data_count - (1 + i)) == AvlTreeCount(tree));
		while (0 != StackGetSize(test_stack))
		{
			StackPop(test_stack);
		}
		REQUIRE(SUCCESS == AvlTreeForEach(tree, TestPosition, test_stack));
	}
/*	REQUIRE(4 == AvlTreeHeight(tree));*/ /* no longer works now that it is balanced */

	AvlTreeDestroy(tree);
	tree = NULL;
	StackDestroy(&test_stack);
	test_stack = NULL;

	return (TEST_PASS);
}

TestResult TestBalance()
{
	size_t data[4][8] = {{6, 4, 7, 2, 5, 1, 3, 8},	/* LeftLeft   */
						{6, 2, 7, 1, 4, 3, 5, 8},	/* LeftRight  */
				   		{2, 1, 4, 3, 6, 5, 7, 8},	/* RightRight */
				   		{2, 1, 6, 4, 7, 3, 5, 8}};	/* RightLeft */
	size_t data_count = 8;
	size_t data_sets = 4;
	size_t i = 0;
	size_t j = 0;

	for (i = 0; i < data_sets; ++i)
	{
		avl_tree_t *tree = AvlTreeCreate(AvlTreeKeyCompare);
		stack_t *test_stack = StackCreate(2, sizeof(int));
		REQUIRE(tree);
		REQUIRE(test_stack);

		for (j = 0; j < (data_count - 1); ++j)
		{
			AvlTreeInsert(tree, &data[i][j]);
		}
		printf("%lu\n", AvlTreeHeight(tree));
		REQUIRE(3 == AvlTreeHeight(tree));
		REQUIRE(SUCCESS == AvlTreeForEach(tree, TestPosition, test_stack));

		AvlTreeInsert(tree, &data[i][7]);
		REQUIRE(4 == AvlTreeHeight(tree));
		while (0 != StackGetSize(test_stack))
		{
			StackPop(test_stack);
		}
		REQUIRE(SUCCESS == AvlTreeForEach(tree, TestPosition, test_stack));

		AvlTreeDestroy(tree);
		tree = NULL;
		StackDestroy(&test_stack);
		test_stack = NULL;
	}

	return (TEST_PASS);
}

TestResult TestMultiFind()
{
	int key[] = {5, 2, 1, 4, 6, 3, 7, 10, 12, 11};
	d_linked_list_t *dll = NULL;
	dll_iterator_t begin;
	int i = 0;
	avl_tree_t *tree = AvlTreeCreate(AvlTreeKeyCompare);
	REQUIRE(tree);

	for (i = 0; i < 10; ++i)
	{
		AvlTreeInsert(tree, &key[i]);
	}

	dll = AvlTreeMultiFind(tree, IsEvenNum , NULL);
	REQUIRE(5 == DLinkedListGetSize(dll));

	begin = DLinkedListBegin(dll);
	REQUIRE(TRUE == IsEvenNum(&begin.info, NULL));

	AvlTreeDestroy(tree);
	tree = NULL;
	DLinkedListDestroy(dll);
	dll = NULL;
	return (TEST_PASS);
}

/*TestResult TestMultiRemove()
{
	int key[] = {5, 2, 1, 4, 6, 3, 7, 10, 12, 11};
	int i = 0;
	avl_tree_t *tree = AvlTreeCreate(AvlTreeKeyCompare);
	REQUIRE(tree);

	for (i = 0; i < 10; ++i)
	{
		AvlTreeInsert(tree, &key[i]);
	}

	AvlTreeMultiRemove(tree, IsEvenNum, NULL);
	REQUIRE(5 == AvlTreeCount(tree));
	AvlTreeDestroy(tree);
	tree = NULL;

	return (TEST_PASS);
}
*/
