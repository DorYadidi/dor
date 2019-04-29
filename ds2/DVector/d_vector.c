/*******************************************************************************
* NAME:    test_d_vector                                                       *
*                                                                              *
* PURPOSE: tests for the dynamic vector   	              				       *
*                                                                              *
* AUTHOR: Dor yadidi                                                           *
* DATE UPDATED:  06.11.18                                                      *
*******************************************************************************/

#include <stdlib.h> /* malloc realloc free*/
#include <string.h> /* memcpy */
#include <assert.h> /* assert */
#include "d_vector.h"
#include "d_vector.h"


#define ENLARGE_REZISE_POLICY 2
#define REDUCE_REZISE_POLICY 2
#define REDUCE_POLICY 4

struct d_vector_s
{
	void *data;
	size_t size;
	size_t capacity;
	size_t element_size;
};

status ChangeVectorSize(d_vector_t *dv, size_t requested_capacity);

d_vector_t *DVectorCreate(size_t capacity, size_t element_size)
{
	d_vector_t *dv = malloc(sizeof(d_vector_t));

	if (NULL == dv)
	{
		return NULL;
	}

	dv->data = malloc(capacity * element_size);

	if (NULL == dv->data)
	{
		free(dv);
		return NULL;
	}

	dv->size = 0;
	dv->capacity = capacity;
	dv->element_size = element_size;

	return dv;
}

void DVectorDestroy(d_vector_t **dv)
{
	assert(NULL != dv && NULL != *dv);
	free((*dv)->data);
	(*dv)->data = NULL;
	free(*dv);
	*dv = NULL;
}

status DVectorReserve(d_vector_t *dv, size_t requested_capacity)
{
	assert(NULL != dv);

	if (requested_capacity > dv->capacity)
	{
		if(ChangeVectorSize(dv, requested_capacity)  == MEMORY_ALLOCATION_FAIL)
		{
			return (MEMORY_ALLOCATION_FAIL);
		}
	}

	return (SUCCESS);
}

status DVectorPush(d_vector_t *dv, void *element)
{
	assert(NULL != dv || NULL != element);

	if((dv->size)++ == dv->capacity)
	{
		if(ChangeVectorSize(dv, dv->capacity * ENLARGE_REZISE_POLICY) ==
			MEMORY_ALLOCATION_FAIL)
		{
			return (MEMORY_ALLOCATION_FAIL);
		}
	}

	memcpy((((char*)dv->data) + ((dv->size - 1) * dv->element_size)), element,
		dv->element_size);

	return (SUCCESS);
}

status DVectorPop(d_vector_t *dv)
{
	assert(NULL != dv);

	if(--(dv->size) == ((dv->capacity) / REDUCE_POLICY) &&
		dv->capacity >= REDUCE_POLICY)
	{
		if(ChangeVectorSize(dv, dv->capacity / REDUCE_REZISE_POLICY) ==
			MEMORY_ALLOCATION_FAIL)
		{
			return (MEMORY_ALLOCATION_FAIL);
		}
	}

	return (SUCCESS);
}

void *DVectorGetItem(const d_vector_t *dv , size_t index)
{
	assert(NULL != dv);

	if (0 == dv->size || index > (dv->size - 1))
	{
		return NULL;
	}

	return ((char *)dv->data + (index * dv->element_size));
}

size_t DVectorGetSize(const d_vector_t *dv)
{
	return (dv->size);
}

size_t DVectorGetElementSize(const d_vector_t *dv)
{
	return (dv->element_size);
}

size_t DVectorGetCapacity(const d_vector_t *dv)
{
	return (dv->capacity);
}

status ChangeVectorSize(d_vector_t *dv, size_t requested_capacity)
{
	void *temp = realloc(dv->data, requested_capacity * dv->element_size);

	if (NULL == temp)
	{
		return (MEMORY_ALLOCATION_FAIL);
	}

	dv->data = temp;
	dv->capacity = requested_capacity;

	return (SUCCESS);
}
