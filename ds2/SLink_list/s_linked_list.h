#include <stdio.h>
#include "enum_rd58.h"

#ifndef _DS_S_LinkedList_H__
#define _DS_S_LinkedList_H__

/*******************************************************************************
* NAME: Singly Linked List                                                     *
*                                                                              *
* PURPOSE: Singly Linked List                                                  *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  12.11.18                                                      *
*******************************************************************************/

typedef struct sll_node_s sll_node_t;
typedef bool (*match_function_t)(void *data, void *param);
typedef status (*action_function_t)(void *data, void *param);

/******************************************************************************/

struct sll_node_s
{
	void *data;
	sll_node_t *next;
};

/******************************************************************************/

sll_node_t *SLinkedListCreate(void *data, sll_node_t *next);
/*******************************************************************************
* Creates singly linked list node and returns pointer to memory address of node*
*                                                                              *
* Parameters:                                                                  *
*  data- pointer to memory address containing node data                        *
*  next- pointer to memory address of next node, NULL if singleton             *
*                                                                              *
* Returns:                                                                     *
*  pointer to memory address of node                                           *
*******************************************************************************/

void SLinkedListDestroy(sll_node_t **head);
/*******************************************************************************
* Frees all nodes                                                              *
*                                                                              *
* Parameters:                                                                  *
*  head- pointer to first node of singly linked list, not NULL                 *
*                                                                              *
* Returns:                                                                     *
*  none                                                                        *
*******************************************************************************/

sll_node_t *SLinkedListInsert(sll_node_t *where, sll_node_t *new_node);
/*******************************************************************************
* Inserts node at location "where"                                             *
*                                                                              *
* Parameters:                                                                  *
*  where - pointer to node location where new node will be inserted, not NULL  *
*  new_node - pointer to node to be inserted, not NULL                         *
*                                                                              *
* Returns:                                                                     *
*  pointer to new_node                                                         *
*******************************************************************************/

sll_node_t *SLinkedListInsertAfter(sll_node_t *where, sll_node_t *new_node);
/*******************************************************************************
* Inserts node after location "where"                                          *
*                                                                              *
* Parameters:                                                                  *
*  where - pointer to node after which new node will be inserted, not NULL     *
*  new_node - pointer to node to be inserted, not NULL                         *
*                                                                              *
* Returns:                                                                     *
*  pointer to new_node                                                         *
*******************************************************************************/

sll_node_t *SLinkedListRemove(sll_node_t *where);
/*******************************************************************************
* Removes node at location "where"                                             *
*                                                                              *
* Parameters:                                                                  *
*  where - pointer to node that will be removed, not NULL                      *
*                                                                              *
* Returns:                                                                     *
*  pointer to removed node                                                     *
*******************************************************************************/

sll_node_t *SLinkedListRemoveAfter(sll_node_t *where);
/*******************************************************************************
* Removes node after location "where"                                          *
*                                                                              *
* Parameters:                                                                  *
*  where - pointer to node after which node will be removed, not NULL          *
*                                                                              *
* Returns:                                                                     *
*  pointer to removed node                                                     *
*******************************************************************************/

sll_node_t *SLinkedListFind(sll_node_t *head, match_function_t match, void *param);
/*******************************************************************************
* Uses match_function_t to find a node in the singly linked list                 *
*                                                                              *
* Parameters:                                                                  *
*  head - pointer to first node of singly linked list, not NULL                *
*  match - function to be used in determing which node to return               *
*  param - argument to be used in match_function_t                               *
*                                                                              *
* Returns:                                                                     *
*  pointer to memory address of node                                           *
*******************************************************************************/

sll_node_t *SLinkedListIntersection(sll_node_t *head1,sll_node_t *head2);
/*******************************************************************************
* Determines if two singly linked lists intersect                              *
*                                                                              *
* Parameters:                                                                  *
*  head1 - pointer to first node of singly linked list, not NULL               *
*  head2 - pointer to first node of singly linked list, not NULL               *
*                                                                              *
* Returns:                                                                     *
*  pointer to memory address of intersection                                   *
*******************************************************************************/

status SLinkedListForEach(sll_node_t *head, action_function_t action, void *param);
/*******************************************************************************
* Impelements action_function on each node of singly linked list               *
*                                                                              *
* Parameters:                                                                  *
*  head - pointer to first node of singly linked list, not NULL                *
*  action - function to be implemented for each node                           *
*  param - argument to be used in action_function                              *
*                                                                              *
* Returns:                                                                     *
*  SUCCESS - if successful                                                     *
*  ACTION_FAIL - if failed                                                     *
*******************************************************************************/

size_t SLinkedListGetSize(const sll_node_t *head);
/*******************************************************************************
* Returns current size of singly linked list                                   *
*                                                                              *
* Parameters:                                                                  *
*  head - pointer to first node of singly linked list, not NULL                *
*                                                                              *
* Returns:                                                                     *
*  current size of singly linked list                                          *
*******************************************************************************/

bool SLinkedListHasLoop(sll_node_t *head);
/*******************************************************************************
* Determines if singly linked list has a loop                                  *
*                                                                              *
* Parameters:                                                                  *
*  head - pointer to first node of singly linked list, not NULL                *
*                                                                              *
* Returns:                                                                     *
*  TRUE - if loop exists                                                       *
*  FALSE - if no loop                                                          *
*******************************************************************************/

sll_node_t *SLinkedListFlip(sll_node_t *head);
/*******************************************************************************
* Flips node order of singly linked list                                       *
*                                                                              *
* Parameters:                                                                  *
* head - pointer to first node of singly linked list, not NULL                 *
*                                                                              *
* Returns:                                                                     *
* pointer to memory address of first node                                      *
*******************************************************************************/

/*****************************************ERRORS*******************************/

#endif

