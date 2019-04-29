/*******************************************************************************
* NAME: Hash Table                                                             *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  25.12.18                                                      *
*******************************************************************************/

#include <stdlib.h> /* free */
#include <ctype.h>
#include <stdio.h> /* fopen */
#include <string.h> /* strtok */
#include "test.h"
#include "function_pointers.h"
#include "hash_table.h"

#define CHARS_IN_DICT 971578
#define NUM_OF_KEYS 17577
#define MAX_INPUT 100


static size_t HashTranslation(const void *key)
{
	char temp[MAX_INPUT];
	size_t result = 5381;
	char *p_temp = NULL;

	strcpy(temp, key);
	p_temp = temp;

	while (*p_temp != '\0')
	{
		result = (result << 5) + result + *p_temp;
		++p_temp;
	}

	return (result % NUM_OF_KEYS);
}

static bool MatchString(void *data, void *param)
{
    if (0 == strcmp(data,param))
    {
        return (TRUE);
    }
    return (FALSE);
}

static char *CreateDictionary()
{
    FILE *fp = NULL;
    char *dict = (char *)calloc(sizeof(char), CHARS_IN_DICT);

    if (NULL == dict)
    {
        return (NULL);
    }

    fp = fopen("/usr/share/dict/american-english", "r");

    if (NULL == fp)
    {
        free(dict);
        dict = NULL;
        return (NULL);
    }

    fread(dict, sizeof(char), CHARS_IN_DICT, fp);
    fclose(fp);

    return (dict);
}

static void LoadDictToHash(hash_table_t *hash, char *dict)
{
    char *delim = "\n";
    char *token = NULL;

    token = strtok(dict, delim);

    while (token != NULL)
    {
        HashInsert(hash, token);
        token = strtok(NULL, delim);
    }
}

void SpellCheck()
{
    char *input = NULL;
    char *dictionar = NULL;
    hash_table_t *hash = NULL;

    input = (char *)calloc(sizeof(char), MAX_INPUT);
    if (NULL == input)
    {
        return;
    }

    hash = HashCreate(HashTranslation, MatchString, NUM_OF_KEYS);
    if (NULL == hash)
    {
        free(input);
        input = NULL;
        return;
    }

    dictionar = CreateDictionary();
    if (NULL == dictionar)
    {
        free(input);
        input = NULL;
        free(hash);
        hash = NULL;
        return;
    }

    LoadDictToHash(hash, dictionar);

    while (0 != strcmp(input,"exit"))
    {
        printf( "Enter input :");
        scanf("%s", input);

        if(NULL != HashFind(hash,input))
        {
            printf("OK\n");
        }
        else
        {
            printf("Wrong spelling\n");
        }
    }

	HashStatistic(hash);

	free(input);
	input = NULL;
	free(dictionar);
	dictionar = NULL;
	HashDestroy(hash);
}

int main()
{
	SpellCheck();

	return (0);
}
