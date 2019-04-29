#include<stdio.h>
#include<stdlib.h>


char *Strcat(char *dest, const char *src)
{
	while (*dest != '\0')
	{
		dest ++;
	}

	while (*src != '\0')
	{
		*dest = *src;
		dest ++;
		src ++;
	}
	
	*dest = '\0';
	return dest;
}
	
char *Strncat(char *dest, const char *src, size_t n)
{
	unsigned int count = 0;
	while (*dest != '\0')
	{
		dest ++;
	}

	while (*src != '\0' && count < n)
	{
		*dest = *src;
		dest ++;
		src ++;
		count ++;
	}
	
	*dest = '\0';
	return dest;
}

char *Strstr(const char *haystack, const char *needle)
{
	int len = 0;
	while(*haystack != '\0')
	{
		while(*needle != '\0')
		{
			if (*haystack == *needle) 
			{
				haystack ++;
				needle ++;
				len ++;
			}

			else
			{
				break;
			}
		}
		
		if (*needle == '\0')
		{
			return (char *)(haystack - len);
		}
		
		haystack ++;
	}
	
	return (char *)NULL;
}	
	
size_t Strspn(const char *str1, const char *str2)
{
	int len = 0;
	while(*str1 != '\0')
	{
		while(*str2 != '\0')
		{
			if (*str1 != *str2) 
			{
				str2 ++;
			}

			if (*str1 == *str2)
			{
				str1 ++;
				len ++;
				break;
			}
		}

		if (*str2 == '\0') 
		{
			return len;
		}
	}
	return len;
}


