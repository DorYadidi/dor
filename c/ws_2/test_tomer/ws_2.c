#include<stdio.h>
#include<stdlib.h>

size_t Strlen(char *str)
{
	int count = 0;
	while (*str != '\0')
	{
		str ++ ;
		count ++ ;
	}
	return count;
}

int Strcmp(const char *str1, const char *str2)
{

	while((*str1 != '\0') || (*str2 != '\0'))  

/*while at least one is not null, if one of them is null the loop continues */
	{
		if(*str1 == '\0')
		{
			return -1;
		}
		
		if(*str2 == '\0')
		{
			return 1;
		}
		
		if(*str1 > *str2)
		{
			return 1;
		}
		
		if(*str1 < *str2)
		{
			return -1;
		}
		str1 ++;
		str2 ++;
	}

	return 0;
}

char *Strcpy(char *dest, const char *src)
{

	char *temp = dest;

	while(*src != '\0')
	{	
	 	*dest = *src;
		dest ++;
		src ++;
	}	
	
	*dest = '\0';
	
	return temp;
}	


char *Strncpy(char *dest, const char *src, size_t n)
{

	unsigned int count = 0;
	char *temp = dest;

	while(*src != '\0' && count != n)
	{	
	 	*dest = *src;
		dest ++;
		src ++;
		count ++;
	}	
	
	*dest = '\0';
	
	return temp;
}

int Strcasecmp(const char *f1, const char *f2)
{
	
	while((*f1 != '\0') || (*f2 != '\0'))  

/*while at least one is not null, if one of them is null the loop continues */
	{
		if(*f1 == '\0')
		{
			return -1;
		}
		
		if(*f2 == '\0')
		{
			return 1;
		}
		
		if((*f1 > *f2) && (*f1 > *f2 + 32)) 
		{
			return 1;
		}
		
		if((*f1 < *f2) && (*f1 + 32 < *f2))
		{
			return -1;
		}

		f1 ++;
		f2 ++;
	}

	return 0;
}

char *Strchr(const char *str, int c)
{

	while(*str != (char) c)
	{
		str ++;
	}
	
	return (char*) str;
}

char * Strdup(const char *str)
{
	char *new_str;  
	int len = 0; 
	const char* p = str;

	while (*str != '\0')
	{
		str ++;
        	len ++;
	}

	new_str = malloc(len + 1);

	if( new_str == '\0')
	{
		return (char *)NULL;
	}

	Strcpy(new_str, p);
	
	return new_str;                          
}

