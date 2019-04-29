/*******************************************************************************
* NAME: Sorting Algorithms                                                     *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  08.12.18                                                      *
*******************************************************************************/

#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc free*/
#include "sorting_algorithms.h"

#define MAX_OPTIONS_NUM_BYTE 256
#define MASK_SIZE_T 0x00000000000000ff
#define ELEMENT(x) ((char *)elements + (x) * element_size)


static void Swap(char *ptr1, char *ptr2, size_t element_size)
{
	char temp_char;
	for(; (signed)element_size > 0; --element_size)
	{
		temp_char = *ptr1;
		*ptr1 = *ptr2;
		*ptr2 = temp_char;
		++ptr1;
		++ptr2;
	}
}

void BubbleSort(void *elements, size_t element_size, size_t element_count,
                compare_function_t compare)
{
	size_t i = 0;
	size_t j = 0;
	assert(elements != NULL);

	for (i = element_count -1; (signed)i >= 0; --i)
	{
		bool swap_flag = FALSE;
		void *param = NULL;
		void *next_param = NULL;

		for (j = 0; j < i; ++j)
		{
			param = (char *)elements + (j * element_size);
			next_param = (char *)elements + ((j + 1) * element_size);

			if (compare(param, next_param) > 0)
			{
				swap_flag = TRUE;
				Swap(param, next_param, element_size);
			}
		}

		if (FALSE == swap_flag)
		{
			break;
		}
    }
}

void InsertionSort(void *elements, size_t element_size, size_t element_count,
                   compare_function_t compare)
{
	size_t i = 0, j = 0;
   	assert(elements != NULL);

	for (i = 1; i < element_count; ++i)
	{
        j = i;
		while (j > 0 &&
			 compare((char *)elements + ((j - 1) * element_size),
                     (char *)elements + (j * element_size)) > 0)
		{
			Swap((char *)elements + ((j - 1) * element_size),
                 (char *)elements + (j * element_size), element_size);
			--j;
		}
	}
}

void SelectionSort(void *elements, size_t element_size, size_t element_count,
                   compare_function_t compare)
{
	size_t i = 0, j = 0;
	void *min = NULL;
	void *save_place = NULL;
   	assert(elements != NULL);

	for (i = 0; i < element_count -1; ++i)
	{
		min = (char *)elements + (i * element_size);
		save_place = min;

		for (j = i + 1; j < element_count; ++j)
		{
			if (compare(min, (char *)elements + (j * element_size)) > 0)
			{
				min = (char *)elements + (j * element_size);
			}
		}

		if (min != save_place)
		{
			Swap(min, save_place, element_size);
		}
	}
}
/*****************************************************************************/

void CountKeys(void *elements, size_t element_size,size_t element_count,
                     key_to_num_t key_to_num, void *param,
                     size_t range, size_t *counting_array)
{
	size_t  i = 0;

	for(i = 0; i < element_count; ++i)
	{
		++counting_array[key_to_num((char *)elements + (i * element_size), param)];
	}

	for(i = 1; i <= range; ++i)
	{
		counting_array[i] += counting_array[i - 1];
	}
}

void SortingTmpAarray(void *elements, size_t element_size,size_t element_count,
                     key_to_num_t key_to_num, void *param,
                     size_t *counting_array, void *sorted_array)
{
	void *tmp_element = NULL;
	void *tmp_sorted_array = NULL;
	size_t key = 0;
	size_t  i = 0;

	for(i = element_count - 1; (signed)i >= 0; --i)
	{
		tmp_element = (char *)elements + (i * element_size);
		key = key_to_num(tmp_element, param);
		--counting_array[key];
		tmp_sorted_array = (char *)sorted_array + (counting_array[key] * element_size);

		memcpy(tmp_sorted_array, tmp_element, element_size);
	}

}

