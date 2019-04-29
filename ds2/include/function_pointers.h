#pragma once

/*******************************************************************************
* NAME: function pointers                                                      *
*                                                                              *
* PURPOSE: define custom function pointers for rd58 projects                   *
*                                                                              *
* AUTHOR: Etay Penner                                                          *
* DATE UPDATED:  23.12.18                                                      *
*******************************************************************************/

#include "enum_rd58.h"

typedef bool (*match_function_t)(void *data, void *param);
typedef status (*action_function_t)(void *data, void *param);
typedef status (*task_function_t)(void *param);
typedef void (*destroy_task_function_t)(void *param);
typedef int (*compare_function_t)(const void *data1, const void *data2);
typedef size_t (*hash_function_t)(const void *data);
