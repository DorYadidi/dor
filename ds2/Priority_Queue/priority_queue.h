#include <stdlib.h> /* size_t */

#include "enum_rd58.h"
#include "function_pointers.h"

#ifndef __DS_P_QUEUE_H__
#define __DS_P_QUEUE_H__

/*******************************************************************************
* NAME: Priority Queue                                                         *
*                                                                              *
* PURPOSE:                                                                     *
*                                                                              *
* AUTHOR: chen mardix                                                          *
* DATE UPDATED:  20.11.18                                                      *
*******************************************************************************/

typedef struct p_queue_s p_queue_t;

typedef bool (*is_higher_priority_t)(void *current_data, void *new_data);

/******************************************************************************/

p_queue_t *PQueueCreate(is_higher_priority_t is_higher_priority);
/*******************************************************************************
* Creates priority queue structure                                             *
*                                                                              *
* Parameters:                                                                  *
*  none                                                                        *
*                                                                              *
* Returns:                                                                     *
*  pointer to memory address of priority queue                                 *
*******************************************************************************/

void PQueueDestroy(p_queue_t *pq);
/*******************************************************************************
* Frees all memory allocated to priority queue                                 *
*                                                                              *
* Parameters:                                                                  *
*  pq - pointer to memory address of priority queue, Not NULL                  *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

status PQueueEnqueue(p_queue_t *pq, void* data);
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

void *PQueueDequeue(p_queue_t *pq);
/*******************************************************************************
* Removes and returns the highest priority element                             *
*                                                                              *
* Parameters:                                                                  *
*  q - pointer to memory address of priority queue, Not NULL                   *
*                                                                              *
* Returns:                                                                     *
*  pointer to removed data                                                     *
*******************************************************************************/

void *PQueuePeek(p_queue_t *pq);
/*******************************************************************************
* Returns the highest priority element                                         *
*                                                                              *
* Parameters:                                                                  *
*  pq - pointer to memory address of priority queue, Not NULL                  *
*                                                                              *
* Returns:                                                                     *
*  pointer to data                                                             *
*******************************************************************************/

size_t PQueueGetSize(const p_queue_t *pq);
/*******************************************************************************
* Returns current size of priority queue                                       *
*                                                                              *
* Parameters:                                                                  *
*  q - pointer to memory address of priority queue, Not NULL                   *
*                                                                              *
* Returns:                                                                     *
*  current size of priority queue                                              *
*******************************************************************************/

bool PQueueIsEmpty(const p_queue_t *pq);
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

void *PQueueRemove(p_queue_t *pq, match_function_t match, void *param);
/*******************************************************************************
* Removes the data from the queue. if data does not exist - does nothing.      *
*                                                                              *
* Parameters:                                                                  *
*  pq - pointer to memory address of priority queue, Not NULL                  *
*  match - function to be used in determing data to remove                     *
*  param - match function paramter                                             *
*                                                                              *
* Returns:                                                                     *
*  removed data                                                                *
*******************************************************************************/

#endif

