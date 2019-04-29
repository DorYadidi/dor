/*******************************************************************************
* NAME: Fixed Size Memory Allocation                                           *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  29.11.18                                                      *
*******************************************************************************/

#include <stdlib.h> /* size_t */
#include <stdlib.h> /*__WORDSIZE malloc*/
#include <assert.h> /*assert*/
#include "../include/fixed_size_memory_allocation.h"

#define BITINBYTE 8
#define WORDSIZE ( __WORDSIZE / BITINBYTE )

struct fsmalloc_s
{
	char *data;
	void *get_next;
	size_t conter;
};

fsmalloc_t *FSMAllocCreate(size_t block_size, size_t number_of_blocks)
{
	fsmalloc_t *fsm = (fsmalloc_t *)malloc(sizeof(fsmalloc_t));
	unsigned i = 0;
	char *p_data = NULL;
	
	assert(block_size % WORDSIZE == 0);
	
	if (NULL == fsm)
	{
		return (NULL);
	}
	
	p_data = (char *)malloc(number_of_blocks * block_size);
	
	if (NULL == p_data)
	{
		free(fsm);
		return (NULL);
	}
	
	fsm->data = p_data;
	
	fsm->get_next = fsm->data;	
	
	for(i = 1; i < number_of_blocks; ++i)
	{
		*(size_t *)(fsm->data) = (size_t)(fsm->data + block_size);
		fsm->data = fsm->data + block_size;
	}
	
	fsm->data = fsm->get_next;
	
	fsm->conter = number_of_blocks;


	return (fsm);	
}

void FSMAllocDestroy(fsmalloc_t *fsm)
{
	assert(fsm != NULL);
	
	free(fsm->data);
	free(fsm);
}

void *FSMAllocGetBlock(fsmalloc_t *fsm)
{
	void *return_value = NULL;

	assert(fsm != NULL);
	
	return_value = fsm->get_next;
	*(size_t *)&fsm->get_next = *(size_t *)(fsm->get_next);
	--fsm->conter;
	
	return (return_value);
}

void FSMAllocFreeBlock(fsmalloc_t *fsm, void *block)
{
	void *tmp = NULL;
	assert(fsm != NULL);
	
	tmp = fsm->get_next;
	fsm->get_next = block;
	*(size_t *)block = *(size_t *)&tmp;	
	++fsm->conter;
}

size_t FSMAllocCountFree(fsmalloc_t *fsm)
{
	assert(fsm != NULL);
	
	return (fsm->conter);	
}

size_t FSMAllocSupportedBlockSize(size_t block_size)
{
	while (block_size % WORDSIZE != 0)
	{
		++block_size;
	}
	
	return (block_size);
}

