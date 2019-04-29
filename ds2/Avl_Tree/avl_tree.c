/*******************************************************************************
* NAME: Avl tree                                                               *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  23.12.18                                                      *
*******************************************************************************/

#include <stdio.h> /*sizeof*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/
#include "avl_tree.h"
#include "function_pointers.h"
#include "d_linked_list.h"

#define MAX(left, right) (((left) > (right)) ? (left) : (right))

#define MIN_HEIGHT 1
#define LEFT_UNBALANCED -2
#define RIGHT_UNBALANCED 2
#define LEFT_HEAVY -1
#define RIGHT_HEAVY 1


typedef struct avl_node_s avl_node_t;
struct avl_node_s
{
	void *data;
	avl_node_t *left;
	avl_node_t *right;
	size_t height;
};

struct avl_tree_s
{
	avl_node_t *root;
	compare_function_t compare;
};

static avl_node_t *AvlNodeCreate();
static void RecursiveDestroy(avl_node_t *root);
static size_t RecursiveCount(const avl_node_t *root);
static avl_node_t *RecursiveSearch(avl_node_t *root,
                          compare_function_t compare, const void *data_to_match);
static size_t AvlNodeHeight(const avl_node_t *root);
static status RecursiveForEach(avl_node_t *root, action_function_t action,
                               void *param);
static void UpdateHeight(avl_node_t *node);
static avl_node_t *RecursiveInsert(avl_node_t *node, compare_function_t compare,
                                   avl_node_t *new_node);
static avl_node_t *Balance(avl_node_t *node);
static avl_node_t *RecursiveRemove(avl_node_t *node, compare_function_t compare,
                            const void *data);
static avl_node_t *RotateLeft(avl_node_t *node);
static avl_node_t *RotateRight(avl_node_t *node);
static size_t GetBalanceFactor(avl_node_t *node);
static void RecursiveMultiFind(
	avl_node_t *node, match_function_t match, void *param, d_linked_list_t *dll);
static void RecursiveMultiRemove(avl_tree_t *avl, avl_node_t *node,
		                             match_function_t match, void *param);

/*****************************************************************************/

static avl_node_t *AvlNodeCreate(void *data)
{
	avl_node_t *new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
	if(NULL == new_node)
	{
		return (NULL);
	}

	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->height = MIN_HEIGHT;

	return (new_node);
}

avl_tree_t *AvlTreeCreate(compare_function_t compare)
{
	avl_tree_t *avl = (avl_tree_t *)malloc(sizeof(avl_tree_t));
	if(NULL == avl)
	{
		return (NULL);
	}

	avl->compare = compare;
	avl->root = NULL;

	return (avl);
}


/*****************************************************************************/
static void RecursiveDestroy(avl_node_t *root)
{
	if (NULL == root)
	{
		return;
	}

	RecursiveDestroy(root->left);
	RecursiveDestroy(root->right);
	free(root);
}

void AvlTreeDestroy(avl_tree_t *avl)
{
	assert(avl != NULL);
	if (NULL != avl->root)
	{
		RecursiveDestroy(avl->root);
	}
	free(avl);
}

/*****************************************************************************/
static size_t RecursiveCount(const avl_node_t *root)
{
	if (NULL == root)
	{
		return 0;
	}

	return (1 + RecursiveCount(root->left) + RecursiveCount(root->right));
}

size_t AvlTreeCount(const avl_tree_t *avl)
{
	assert(avl != NULL);
	return (RecursiveCount(avl->root));
}

/*****************************************************************************/
bool AvlTreeIsEmpty(const avl_tree_t *avl)
{
	if (NULL == avl->root)
	{
		return (TRUE);
	}

	return (FALSE);
}

/*****************************************************************************/
static size_t AvlNodeHeight(const avl_node_t *root)
{
	return (root->height);
}

size_t AvlTreeHeight(const avl_tree_t *avl)
{
	assert(avl != NULL && AvlTreeIsEmpty(avl) == FALSE);
	return (AvlNodeHeight(avl->root));
}
/******************************************************************************/

static void UpdateHeight(avl_node_t *node)
{
	if (NULL == node)
	{
		return;
	}
	if (NULL == node->left && NULL == node->right)
	{
		node->height = MIN_HEIGHT;
		return;
	}
	if (NULL == node->left)
	{
		node->height = MIN_HEIGHT + node->right->height;
		return;
	}
	if (NULL == node->right)
	{
		node->height = MIN_HEIGHT + node->left->height;
		return;
	}

	node->height = MIN_HEIGHT + MAX(node->left->height, node->right->height);
}

static avl_node_t *RecursiveInsert(avl_node_t *node, compare_function_t compare,
                            avl_node_t *new_node)
{
	int compare_result = 0;

	if (NULL == node)
	{
		return (new_node);
	}

	compare_result = compare(node->data, new_node->data);
	assert(compare_result != 0);

	if(compare_result > 0)
	{
		node->left = RecursiveInsert(node->left, compare, new_node);
	}
	else
	{
		node->right = RecursiveInsert(node->right, compare, new_node);
	}

	return (Balance(node));
}

status AvlTreeInsert(avl_tree_t *avl, void *data)
{
	avl_node_t *new_node = AvlNodeCreate(data);
	if (NULL == new_node)
	{
		return (MEMORY_ALLOCATION_FAIL);
	}

	avl->root = RecursiveInsert(avl->root, avl->compare, new_node);

	return (SUCCESS);
}

/******************************************************************************/

