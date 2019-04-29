/******************************************************************************
* Name: Variable Size Memory Allocation                                        *
*                                                                              *
* Author: Dor Yadidi                                                           *
* Last Update: 4.12.18                                                         *
*******************************************************************************/

#include <stdlib.h> /* size_t */
#include <stdlib.h> /*__WORDSIZE malloc free*/
#include <assert.h> /*assert*/
#include "../include/variable_size_memory_allocation.h"

#define MAGIC_NUM 0xDEADBEEF
#define EMPTY_SEGMENT 0
#define BITINBYTE 8
#define WORDSIZE ( __WORDSIZE / BITINBYTE )

#define OFFSETOF(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define CONTAINER_OF(ptr, type, member) \
                      ((type *) ((char *)(ptr) - OFFSETOF(type, member)))

typedef struct free_link_list_s free_link_list_t;

struct free_link_list_s
{
	free_link_list_t *next;
};

struct vsm_head_s 
{
	free_link_list_t node;
	long segment_size;
	
	#ifndef NDEBUG
	long magic_num;
	#endif
};

struct vsmalloc_s
{
	vsm_head_t dummy_head;
	vsm_head_t dummy_tail;
	char *memory;	
};

vsm_head_t VSMAHeadCreate(size_t segment_size, free_link_list_t *next_head);
size_t VSMADefragmentize(vsmalloc_t *vsm, vsm_head_t *head);

vsm_head_t VSMAHeadCreate(size_t segment_size, free_link_list_t *next_head)
{
	vsm_head_t new_head;
	new_head.segment_size = segment_size - sizeof(vsm_head_t);
	new_head.node.next = next_head;
	
	#ifndef NDEBUG
	new_head.magic_num = MAGIC_NUM;
	#endif
	
	return (new_head);
}

vsmalloc_t *VSMAllocCreate(size_t requested_byte_count)
{
	vsmalloc_t *vsm = (vsmalloc_t *)malloc(sizeof(vsmalloc_t));
	
	assert(requested_byte_count % WORDSIZE == 0);
	
	if (NULL == vsm)
	{
		return (NULL);
	}
			
	vsm->memory = (char *)malloc(requested_byte_count * sizeof(char));
	
	if (NULL == vsm->memory)
	{
		free(vsm);
		return (NULL);
	}
		
	*(vsm_head_t *)vsm->memory = VSMAHeadCreate(requested_byte_count,
                                                &vsm->dummy_tail.node);

	vsm->dummy_head = VSMAHeadCreate(EMPTY_SEGMENT,
                                        &((vsm_head_t *)vsm->memory)->node);
	
	vsm->dummy_tail = VSMAHeadCreate(EMPTY_SEGMENT, NULL);
			
	return (vsm);
}

void VSMAllocDestroy(vsmalloc_t *vsm)
{
	assert(vsm != NULL);
	
	free(vsm->memory);
	free(vsm);
}

size_t VSMADefragmentize(vsmalloc_t *vsm, vsm_head_t *head)
{
	vsm_head_t *head_next = NULL;
	
	assert(vsm != NULL && head != NULL);

	while (head->node.next != &vsm->dummy_tail.node)
	{
		head_next = CONTAINER_OF(head->node.next, vsm_head_t, node);

		if (head_next->segment_size <= 0)
		{
			return (head->segment_size);
		}

		head->segment_size += (head_next->segment_size + sizeof(vsm_head_t));
		
		head->node.next = head_next->node.next;
	}

	return (head->segment_size);
}

void *VSMAllocGetBlock(vsmalloc_t *vsm, size_t block_size)
{
	vsm_head_t *new_head = NULL;
	vsm_head_t *head = NULL;
	size_t new_segment_size = 0;
	
	assert(vsm != NULL);

	head = CONTAINER_OF(vsm->dummy_head.node.next, vsm_head_t, node);

	while (head->node.next)
	{
		if (head->segment_size > 0 && 
			   VSMADefragmentize(vsm, head) > (block_size + sizeof(vsm_head_t)))
		{
			new_head = (vsm_head_t *)((char *)head + sizeof(vsm_head_t) + block_size);
			new_segment_size = head->segment_size - block_size;
			*new_head = VSMAHeadCreate(new_segment_size, head->node.next);

			head->node.next = &new_head->node;
			head->segment_size = -block_size;

			return ((char *)head + sizeof(vsm_head_t));
		}
		
		head = CONTAINER_OF(head->node.next, vsm_head_t, node);	
	}

	return (NULL);
}

void VSMAllocFreeBlock(void *block)
{
	vsm_head_t *head = (vsm_head_t *)((char *)block - sizeof(vsm_head_t));
	
	assert(block != NULL);

	#ifndef NDEBUG
	assert(head->magic_num == MAGIC_NUM);
	#endif
	
	head->segment_size = -head->segment_size;
}

size_t VSMAllocGetBiggestFreeBlockSize(vsmalloc_t *vsm)
{
	size_t max_size = 0;
	vsm_head_t *head = NULL;

	assert(vsm != NULL);

	head = CONTAINER_OF(vsm->dummy_head.node.next, vsm_head_t, node);

	while (head->node.next)
	{
		if (head->segment_size > 0)
		{
			if (VSMADefragmentize(vsm, head) > max_size)
			{
				max_size = head->segment_size;
			}
		}
	
		head = CONTAINER_OF(head->node.next, vsm_head_t, node);
	}

	return (max_size);
}

size_t VSMAllocSupportedBlockSize(size_t block_size)
{
	if (block_size % WORDSIZE)
	{
		return (block_size + (WORDSIZE - (block_size % WORDSIZE)));
	}

	return (block_size);
}

size_t VSMAllocGetHeaderSize()
{
	return (sizeof(vsm_head_t));
}
