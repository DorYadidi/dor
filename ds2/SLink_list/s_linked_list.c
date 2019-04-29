#include <stdio.h>
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/
#include "s_linked_list.h"


/*******************************************************************************
* NAME: Singly Linked List                                                     *
*                                                                              *
* PURPOSE: Singly Linked List                                                  *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  13.11.18                                                      *
*******************************************************************************/

sll_node_t *SLinkedListCreate(void *data, sll_node_t *next)
{
	sll_node_t *head = (sll_node_t *)malloc(sizeof(sll_node_t)*1);
	if(NULL == head)
	{
		return (NULL);
	}

	head->data = data;
	head->next = next;

	return (head);
}

void SLinkedListDestroy(sll_node_t **head)
{
	sll_node_t *current = *head;
	sll_node_t *next = NULL;

	assert(head != NULL);

	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

sll_node_t *SLinkedListInsert(sll_node_t *where, sll_node_t *new_node)
{
	sll_node_t tmp;
	assert(where != NULL && new_node != NULL);

	tmp.data = where->data;
	tmp.next = NULL;
	new_node->next = where->next;
	where->next = new_node;
	where->data = new_node->data;
	new_node->data = tmp.data;

	return (where);
}

sll_node_t *SLinkedListInsertAfter(sll_node_t *where, sll_node_t *new_node)
{
	assert(where != NULL && new_node != NULL);
	new_node->next = where->next;
	where->next = new_node;
	return (new_node);

}

sll_node_t *SLinkedListRemove(sll_node_t *where)
{
	sll_node_t *tmp = NULL;
	sll_node_t tmp_data;
	assert(where != NULL);

	tmp = where->next;
	where->next = tmp->next;

	tmp_data.data = tmp->data;
	tmp->data = where->data;
	where->data = tmp_data.data;
	tmp->next = NULL;

	return (tmp);
}

sll_node_t *SLinkedListRemoveAfter(sll_node_t *where)
{
	sll_node_t *tmp = NULL;
	assert(where != NULL);

	tmp = where->next;
	where->next = tmp->next;
	tmp->next = NULL;

	return (tmp);
}

sll_node_t *SLinkedListIntersection(sll_node_t *head1, sll_node_t *head2)
{
	sll_node_t *tmp1 = head1;
	sll_node_t *tmp2 = head2;
	assert(head1 != NULL && head2 != NULL);

	while(tmp2)
	{
		while(tmp1)
		{
			if(tmp1 == tmp2)
			{
				return (tmp1);
			}

			tmp1 = tmp1->next;
		}

		tmp1 = head1;
		tmp2 = tmp2->next;
	}

	return (NULL);
}

size_t SLinkedListGetSize(const sll_node_t *head)
{
	int count = 0;
	while (head != NULL)
	{
		++count;
		head = head->next;
    }

    return (count);
}

bool SLinkedListHasLoop(sll_node_t *head)
{
	sll_node_t *slow_p = head;
	sll_node_t *fast_p = head;

	assert(head != NULL);

	while (slow_p && fast_p && fast_p->next)
	{
		slow_p = slow_p->next;
		fast_p = fast_p->next->next;

		if(slow_p == fast_p)
		{
			return (TRUE);
		}
	}

	return (FALSE);
}

sll_node_t *SLinkedListFlip(sll_node_t *head)
{
	sll_node_t *current = head;
	sll_node_t *prev = NULL, *next = NULL;

	assert(head != NULL);

	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	head = prev;
	return (head);
}

sll_node_t *SLinkedListFind(sll_node_t *head, match_function_t match, void *param)
{
	sll_node_t *tmp = head;
	assert(head != NULL);

	while(tmp)
	{
		if(match(tmp->data, param) == TRUE)
		{
			return (tmp);
		}

		tmp = tmp->next;
	}

	return (NULL);
}

status SLinkedListForEach(sll_node_t *head, action_function_t action, void *param)
{
	sll_node_t *tmp = head;
	assert(head != NULL);

	while(tmp)
	{
		if(action(tmp->data, param) == ACTION_FAIL)
		{
			return (ACTION_FAIL);
		}

		tmp = tmp->next;
	}

	return (SUCCESS);
}
