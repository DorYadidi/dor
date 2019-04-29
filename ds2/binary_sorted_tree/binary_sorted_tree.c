/*******************************************************************************
* NAME: binary sorted tree                                                     *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  11.12.18                                                      *
*******************************************************************************/

#include <stdio.h> /*sizeof*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/
#include "binary_sorted_tree.h"
#include "function_pointers.h"

#define STUB_TAIL 1
#define CAST_ITER(x) ((bst_node_t *)x.info)

bst_iterator_t BST_ITERATOR_NOT_FOUND = { NULL };

typedef enum {LEFT, RIGHT, STUB} direction_e;

typedef struct bst_node_s bst_node_t;

struct bst_node_s
{
	void *data;
	bst_node_t *parent;
	bst_node_t *children[2];
	direction_e direction;
};

struct bst_s
{
	bst_node_t *stub_tail;
	compare_function_t compare;
};


bst_node_t *BSTCreateNode(void *data, bst_node_t *parent, bst_node_t *left,
                         bst_node_t *right, direction_e direction)
{
	bst_node_t *new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (NULL == new_node)
	{
		return (NULL);
	}

	new_node->data = data;
	new_node->parent = parent;
	new_node->children[LEFT] = left;
	new_node->children[RIGHT] = right;
	new_node->direction = direction;

	return (new_node);
}

bst_t *BSTCreate(compare_function_t compare)
{
	bst_t *bst = (bst_t *)malloc(sizeof(bst_t));

	if(NULL == bst)
	{
		return (NULL);
	}

	bst->stub_tail = BSTCreateNode(NULL, NULL, NULL, NULL, STUB);

	if(NULL == bst->stub_tail)
	{
		free(bst->stub_tail);
		return (NULL);
	}

	bst->compare = compare;

	return (bst);
}

void BSTDestroy(bst_t *bst)
{
	assert(bst);

	while (!BSTIsEmpty(bst))
	{
		BSTRemove(BSTBegin(bst));
	}

	free(bst->stub_tail);
	free(bst);
}

size_t BSTGetSize(bst_t *bst)
{
	bst_iterator_t current;
	size_t count = 0;

	assert(bst != NULL);

	current = BSTBegin(bst);

	while (current.info != NULL)
	{
		++count;
		current = BSTGetNext(current);
	}

	return (count - STUB_TAIL);
}

bool BSTIsEmpty(bst_t *bst)
{
	assert(bst != NULL);

	if (NULL == bst->stub_tail->children[LEFT])
	{
		return (TRUE);
	}

	return (FALSE);
}

bst_iterator_t BSTBegin(bst_t *bst)
{
	bst_iterator_t begining;

	assert(bst != NULL);

	begining.info = bst->stub_tail;

	while (CAST_ITER(begining)->children[LEFT] != NULL)
	{
		begining.info = CAST_ITER(begining)->children[LEFT];
	}

	return (begining);
}

bst_iterator_t BSTEnd(bst_t *bst)
{
	bst_iterator_t ending;

	assert(bst != NULL);

	ending.info = bst->stub_tail;

	return (ending);
}

bst_iterator_t BSTInsert(bst_t *bst, void *data)
{
	bst_iterator_t serch_place;
	bst_iterator_t serch_place_prev;
	direction_e flag = LEFT;
	bst_node_t *new_node = NULL;
	assert(bst != NULL);

	serch_place_prev.info = bst->stub_tail;
	serch_place.info = bst->stub_tail->children[LEFT];

	while (CAST_ITER(serch_place) != NULL)
	{
		assert(bst->compare(CAST_ITER(serch_place)->data, data) != 0);

		serch_place_prev.info = serch_place.info;

		if (bst->compare(CAST_ITER(serch_place)->data, data) < 0)
		{
			flag = RIGHT;
			serch_place.info = CAST_ITER(serch_place)->children[RIGHT];
		}
		else
		{
			flag = LEFT;
			serch_place.info = CAST_ITER(serch_place)->children[LEFT];
		}
	}

	new_node = BSTCreateNode(data, CAST_ITER(serch_place_prev), NULL, NULL, flag);

	if (RIGHT == flag)
	{
		CAST_ITER(serch_place_prev)->children[RIGHT] = new_node;
	}
	else
	{
		CAST_ITER(serch_place_prev)->children[LEFT] = new_node;
	}

	serch_place.info = new_node;

	return (serch_place);
}

