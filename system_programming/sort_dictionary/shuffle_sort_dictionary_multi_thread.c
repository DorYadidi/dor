/*******************************************************************************
* NAME: shuffle and sort dictionary                                            *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  25.12.18                                                      *
*******************************************************************************/

#include <stdlib.h> /* free */
#include <ctype.h>
#include <stdio.h> /* fopen */
#include <string.h> /* strtok strcmp*/
#include <pthread.h>
#include "sorting_algorithms.h"

#define WORD_IN_DICT 11000
#define NUMBER_OF_THREADS 2
#define REPEAT_TEST 650

#define SYS_CALL_PASS(sys_call_function)      \
	if (-1 == sys_call_function)         \
	{                                    \
		exit(1);                         \
	}

pthread_mutex_t lock;
pthread_mutex_t cond_lock;
pthread_cond_t cv;

typedef struct args_dic_len_s
{
	char **dictionary;
	size_t dic_len;
	size_t *counter;

} args_dic_len_t;

static char *CreateArrayStringDictionary();
static char **LoadDictionary(char *data, size_t *dictionary_len);
static int ComperForShuffle(const void *data1, const void *data2);
static void ShuffleArray(char **dictionary, size_t dictionary_len);
static int ComperForSort(const void *data1, const void *data2);
static void MeageChunk(void *elements, size_t element_size,
				  compare_function_t compare, void *temp_array,
				  size_t left_array_count, size_t right_array_count);
void *MergeDictionary(args_dic_len_t *args_dic_len, size_t dictionary_len);
static void SortAndMerge(char **dictionary, size_t dictionary_len, size_t *counter);


static char *CreateArrayStringDictionary()
{
	size_t file_size = 0;
    FILE *fp = NULL;
    char *data = NULL;

    fp = fopen("/usr/share/dict/american-english", "r");

    if (NULL == fp)
    {
        return (NULL);
    }

	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	data = (char *)calloc(sizeof(char), file_size);
	if (NULL == data)
	{
		fclose(fp);
		return (NULL);
	}

    if (file_size != fread(data, sizeof(char), file_size, fp))
	{
		free(data);
        data = NULL;
		fclose(fp);
		return (NULL);
	}

    fclose(fp);

    return (data);
}

static char **LoadDictionary(char *data, size_t *dictionary_len)
{
    char *delim = "\n";
    char *token = NULL;
	size_t i = 0;
	char **dictionary = (char **)calloc(sizeof(char *), WORD_IN_DICT);

	if (NULL == dictionary)
    {
        return (NULL);
    }

	*dictionary_len = 0;

    token = strtok(data, delim);

    for (i = 0; i < WORD_IN_DICT; ++i)
    {
		if (NULL != token)
		{
			if ((*token >= 'a' && *token <= 'z') ||
				(*token >= 'A' && *token <= 'Z'))
			{
				dictionary[i] = token;
				++*dictionary_len;

			}
		}

        token = strtok(NULL, delim);
    }

	return (dictionary);
}

/*****************************shuffle******************************************/

static int ComperForShuffle(const void *data1, const void *data2)
{
	return((*(*(char **)data1 + 1)) - *(*(char **)data2 + 1));
}

static void ShuffleArray(char **dictionary, size_t dictionary_len)
{
	MergeSort(dictionary, sizeof(char *), dictionary_len, ComperForShuffle);
}

/********************************sort******************************************/

static int ComperForSort(const void *data1, const void *data2)
{
	return(strcmp(*(char **)data1, *(char **)data2));
}

static void MeageChunk(void *elements, size_t element_size,
				  compare_function_t compare, void *temp_array,
				  size_t left_array_count, size_t right_array_count)
{
	size_t i = 0, j = 0;
	void *left_sub_array = temp_array;
	void *right_sub_array = (char *)temp_array + (left_array_count * element_size);
	memcpy(left_sub_array, elements, element_size * (left_array_count + right_array_count));

	while (j < left_array_count && i < right_array_count)
	{
		if (compare(right_sub_array, left_sub_array) > 0)
		{
			memcpy(elements, left_sub_array, element_size);
			left_sub_array = (char *)left_sub_array + element_size;
			++j;
		}
		else
		{
			memcpy(elements, right_sub_array, element_size);
			right_sub_array = (char *)right_sub_array + element_size;
			++i;
		}

		elements = (char *)elements + element_size;
	}

	while (j < left_array_count)
	{
		memcpy(elements, left_sub_array, element_size);
		left_sub_array = (char *)left_sub_array + element_size;
		++j;
		elements = (char *)elements + element_size;
	}

	while (i < right_array_count)
	{
		memcpy(elements, right_sub_array, element_size);
		right_sub_array = (char *)right_sub_array + element_size;
		++i;
		elements = (char *)elements + element_size;
	}
}

