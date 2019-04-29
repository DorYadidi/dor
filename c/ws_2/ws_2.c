#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


size_t Strlen (char const *str1)
/*Computes the length of the string str up to but not including the terminating null character
Return Value: This function returns the length of string */

{
	int count = 0;
 	while (*str1 != 0)
	{
		count ++;
		str1 ++;
	}
	return count;
}


int Strcmp (const char *str1, const char *str2)
/*Compares the string pointed to, by str1 to the string pointed to by str2
This function return values that are as follows −
*  if Return value < 0 then it indicates str1 is less than str2.
*  if Return value > 0 then it indicates str2 is less than str1.
*  if Return value = 0 then it indicates str1 is equal to str2.
*/
{


    while ((*str1 != 0) && (*str1 == *str2))
	{
		++str1;
		++str2;
	}
    return (*str1) - (*str2);



}

char *Strcpy (char *dest, const char *src)
/*Parameters
*dest − This is the pointer to the destination array where the content is to be copied.
*src − This is the string to be copied.
*Return Value
*This returns a pointer to the destination string dest.
*/
{
	unsigned i;
	for (i=0; src[i] != '\0'; ++i)
	{
		dest[i] = src[i];
	}
	dest[i]= '\0';

	return dest;

}

char *Strncpy(char *dest, const char *src, size_t n)
/*
Parameters
    dest − This is the pointer to the destination array where the content is to be copied.
    src − This is the string to be copied.
    n − The number of characters to be copied from source.
Return Value
This function returns the final copy of the copied string.
*/
{
	size_t i;
	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}

   return dest;
}

int Strcasecmp(const char *str1, const char *str2)
/*
*ignoring differences in case
*Parameters
*dest − This is the pointer to the destination array where the content is to be copied.
*src − This is the string to be copied.
*Return Value
*This returns a pointer to the destination string dest.
*/
{
	while ((*str1 != 0) && (tolower(*str1) == tolower(*str2)))
	{
		++str1;
		++str2;
	}

	return tolower((*str1)) - tolower((*str2));
}


char *Strchr(const char *str1, int c)
/*= locates the ﬁrst occurrence of c (converted to a char) in the string pointed to by s.
*The terminating null character is considered to be part of the string.
*/
{
	while (*str1 != (char)c)
	{
		if (*str1++ == 0)
		{
			return 0;
		}
	}

	return (char *)str1;
}

char *Strdup(char *src)
{
/*returns a pointer to a null-terminated byte string, which is a duplicate of the string pointed to by s
*/
	char *ret = (char*)malloc(sizeof(char)*(strlen(src)+1));
	if (ret==0)
	{
		return (NULL);
	}

	Strcpy(ret, src);

        return ret;
}

char *Strcat(char *s1, const char *s2)
{
/* Parameters
*    s1 − This is pointer to the destination array, which should contain a C string,
*    and should be large enough to contain the concatenated resulting string.
*    s2 − This is the string to be appended. This should not overlap the destination.
*Return Value
*This function returns a pointer to the resulting string dest.
*/
	char *p = s1 + strlen(s1);
	strcpy(p, s2);
	return s1;
}


char *StrStr(const char *str, const char *target)
{
/*locates the first occurrence of the string string1 in the string string2 and
 *returns a pointer to the beginning of the first occurrence
*/
	char *p1, *p2;
	char *p1Begin;

	if (*target == 0)
	{
		return (char*)str;
	}

	 p1 = (char *)str;

	while (*p1 != 0)
	{
		p1Begin = p1;
		p2 = (char *)target;

		while (*p1 != 0 && *p2 != 0 && *p1 == *p2)
		{
			p1++;
			p2++;
		}

		if (*p2 == 0)
		{
			return (char *)p1Begin;
		}

		p1 = p1Begin + 1;
  }

	return NULL;
}

size_t Strspn(const char *str1, const char *str2)
{
/*Parameters
str1 : string to be scanned
str2 : string containing the
characters to match.
Return Value : number of characters in the initial segment of str1 which consist only of characters
from str2.
*/

    size_t ret=0;

    while(*str1 != 0 && Strchr(str2,*str1) != 0)
	{
		ret++;
		str1++;
	}

    return ret;
}

