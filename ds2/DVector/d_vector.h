#ifndef __DS_DVECTOR_H__
#define __DS_DVECTOR_H__

#include <stdio.h>
#include "enum_rd58.h"
#include "function_pointers.h"

/*******************************************************************************
* NAME: Dynamic Vector                                                         *
*                                                                              *
* PURPOSE: Dynamic Vector (ADT)                                                *
*                                                                              *
* AUTHOR: Dor yadidi                                                           *
* DATE UPDATED:  07.11.18                                                      *
*******************************************************************************/

typedef struct d_vector_s d_vector_t;

/******************************************************************************/

d_vector_t *DVectorCreate(size_t capacity, size_t element_size);
/*******************************************************************************
* Creates dynamic vector and returns pointer to memory address of new vector   *
*                                                                              *
* Parameters:                                                                  *
*	capacity - number of elements in vector                                *
*	element_size - size of element in bytes                                    *
*                                                                              *
* Returns:                                                                     *
*	pointer to memory address of new vector                                    *
*******************************************************************************/

void DVectorDestroy(d_vector_t **dv);
/*******************************************************************************
* Frees dynamic vector memory                                                  *
*                                                                              *
* Parameters:                                                                  *
*	dv - pointer to memory address of vector, not NULL                         *
*                                                                              *
* Returns:                                                                     *
*	none                                                                       *
*******************************************************************************/

status DVectorReserve(d_vector_t *dv, size_t requested_capacity);
/*******************************************************************************
* Increases dynamic vector capacity to requested capacity.                     *
* If requested capacity is less than current capacity, does nothing.           *
*                                                                              *
* Parameters:                                                                  *
*	dv - pointer to memory address of vector, not NULL                         *
*	requested_capacity - min number of elements in vector                      *
*                                                                              *
* Returns:                                                                     *
*	0 - if SUCCESS                                                             *
*   1 - if memory allocation failed                                            *
*******************************************************************************/

status DVectorPush(d_vector_t *dv, void *element);
/*******************************************************************************
* Adds element to top of dynamic vector.                                       *
* If size reaches capacity after the push, doubles the capacity.               *
*                                                                              *
* Parameters:                                                                  *
*	dv - pointer to memory address of vector, not NULL                         *
*	element - pointer to element to be copied to vector, not NULL              *
*                                                                              *
* Returns:                                                                     *
*	0 - if SUCCESS                                                             *
*   1 - if memory allocation failed                                            *
*******************************************************************************/

status DVectorPop(d_vector_t *dv);
/*******************************************************************************
* Removes element from top of dynamic vector.                                  *
* If size drops below 1/4 of capacity after the pop, reduces capacity by 1/2.  *
*                                                                              *
* Parameters:                                                                  *
*	dv - pointer to memory address of vector, not NULL                         *
*                                                                              *
* Returns:                                                                     *
*	0 - if SUCCESS                                                             *
*   1 - if memory allocation failed                                            *
*                                                                              *
* Warning: pop will result in undefined behavior if vector is empty!           *
*******************************************************************************/

void *DVectorGetItem(const d_vector_t *dv , size_t index);
/*******************************************************************************
* Retrieves element from dynamic vector                                        *
*                                                                              *
* Parameters:                                                                  *
*	dv - pointer to memory address of vector, not NULL                         *
*	index - relative position of element in the vector                         *
*                                                                              *
* Returns:                                                                     *
* 	pointer to address of element at position index.                           *
*   NULL if index is not within dynamic vector size.                           *
*                                                                              *
* Warning: pointer behavior is unpredictable after push or pop!                *
*******************************************************************************/

size_t DVectorGetSize(const d_vector_t *dv);
/*******************************************************************************
* Returns current size of dynamic vector as size_t                             *
*                                                                              *
* Parameters:                                                                  *
*	dv - pointer to memory address of vector, not NULL                         *
*                                                                              *
* Returns:                                                                     *
*	current size of vector as size_t                                           *
*******************************************************************************/

size_t DVectorGetElementSize(const d_vector_t *dv);
/*******************************************************************************
* Returns dynamic vector element size as size_t                                *
*                                                                              *
* Parameters:                                                                  *
*	dv - pointer to memory address of vector, not NULL                         *
*                                                                              *
* Returns:                                                                     *
*	vector element size as size_t                                              *
*******************************************************************************/

size_t DVectorGetCapacity(const d_vector_t *dv);
/*******************************************************************************
* Returns dynamic vector capacity as size_t                                    *
*                                                                              *
* Parameters:                                                                  *
*	dv - pointer to memory address of vector, not NULL                         *
*                                                                              *
* Returns:                                                                     *
*	current vector capacity as size_t                                          *
*******************************************************************************/

#endif