static avl_node_t *RecursiveRemove(avl_node_t *node, compare_function_t compare,
                                   const void *data)
{
	int compare_result = 0;
	avl_node_t *change_place = NULL;

	if (NULL == node)
	{
		return (node);
	}

	compare_result = compare(node->data, data);

	if (compare_result > 0)
	{
		node->left = RecursiveRemove(node->left, compare, data);
	}
	else if (compare_result < 0)
	{
		node->right = RecursiveRemove(node->right, compare, data);
	}
	else /*after find the node to remove*/
	{
		if (NULL == node->left) /*case 1: no children or no left children*/
		{
			change_place = node->right;
			free(node);
			return (change_place);
		}

		if (NULL == node->right) /*case 2: no right children*/
		{
			change_place = node->left;
			free(node);
			return (change_place);
		}

		/*case 3: have 2 children*/
		change_place = node->right;
		change_place = RecursiveInsert(change_place, compare, node->left);
		free(node);
		return (change_place);
	}

	return (Balance(node));
}

void AvlTreeRemove(avl_tree_t *avl, const void *data)
{
	assert(avl != NULL);
	avl->root = RecursiveRemove(avl->root, avl->compare, data);
}

/******************************************************************************/
static avl_node_t *RecursiveSearch(avl_node_t *root,
                          compare_function_t compare, const void *data_to_match)
{
	if (NULL == root || 0 == compare(root->data, data_to_match))
	{
		return (root);
	}

	if(compare(root->data, data_to_match) > 0)
	{
		return (RecursiveSearch(root->left, compare, data_to_match));
	}
	else
	{
		return (RecursiveSearch(root->right, compare, data_to_match));
	}
}

void *AvlTreeFind(avl_tree_t *avl, const void *data_to_match)
{
	avl_node_t *find_node = NULL;
	assert(NULL != avl);

	find_node = RecursiveSearch(avl->root, avl->compare, data_to_match);
	if (NULL == find_node)
	{
		return (NULL);
	}

	return (find_node->data);
}

/******************************************************************************/
static status RecursiveForEach(avl_node_t *node, action_function_t action,
                               void *param)
{
	status stat = SUCCESS;

	if (NULL == node)
	{
		return (SUCCESS);
	}

	stat = RecursiveForEach(node->left, action, param);
	if (SUCCESS != stat)
	{
		return (FAIL);
	}

	if(action(node->data, param) != SUCCESS)
	{
		return (FAIL);
	}

	stat = RecursiveForEach(node->right, action, param);
	if (SUCCESS != stat)
	{
		return (FAIL);
	}

	return (SUCCESS);
}

status AvlTreeForEach(avl_tree_t *avl, action_function_t action, void *param)
{
	assert(NULL != avl);

	return (RecursiveForEach(avl->root, action, param));
}
/******************************************************************************/
static avl_node_t *RotateLeft(avl_node_t *node)
{
	avl_node_t *new_root = node->right;

	node->right = new_root->left;
	new_root->left = node;

	UpdateHeight(node);
	UpdateHeight(new_root);

	return (new_root);
}

static avl_node_t *RotateRight(avl_node_t *node)
{
	avl_node_t *new_root = node->left;

	node->left = new_root->right;
	new_root->right = node;

	UpdateHeight(node);
	UpdateHeight(new_root);

 	return (new_root);
}

static size_t GetBalanceFactor(avl_node_t *node)
{
	size_t right_height = 0;
	size_t left_height = 0;

	if (node == NULL)
	{
		return (0);
	}

	if (node->right)
	{
		right_height = AvlNodeHeight(node->right);
	}

	if (node->left)
	{
		left_height = AvlNodeHeight(node->left);
	}

	return (right_height - left_height);
}

static avl_node_t *Balance(avl_node_t *node)
{
	int balance = GetBalanceFactor(node);

	if (LEFT_UNBALANCED == balance)
	{
		balance = GetBalanceFactor(node->left);
		if (RIGHT_HEAVY == balance)
		{
			node->left = (RotateLeft(node->left));
		}

		return (RotateRight(node));
	}

	if (RIGHT_UNBALANCED == balance)
	{
		balance = GetBalanceFactor(node->right);
		if (LEFT_HEAVY == balance)
		{
			node->right = RotateRight(node->right);
		}

		return (RotateLeft(node));
	}

	UpdateHeight(node);
	return (node);
}

/*******************************************************************************/
static void RecursiveMultiFind(avl_node_t *node, match_function_t match,
	                           void *param, d_linked_list_t *dll)
{
	if (NULL == node)
	{
		return;
	}

	RecursiveMultiFind(node->left, match, param, dll);

	if (TRUE == match(node->data, param))
	{
		DLinkedListPushBack(dll, node->data);
	}

	RecursiveMultiFind(node->right, match, param, dll);
}

d_linked_list_t *AvlTreeMultiFind(avl_tree_t *avl, match_function_t match,
	                              void *param)
{
	d_linked_list_t *dll = NULL;
	assert(avl != NULL);

	dll = DLinkedListCreate();
	if (NULL == dll)
	{
		return (NULL);
	}

	RecursiveMultiFind(avl->root, match, param, dll);

	return (dll);
}

/******************************************************************************/

static void RecursiveMultiRemove(avl_tree_t *avl, avl_node_t *node,
	                             match_function_t match, void *param)
{
	if (NULL == node)
	{
		return;
	}

	RecursiveMultiRemove(avl, node->left, match, param);
	RecursiveMultiRemove(avl, node->right, match, param);

	if (TRUE == match(node->data, param))
	{
		AvlTreeRemove(avl, node->data);
	}
}

void AvlTreeMultiRemove(avl_tree_t *avl, match_function_t match, void *param)
{
	assert(avl != NULL);

	RecursiveMultiRemove(avl, avl->root, match, param);
}
