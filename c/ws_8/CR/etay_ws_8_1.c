/*******************************************************************************
*                                                                              *
*                             File name   : ws_8_1.c                           *
*                             Author      : Etay Pennner                       *
*                             Created     : 25/10/2018                         *
*                             Last updated: 28/10/2018                         *
*                                                                              *
*******************************************************************************/

#include <stdlib.h> /*malloc realloc free*/
#include <string.h> /*strlen strcat*/
#include <stdio.h>  /*fprintf*/
#include "etay_ws_8_1.h"

struct s_polymorphism
{
	void *data;
	add_type Add;
	print_type Print;
	free_type Free;
};

enum
{
	OK,
	MALLOC_FAIL
};

int CreateStructArray(poly_type **array_p);
int TestMain(int number_to_add);

int main()
{
	TestMain(3434);
	
	return (0);
}

int TestMain(int number_to_add)
{
	int i = 0;
	poly_type *array = NULL;
	
	if (CreateStructArray(&array))
	{
		fprintf(stderr, "Malloc failed");
		return MALLOC_FAIL;
	}
	
	for (i = 0; i < 3; ++i)
	{
		if (array[i].Add(&array[i], number_to_add))
		{
			fprintf(stderr, "Malloc failed");
			free(array);
			return MALLOC_FAIL;
		}
		
		array[i].Print(array[i]);
	}
	
	printf("\n");
	
	for (i = 0; i < 3; ++i)
	{
		array[i].Free(array[i]);
	}
	
	free(array);
	
	return OK;
}

int CreateStructArray(poly_type **array_p)
{
	poly_type *array = NULL;
	*array_p = (poly_type *)malloc(sizeof(poly_type) * 3);
	
	if (!array_p)
	{
		return MALLOC_FAIL;
	}
	
	array = *array_p;
	
	array[0].data = (int)0;
	*(float *)&array[1].data = 0;
	
	if (!(array[2].data = malloc(1)))
	{
		free(array);
		return MALLOC_FAIL;
	}
	
	*(char *)(array[2].data) = '\0';
	
	array[0].Add = AddIntToInt;
	array[1].Add = AddIntToFloat;
	array[2].Add = AddIntToString;
	
	array[0].Print = PrintInt;
	array[1].Print = PrintFloat;
	array[2].Print = PrintString;
	
	array[0].Free = FreeIntFloat;
	array[1].Free = FreeIntFloat;
	array[2].Free = FreeString;

	return OK;
}

int AddIntToInt(poly_type *pt, int n)
{
	void **data = &pt->data;
	**(int **)&data += n;
	
	return OK;
}

int AddIntToFloat(poly_type *pt, int n)
{
	void **data = &pt->data;
	**(float **)&data += (float)n;
	
	return OK;
}

int AddIntToString(poly_type *pt, int n)
{
	int number_of_digits;
	size_t length = strlen(pt->data);
	char *temp_str = malloc(10);
	number_of_digits = sprintf(temp_str, "%d", n);
	
	if (!temp_str)
	{
		return MALLOC_FAIL;	
	}
	
	if (!(pt->data = realloc(pt->data,
		sizeof(char) * (length + number_of_digits + 1))))
	{
		free(temp_str);
		free(pt->data);
		return MALLOC_FAIL;
	}
	
	strcat(pt->data, temp_str);
	free(temp_str);
	
	return OK;
}

void PrintInt(poly_type pt)
{
	printf("%d\n", *(int *)&pt.data);
}

void PrintFloat(poly_type pt)
{
	printf("%f\n", *(float *)&pt.data);
}

void PrintString(poly_type pt)
{
	printf("%s\n", (char *)pt.data);
}

void FreeIntFloat(poly_type pt)
{
	(void)pt;
}

void FreeString(poly_type pt)
{
	free(pt.data);
}
