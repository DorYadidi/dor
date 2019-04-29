/*******************************************************************************
* NAME: shuffle and sort dictionary                                            *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  25.12.18                                                      *
*******************************************************************************/

#include <stdlib.h> /* free */
#include <ctype.h>
#include <stdio.h> /* fopen */
#include <string.h> /* strtok */
#include "sorting_algorithms.h"

#define WORD_IN_DICT 99155
#define REPEAT_TEST 555

static char *CreateArrayStringDictionary();
static char **LoadDictionary(char *data, size_t *dictionary_len);
static int ComperForShuffle(const void *data1, const void *data2);
static void ShuffleArray(char **dictionary, size_t dictionary_len);
static int ComperForSort(const void *data1, const void *data2);
void *ThreadSort(void *dictionary, size_t dictionary_len);

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

void *ThreadSort(void *dictionary, size_t dictionary_len)
{
	MergeSort(dictionary, sizeof(char *), dictionary_len, ComperForSort);

	return (NULL);
}

int main()
{
	size_t i = 0, j = 0;
	char *data = NULL;
	size_t dictionary_len = 0;
	char **dictionary = NULL;
	char **temp_dictionary = NULL;


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
		ThreadSort(dictionary, dictionary_len);
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
