#include <stdio.h>
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/
#include "d_linked_list.h"
#include "function_pointers.h"

#define DUMMYS 2

typedef struct dll_node_s dll_node_t;

struct dll_node_s
{
	void *data;
	dll_node_t *next;
	dll_node_t *prev;

};

struct d_linked_list_s
{
	dll_node_t *dummy_head;
	dll_node_t *dummy_tail;

};

dll_node_t *DLLNodeCreate();
void DLLNodeDestroy(dll_node_t *dummy_head);

dll_node_t *DLLNodeCreate()
{
	dll_node_t *new_node = (dll_node_t *)malloc(sizeof(dll_node_t));
	if (NULL == new_node)
	{
		return (NULL);
	}

	new_node->data = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;

	return (new_node);
}

d_linked_list_t *DLinkedListCreate()
{
	d_linked_list_t *control = (d_linked_list_t *)malloc(sizeof(d_linked_list_t));
	dll_node_t *dummy_head = DLLNodeCreate();
	dll_node_t *dummy_tail = DLLNodeCreate();

	if (NULL == dummy_head)
	{
		free(dummy_tail);
		free(control);
		return (NULL);
	}

	if (NULL == control)
	{
		free(dummy_tail);
		free(dummy_head);
		return (NULL);
	}

	if (NULL == dummy_tail)
	{
		free(dummy_head);
		free(control);
		return (NULL);
	}

	control->dummy_head = dummy_head;
	control->dummy_tail = dummy_tail;
	control->dummy_head->next = control->dummy_tail;
	control->dummy_tail->prev = control->dummy_head;

	return (control);
}