/*char *Strtok(char *str, const char *delim)
breaks the string s1 into tokens and null-terminates them. Delimiter-Characters at the beginning and end of str are skipped.
*On each subsequent call delim may change.

{


}
*/

int IsPalindrome(char *str)
/*A function to check if a string str is palindrome
*Return 1 if palindrome and 0 if not
*/
{

	int l = 0;
	int h = Strlen(str) - 1;

	while (l < h)
	{
		if (str[l++] != str[h--])
		{
			return 0;
		}
	}

	return 1;
}

int HaveSeven (int num)
{
/*check if num have 7 and retrun 1 if true and 0 is false*/

	while (num != 0)
	{
		if (num % 10 == 7)
		{
			return 1;
		}

		num = num / 10;
	}

	 return 0;
}

void SevenBoom(int from, int to)
{
/*
*recives a range (from,to) and prints all nummber ib the range except for number that have 7 or divide by 7 no
*remainder instead print "BOOM"
*/
	int i;
    for (i = from; i<to; i++)
	{
		if (i%7==0 || HaveSeven(i) == 1)
		{
			printf ("BOOM");
		}
		else
		{
		printf("%d\n",i);
		}
	}
}



void RmSpaces(char str[])
/*cleabs white spaces from the beginning and the end of the string and clean up, when there
*is more then 1 spaces and the middle of the string
*/
{
	int i= 0, j=0;
	char str2[200] = {0};

	while (str[i] != 0)
		{
			if (str[i] == ' ')
			{
				i++;
				continue;
			}
			break;
		}

	for (; str[i] != 0; i++)
	{

		if (str[i] != ' ')
		{
			str2[j] = str [i];
			j++;
		}

		else if (str[i] == ' '  && str[i+1] == ' ')
		{
			continue;

		}
		else if (str[i] == ' '  && str[i+1] == 0)
		{
				str2[j] = str [i];
				break;
		}


		else if (str[i] == ' ' && str[i+1] != ' ' )
		{
			str2[j] = str[i];
			j++;
		}

	}
		strcpy(str, str2);

}

void SwapPointers(int **a, int **b)
/*Swap 2  two poninter 2 int
*/
{

	int *temp = *a;
	*a=*b;
	*b = temp;


}


char *AddInt(char *str1, char *str2, char *result)
{
/*
retrun a result of an addition positive number represented as strings.
*/
	int add1,add2;
	int carry = 0;
	int sum;
	int i= strlen(str1) - 1 ;
	int j= strlen(str2) -1 ;
	int max = (j > i) ? j : i;
	int min = (j < i) ? j : i;
	int lenresult = max + 1;

	while ((min + 1) > 0)
	{
		add1 = str1[i] - 48;
		add2 = str2[j] - 48;

		sum = add1 + add2 + carry;
		carry = 0;
		if (sum >= 10)
		{
			result[lenresult] = sum % 10 + 48;
			carry++;
			lenresult--;

		}
		else
		{
			result[lenresult] = sum + 48;
			lenresult--;
		}

		i--;
		j--;
		min--;


	}

    while (i >= 0)
	{

		add1 = str1[i] +carry - 48;
		carry = 0;

		if (add1 >= 10)
		{
			result[lenresult] = add1 % 10 + 48;
			carry++;
			lenresult--;

		}
		else
		{
			result[lenresult] = add1 + 48;
			lenresult--;
		}

		i--;

	}
    while (j >= 0)
	{

		add2 = str2[j] + carry - 48;
		carry = 0;

		if (add2 >= 10)
		{
			result[lenresult] = add2 % 10 + 48;
			carry++;
			lenresult--;

		}
		else
		{
			result[lenresult] = add2 + 48;
			lenresult--;
		}

		j--;

	}
	if(carry==1)
	{
		result[lenresult] = '1';
	}
	return result;

}
