#include <stdio.h> /*printf, sprintf*/
#include <stdlib.h>  /*calloc, free, realloc*/
#include <string.h> /* strlen */
#include "ws_8_1.h"

struct s_polymorphism
{
	void *data;
	add_type add;
	print_type print;
	free_type free_memory;

};

int Test_Poly(int data_user)
{
	int j = 0;
	poly_type *pt = calloc(3,sizeof(poly_type));
	if (NULL == pt)
	{
		return 0;
	}
	
	pt[0].add = AddIntToInt;
	pt[0].print = PrintInt;
	pt[0].free_memory = FreeIntFloat;

	pt[1].add = AddIntToFloat;
	pt[1].print = PrintFloat;
	pt[1].free_memory = FreeIntFloat;

	pt[2].data = calloc(5,sizeof(char));
	if (NULL == pt[2].data)
	{
		return 0;
	}
	pt[2].add = AddIntToString;
	pt[2].print = PrintString;
	pt[2].free_memory = FreeString;

	
	for (j = 0; j < 3; j++)
	{
		pt[j].add(&pt[j], data_user);
		pt[j].print(pt[j]);
		pt[j].free_memory(pt[j]);

	}

	free(pt);		
	return 0;
}

int AddIntToInt(poly_type *pt , int n)
{
	void **data = &(*pt).data;
	**(int **)&data += n;
	
	return 1;
}

int AddIntToFloat(poly_type *pt, int n)
{
	void **data = &(*pt).data;
	**(float **)&data += n;
	
	return 1;
}

int AddIntToString(poly_type *pt, int n)
{
	void **data = &(*pt).data;
	int count = 0;
	int n_new = n;
	int len_data = strlen((char *)*data);
	char *tmp = NULL;
	while (n_new != 0)
	{
		++count;
		n_new = n_new / 10;
		
	}
	
	tmp = (char *)malloc(count+1);
	if (NULL == tmp)
	{
		return 0;
	}
	
	*data = realloc(*data, count + len_data +1);
	if (NULL == data)
	{
		printf("Realloc fail\n");
		return 0;
	}
	
	sprintf(tmp, "%d", n);
	strcat(*data, tmp);
	
	free(tmp);
	
	return 1;
}

void PrintInt(poly_type pt)
{
	printf("Int %d\n", *(int *)&(pt.data));
}

void PrintFloat(poly_type pt)
{
	printf("Float %f\n", *(float *)&(pt.data));
}

void PrintString(poly_type pt)
{
	
	printf("String %s\n'", (char *)(pt.data));
}


void FreeIntFloat(poly_type pt)
{
	(void) pt;
}

void FreeString(poly_type pt)
{
	free(pt.data);
}

int main ()
{
	int data_user = 32;
	Test_Poly(data_user);

	return 0;
}
