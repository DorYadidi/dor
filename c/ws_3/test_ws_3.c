#include <stdio.h>
#include "ws_3.c"






int main(int argc, char **argv, char **envp)

{
	char **p_env = envp;
	int count =0;
	int a;
	char **buffer = NULL;
	char **buffer_ptr = NULL;


	while (*p_env != 0)
	{
		++count;
		++p_env;
	}

	printf ("%d\n'", count);
	buffer = (char **)malloc((count+1) * sizeof(char *));

	buffer_ptr = buffer;

	DupEvn(envp, buffer);

	while (*buffer_ptr != 0)
	{
		free(*buffer_ptr);
		++buffer_ptr;
	}


	free(buffer);


	 a = Josephus(30);
	 printf("\n%d\n", a);

	 CDataTypes();

	return 0;


}
