/*******************************************************************************
* NAME: Hash Table                                                             *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  25.12.18                                                      *
*******************************************************************************/
#include <stdio.h>
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/
#include "d_linked_list.h"
#include "hash_table.h"

struct hash_table_s
{
  hash_function_t hash_function;
  match_function_t match;
  d_linked_list_t **lut;
  size_t number_of_keys;
};


hash_table_t *HashCreate(hash_function_t hash_function,
                         match_function_t match, size_t number_of_keys)
{
	hash_table_t *hash = (hash_table_t *)malloc(sizeof(hash_table_t));
	size_t i = 0;

	if (NULL == hash)
	{
		return (NULL);
	}

	hash->hash_function = hash_function;
	hash->match = match;
	hash->number_of_keys = number_of_keys;

	hash->lut = (d_linked_list_t **)malloc(sizeof(d_linked_list_t *) * number_of_keys);

	if (NULL == hash->lut)
	{
		free (hash);
		hash = NULL;
		return (NULL);
	}

	for(	; i < number_of_keys; ++i)
	{
		size_t j = 0;
		hash->lut[i] = DLinkedListCreate();

		if (NULL == hash->lut[i])
		{
			for (	; j < i; --j)
			{
				DLinkedListDestroy(hash->lut[j]);
			}

			free (hash->lut);
			hash->lut = NULL;
			free(hash);
			hash = NULL;
		}
	}

	return (hash);
}

void HashDestroy(hash_table_t *hash)
{
	size_t i = 0;
	assert(NULL != hash);

	for( ; i < hash->number_of_keys; ++i)
	{
		DLinkedListDestroy(hash->lut[i]);
	}

	free (hash->lut);
	hash->lut = NULL;
	free(hash);
	hash = NULL;
}

size_t HashCount(const hash_table_t *hash)
{
	size_t i = 0;
	size_t count = 0;
	assert(NULL != hash);

	for( ; i < hash->number_of_keys; ++i)
	{
		count += DLinkedListGetSize(hash->lut[i]);
	}

	return (count);
}

bool HashIsEmpty(const hash_table_t *hash)
{
	size_t i = 0;
	assert(NULL != hash);

	for( ; i < hash->number_of_keys; ++i)
	{
		if (FALSE == DLinkedListIsEmpty(hash->lut[i]))
		{
			return (FALSE);
		}
	}

	return (TRUE);
}

status HashInsert(hash_table_t *hash, void *data)
{
	size_t hash_index = 0;
	assert(NULL != hash);

	hash_index = hash->hash_function(data);
	if(NULL == DLinkedListPushBack(hash->lut[hash_index], data).info)
	{
		return (MEMORY_ALLOCATION_FAIL);
	}

	return (SUCCESS);
}

void HashRemove(hash_table_t *hash, void *data)
{
	size_t hash_index = 0;
	dll_iterator_t iter;
	assert(NULL != hash);

	hash_index = hash->hash_function(data);
	iter = DLinkedListFind(hash->lut[hash_index], hash->match, data);

	if (NULL == iter.info)
	{
		return;
	}

	DLinkedListErase(iter);
}

void *HashFind(hash_table_t *hash, void *data_to_match)
{
	size_t hash_index = 0;
	dll_iterator_t iter;
	void *result = NULL;

	assert(NULL != hash);

	hash_index = hash->hash_function(data_to_match);
	iter = DLinkedListFind(hash->lut[hash_index], hash->match, data_to_match);

	if (NULL == iter.info)
	{
		return (NULL);
	}

	result = DLinkedListGetData(iter);

	/*cache last used item*/
	if (NULL == DLinkedListPushFront(hash->lut[hash_index], result).info)
	{
		DLinkedListErase(iter);
	}

	return (result);
}

status HashForEach(hash_table_t *hash, action_function_t action, void *param)
{
	size_t i = 0;
	assert(NULL != hash);

	for( ; i < hash->number_of_keys; ++i)
	{
		if (SUCCESS != DLinkedListForEach(hash->lut[i], action, param))
		{
			return (ACTION_FAIL);
		}
	}

	return (SUCCESS);
}

/******************************************************************************/

static size_t HashGetBiggestDLL(hash_table_t *hash)
{
	size_t i = 0;
	size_t biggest = 0;
	assert(NULL != hash);

	biggest = DLinkedListGetSize(hash->lut[i]);

	for(i = 1; i < hash->number_of_keys; ++i)
	{
		size_t current_size = DLinkedListGetSize(hash->lut[i]);

		if (biggest < current_size)
		{
			biggest = current_size;
		}
	}

	return (biggest);
}

static size_t HashGetSmallesttDLL(hash_table_t *hash)
{
	size_t i = 0;
	size_t smallest = 0;
	assert(NULL != hash);

	smallest = DLinkedListGetSize(hash->lut[i]);

	for(i = 1; i < hash->number_of_keys; ++i)
	{
		size_t current_size = DLinkedListGetSize(hash->lut[i]);

		if (smallest > current_size)
		{
			smallest = current_size;
		}
	}

	return (smallest);
}

static size_t HashGetEmptyEnter(hash_table_t *hash)
{
	size_t i = 0;
	size_t counter = 0;
	assert(NULL != hash);


	for( ; i < hash->number_of_keys; ++i)
	{
		if (TRUE == DLinkedListIsEmpty(hash->lut[i]))
		{
			++counter;
		}
	}

	return (counter);
}

void HashStatistic(hash_table_t *hash)
{
	printf("Biggest Enter %lu\n", HashGetBiggestDLL(hash));
	printf("Smallestest Enter %lu\n", HashGetSmallesttDLL(hash));
	printf("Empty Enter %lu\n", HashGetEmptyEnter(hash));
}
