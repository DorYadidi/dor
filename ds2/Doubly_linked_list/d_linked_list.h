#ifndef __D_LINKED_LIST_H__
#define __D_LINKED_LIST_H__

#include <stdio.h>
#include "enum_rd58.h"
#include "function_pointers.h"

/*******************************************************************************
* NAME: Doubly Linked List                                                     *
*                                                                              *
* AUTHOR: Yaakov Sidikman                                                      *
* DATE UPDATED:  20.11.18                                                      *
*******************************************************************************/

typedef struct d_linked_list_s d_linked_list_t;
typedef struct dll_iterator_s 
{
	void *info;
} dll_iterator_t;

d_linked_list_t *DLinkedListCreate();
/*******************************************************************************
* Creates doubly linked list                                                   *
*                                                                              *
* Parameters:                                                                  *
*  none                                                                        *
*                                                                              *
* Returns:                                                                     *
*  pointer to memory address of list                                           *
*******************************************************************************/

void DLinkedListDestroy(d_linked_list_t *dll);
/*******************************************************************************
* Frees doubly linked list                                                     *
*                                                                              *
* Parameters:                                                                  *
*  dll - pointer to doubly linked list, not NULL                               *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

size_t DLinkedListGetSize(d_linked_list_t *dll);
/*******************************************************************************
* Returns current size of doubly linked list                                   *
*                                                                              *
* Parameters:                                                                  *
*  dll - pointer to doubly linked list, not NULL                               *
*                                                                              *
* Returns:                                                                     *
*  current size of doubly linked list                                          *
*******************************************************************************/

bool DLinkedListIsEmpty(d_linked_list_t *dll);
/*******************************************************************************
* Determines if doubly linked list is empty                                    *
*                                                                              *
* Parameters:                                                                  *
*  dll - pointer to doubly linked list, not NULL                               *
*                                                                              *
* Returns:                                                                     *
*  TRUE - if list is empty                                                     *
*  FALSE - if list is not empty                                                *
*******************************************************************************/

dll_iterator_t DLinkedListBegin(d_linked_list_t *dll);
/*******************************************************************************
* Returns pointer to iterator to head of doubly linked list                    *
*                                                                              *
* Parameters:                                                                  *
*  dll - pointer to doubly linked list, not NULL                               *
*                                                                              *
* Returns:                                                                     *
*  iterator pointer to head of doubly linked list, undefined if empty          *
*******************************************************************************/

dll_iterator_t DLinkedListEnd(d_linked_list_t *dll);
/*******************************************************************************
* Returns pointer to iterator to end of doubly linked list                     *
*                                                                              *
* Parameters:                                                                  *
*  dll - pointer to doubly linked list, not NULL                               *
*                                                                              *
* Returns:                                                                     *
*  iterator pointer to place beyond last element of list, undefined if empty   *
*******************************************************************************/

dll_iterator_t DLinkedListInsert(dll_iterator_t iter, void *data);
/*******************************************************************************
* Inserts element to doubly linked list at location of iterator                *
*                                                                              *
* Parameters:                                                                  *
*  iter - pointer to iterator of doubly linked list, not NULL                  *
*  data - pointer to memory address of data                                    *
*                                                                              *
* Returns:                                                                     *
*  iterator pointer to inserted element                                        *
*******************************************************************************/

dll_iterator_t DLinkedListInsertAfter(dll_iterator_t iter, void *data);
/*******************************************************************************
* Inserts element to doubly linked list after location of iterator             *
*                                                                              *
* Parameters:                                                                  *
*  iter - pointer to iterator of doubly linked list, not NULL                  *
*  data - pointer to memory address of data                                    *
*                                                                              *
* Returns:                                                                     *
*  iterator pointer to inserted element                                        *
*******************************************************************************/

void DLinkedListErase(dll_iterator_t iter);
/*******************************************************************************
* Removes element from doubly linked list at iterator location                 *
*                                                                              *
* Parameters:                                                                  *
*  iter - pointer to iterator of doubly linked list, not NULL                  *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

dll_iterator_t DLinkedListPushFront(d_linked_list_t *dll, void *data);
/*******************************************************************************
* Add element to head of doubly linked list                                    *
*                                                                              *
* Parameters:                                                                  *
*  dll - pointer to doubly linked list, not NULL                               *
*  data - pointer to memory address of data                                    *
*                                                                              *
* Returns:                                                                     *
*  iterator pointer to inserted element                                        *
*******************************************************************************/