status CountingSort(void *elements, size_t element_size,size_t element_count,
                  key_to_num_t key_to_num, void *param, size_t range)
{
	size_t *counting_array = calloc(sizeof(size_t), range + 1);
	void *sorted_array = malloc(element_size * element_count);

   	assert(elements != NULL);

	if (NULL == counting_array)
	{
		return (MEMORY_ALLOCATION_FAIL);
	}

	if(NULL == sorted_array)
	{
		free(counting_array);
		return (MEMORY_ALLOCATION_FAIL);
	}

	CountKeys(elements, element_size, element_count, key_to_num, param,
                     range, counting_array);

	SortingTmpAarray(elements, element_size, element_count, key_to_num, param,
                     counting_array, sorted_array);

	memcpy(elements, sorted_array, element_size * element_count);

	free(counting_array);
	free(sorted_array);

	return (SUCCESS);
}

/***************************************************************************/

typedef struct radix_param_s
{
	key_to_num_t key_to_num;
	void *param;
	size_t byte_count;

}radix_param_t;

size_t KeyToNumForRadix(void *element, void *radix_param)
{
	size_t num = ((radix_param_t *)radix_param)->
	             key_to_num(element, ((radix_param_t *)radix_param)->param);

	return (MASK_SIZE_T &
	       (*((char *)&num + ((radix_param_t *)radix_param)->byte_count)));
}

status RadixSort(void *elements, size_t element_size, size_t element_count,
               key_to_num_t key_to_num, void *param, size_t byte_count)
{
	size_t  i = 0;
	radix_param_t *radix_param = (radix_param_t *)malloc(sizeof(radix_param_t));

   	assert(elements != NULL);

	if(NULL == radix_param)
	{
		return (MEMORY_ALLOCATION_FAIL);
	}

	radix_param->key_to_num = key_to_num;
	radix_param->param = param;

	for(i = 0; i < byte_count; ++i)
	{
		radix_param->byte_count = i;

		if(CountingSort(elements, element_size, element_count,
		               KeyToNumForRadix, radix_param, MAX_OPTIONS_NUM_BYTE)
		               == MEMORY_ALLOCATION_FAIL)
		{
			return (MEMORY_ALLOCATION_FAIL);
		}
	}

	free(radix_param);

	return (SUCCESS);
}

/******************************************************************************/

static void Merge(void *elements, void *right, size_t element_size,
	              size_t element_count,
	              compare_function_t compare, char *temp_array)
{
	size_t left_index = 0, right_index = 0, i = 0;
	size_t left_len = (element_count / 2);
	size_t right_len = (element_count / 2 + element_count % 2);

	while (left_index < left_len && right_index < right_len)
	{
		if (compare((char *)elements + (element_size * left_index),
			(char *)right + (element_size * right_index)) >= 0) /*copy from right*/
		{
			memcpy(temp_array + (element_size * i),
				(char *)right + (element_size * right_index),
				element_size);
			++right_index;
			++i;
		}
		else /*copy from left*/
		{
			memcpy(temp_array + (element_size * i),
				(char *)elements + (element_size * left_index),
				element_size);
			++left_index;
		    ++i;
		}
	}

	if (left_index < left_len) /*if right finsh befor left*/
	{
		memcpy(temp_array + (element_size * i),
			(char *)elements + (element_size * left_index),
			element_size * (left_len - left_index));
	}

	if (right_index < right_len) /*if left finsh befor right*/
	{
		memcpy(temp_array + (element_size * i),
			(char *)right + (element_size * right_index),
			element_size * (right_len - right_index));
	}

	memcpy(elements, temp_array, element_count * element_size);
}

static void RecursiveMergeSort(void *elements, size_t element_size,
                                size_t element_count,
                        compare_function_t compare, char *temp_array)
{
    size_t middle = 0;
    void *right = NULL;

	if (element_count <= 1)
	{
		return;
	}

    middle = element_count / 2;
    right = (char *)elements + ((element_size * middle));

    RecursiveMergeSort(elements, element_size, middle,
	                                 compare, temp_array);

    RecursiveMergeSort(right, element_size, middle + (element_count % 2),
		compare, temp_array);


	Merge(elements, right, element_size, element_count, compare, temp_array);
}