void *MergeDictionary(args_dic_len_t *args_dic_len, size_t dictionary_len)
{
	int i = 0;
	void *temp_buffer = NULL;
	size_t dict_size = args_dic_len[0].dic_len;
	temp_buffer = (void *)malloc(sizeof(void *) * dictionary_len);

	for (i = 0; i < NUMBER_OF_THREADS - 1; ++i)
	{
		MeageChunk(args_dic_len[0].dictionary, sizeof(void *), ComperForSort, temp_buffer,
			  dict_size + (i * dict_size), args_dic_len[i + 1].dic_len);
	}

	free(temp_buffer);
	temp_buffer = NULL;
	return (NULL);
}

void *ThreadSort(void *args_dic_len)
{
	args_dic_len_t dic;
	dic = *(args_dic_len_t *)args_dic_len;

	MergeSort(dic.dictionary, sizeof(char *), dic.dic_len, ComperForSort);

	pthread_mutex_lock(&lock);
	--*dic.counter;
	pthread_cond_signal(&cv);
	pthread_mutex_unlock(&lock);

	return (NULL);
}

static void SortAndMerge(char **dictionary, size_t dictionary_len, size_t *counter)
{
	size_t i = 0;
	pthread_t sort_dic_chunk[NUMBER_OF_THREADS];
	size_t dic_chunk_len = dictionary_len / NUMBER_OF_THREADS;
	size_t last_chunk_res = dic_chunk_len + (dictionary_len % NUMBER_OF_THREADS);
	args_dic_len_t *dic_struct = NULL;

	dic_struct = (args_dic_len_t *)malloc(sizeof(args_dic_len_t) * NUMBER_OF_THREADS);
	if (NULL == dic_struct)
	{
		exit (1);
	}

	*counter = NUMBER_OF_THREADS;

	for (i = 0; i < NUMBER_OF_THREADS - 1; ++i)
	{
		dic_struct[i].dictionary = dictionary + (i * dic_chunk_len);
		dic_struct[i].dic_len = dic_chunk_len;
		dic_struct[i].counter = counter;
	}

	dic_struct[i].dictionary = dictionary + (i * dic_chunk_len);
	dic_struct[i].dic_len = last_chunk_res;
	dic_struct[i].counter = counter;

	for (i = 0; i < NUMBER_OF_THREADS; ++i)
	{
		SYS_CALL_PASS(pthread_create(&sort_dic_chunk[i], NULL,
			     ThreadSort, &dic_struct[i]));
		SYS_CALL_PASS(pthread_detach(sort_dic_chunk[i]));
	}

	pthread_mutex_lock(&cond_lock);
	while (*dic_struct[0].counter != 0)
	{
		pthread_cond_wait(&cv, &lock);
	}
	pthread_mutex_unlock(&cond_lock);

	MergeDictionary(dic_struct, dictionary_len);

	free(dic_struct);
	dic_struct = NULL;
}

/******************************************************************************/

int main()
{
	size_t i = 0, j = 0;
	char *data = NULL;
	size_t dictionary_len = 0;
	char **dictionary = NULL;
	char **temp_dictionary = NULL;
	size_t counter = NUMBER_OF_THREADS;


	data = CreateArrayStringDictionary();
	if (NULL == data)
	{
		return (1);
	}

	dictionary = LoadDictionary(data, &dictionary_len);
	if (NULL == dictionary)
	{
		free (data);
		data = NULL;
		return (1);
	}

	temp_dictionary = (char **)calloc(sizeof(char *), WORD_IN_DICT);
	if (NULL == temp_dictionary)
	{
		free (dictionary);
		dictionary = NULL;
		free (data);
		data = NULL;
		return (1);
	}

	memcpy(temp_dictionary, dictionary, WORD_IN_DICT * sizeof(char *));

	for (i = 0; i < REPEAT_TEST; ++i)
	{
		ShuffleArray(dictionary, dictionary_len);
		SortAndMerge(dictionary, dictionary_len, &counter);
	}

	for(j = 0; j < dictionary_len; ++j)
	{
		if (strcmp(dictionary[j], temp_dictionary[j]) != 0)
		{
			printf("[TEST FAIL]\n");
			return (1);
		}
	}

	printf("[OK]\n");

	free(dictionary);
	dictionary = NULL;
	free(temp_dictionary);
	temp_dictionary = NULL;
	free(data);
	data = NULL;

	return (0);
}