dll_iterator_t DLinkedListPushBack(d_linked_list_t *dll, void *data);
/*******************************************************************************
* Add element to end of doubly linked list                                     *
*                                                                              *
* Parameters:                                                                  *
*  dll - pointer to doubly linked list, not NULL                               *
*  data - pointer to memory address of data                                    *
*                                                                              *
* Returns:                                                                     *
*  iterator pointer to inserted element                                        *
*******************************************************************************/

void DLinkedListPopFront(d_linked_list_t *dll);
/*******************************************************************************
* Remove element from head of doubly linked list                               *
*                                                                              *
* Parameters:                                                                  *
*  dll - pointer to doubly linked list, not NULL                               *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

void DLinkedListPopBack(d_linked_list_t *dll);
/*******************************************************************************
* Remove element from end of doubly linked list                                *
*                                                                              *
* Parameters:                                                                  *
*  dll - pointer to doubly linked list, not NULL                               *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

dll_iterator_t DLinkedListFind
	(d_linked_list_t *dll, match_function_t match, void *param);
/*******************************************************************************
* Uses match function to find an element in a doubly linked list               *
*                                                                              *
* Parameters:                                                                  *
*  dll - pointer to doubly linked list, not NULL                               *
*  match - function to be used in determing element to return                  *
*  param - argument to be used in match function                               *
*                                                                              *
* Returns:                                                                     *
*  pointer to memory address of return element                                 *
*******************************************************************************/

status DLinkedListForEach
	(d_linked_list_t *dll, action_function_t action, void *param);
/*******************************************************************************
* Impelements action function on each element of doubly linked list            *
*                                                                              *
* Parameters:                                                                  *
*  dll - pointer to doubly linked list, not NULL                               *
*  action - function to be implemented for each node                           *
*  param - argument to be used in action function                              *
*                                                                              *
* Returns:                                                                     *
*  SUCCESS - if successful                                                     *
*  ACTION_FAIL - if failed                                                     *
*******************************************************************************/

void DLinkedListSplice(
	dll_iterator_t where, dll_iterator_t from, dll_iterator_t to);
/*******************************************************************************
* Inserts segment of source doubly linked list into destination list           *
*                                                                              *
* Parameters:                                                                  *
*  where - iterator of splice loaction in destination doubly linked list       *
*  from - iterator of begining of source segment                               *
*  to - iterator of end of source segment                                      *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

dll_iterator_t DLinkedListGetNext(dll_iterator_t iter);
/*******************************************************************************
* Returns iterator pointer to next element                                     *
*                                                                              *
* Parameters:                                                                  *
*  iter - pointer to iterator of doubly linked list, not NULL                  *
*                                                                              *
* Returns:                                                                     *
*  iterator pointer to next element                                            *
*******************************************************************************/

dll_iterator_t DLinkedListGetPrevious(dll_iterator_t iter);
/*******************************************************************************
* Returns iterator pointer to previous element                                 *
*                                                                              *
* Parameters:                                                                  *
*  iter - pointer to iterator of doubly linked list, not NULL                  *
*                                                                              *
* Returns:                                                                     *
*  iterator pointer to previous element                                        *
*******************************************************************************/

void *DLinkedListGetData(dll_iterator_t iter);
/*******************************************************************************
* Returns pointer to element data                                              *
*                                                                              *
* Parameters:                                                                  *
*  iter - pointer to iterator of doubly linked list, not NULL                  *
*                                                                              *
* Returns:                                                                     *
*  pointer to element data                                                     *
*******************************************************************************/

bool DLinkedListIsSameIterator(dll_iterator_t iter1, dll_iterator_t iter2);
/*******************************************************************************
* Returns boolean value of if iter1 and iter2 are the same iterator            *
*                                                                              *
* Parameters:                                                                  *
*  iter1 - pointer to iterator of doubly linked list, not NULL                 *
*  iter2 - pointer to iterator of doubly linked list, not NULL                 *
*                                                                              *
* Returns:                                                                     *
*  TRUE - if iterators are the same                                            *
*  FALSE - if iteratos are not the same                                        *
*******************************************************************************/

#endif
