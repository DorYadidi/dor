#include <stdio.h>
#include <string.h> /*memcpy*/
#include "safe_stack.h"
#include "stack.h"


safe_stack_t *SafeStackCreate(size_t capacity, size_t element_size)
{
	return StackCreate(capacity, element_size);
}

void SafeStackDestroy(stack_t **s)
{
	StackDestroy(s);
}

int SafeStackPush(safe_stack_t *s, void *element)
{

	if (StackGetSize(s) == StackGetCapacity(s))
	{
		return 1;
	}

	StackPush(s, element);
	return 0;
}

int SafeStackPop(safe_stack_t *s)
{
	if(0 == StackGetSize(s))
	{
		return 1;
	}

	StackPop(s);
	return 0;
}

void *SafeStackPeek(safe_stack_t *s)
{
	if(0 == StackGetSize(s))
	{
		return NULL;
	}

	return StackPeek(s);
}

size_t SafeStackGetSize(safe_stack_t *s)
{
	return StackGetSize(s);
}

size_t SafeStackGetCapacity(safe_stack_t *s)
{
	return StackGetCapacity(s);
}

size_t SafeStackGetElementSize(safe_stack_t *s)
{
	return StackGetElementSize(s);
}
