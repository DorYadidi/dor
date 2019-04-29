/*******************************************************************************
* NAME: Heap Priority Queue                                                    *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  27.12.18                                                      *
*******************************************************************************/
#ifndef __HEAP_P_QUEUE_H__
#define __HEAP_P_QUEUE_H__

#include <stddef.h>

#include "enum_rd58.h"
#include "function_pointers.h"

typedef struct heap_p_queue_s heap_p_queue_t;

heap_p_queue_t *HeapPQueueCreate(compare_function_t priority);
/*******************************************************************************
* Creates heap based priority queue structure                                  *
*                                                                              *
* Parameters:                                                                  *
*  none                                                                        *
*                                                                              *
* Returns:                                                                     *
*  pointer to memory address of priority queue                                 *
*******************************************************************************/

void HeapPQueueDestroy(heap_p_queue_t *pq);
/*******************************************************************************
* Frees all memory allocated to priority queue                                 *
*                                                                              *
* Parameters:                                                                  *
*  pq - pointer to memory address of priority queue, Not NULL                  *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

status HeapPQueueEnqueue(heap_p_queue_t *pq, void* data);
/*******************************************************************************
* Inserts data to priority queue                                               *
*                                                                              *
* Parameters:                                                                  *
*  pq - pointer to memory address of priority queue, Not NULL                  *
*  data- pointer to memory address containing data                             *
*                                                                              *
* Returns:                                                                     *
*  SUCCESS - if successful                                                     *
*  MEMORY_ALLOCATION_FAIL - if malloc failed                                   *
*******************************************************************************/

void *HeapPQueueDequeue(heap_p_queue_t *pq);
/*******************************************************************************
* Removes and returns the highest priority element                             *
*                                                                              *
* Parameters:                                                                  *
*  q - pointer to memory address of priority queue, Not NULL                   *
*                                                                              *
* Returns:                                                                     *
*  pointer to removed data                                                     *
*******************************************************************************/

void *HeapPQueuePeek(heap_p_queue_t *pq);
/*******************************************************************************
* Returns the highest priority element                                         *
*                                                                              *
* Parameters:                                                                  *
*  pq - pointer to memory address of priority queue, Not NULL                  *
*                                                                              *
* Returns:                                                                     *
*  pointer to data                                                             *
*******************************************************************************/

size_t HeapPQueueGetSize(const heap_p_queue_t *pq);
/*******************************************************************************
* Returns current size of priority queue                                       *
*                                                                              *
* Parameters:                                                                  *
*  q - pointer to memory address of priority queue, Not NULL                   *
*                                                                              *
* Returns:                                                                     *
*  current size of priority queue                                              *
*******************************************************************************/

bool HeapPQueueIsEmpty(const heap_p_queue_t *pq);
/*******************************************************************************
* Determines if priority queue is empty                                        *
*                                                                              *
* Parameters:                                                                  *
*  pq - pointer to memory address of priority queue, Not NULL                  *
*                                                                              *
* Returns:                                                                     *
*  TRUE - if priority queue is empty                                           *
*  FALSE - if loop is not empty                                                *
*******************************************************************************/

void *HeapPQueueRemove(heap_p_queue_t *pq, match_function_t match, void *param);
/*******************************************************************************
* Removes the data from the queue.                                             *
*                                                                              *
* Parameters:                                                                  *
*  pq - pointer to memory address of priority queue, Not NULL                  *
*  match - function to be used in determing data to remove                     *
*  param - match function paramter                                             *
*                                                                              *
* Returns:                                                                     *
*  removed data. if data does not exist - returns NULL.                        *
*******************************************************************************/

#endif
