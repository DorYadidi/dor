#ifndef __DS_STACK_H__
#define __DS_STACK_H__

#include <stdio.h>

/*******************************************************************************
* NAME: STACK                                                                  *
*                                                                              *
* PURPOSE: STACK manipulation functions                                        *
*                                                                              *
* AUTHOR: dor yadidi                                                           *
* DATE UPDATED:  04.11.18                                                      *
*******************************************************************************/

typedef struct stack_s stack_t;

stack_t *StackCreate(size_t capacity, size_t element_size);

void StackDestroy(stack_t **s);

size_t StackGetSize(stack_t *s);

void StackPush(stack_t *s, void *element);

void StackPop(stack_t *s);

void *StackPeek(stack_t *s);

size_t StackGetElementSize(stack_t *s);

size_t StackGetCapacity(stack_t *s);



#endif
