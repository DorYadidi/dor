/*
WS_3
Dor yadidi
14.10
*/

#include <stdio.h>
#include <stdlib.h>  /*malloc, free*/
#include <string.h> /*strlen*/
#include <ctype.h> /*tolower*/





char **DupEvn(char **env, char **buffer);
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

		char *new_env = (char *)malloc( strlen(*env) * sizeof(char) );
		if(new_env == NULL)
		{
    			printf("Error: could not allocate memory!\n");	
			return (NULL);
		}
		
		strcpy(new_env, *env);
		new_env = StrLower(new_env);
		*run_buffer = new_env;
		++env;	
		++run_buffer;
	}
	
	Print(buffer);
	return buffer;

}

char *StrLower(char *str)
/*
recives string and return it in lower case
*/

{
	char *mystr = str;
	while (*mystr)
	{
		*mystr = tolower(*mystr);
		
		++mystr;
	}
    return str;
}


void Print(char **buffer)
/*
recives  **buffer and print all its content
*/
{

	while (*buffer != 0)
	{
		printf("%s\n", *buffer);
		++buffer;
	}


}


/*2)--------------------------------------------------------------------------------------------------------------------------------------------------*/


int Josephus (int num)
/*
Josephus problem. recive a num of soliers and return who live
*/
{
	int i, count = 0, steps;
	int result = 0;
	int *arr = (int *)malloc(sizeof(int) * num);
	if(arr == NULL)
	{
		return 0;
	}       

  
	for (i=0; i < num; i++)
	{ 
		arr[i] = i+1;
		printf("%d ", arr[i]);
	}

	printf("\n");
	arr[i] = -1;
	i--;
	
	while (count < num)
	{
		for (steps = 0; steps < 2; steps++)
		{
			i++;
			
			if (arr[i] == -1) 
			{
				i = 0; 
			}

			while (arr[i] == 0) 
			{
				i++;
				if (arr[i] == -1) i = 0;
			}
		}
		
		while (arr[i] == 0)
		{
			i++;
			if (arr[i] == -1)
			{
				i = 0;
			}
			
		}
		
		printf("%d ", arr[i]);
		result = arr[i];
		arr[i] = 0;
		count++;

		
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
