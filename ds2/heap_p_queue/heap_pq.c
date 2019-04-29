/*******************************************************************************
* NAME: Heap Priority Queue                                                    *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  27.12.18                                                      *
*******************************************************************************/

#include <stdlib.h>
#include <assert.h>

#include "heap_pq.h"
#include "heap.h"

struct heap_p_queue_s
{
	heap_t *heap;
};

heap_p_queue_t *HeapPQueueCreate(compare_function_t priority)
{
	heap_p_queue_t *pq = malloc(sizeof(heap_p_queue_t));

	if (NULL == pq)
	{
		return (NULL);
	}

	pq->heap = HeapCreate(priority);

	if (NULL == pq->heap)
	{
		free(pq);
		pq = NULL;
		return (NULL);
	}

	return (pq);
}

void HeapPQueueDestroy(heap_p_queue_t *pq)
{
	assert(NULL != pq);

	HeapDestroy(pq->heap);
	free(pq);
	pq = NULL;
}

status HeapPQueueEnqueue(heap_p_queue_t *pq, void *data)
{
	assert(NULL != pq && NULL != pq->heap);

	if (SUCCESS != HeapPush(pq->heap, data))
	{
		return (MEMORY_ALLOCATION_FAIL);
	}

	return (SUCCESS);
}

void *HeapPQueueDequeue(heap_p_queue_t *pq)
{
	void *return_data = NULL;
	assert(NULL != pq && NULL != pq->heap);

	return_data = HeapPeek(pq->heap);
	HeapPop(pq->heap);

	return (return_data);
}

void *HeapPQueuePeek(heap_p_queue_t *pq)
{
	assert(NULL != pq && NULL != pq->heap);
	return (HeapPeek(pq->heap));
}

size_t HeapPQueueGetSize(const heap_p_queue_t *pq)
{
	assert(NULL != pq && NULL != pq->heap);
	return (HeapCount(pq->heap));
}

bool HeapPQueueIsEmpty(const heap_p_queue_t *pq)
{
	assert(NULL != pq && NULL != pq->heap);
	return (HeapIsEmpty(pq->heap));
}

void *HeapPQueueRemove(heap_p_queue_t *pq, match_function_t match, void *param)
{
	assert(NULL != pq && NULL != pq->heap && NULL != match);

	return (HeapRemove(pq->heap, match, param));
}