void BSTRemove(bst_iterator_t iter)
{
/*	case 1: no children*/
	if (NULL == CAST_ITER(iter)->children[LEFT] &&
        NULL == CAST_ITER(iter)->children[RIGHT])
	{
		CAST_ITER(iter)->parent->children[CAST_ITER(iter)->direction] = NULL;
		free(iter.info);
		return;
	}
/*	 case 2: one child (right)*/
	else if(NULL == CAST_ITER(iter)->children[LEFT])
	{
		CAST_ITER(iter)->parent->children[CAST_ITER(iter)->direction] =
		CAST_ITER(iter)->children[RIGHT];
		CAST_ITER(iter)->children[RIGHT]->parent = CAST_ITER(iter)->parent;
		CAST_ITER(iter)->children[RIGHT]->direction = CAST_ITER(iter)->direction;
		free(iter.info);
		return;
	}
/*	 case 3: one child (left) */
	else if (NULL == CAST_ITER(iter)->children[RIGHT])
	{
		CAST_ITER(iter)->parent->children[CAST_ITER(iter)->direction] =
		CAST_ITER(iter)->children[LEFT];
		CAST_ITER(iter)->children[LEFT]->parent = CAST_ITER(iter)->parent;
		CAST_ITER(iter)->children[LEFT]->direction = CAST_ITER(iter)->direction;
		free(iter.info);
		return;
	}
/*	 case 4: two child */
	else
	{
		bst_iterator_t serch_place;
		serch_place.info = CAST_ITER(iter)->children[RIGHT];

		while (CAST_ITER(serch_place)->children[LEFT] != NULL)
		{
			serch_place.info = CAST_ITER(serch_place)->children[LEFT];
		}

		CAST_ITER(iter)->children[LEFT]->parent = serch_place.info;
		CAST_ITER(serch_place)->children[LEFT] = CAST_ITER(iter)->children[LEFT];
		CAST_ITER(iter)->children[RIGHT]->parent = CAST_ITER(iter)->parent;
		CAST_ITER(iter)->parent->children[CAST_ITER(iter)->direction] =
		CAST_ITER(iter)->children[RIGHT];
		CAST_ITER(iter)->children[RIGHT]->direction = CAST_ITER(iter)->direction;
		free(iter.info);
	}
}

bst_iterator_t BSTGetNext(bst_iterator_t iter)
{
	assert (iter.info != NULL);

	if (CAST_ITER(iter)->children[RIGHT] != NULL)
	{
		iter.info = CAST_ITER(iter)->children[RIGHT];

		while (CAST_ITER(iter)->children[LEFT] != NULL)
		{
			iter.info = CAST_ITER(iter)->children[LEFT];
		}

		return (iter);
	}

	if (NULL == CAST_ITER(iter)->parent)
	{
		iter.info = NULL;
		return (iter);
	}

	if (CAST_ITER(iter) == CAST_ITER(iter)->parent->children[LEFT])
	{
		iter.info = CAST_ITER(iter)->parent;
		return (iter);
	}
	else
	{
		while (iter.info == CAST_ITER(iter)->parent->children[RIGHT])
		{
			iter.info = CAST_ITER(iter)->parent;
		}

		iter.info = CAST_ITER(iter)->parent;
		return (iter);
	}
}

bst_iterator_t BSTGetPrevious(bst_iterator_t iter)
{
	assert (iter.info != NULL);

	if(CAST_ITER(iter)->children[LEFT] != NULL)
	{
		iter.info = CAST_ITER(iter)->children[LEFT];

		while (CAST_ITER(iter)->children[RIGHT] != NULL)
		{
			iter.info = CAST_ITER(iter)->children[RIGHT];
		}

		return (iter);
	}

	if (NULL == CAST_ITER(iter)->parent)
	{
		iter.info = NULL;
		return (iter);
	}

	if (CAST_ITER(iter) == CAST_ITER(iter)->parent->children[RIGHT])
	{
		iter.info = CAST_ITER(iter)->parent;
		return (iter);
	}
	else
	{
		while (CAST_ITER(iter) == CAST_ITER(iter)->parent->children[LEFT])
		{
			iter.info = CAST_ITER(iter)->parent;
		}

		iter.info = CAST_ITER(iter)->parent;
		return (iter);
	}

	iter.info = NULL;
	return (iter);
}

void *BSTGetData(bst_iterator_t iter)
{
	assert(iter.info != NULL);

	return (CAST_ITER(iter)->data);
}

bst_iterator_t BSTFind(bst_t *bst, void *data)
{
	bst_iterator_t current;
	bst_iterator_t result = BST_ITERATOR_NOT_FOUND;
	assert(bst != NULL);

	current.info = bst->stub_tail->children[LEFT];

	while (current.info != NULL)
	{
		int check_cmp = bst->compare(CAST_ITER(current)->data, data);

		if (check_cmp < 0)
		{
			current.info = CAST_ITER(current)->children[RIGHT];
		}
		else if (check_cmp > 0)
		{
			current.info = CAST_ITER(current)->children[LEFT];
		}
		else
		{
			result.info = current.info;
			return (result);
		}
	}

	return (result);
}

status BSTForEach
	(bst_t *bst, action_function_t action, void *param)
{
	bst_iterator_t current;
	assert(bst != NULL);

	current = BSTBegin(bst);

	while (current.info != bst->stub_tail)
	{
		if(action(CAST_ITER(current)->data, param) == ACTION_FAIL)
		{
			return (ACTION_FAIL);
		}

		current = BSTGetNext(current);
	}

	return (SUCCESS);
}

bool BSTIsSameIterator(
	const bst_iterator_t iter1, const bst_iterator_t iter2)
{
		if (iter1.info == iter2.info)
	{
		return (TRUE);
	}

	return (FALSE);
}
