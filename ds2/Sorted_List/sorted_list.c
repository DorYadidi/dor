/*******************************************************************************
* NAME: sorted list                                                            *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  19.11.18                                                      *
*******************************************************************************/


#include "d_linked_list.h"
#include "sorted_list.h"
#include "function_pointers.h"
#include <stdio.h>
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/

struct sorted_list_s
{
	d_linked_list_t *list;
	is_before_t is_before;
};

sorted_list_t *SortedListCreate(is_before_t is_before)
{
	sorted_list_t *control = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	control->list = DLinkedListCreate();

	assert(is_before != NULL);

	if (NULL == control)
	{
		free(control->list);
		return (NULL);
	}

	if (NULL == control->list)
	{
		free(control);
		return (NULL);
	}

	control->is_before = is_before;

	return (control);
}

void SortedListDestroy(sorted_list_t *sl)
{
	assert(sl != NULL);
	DLinkedListDestroy(sl->list);
	free(sl);
}

size_t SortedListGetSize(const sorted_list_t *sl)
{
	assert(sl != NULL);

	return (DLinkedListGetSize(sl->list));
}

bool SortedListIsEmpty(const sorted_list_t *sl)
{
	assert(sl != NULL);

	return (DLinkedListIsEmpty(sl->list));
}

sorted_iterator_t SortedListBegin(const sorted_list_t *sl)
{
	sorted_iterator_t result;

	assert(sl != NULL);

	result.info = DLinkedListBegin(sl->list).info;

	return (result);
}

sorted_iterator_t SortedListEnd(const sorted_list_t *sl)
{
	sorted_iterator_t result;

	assert(sl != NULL);

	result.info = DLinkedListEnd(sl->list).info;

	return (result);
}

sorted_iterator_t SortedListInsert(sorted_list_t *sl, void *data)
{
	sorted_iterator_t result;
	dll_iterator_t tmp;

	tmp = (DLinkedListFind(sl->list, sl->is_before, data));

	if(NULL == tmp.info)
	{
		result.info = DLinkedListPushBack(sl->list , data).info;
	}
	else
	{
		result.info = DLinkedListInsert(tmp, data).info;
	}

	return (result);
}

void SortedListErase(sorted_iterator_t iter)
{
	dll_iterator_t tmp;

	assert(iter.info != NULL);

	tmp.info = iter.info;
	DLinkedListErase(tmp);
}

void SortedListPopFront(sorted_list_t *sl)
{
	assert(sl != NULL);
	DLinkedListPopFront(sl->list);
}

void SortedListPopBack(sorted_list_t *sl)
{
	assert(sl != NULL);
	DLinkedListPopBack(sl->list);
}

sorted_iterator_t SortedListFind
	(sorted_list_t *sl, match_function_t match, void *param)
{
	sorted_iterator_t result;
	dll_iterator_t tmp;

	assert(sl != NULL);

	tmp = DLinkedListFind(sl->list, match, param);
	result.info = tmp.info;

	return (result);
}

status SortedListForEach
	(sorted_list_t *sl, action_function_t action, void *param)
{
	assert(sl != NULL);

	return (DLinkedListForEach(sl->list, action, param));
}

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
	dll_iterator_t dest_iter;
	dll_iterator_t src_iter;
	dll_iterator_t dest_end;
	dll_iterator_t src_end;
	dll_iterator_t from_src;

	void *dest_data = NULL;
	void *src_data = NULL;

	assert(dest);
	assert(src);

	dest_iter = DLinkedListBegin(dest->list);
	src_iter = DLinkedListBegin(src->list);
	dest_end = DLinkedListEnd(dest->list);
	src_end = DLinkedListEnd(src->list);


	while (dest_iter.info != dest_end.info && src_iter.info != src_end.info)
	{
		dest_data = DLinkedListGetData(dest_iter);
		src_data = DLinkedListGetData(src_iter);

		from_src.info = src_iter.info;

		while (src_iter.info != src_end.info && dest->is_before(dest_data, src_data))
		{
			src_iter = DLinkedListGetNext(src_iter);
			src_data = DLinkedListGetData(src_iter);
		}

		if(from_src.info != src_iter.info)
		{
			DLinkedListSplice(dest_iter, from_src, src_iter);
		}

		dest_iter = DLinkedListGetNext(dest_iter);

	}

	if (src_iter.info != src_end.info)
	{
		DLinkedListSplice(dest_iter, src_iter, src_end);
	}
}

sorted_iterator_t SortedListGetNext(sorted_iterator_t iter)
{
	sorted_iterator_t result;
	dll_iterator_t tmp;

	assert(iter.info != NULL);

	tmp.info = iter.info;
	tmp = DLinkedListGetNext(tmp);
	result.info = tmp.info;

	return (result);
}

sorted_iterator_t SortedListGetPrevious(sorted_iterator_t iter)
{
	sorted_iterator_t result;
	dll_iterator_t tmp;

	assert(iter.info != NULL);

	tmp.info = iter.info;
	tmp = DLinkedListGetPrevious(tmp);
	result.info = tmp.info;

	return (result);
}

void *SortedListGetData(sorted_iterator_t iter)
{
	dll_iterator_t tmp;
	assert(iter.info != NULL);

	tmp.info = iter.info;
	return (DLinkedListGetData(tmp));
}

bool SortedListIsSameIterator(sorted_iterator_t iter1, sorted_iterator_t iter2)
{
	dll_iterator_t tmp1, tmp2;

	assert(iter1.info != NULL && iter2.info != NULL);

	tmp1.info = iter1.info;
	tmp2.info = iter2.info;

	return (DLinkedListIsSameIterator(tmp1, tmp2));
}