void DLLNodeDestroy(dll_node_t *dummy_head)
{
	dll_node_t *current = dummy_head;
	dll_node_t *next = NULL;

	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void DLinkedListDestroy(d_linked_list_t *dll)
{
	assert(dll != NULL);
	DLLNodeDestroy(dll->dummy_head);
	free(dll);
}

size_t DLinkedListGetSize(d_linked_list_t *dll)
{
	size_t count = 0;
	dll_node_t *tmp = dll->dummy_head;
	assert(dll != NULL);

	for( ; tmp != NULL; ++count)
	{
		tmp = tmp->next;
	}

    return (count - DUMMYS);
}

bool DLinkedListIsEmpty(d_linked_list_t *dll)
{
	assert(dll != NULL);
	if(dll->dummy_head->next == dll->dummy_tail)
	{
		return (TRUE);
	}

	return (FALSE);
}

dll_iterator_t DLinkedListBegin(d_linked_list_t *dll)
{
	dll_iterator_t result;
	assert(dll != NULL);
	result.info = dll->dummy_head->next;

	return (result);
}

dll_iterator_t DLinkedListEnd(d_linked_list_t *dll)
{
	dll_iterator_t result;
	assert(dll != NULL);
	result.info = dll->dummy_tail;

	return (result);
}

dll_iterator_t DLinkedListInsert(dll_iterator_t iter, void *data)
{
	dll_node_t *new_node = DLLNodeCreate();
	dll_iterator_t result;

	assert(iter.info != NULL);

	if (NULL == new_node)
	{
		result.info = NULL;
		return (result);
	}

	new_node->data = data;
	new_node->next = iter.info;
	new_node->prev = ((dll_node_t *)iter.info)->prev;
	((dll_node_t *)iter.info)->prev = new_node;
	new_node->prev->next = new_node;

	result.info = new_node;

	return (result);
}


dll_iterator_t DLinkedListInsertAfter(dll_iterator_t iter, void *data)
{
	dll_node_t *new_node = DLLNodeCreate();
	dll_iterator_t result;

	assert(iter.info != NULL);

	if (NULL == new_node)
	{
		result.info = NULL;
		return (result);
	}

	new_node->data = data;
	new_node->prev = ((dll_node_t *)iter.info);
	new_node->next = ((dll_node_t *)iter.info)->next;
	((dll_node_t *)iter.info)->next = new_node;
	new_node->next->prev = new_node;

	result.info = new_node;

	return (result);
}

void DLinkedListErase(dll_iterator_t iter)
{
	assert(iter.info != NULL);
	((dll_node_t *)iter.info)->next->prev = ((dll_node_t *)iter.info)->prev;
	((dll_node_t *)iter.info)->prev->next = ((dll_node_t *)iter.info)->next;
	free(iter.info);
}

dll_iterator_t DLinkedListPushFront(d_linked_list_t *dll, void *data)
{
	dll_node_t *new_node = DLLNodeCreate();
	dll_iterator_t result;

	assert(dll != NULL);

	if (NULL == new_node)
	{
		result.info = NULL;
		return (result);
	}

	new_node->data = data;
	new_node->next = dll->dummy_head->next;
	new_node->prev = dll->dummy_head;
	dll->dummy_head->next = new_node;
	new_node->next->prev = new_node;

	result.info = new_node;

	return (result);
}

dll_iterator_t DLinkedListPushBack(d_linked_list_t *dll, void *data)
{
	dll_node_t *new_node = DLLNodeCreate();
	dll_iterator_t result;

	assert(dll != NULL);

	if (NULL == new_node)
	{
		result.info = NULL;
		return (result);
	}

	new_node->data = data;
	new_node->next = dll->dummy_tail;
	new_node->prev = dll->dummy_tail->prev;
	dll->dummy_tail->prev = new_node;
	new_node->prev->next = new_node;

	result.info = new_node;

	return (result);
}

void DLinkedListPopFront(d_linked_list_t *dll)
{
	dll_node_t *removed = dll->dummy_head->next;
	dll->dummy_head->next = dll->dummy_head->next->next;
	dll->dummy_head->next->prev = dll->dummy_head;
	free(removed);
}

void DLinkedListPopBack(d_linked_list_t *dll)
{
	dll_node_t *removed = dll->dummy_tail->prev;
	assert(dll != NULL);
	dll->dummy_tail->prev = dll->dummy_tail->prev->prev;
	dll->dummy_tail->prev->next = dll->dummy_tail;
	free(removed);
}

dll_iterator_t DLinkedListFind
	(d_linked_list_t *dll, match_function_t match, void *param)
{
	dll_node_t *tmp = dll->dummy_head->next;
	dll_iterator_t result;

	assert(dll != NULL && dll->dummy_head != NULL);

	while(tmp != dll->dummy_tail)
	{
		if(match(tmp->data, param) == TRUE)
		{
			result.info = tmp;
			return (result);
		}

		tmp = tmp->next;
	}

		result.info = NULL;

		return (result);
}

status DLinkedListForEach
	(d_linked_list_t *dll, action_function_t action, void *param)
{
	dll_node_t *tmp = dll->dummy_head->next;
	assert(dll != NULL && dll->dummy_head != NULL);

	while(tmp != dll->dummy_tail)
	{
		if(action(tmp->data, param) == ACTION_FAIL)
		{
			return (ACTION_FAIL);
		}

		tmp = tmp->next;
	}

	return (SUCCESS);
}

void DLinkedListSplice(
	dll_iterator_t where, dll_iterator_t from, dll_iterator_t to)
{
	dll_iterator_t tmp1;

	assert(where.info != NULL && to.info != NULL && from.info != NULL);

	tmp1.info = ((dll_node_t *)from.info)->prev;

	((dll_node_t *)where.info)->prev->next = ((dll_node_t *)from.info);
	((dll_node_t *)from.info)->prev = ((dll_node_t *)where.info)->prev;

	((dll_node_t *)where.info)->prev = ((dll_node_t *)to.info)->prev;
	((dll_node_t *)to.info)->prev->next = ((dll_node_t *)where.info);

	((dll_node_t *)tmp1.info)->next = ((dll_node_t *)to.info);
	((dll_node_t *)to.info)->prev = ((dll_node_t *)tmp1.info);
}

dll_iterator_t DLinkedListGetNext(dll_iterator_t iter)
{
	dll_iterator_t result;
	assert(iter.info != NULL);
	result.info = ((dll_node_t *)iter.info)->next;

	return (result);
}

dll_iterator_t DLinkedListGetPrevious(dll_iterator_t iter)
{
	dll_iterator_t result;
	assert(iter.info != NULL);
	result.info = ((dll_node_t *)iter.info)->prev;

	return (result);
}

void *DLinkedListGetData(dll_iterator_t iter)
{
	assert(iter.info != NULL);
	return (((dll_node_t *)iter.info)->data);
}

bool DLinkedListIsSameIterator(dll_iterator_t iter1, dll_iterator_t iter2)
{
	if (iter1.info == iter2.info)
	{
		return (TRUE);
	}

	return (FALSE);
}
