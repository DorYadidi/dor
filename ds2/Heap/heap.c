/*/*******************************************************************************
* NAME: Heap                                                                   *
*                                                                              *
* AUTHOR: Dor yadidi                                                           *
* DATE UPDATED:  27.12.18                                                      *
*******************************************************************************/

#include <stdlib.h> /* malloc realloc free*/
#include <string.h> /* memcpy */
#include <assert.h> /* assert */
#include "d_vector.h"
#include "heap.h"

#define DUMMY 1
#define INDEX_FIRST_ELEMENT 1
#define ELEMENT_SIZE sizeof(void *)

struct heap_s
{
	d_vector_t *vector;
	compare_function_t compare;
};

heap_t *HeapCreate(compare_function_t compare)
{
	size_t dummy_head = 0xDEADBEEF;
	heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
	assert(compare != NULL);

	if (NULL == heap)
	{
		return (NULL);
	}

	heap->vector = DVectorCreate(DUMMY, ELEMENT_SIZE);

	if (NULL == heap->vector)
	{
		free(heap);
		heap = NULL;
		return (NULL);
	}

	if (SUCCESS != DVectorPush(heap->vector, &dummy_head))
	{
		free(heap->vector);
		heap->vector = NULL;
		free(heap);
		heap = NULL;
		return (NULL);
	}

	heap->compare = compare;

	return (heap);
}

void HeapDestroy(heap_t *heap)
{
	assert(heap != NULL);
	DVectorDestroy(&(heap->vector));
	heap->vector = NULL;
	free(heap);
	heap = NULL;
}

size_t HeapCount(const heap_t *heap)
{
	assert(heap != NULL);

	return (DVectorGetSize(heap->vector) - DUMMY);
}

bool HeapIsEmpty(const heap_t *heap)
{
	assert(heap != NULL);

	return (DUMMY > HeapCount(heap));
}

/**************************************************************************/

static void Swap(void **data1, void **data2)
{
	*data1 = (size_t *)((size_t)*data1 ^ (size_t)*data2);
	*data2 = (size_t *)((size_t)*data1 ^ (size_t)*data2);
	*data1 = (size_t *)((size_t)*data1 ^ (size_t)*data2);
}

static void HeapifyUp(heap_t *heap, size_t index)
{
	void *data = NULL;
	void *parent_data = NULL;

	if (index <= DUMMY)
	{
		return;
	}

	data = DVectorGetItem(heap->vector, index);
	parent_data = DVectorGetItem(heap->vector, (index / 2));

	if (heap->compare(*(size_t **)data, *(size_t **)parent_data) > 0)
	{
		Swap(data, parent_data);
		HeapifyUp(heap, index / 2);
	}
}

status HeapPush(heap_t *heap, void *data)
{
    size_t index = 0;
	assert(heap != NULL);

	index = DVectorGetSize(heap->vector);

	if (SUCCESS != DVectorPush(heap->vector, &data))
	{
		return (MEMORY_ALLOCATION_FAIL);
	}

	HeapifyUp(heap, index);

	return (SUCCESS);
}

/********************************************************************/
void *HeapPeek(heap_t *heap)
{
	assert(heap != NULL);

	return (*(size_t **)DVectorGetItem(heap->vector, INDEX_FIRST_ELEMENT));
}

/************************************************************************/
static void HeapifyDown(heap_t *heap, size_t index)
{
	void *data = NULL;
	void *left_data = NULL, *right_data = NULL;
	void *max = NULL;
	size_t right_index = index * 2 + 1;
	size_t left_index = index * 2;
	size_t max_index = index;

	data = DVectorGetItem(heap->vector, index);
	max = data;
	left_data = DVectorGetItem(heap->vector, left_index);
	right_data = DVectorGetItem(heap->vector, right_index);

	if (NULL == left_data)
	{
		return;
	}

	if (heap->compare(*(size_t **)max, *(size_t **)left_data) < 0)
	{
		max = left_data;
		max_index = left_index;
	}

	if (NULL != right_data)
	{
		if (heap->compare(*(size_t **)max, *(size_t **)right_data) < 0)
		{
			max = right_data;
			max_index = right_index;
		}
	}

	if (max != data)
	{
		Swap(data, max);
		HeapifyDown(heap, max_index);
	}
}

void HeapPop(heap_t *heap)
{
    void **first_data = NULL;
    void **last_data = NULL;
	assert(heap != NULL);

    first_data = DVectorGetItem(heap->vector, INDEX_FIRST_ELEMENT);
    last_data = DVectorGetItem(heap->vector, HeapCount(heap));

	Swap(first_data, last_data);
	DVectorPop(heap->vector);
	HeapifyDown(heap, INDEX_FIRST_ELEMENT);
}

/**************************************************************************/

static void Remove(heap_t *heap, size_t index)
{
	void **remove_data = NULL;
	void **last_data = NULL;

	remove_data = DVectorGetItem(heap->vector, index);
	last_data = DVectorGetItem(heap->vector, HeapCount(heap));

	if (index == HeapCount(heap))
	{
		DVectorPop(heap->vector);
		return;
	}

	if (heap->compare(*remove_data, *last_data) > 0)
	{
		Swap(remove_data, last_data);
		DVectorPop(heap->vector);
		HeapifyDown(heap, index);
	}
	else
	{
		Swap(remove_data, last_data);
		DVectorPop(heap->vector);
		HeapifyUp(heap, index);
	}
}

void *HeapRemove(heap_t *heap, match_function_t match, void *data_to_match)
{
	size_t index = INDEX_FIRST_ELEMENT;
	size_t len = 0;
	assert(heap != NULL);

	len = DVectorGetSize(heap->vector);

	for ( ; index < len; ++index)
	{
		size_t **data = DVectorGetItem(heap->vector, index);
		size_t *result = NULL;
		if (match(*data, data_to_match))
		{
			result = *data;
			Remove(heap, index);
			return (result);
		}
	}

	return (NULL);
}
