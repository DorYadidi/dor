/*******************************************************************************
* NAME: binary sorted tree                                                     *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  11.12.18                                                      *
*******************************************************************************/

#include "test.h"
#include <stdio.h>
#include <string.h>

size_t RecursionStrlen(char const *str1);
int RecursionStrcmp(const char *str1, const char *str2);
char *RecursionStrcpy(char *dest, const char *src);
char *RecursionStrcat(char *s1, const char *s2);
char *RecursionStrStr(const char *str, const char *target);

TestResult TestStrlen();
TestResult TestStrcmp();
TestResult TestStrcpy();
TestResult TestStrcat();
TestResult TestStrStr();

int main()
{
	RUN_TEST(TestStrlen);
	RUN_TEST(TestStrcmp);
	RUN_TEST(TestStrcpy);
	RUN_TEST(TestStrStr);
	RUN_TEST(TestStrcat);

	return (0);
}

size_t RecursionStrlen(char const *str)
{
	if ('\0' == *str)
	{
		return (0);
	}

	return (1 + RecursionStrlen(str + 1));
}

int RecursionStrcmp(const char *str1, const char *str2)
{
	if ('\0' == *str1 || *str1 != *str2)
	{
		return (*str1 - *str2);
	}

	return (RecursionStrcmp(str1 + 1, str2 + 1));
}

char *RecursionStrcpy(char *dest, const char *src)
{
	*dest = *src;
	if ('\0' != *src)
	{
		RecursionStrcpy(dest + 1, src + 1);
	}

	return (dest);
}

char *RecursionStrcat(char *dest, const char *src)
{
	char *start_dest = dest;

	if (*dest != '\0')
	{
		RecursionStrcat(++dest, src);
	}
	else
	{
		*dest = *src;
		if ('\0' != *dest)
		{
			*(dest + 1) = '\0';
			RecursionStrcat(dest + 1, src + 1);
		}
	}

	return (start_dest);
}

char *RecursionStrStr(const char *str, const char *target)
{
	if ('\0' == *str)
	{
		return NULL;
	}
	else if (0 == strncmp(str, target, strlen(target)))
	{
		return ((char *)str);
	}
	else
	{
		return(RecursionStrStr(str + 1, target));
	}
}

/**********************************TEST*********************************************/

TestResult TestStrlen()
{
	char str1[] = "Hello World!";

	REQUIRE(RecursionStrlen(str1) == strlen(str1));

	return (TEST_PASS);
}

TestResult TestStrcmp()
{
	char str1[] = "Hello World!";
	char str2[] = "Hello World!";
	char str3[] = "Hello!";
	char str4[] = "World!";
	REQUIRE(RecursionStrcmp(str1, str2) == strcmp(str1, str2));
	REQUIRE(RecursionStrcmp(str3, str4) == 'H' - 'W');

	return (TEST_PASS);
}

TestResult TestStrcpy()
{
	char str1[50];
	char str2[50];
	REQUIRE(strcmp(RecursionStrcpy(str1,"qaqa"), strcpy(str2,"qaqa")) == 0);
	REQUIRE(strcmp(RecursionStrcpy(str1,"12345"), strcpy(str2,"12345")) == 0);

	return (TEST_PASS);
}

TestResult TestStrcat()
{
	char str1[20] = "geqlsl";
	char str2[30] = "geqlsl";
	REQUIRE(strcmp(strcat(str1,"qaqa"), RecursionStrcat(str2,"qaqa")) == 0);
	return (TEST_PASS);
}


TestResult TestStrStr()
{
	const char haystack[20] = "TutorialsPoint";
 	const char needle[10] = "Point";
 	REQUIRE(RecursionStrStr(haystack, needle) == strstr(haystack, needle));

	return (TEST_PASS);
}
