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
#include "../../ds/include/stack.h"

#define BITINBYTE 8
#define WORDSIZE ( __WORDSIZE / BITINBYTE )

struct fsmalloc_s
{
	stack_t *stack;
	char *data;
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
	
	fsm->stack = StackCreate(number_of_blocks, WORDSIZE);
	if (NULL == fsm->stack)
	{
		free(fsm->data);
		free(fsm);
		return (NULL);
	}
	
	for(i = 0; i < number_of_blocks; ++i)
	{
		StackPush(fsm->stack, p_data);
		p_data += block_size;
	}

	return (fsm);	
}

void FSMAllocDestroy(fsmalloc_t *fsm)
{
	assert(fsm != NULL);
	
	free(fsm->data);
	StackDestroy(&(fsm->stack));
	free(fsm);
}

void *FSMAllocGetBlock(fsmalloc_t *fsm)
{
	void *return_value = StackPeek(fsm->stack);

	assert(fsm != NULL);

	StackPop(fsm->stack);
	
	return (return_value);
}


void FSMAllocFreeBlock(fsmalloc_t *fsm, void *block)
{
	assert(fsm != NULL);
	
	StackPush(fsm->stack, block);	
}

size_t FSMAllocCountFree(fsmalloc_t *fsm)
{
	assert(fsm != NULL);
	
	return (StackGetSize(fsm->stack));	
}

size_t FSMAllocSupportedBlockSize(size_t block_size)
{
	while (block_size % WORDSIZE != 0)
	{
		++block_size;
	}
	
	return (block_size);
}

