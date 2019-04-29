#include <stdio.h> /*fclose, fopen, fgets, fseek*/


int main()
{
	int a = 5;
	int *p_a = &a;
	int x = 0;
	
	FILE *file = fopen("test_virtual.txt", "wb+");
	if (NULL == file)
	{
		return (0);
	}
	
	fwrite(&p_a ,sizeof(int *), 1, file);
	
	fclose(file);

	scanf("%d", &x);
	
	return (0);
}
