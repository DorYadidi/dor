#ifndef __DS_STACKSAFE_H__
#define __DS_STACKSAFE_H__

#include <stdio.h>


/*******************************************************************************
* NAME: STACK                                                                  * 
*                                                                              *
* PURPOSE: STACK manipulation functions                                        *
*                                                                              *
* AUTHOR: dor yadidi                                                           *
* DATE UPDATED:  04.11.18                                                      *
*******************************************************************************/

typedef struct stack_s safe_stack_t;

safe_stack_t *SafeStackCreate(size_t capacity, size_t element_size);

void SafeStackDestroy(safe_stack_t **s);

size_t SafeStackGetSize(safe_stack_t *s);

int SafeStackPush(safe_stack_t *s, void *element);

int SafeStackPop(safe_stack_t *s);

void *SafeStackPeek(safe_stack_t *s);

size_t SafeStackGetElementSize(safe_stack_t *s);

size_t SafeStackGetCapacity(safe_stack_t *s);

#endif
