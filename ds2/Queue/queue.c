#include "queue.h"
#include "s_linked_list.h"
#include <stdio.h>
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

/*******************************************************************************
* NAME: Queue (FIFO)                                                           *
*                                                                              *
* PURPOSE: Queue                                                               *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  13.11.18                                                      *
*******************************************************************************/

struct queue_s
{
	sll_node_t *head;
	sll_node_t *tail;
};

queue_t *QueueCreate()
{
	queue_t *queue =(queue_t *)malloc(sizeof(queue_t));
	sll_node_t *dummy = SLinkedListCreate(NULL, NULL);

	if(NULL == queue)
	{
		free(dummy);
		return (NULL);
	}

	if(NULL == dummy)
	{
		free(queue);
		return (NULL);
	}

	queue->head = dummy;
	queue->tail = dummy;

	return (queue);
}

void QueueDestroy(queue_t **q)
{
	assert(q != NULL && *q != NULL);
	SLinkedListDestroy(&(*q)->head);
	free(*q);
	*q = NULL;
}

status QueueEnqueue(queue_t *q, void* data)
{
	sll_node_t *new_node = SLinkedListCreate(data, NULL);
	assert(q != NULL);

	if(NULL == new_node)
	{
		return (MEMORY_ALLOCATION_FAIL);
	}

	SLinkedListInsertAfter(q->tail, new_node);
	q->tail = q->tail->next;

	return (SUCCESS);
}

void *QueueDequeue(queue_t *q)
{
	void *tmp = NULL;
	void *data_removed = NULL;
	assert(q != NULL);
	tmp = q->head;
	q->head = q->head->next;
	data_removed = q->head->data;
	free(tmp);
	q->head->data = NULL;
	return (data_removed);
}

void *QueuePeek(queue_t *q)
{
	assert(q != NULL);
	return (q->head->next->data);
}

size_t QueueGetSize(const queue_t *q)
{
	assert(q != NULL);
	return (SLinkedListGetSize(q->head->next));
}

bool QueueIsEmpty(const queue_t *q)
{
	if(0 == SLinkedListGetSize(q->head->next))
	{
		return (TRUE);
	}

	return (FALSE);
}

void QueueAppend(queue_t *dest, queue_t *src)
{
	dest->tail->next = src->head->next;
	dest->tail = src->tail;
	free(src->head);
}
