#include <stdio.h> /*fclose, fopen, fgets, fseek*/


int main()
{
	int *p_a = NULL;
	FILE *file = fopen("test_virtual.txt", "rb+");
	if (NULL == file)
	{
		return (0);
	}
	
	fread(&p_a, sizeof(int *), 1, file);
	
	printf("TheNumberIs  %d\n'", *p_a);
	
	fclose(file);

	
	return (0);
}
