/*******************************************************************************
* NAME: Avl tree                                                               *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  23.12.18                                                      *
*******************************************************************************/
#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <stddef.h>

#include "enum_rd58.h"
#include "function_pointers.h"
#include "d_linked_list.h"

typedef struct avl_tree_s avl_tree_t;

avl_tree_t *AvlTreeCreate(compare_function_t compare);
/*******************************************************************************
* Avl tree constractor                                                         *
*                                                                              *
* parameters                                                                   *
*  compare - compare dunction to determine order of data points in the tree    *
*                                                                              *
* returns                                                                      *
*  Avl tree descriptor pointer                                                 *
*******************************************************************************/

void AvlTreeDestroy(avl_tree_t *avl);
/*******************************************************************************
* Frees all memory allocated for Avl tree                                      *
*                                                                              *
* parameters                                                                   *
*  avl - Avl tree descriptor pointer                                           *
*                                                                              *
* returns                                                                      *
*  none                                                                        *
*******************************************************************************/

size_t AvlTreeCount(const avl_tree_t *avl);
/*******************************************************************************
* Counts the number of data points stored in Avl tree                          *
*                                                                              *
* parameters                                                                   *
*  avl - Avl tree descriptor pointer                                           *
*                                                                              *
* returns                                                                      *
*  number of data points stored in Avl tree                                    *
*******************************************************************************/

bool AvlTreeIsEmpty(const avl_tree_t *avl);
/*******************************************************************************
* Check if Avl tree is empty                                                   *
*                                                                              *
* parameters                                                                   *
*  avl - Avl tree descriptor pointer                                           *
*                                                                              *
* returns                                                                      *
*  TRUE if empty                                                               *
*  FALSE if not empty                                                          *
*******************************************************************************/

status AvlTreeInsert(avl_tree_t *avl, void *data);
/*******************************************************************************
*  Inserts a new data point into an Avl tree. Keeps tree balanced              *
*                                                                              *
* parameters                                                                   *
*  avl - Avl tree descriptor pointer                                           *
*  data - new data point. must not exist in tree already                       *
*                                                                              *
* returns                                                                      *
*  SUCCESS on successful insert                                                *
*  MEMORY_ALLOCATION_FAIL if memory allocation faild                           *
*******************************************************************************/

void AvlTreeRemove(avl_tree_t *avl, const void *data);
/*******************************************************************************
*  Removes a data point from Avl tree. if doent exist does nothing             *
*                                                                              *
* parameters                                                                   *
*  avl - Avl tree descriptor pointer                                           *
*  data - data point to be removed                                             *
*                                                                              *
* returns                                                                      *
*  none                                                                        *
*******************************************************************************/

void *AvlTreeFind(avl_tree_t *avl, const void *data_to_match);
/*******************************************************************************
*  Finds data point in Avl tree                                                *
*                                                                              *
* parameters                                                                   *
*  avl - Avl tree descriptor pointer                                           *
*  data_to_match - data to be compared with other data points in the tree      *
*                                                                              *
* returns                                                                      *
*  Data point in tree. NULL if doesn't exist                                   *
*******************************************************************************/

status AvlTreeForEach(avl_tree_t *avl, action_function_t action, void *param);
/*******************************************************************************
*  Iterates action on each data point in Avl tree                              *
*                                                                              *
* parameters                                                                   *
*  avl - Avl tree descriptor pointer                                           *
*  action - action function to be call with each data point in the tree        *
*  param - parameter to be transfered into action function                     *
*                                                                              *
* returns                                                                      *
*  SUCCESS on successful iteration over the entire tree                        *
*  status returned by action function else                                     *
*******************************************************************************/

d_linked_list_t *AvlTreeMultiFind(
	avl_tree_t *avl, match_function_t match, void *param
);
/*******************************************************************************
* Finds multiple data points according to a match function                     *
*                                                                              *
* parameters                                                                   *
*  avl - Avl tree descriptor pointer                                           *
*  match - match function to determine what data points are found              *
*  param - parameter to be transfered into match function                      *
*                                                                              *
* returns                                                                      *
*  Double linked list descriprot pointer that contains all found data points   *
*******************************************************************************/

void AvlTreeMultiRemove(avl_tree_t *avl, match_function_t match, void *param);
/*******************************************************************************
* Finds multiple data points according to a match function and                 *
*  removes the from the tree                                                   *
*                                                                              *
* parameters                                                                   *
*  avl - Avl tree descriptor pointer                                           *
*  match - match function to determine what data points are found              *
*  param - parameter to be transfered into match function                      *
*                                                                              *
* returns                                                                      *
*  none                                                                        *
*******************************************************************************/

size_t AvlTreeHeight(const avl_tree_t *avl);
/*******************************************************************************
*  returns the hight of an Avl tree                                            *
*                                                                              *
* parameters                                                                   *
*  avl - Avl tree descriptor pointer                                           *
*                                                                              *
* returns                                                                      *
*  hight of an Avl tree                                                        *
*******************************************************************************/

#endif
