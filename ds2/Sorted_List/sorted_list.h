#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include <stdio.h> /* size_t */

#include "enum_rd58.h"
#include "function_pointers.h"

/*******************************************************************************
* NAME: sorted list                                                            *
*                                                                              *
* AUTHOR: Yaakov Sidikman                                                      *
* DATE UPDATED:  20.11.18                                                      *
*******************************************************************************/

typedef struct sorted_list_s sorted_list_t;
typedef struct sorted_list_iter_s
{
	void *info;
} sorted_iterator_t;

typedef bool (*is_before_t)(void *current_data, void *new_data);

sorted_list_t *SortedListCreate(is_before_t is_before);
/*******************************************************************************
* Creates sorted list                                                          *
*                                                                              *
* Parameters:                                                                  *
*  none                                                                        *
*                                                                              *
* Returns:                                                                     *
*  pointer to memory address of list                                           *
*******************************************************************************/

void SortedListDestroy(sorted_list_t *sl);
/*******************************************************************************
* Frees sorted list                                                            *
*                                                                              *
* Parameters:                                                                  *
*  sl - pointer to sorted list, not NULL                                       *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

size_t SortedListGetSize(const sorted_list_t *sl);
/*******************************************************************************
* Returns current size of sorted list                                          *
*                                                                              *
* Parameters:                                                                  *
*  sl - pointer to sorted list, not NULL                                       *
*                                                                              *
* Returns:                                                                     *
*  current size of sorted list                                                 *
*******************************************************************************/

bool SortedListIsEmpty(const sorted_list_t *sl);
/**********************************src******************************************
* Determines if sorted list is empty                                           *
*                                                                              *
* Parameters:                                                                  *
*  sl - pointer to sorted list, not NULL                                       *
*                                                                              *
* Returns:                                                                     *
*  TRUE - if list is empty                                                     *
*  FALSE - if list is not empty                                                *
*******************************************************************************/

sorted_iterator_t SortedListBegin(const sorted_list_t *sl);
/*******************************************************************************
* Returns iterator to begining of sorted list                                  *
*                                                                              *
* Parameters:                                                                  *
*  sl - pointer to sorted list, not NULL, not empty                            *
*                                                                              *
* Returns:                                                                     *
*  returns iterator to head of sorted list, undefined if empty                 *
*******************************************************************************/

sorted_iterator_t SortedListEnd(const sorted_list_t *sl);
/*******************************************************************************
* Returns iterator to end of sorted list                                       *
*                                                                              *
* Parameters:                                                                  *
*  sl - pointer to sorted list, not NULL, not empty                            *
*                                                                              *
* Returns:                                                                     *
*  iterator pointer to place beyond last element of list, undefined if empty   *
*******************************************************************************/

sorted_iterator_t SortedListInsert(sorted_list_t *sl, void *data);
/*******************************************************************************
* Inserts element to sorted list                                               *
*                                                                              *
* Parameters:                                                                  *
*  sl - pointer to sorted list, not NULL, not empty                            *
*  data - pointer to memory address of data                                    *
*                                                                              *
* Returns:                                                                     *
*  iterator to inserted element                                                *
*******************************************************************************/

void SortedListErase(sorted_iterator_t iter);
/*******************************************************************************
* Removes element from sorted list at iterator location                        *
*                                                                              *
* Parameters:                                                                  *
*  iter - iterator of sorted list, not NULL                                    *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

void SortedListPopFront(sorted_list_t *sl);
/*******************************************************************************
* Remove element from head of sorted list                                      *
*                                                                              *
* Parameters:                                                                  *
*  sl - pointer to sorted list, not NULL                                       *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

void SortedListPopBack(sorted_list_t *sl);
/*******************************************************************************
* Remove element from end of sorted list                                       *
*                                                                              *
* Parameters:                                                                  *
*  sl - pointer to sorted list, not NULL                                       *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

sorted_iterator_t SortedListFind
	(sorted_list_t *sl, match_function_t match, void *param);
/*******************************************************************************
* Uses match function to find an element in a sorted list                      *
*                                                                              *
* Parameters:                                                                  *
*  sl - pointer to sorted list, not NULL                                       *
*  match - function to be used in determing element to return                  *
*  param - argument to be used in match function                               *
*                                                                              *
* Returns:                                                                     *
*  iterator to matched element                                                 *
*******************************************************************************/

status SortedListForEach
	(sorted_list_t *sl, action_function_t action, void *param);
/*******************************************************************************
* Impelements action function on each element of doubly linked list            *
*                                                                              *
* Parameters:                                                                  *
*  sl - pointer to sorted list, not NULL                                       *
*  action - function to be implemented on each element of list                 *
*  param - argument to be used in action function                              *
*                                                                              *
* Returns:                                                                     *
*  SUCCESS - if successful                                                     *
*  ACTION_FAIL - if failed                                                     *
*******************************************************************************/

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src);
/*******************************************************************************
* Merge src list into dest list                                                *
*                                                                              *
* Parameters:                                                                  *
*  dest - pointer to dest sorted list, not NULL                                *
*  src - pointer to src sorted list, not NULL                                  *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*                                                                              *
* WARNING: src list is emptied on execution of function                        *
*******************************************************************************/

sorted_iterator_t SortedListGetNext(sorted_iterator_t iter);
/*******************************************************************************
* Moves iterator forward one element                                           *
*                                                                              *
* Parameters:                                                                  *
*  iter - iterator of sorted list, not NULL                                    *
*                                                                              *
* Returns:                                                                     *
*  iterator                                                                    *
*******************************************************************************/

sorted_iterator_t SortedListGetPrevious(sorted_iterator_t iter);
/*******************************************************************************
* Moves iterator backward one element                                          *
*                                                                              *
* Parameters:                                                                  *
*  iter - iterator of sorted list, not NULL                                    *
*                                                                              *
* Returns:                                                                     *
*  iterator                                                                    *
*******************************************************************************/

void *SortedListGetData(sorted_iterator_t iter);
/*******************************************************************************
* Returns pointer to element data                                              *
*                                                                              *
* Parameters:                                                                  *
*  iter - iterator of sorted list, not NULL                                    *
*                                                                              *
* Returns:                                                                     *
*  pointer to element data                                                     *
*******************************************************************************/

bool SortedListIsSameIterator(
	const sorted_iterator_t iter1, const sorted_iterator_t iter2);
/*******************************************************************************
* Returns boolean value of if iter1 and iter2 are the same iterator            *
*                                                                              *
* Parameters:                                                                  *
*  iter1 - iterator of sorted list                                             *
*  iter2 - iterator of sorted list                                             *
*                                                                              *
* Returns:                                                                     *
*  TRUE - if iterators are the same                                            *
*  FALSE - if iteratos are not the same                                        *
*******************************************************************************/

#endif