status MergeSort(void *elements, size_t element_size,
	            size_t element_count, compare_function_t compare)
{
	char *temp_array = malloc(element_size * element_count);

	if (!temp_array)
	{
		return (MEMORY_ALLOCATION_FAIL);
	}

	RecursiveMergeSort(elements, element_size, element_count,
	                   compare, temp_array);

	free(temp_array);

	return (SUCCESS);
}

/***************************************************************************/
static void Heapify(void *elements, size_t element_size, size_t element_count,
				compare_function_t compare, size_t index)
{
	size_t right_index = (index * 2) + 2;
	size_t left_index = (index * 2) + 1;
	size_t largest = index;
	void *curr_data = (char *)elements + (index * element_size);
	void *left_data =  (char *)elements + (left_index * element_size);
	void *right_data =  (char *)elements + (right_index * element_size);
	void *largest_data = curr_data;

	if (element_count > left_index && compare(left_data, largest_data) > 0)
	{
		largest_data = left_data;
		largest = left_index;
	}

	if (element_count > right_index && compare(right_data, largest_data) > 0)
	{
		largest_data = right_data;
		largest = right_index;
	}

	if (largest_data != curr_data)
	{
		Swap(curr_data, largest_data, element_size);
		Heapify(elements, element_size, element_count, compare, largest);
	}
}

void HeapSort(void *elements, size_t element_size, size_t element_count,
				compare_function_t compare)
{
	int i = (element_count / 2) - 1;
	int j =  element_count - 1;
	assert(elements != NULL);

	for (	; i >= 0; --i) /*build max heap*/
	{
		Heapify(elements, element_size, element_count, compare, i);
	}

	for (	; j >= 0; --j) /*heap sort*/
	{
		Swap(elements, (char *)elements + (j * element_size), element_size);
		Heapify(elements, element_size, j, compare, 0);
	}
}
/******************************************************************************/

void QuickSort(void *elements, size_t element_size, size_t element_count,
				compare_function_t compare)
{
	size_t pivot = element_count - 1;
	size_t i = 0, smaller_element = 0;

	assert(elements != NULL);

	if (2 > element_count)
	{
		return;
	}

	for ( ; i < pivot; ++i)
	{
		if (0 >= compare(ELEMENT(i), ELEMENT(pivot)))
		{
			Swap(ELEMENT(smaller_element), ELEMENT(i), element_size);
			++smaller_element;
		}
	}

	Swap(ELEMENT(smaller_element), ELEMENT(pivot), element_size);
	QuickSort(elements, element_size, smaller_element, compare);
	QuickSort(ELEMENT(smaller_element + 1), element_size,
	          i - smaller_element, compare);
}

/****************************************************************************/
int *BSearchIterative(int sorted_array[], size_t array_size, int key)
{
	int low = 0;
	int high = array_size - 1;
	assert(sorted_array != NULL);

	while (low <= high)
	{
		int	middle = (low + high) / 2;

		if (sorted_array[middle] == key)
		{
			return (sorted_array + middle);
		}

		else if (key < sorted_array[middle])
		{
			high = middle - 1;
		}
		else
		{
			low = middle + 1;
		}
	}

	return (NULL);
}
/*****************************************************************************/

static int *FindRecursive(int sorted_array[], int low, int high, int key)
{
	int	middle = 0;

	if (low > high)
	{
		return (NULL);
	}

	middle = (low + high) / 2;

	if (sorted_array[middle] == key)
	{
		return (sorted_array + middle);
	}

	else if (key < sorted_array[middle])
	{
		return (FindRecursive(sorted_array, low, middle - 1, key));
	}
	else
	{
		return (FindRecursive(sorted_array, middle + 1, high, key));
	}
}

int *BSearchRecursive(int sorted_array[], size_t array_size, int key)
{
	int low = 0;
	int high = array_size - 1;
	assert(sorted_array != NULL);

	return (FindRecursive(sorted_array, low, high, key));
}
