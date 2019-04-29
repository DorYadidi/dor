

void Josephus(int num);
void CDataTypes();
char **DupEnv(char **env, char **buffer);
void Print(char **buffer);
char *ToLower(char *p);

/* */
/* */


/* */

char **DupEnv(char **env, char **buffer)
{
	char *p = NULL;
	char **buffertemp= buffer;
	while (*env != 0)
	{
		p = (char *)malloc((strlen(*env)) * sizeof(char));
		if(0 == p)
		{
			printf ("Error");
			return NULL;
		}
		strcpy(p, *env);
		ToLower(p);
		*buffertemp = p;
		++buffertemp;
		++env;
	}
	
	Print(buffer);
	return buffer;
	

	
}

void Print(char **buffer)
{
	int i = 0;
	while (buffer[i] != '\0')
	{
		printf ("%s\n", buffer[i]);
		++i;
	}
}


char *ToLower(char *p)
{
	char *mystr = p;
	while (*mystr != 0)
	{
		*mystr = tolower(*mystr);
		++mystr;
	
	}

	return p;
} 




/* */
/* */


/* */

void Josephus(int num)
{

	int i = 0, j = 1, k = 0, target = 0 ,kill = target + 1;
   	int islive = num;
	int temp = num;
	int *array=((int *)malloc(sizeof(int) * num));
	
	int iszero = 0;
	int zerocheck = 0;
	int secondloop = 0;

/*/-----------------------------create first loop ---------------------------------------------------------------*/
	for(i=0; i<num; ++i)
	{
		array[i] = j;
		
		++j;

	}

	printf ("\n");
/* --------------------------------- kill --------------------------------*/


	for (target = 0; islive + 1 > 1; ++target)
	{
		if (array[target] != 0)
		{

			for (kill = target + 1; array[kill-1] != 0; ++kill)
			{
				zerocheck = 0;
				iszero = 0;
				
				if ((temp - 1 <= target) || secondloop == 1)
				{
				
					if (target > temp && array[temp] != 0)
					{
						target = 0;
					}
				
					if (array[temp] == 0 && target > temp)
					{
						target = 0;
					}
					secondloop = 1;
					
					while (array[target] == 0)
					{
					++target;
					}

				}
				
				if (kill >= num || secondloop == 1)
				{
					zerocheck = kill;
					
					while (zerocheck < temp)
					{
						if (array[zerocheck] != 0)
						{
							iszero = 1;
						}
						
						++zerocheck;
					}
					
					if (kill > temp || iszero == 0)
					{
						kill = 0;
					}
					
					if (kill == target)
					{
						++kill;
					}
					
					while (array[kill] == 0)
					{
						++kill;
						
						if (kill == target )
						{
							++kill;
						}
					}

				}
				
				while (array[kill] == 0)
				{
					++kill;
				}

				array[kill] = 0;
				islive = islive - 1;
			}
		}	

		} 

/* --------------------------------- kill --------------------------------*/

		for (k = 0; k < num; ++k)
		{
			if (array[k] != 0)
			{
				printf ("the last one is:  %d ", array[k]);
			}	
				
		}
		printf ("\n");
		

}

/* */
/* */


void CDataTypes()
{
	fprintf(stdout, "the size of short int is %lu \n", sizeof (short int) );
	fprintf(stdout, "the size of short unsigned short int %lu \n", sizeof (unsigned short int) );
	fprintf(stdout, "the size of unsigned int is %lu \n", sizeof (unsigned int) );
	fprintf(stdout, "the size of int is %lu \n", sizeof (int) );
	fprintf(stdout, "the size of long int  is %lu \n", sizeof (long int ) );
	fprintf(stdout, "the size of unsigned long int is %lu \n", sizeof (unsigned long int) );	
	fprintf(stdout, "the size of signed char is %lu \n", sizeof (signed char) );
	fprintf(stdout, "the size of unsigned char is %lu \n", sizeof (unsigned char) );
	fprintf(stdout, "the size of float is %lu \n", sizeof (float) );
	fprintf(stdout, "the size of double is %lu \n", sizeof (double) );
	fprintf(stdout, "the size of long double is %lu \n", sizeof (long double) );
	
	
}


