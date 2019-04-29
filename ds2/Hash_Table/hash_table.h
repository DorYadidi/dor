/*******************************************************************************
* NAME: Hash Table                                                             *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  25.12.18                                                      *
*******************************************************************************/
#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stddef.h>

#include "enum_rd58.h"
#include "function_pointers.h"

typedef struct hash_table_s hash_table_t;

hash_table_t *HashCreate(hash_function_t hash_function,
                         match_function_t match, size_t number_of_keys);
/*******************************************************************************
* Hash Table constractor                                                       *
*                                                                              *
* parameters                                                                   *
*  hash_function -                                                             *
*  match -                                                                     *
*  number_of_keys -                                                            *
*                                                                              *
* returns                                                                      *
*  Hash Table descriptor pointer                                               *
*******************************************************************************/

void HashDestroy(hash_table_t *hash);
/*******************************************************************************
* Frees all memory allocated for hash table                                    *
*                                                                              *
* parameters                                                                   *
*  hash - hash table descriptor pointer                                        *
*                                                                              *
* returns                                                                      *
*  none                                                                        *
*******************************************************************************/

size_t HashCount(const hash_table_t *hash);
/*******************************************************************************
* Counts the number of data points stored in hash table                        *
*                                                                              *
* parameters                                                                   *
*  hash - Hash Table descriptor pointer                                        *
*                                                                              *
* returns                                                                      *
*  number of data points stored in hash table                                  *
*******************************************************************************/

bool HashIsEmpty(const hash_table_t *hash);
/*******************************************************************************
* Check if hash table is empty                                                 *
*                                                                              *
* parameters                                                                   *
*  hash - hash table descriptor pointer                                         *
*                                                                              *
* returns                                                                      *
*  TRUE if empty                                                               *
*  FALSE if not empty                                                          *
*******************************************************************************/

status HashInsert(hash_table_t *hash, void *data);
/*******************************************************************************
*  Inserts a new data point into an hash table.                                *
*                                                                              *
* parameters                                                                   *
*  hash - hash table descriptor pointer                                        *
*  data - new data point. must not exist in table already                      *
*                                                                              *
* returns                                                                      *
*  SUCCESS on successful insert                                                *
*  MEMORY_ALLOCATION_FAIL if memory allocation failed                          *
*******************************************************************************/

void HashRemove(hash_table_t *hash, void *data);
/*******************************************************************************
*  Removes a data point from hash table. if doesn't exist does nothing.        *
*                                                                              *
* parameters                                                                   *
*  hash - hash table descriptor pointer                                        *
*  data - data point to be removed                                             *
*                                                                              *
* returns                                                                      *
*  none                                                                        *
*******************************************************************************/

void *HashFind(hash_table_t *hash, void *data_to_match);
/*******************************************************************************
*  Finds data point in hash table                                              *
*                                                                              *
* parameters                                                                   *
*  hash - hash table descriptor pointer                                        *
*  data_to_match - data to be compared with other data points in the table     *
*                                                                              *
* returns                                                                      *
*  Data point in table. NULL if doesn't exist                                  *
*******************************************************************************/

status HashForEach(hash_table_t *hash, action_function_t action, void *param);
/*******************************************************************************
*  Iterates action on each data point in hash table                            *
*                                                                              *
* parameters                                                                   *
*  hash - hash table descriptor pointer                                        *
*  action - action function to be call with each data point in the table       *
*  param - parameter to be transfered into action function                     *
*                                                                              *
* returns                                                                      *
*  SUCCESS on successful iteration over the entire hash table                  *
*  else returned status by action function                                     *
*******************************************************************************/

void HashStatistic(hash_table_t *hash);

#endif
