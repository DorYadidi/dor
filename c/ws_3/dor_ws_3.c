/*
WS_3
Dor yadidi
14.10
*/

/* Code Review:

    1. function headers should include description of arguments and return
        values.
    2. <ctype.h> not included
    3. CC at lines: 23, 40, 41, 42, 44, 65, 69, 71, 81, 87, 88, 100, 101, 104,
                    107, 113, 114, 128, 129, 135, 140, 146
    4. Test error: DupEnv: should call Print.
    5. Test error: Josephus: *** stack smashing detected ***: <unknown> terminated
    6. Test error: Josephus: Aborted (core dumped)
    7. Test error: CDataTypes: missing types

*/

#include <stdio.h>
#include <stdlib.h>  /*malloc, free*/
#include <string.h> /*strlen*/
#include <ctype.h> /*tolower*/


char **DupEvn(char **env, char **buffer); /* name is funky... DupEvn? */
char *StrLower(char *str);
void Print(char **buffer);
int Josephus (int num);




char **DupEvn(char **env, char **buffer)
/*
copy all the env in lower case into **buffer
*/
{

	char **run_buffer = buffer;	

	
	while (*env != 0)
	{
/* extra space */
		char *new_env = (char *)malloc( strlen(*env) * sizeof(char) ); /* needs space before block */
		if(new_env == NULL) /* NULL should be on left */
		{
    			printf("Error: could not allocate memory!\n");	/* need space between printf and return; fix tab spacing */
			return (NULL);
		}
		
		strcpy(new_env, *env);
		new_env = StrLower(new_env);
		*run_buffer = new_env;
		++env;	
		++run_buffer;
	}
	
	return buffer;

}

char *StrLower(char *str)
/*
recives string and return it in lower case
*/

{
	char *mystr = str; /* don't use names with "my" */
	while (*mystr)
	{
		*mystr = tolower(*mystr);
		/* remove space */
		++mystr;
	} /* add space between block and return */
    return str;
}


void Print(char **buffer)
/*
recives  **buffer and print all its content
*/
{
 /* remove space */
	while (*buffer != 0)
	{
		printf("%s\n", *buffer);
		++buffer;
	}
 /* remove space */
 /* remove space */
}


/*2)--------------------------------------------------------------------------------------------------------------------------------------------------*/


int Josephus (int num)
/*
Josephus problem. recive a num of soliers and return who live
*/
{
	int i, count = 0, steps; /* seperate lines unless all index letters */
	int *arr = (int *)malloc(sizeof(int) * num);            /* in this context i have no idea what steps means */
	int result = 0;

    /* remove space */
	for (i=0; i < num; i++)
	{ 
		arr[i] = i+1; /* add spaces around arithmetic operators */
		printf("%d ", arr[i]);
	}

	printf("\n");
	arr[i] = -1;
	i--; /* --i */
	
	while (count < num)
	{
		for (steps = 0; steps < 2; steps++)
		{
			i++; /* ++i */
			
			if (arr[i] == -1) 
			{
				i = 0; 
			}

			while (arr[i] == 0) 
			{
				i++; /* ++i */
				if (arr[i] == -1) i = 0; /* ??? */
			}
		}
		
		while (arr[i] == 0)
		{
			i++; /* ++i */
			if (arr[i] == -1)
			{
				i = 0;
			}
			/* remove space */
		}
		
		printf("%d ", arr[i]);
		result = arr[i];
		arr[i] = 0;
		count++; /* ++count */
	}

	return result;
	
}

/*3)-------------------------------------------------------------------------------------------*/

void CDataTypes()
/*
print all the type data in see to stdout
*/
{
	fprintf (stdout , "The sizeof char is %ld\n", sizeof(char));
	fprintf (stdout, "The sizeof unsigned char is %ld\n", sizeof(unsigned char));
 	fprintf (stdout, "The sizeof int is %ld\n", sizeof(int));
 	fprintf (stdout, "The sizeof unsigned int is %ld\n", sizeof(unsigned int));
	fprintf (stdout, "The sizeof long is %ld\n", sizeof(long));
	fprintf (stdout, "The sizeof unsigned long is %ld\n", sizeof(unsigned long));
	fprintf (stdout, "The sizeof double is %ld\n", sizeof(double));
	fprintf (stdout, "The sizeof long double is %ld\n", sizeof(long double));
	fprintf (stdout, "The sizeof float is %ld\n", sizeof(float));
}
