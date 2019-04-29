/*******************************************************************************
* NAME: Heap                                                                   *
*                                                                              *
* AUTHOR: Chen Avisar                                                          *
* DATE UPDATED:  27.12.18                                                      *
*******************************************************************************/
#ifndef __HEAP__H__
#define __HEAP__H__

#include <stddef.h>

#include "enum_rd58.h"
#include "function_pointers.h"

/*{
	compare_function_t compare;
	d_vector_t *vector
}*/
typedef struct heap_s heap_t;

heap_t *HeapCreate(compare_function_t compare);
/*******************************************************************************
* Heap constractor                                                             *
*                                                                              *
* parameters                                                                   *
*  compare - compare function, not NULL                                        *
*                                                                              *
* returns                                                                      *
*  Heap descriptor pointer                                                     *
*******************************************************************************/

void HeapDestroy(heap_t *heap);
/*******************************************************************************
* Frees all memory allocated for Heap                                          *
*                                                                              *
* parameters                                                                   *
*  heap - heap descriptor pointer, not NULL                                    *
*                                                                              *
* returns                                                                      *
*  none                                                                        *
*******************************************************************************/

size_t HeapCount(const heap_t *heap);
/*******************************************************************************
* Counts the number of data points stored in Heap                              *
*                                                                              *
* parameters                                                                   *
*  heap - heap descriptor pointer, not NULL                                    *
*                                                                              *
* returns                                                                      *
*  number of data points stored in heap                                        *
*******************************************************************************/

bool HeapIsEmpty(const heap_t *heap);
/*******************************************************************************
* Check if Heap  is empty                                                      *
*                                                                              *
* parameters                                                                   *
*  heap - heap descriptor pointer, not NULL                                    *
*                                                                              *
* returns                                                                      *
*  TRUE if empty                                                               *
*  FALSE if not empty                                                          *
*******************************************************************************/

status HeapPush(heap_t *heap, void *data);
/*******************************************************************************
*  Inserts a new data point into an Heap .                                     *
*                                                                              *
* parameters                                                                   *
*  heap - heap descriptor pointer, not NULL                                    *
*  data - new data point.        					                           *
*                                                                              *
* returns                                                                      *
*  SUCCESS on successful insert                                                *
*  MEMORY_ALLOCATION_FAIL if memory allocation failed                          *
*******************************************************************************/

void *HeapPeek(heap_t *Heap);
/*******************************************************************************
*  Peek a top data point from Heap                                             *
*                                                                              *
* parameters                                                                   *
*  heap - heap descriptor pointer, not NULL                                    *
*                                                                              *
* returns                                                                      *
*  none                                                                        *
*******************************************************************************/

void HeapPop(heap_t *Heap);
/*******************************************************************************
*  Pops a top data point from Heap                                             *
*                                                                              *
* parameters                                                                   *
*  heap - heap descriptor pointer, not NULL                                    *
*                                                                              *
* returns                                                                      *
*  none                                                                        *
*******************************************************************************/

void *HeapRemove
(heap_t *Heap, match_function_t match, void *data_to_match);
/*******************************************************************************
*  Removes a data point from Heap . if doesn't exist does nothing.             *
*                                                                              *
* parameters                                                                   *
*  heap - heap descriptor pointer, not NULL                                    *
*  match - match function                                                      *
* data_to_match - data for femove                                              *
* returns                                                                      *
*  pointer to the removed data.                                                                       *
*******************************************************************************/

#endif
