/*******************************************************************************
* NAME: binary sorted tree                                                     *
*                                                                              *
* AUTHOR: Dor Yadidi                                                         *
* DATE UPDATED:  11.12.18                                                      *
*******************************************************************************/

#ifndef __BINARY_SORTED_TREE_H__
#define __BINARY_SORTED_TREE_H__

#include <stdlib.h> /* size_t */

#include "enum_rd58.h"
#include "function_pointers.h"

typedef struct bst_s bst_t;
typedef struct bst_iterator_s
{
	void *info;
} bst_iterator_t;

extern bst_iterator_t BST_ITERATOR_NOT_FOUND;

bst_t *BSTCreate(compare_function_t compare);
/*******************************************************************************
* Creates binary tree                                                          *
*                                                                              *
* Parameters:                                                                  *
*  compare - comparison function                                               *
*                                                                              *
* Returns:                                                                     *
*  pointer to memory address of tree                                           *
*******************************************************************************/

void BSTDestroy(bst_t *bst);
/*******************************************************************************
* Frees binary tree                                                            *
*                                                                              *
* Parameters:                                                                  *
*  bst - pointer to binary tree, not NULL                                      *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

size_t BSTGetSize(bst_t *bst);
/*******************************************************************************
* Returns current size of binary tree                                          *
*                                                                              *
* Parameters:                                                                  *
*  bst - pointer to binary tree, not NULL                                      *
*                                                                              *
* Returns:                                                                     *
*  current size of binary tree                                                 *
*******************************************************************************/

bool BSTIsEmpty(bst_t *bst);
/*******************************************************************************
* Determines if binary tree is empty                                           *
*                                                                              *
* Parameters:                                                                  *
*  bst - pointer to binary tree, not NULL                                      *
*                                                                              *
* Returns:                                                                     *
*  TRUE - if list is empty                                                     *
*  FALSE - if list is not empty                                                *
*******************************************************************************/

bst_iterator_t BSTBegin(bst_t *bst);
/*******************************************************************************
* Returns iterator to the begining of binary tree                              *
*                                                                              *
* Parameters:                                                                  *
*  bst - pointer to binary tree, not NULL, not empty                           *
*                                                                              *
* Returns:                                                                     *
*  returns iterator beyond the data inserted                                   *
*******************************************************************************/

bst_iterator_t BSTEnd(bst_t *bst);
/*******************************************************************************
* Returns iterator to the end of binary tree                                   *
*                                                                              *
* Parameters:                                                                  *
*  bst - pointer to binary tree, not NULL, not empty                           *
*                                                                              *
* Returns:                                                                     *
*  iterator to head of binary tree, go to previous for the root                *
*******************************************************************************/

bst_iterator_t BSTInsert(bst_t *bst, void *data);
/*******************************************************************************
* Inserts element to binary tree                                               *
*                                                                              *
* Parameters:                                                                  *
*  bst - pointer to binary tree, not NULL, not empty                           *
*  data - pointer to memory address of data                                    *
*                                                                              *
* Returns:                                                                     *
*  iterator to inserted element                                                *
*******************************************************************************/

void BSTRemove(bst_iterator_t iter);
/*******************************************************************************
* Removes element from binary tree at iterator location                        *
*                                                                              *
* Parameters:                                                                  *
*  iter - iterator of binary tree, not NULL                                    *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

bst_iterator_t BSTFind(bst_t *bst, void *data);
/*******************************************************************************
* Uses match function to find an element in a binary tree                      *
*                                                                              *
* Parameters:                                                                  *
*  bst - pointer to binary tree, not NULL                                      *
*  data - data to be used in match function                                    *
*                                                                              *
* Returns:                                                                     *
*  iterator to matched element, if not found iterator info is NULL             *
*******************************************************************************/

status BSTForEach
	(bst_t *bst, action_function_t action, void *param);
/*******************************************************************************
* Impelements action function on each element of doubly linked list            *
*                                                                              *
* Parameters:                                                                  *
*  bst - pointer to binary tree, not NULL                                      *
*  action - function to be implemented on each element of list                 *
*  param - argument to be used in action function                              *
*                                                                              *
* Returns:                                                                     *
*  SUCCESS - if successful                                                     *
*  ACTION_FAIL - if failed                                                     *
*******************************************************************************/

bst_iterator_t BSTGetNext(bst_iterator_t iter);
/*******************************************************************************
* Moves iterator forward one element                                           *
*                                                                              *
* Parameters:                                                                  *
*  iter - iterator of binary tree, not NULL                                    *
*                                                                              *
* Returns:                                                                     *
*  iterator                                                                    *
*******************************************************************************/

bst_iterator_t BSTGetPrevious(bst_iterator_t iter);
/*******************************************************************************
* Moves iterator backward one element                                          *
*                                                                              *
* Parameters:                                                                  *
*  iter - iterator of binary tree, not NULL                                    *
*                                                                              *
* Returns:                                                                     *
*  iterator                                                                    *
*******************************************************************************/

void *BSTGetData(bst_iterator_t iter);
/*******************************************************************************
* Returns pointer to element data                                              *
*                                                                              *
* Parameters:                                                                  *
*  iter - iterator of binary tree, not NULL                                    *
*                                                                              *
* Returns:                                                                     *
*  pointer to element data                                                     *
*******************************************************************************/

bool BSTIsSameIterator(
	const bst_iterator_t iter1, const bst_iterator_t iter2);
/*******************************************************************************
* Returns boolean value of if iter1 and iter2 are the same iterator            *
*                                                                              *
* Parameters:                                                                  *
*  iter1 - iterator of binary tree                                             *
*  iter2 - iterator of binary tree                                             *
*                                                                              *
* Returns:                                                                     *
*  TRUE - if iterators are the same                                            *
*  FALSE - if iteratos are not the same                                        *
*******************************************************************************/

#endif
