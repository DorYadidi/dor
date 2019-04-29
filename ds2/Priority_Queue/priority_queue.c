/*******************************************************************************
* NAME: Priority Queue                                                         *
*                                                                              *
* PURPOSE:                                                                     *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  14.11.18                                                      *
*******************************************************************************/

#include "sorted_list.h"
#include "priority_queue.h"
#include <stdio.h>
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/

struct p_queue_s
{
	sorted_list_t *sl;
};

p_queue_t *PQueueCreate(is_higher_priority_t is_higher_priority)
{
	p_queue_t *pq = (p_queue_t *)malloc(sizeof(p_queue_t));

	assert(is_higher_priority != NULL);

	if(NULL == pq)
	{
		return (NULL);
	}

	pq->sl = SortedListCreate(is_higher_priority);

	if(NULL == pq->sl)
	{
		free(pq);
		return (NULL);
	}

	return (pq);
}

void PQueueDestroy(p_queue_t *pq)
{
	assert(pq != NULL);
	SortedListDestroy(pq->sl);
	free(pq);
}

status PQueueEnqueue(p_queue_t *pq, void* data)
{
	sorted_iterator_t tmp;
	assert(pq != NULL);

	tmp = SortedListInsert(pq->sl, data);

	if(NULL == tmp.info)
	{
		return (MEMORY_ALLOCATION_FAIL);
	}

	return (SUCCESS);
}

void *PQueueDequeue(p_queue_t *pq)
{
	sorted_iterator_t tmp;
	void *data = NULL;
	assert(pq != NULL);

	tmp = SortedListBegin(pq->sl);
	data = SortedListGetData(tmp);

	SortedListPopFront(pq->sl);

	return (data);
}

void *PQueuePeek(p_queue_t *pq)
{
	sorted_iterator_t tmp;
	assert(pq != NULL);

	tmp = SortedListBegin(pq->sl);

	return (SortedListGetData(tmp));
}

size_t PQueueGetSize(const p_queue_t *pq)
{
	assert(pq != NULL);

	return (SortedListGetSize(pq->sl));
}

bool PQueueIsEmpty(const p_queue_t *pq)
{
	assert(pq != NULL);

	return (SortedListIsEmpty(pq->sl));
}

void *PQueueRemove(p_queue_t *pq, match_function_t match, void *param)
{
	sorted_iterator_t tmp;
	void *data_tmp;

	assert(pq != NULL);

	tmp = SortedListFind(pq->sl, match, param);
	if(tmp.info != NULL)
	{
		data_tmp = SortedListGetData(tmp);
		SortedListErase(tmp);
		return (data_tmp);
	}

	return (NULL);
}
