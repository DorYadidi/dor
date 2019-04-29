#include <stdio.h>
#include <stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/
#include "stack.h"

struct stack_s
{
  void *data;
  size_t total_elements;
  size_t member_size;
  int top;
};

stack_t *StackCreate(size_t capacity, size_t element_size)
{
	stack_t *s = malloc(sizeof(stack_t));
	if(NULL == s)
	{
		return NULL;
	}

	s->top = -1;
	s->member_size = element_size;
	s->total_elements = capacity;
	s->data = malloc(capacity * element_size);
	if(NULL == s->data)
	{
	    	return NULL;
	}

	return s;
}

void StackDestroy(stack_t **s)
{
	free ((*s)->data);
	free(*s);
	*s = NULL;
}

void StackPush(stack_t *s, void *element)
{
	void *target = NULL;
	++s->top;
	target = (char*)s->data + (size_t)(s->top * s->member_size);
	memcpy(target, element, s->member_size);
}


void StackPop(stack_t *s)
{
	--s->top;
}

void *StackPeek(stack_t *s)
{
	void* source = NULL;
	source = (char*)s->data + (size_t)(s->top * s->member_size);
	return source;
}

size_t StackGetSize(stack_t *s)
{
	 return (size_t)(s->top + 1);
}

size_t StackGetElementSize(stack_t *s)
{
	return s->member_size;
}

size_t StackGetCapacity(stack_t *s)
{
	return s->total_elements;
}
