#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "ws_2.c"

void TestStrlen ();
void TestStrcmp ();
void TestStrcpy ();
void TestStrcasecmp();
void TestStrchr();
void TestStrdup();
char *strdup(char *src);
void TestStrcat();
void TestStrspn();
void TestIsPalindrome();




int main ()
{
	TestStrlen ();
	TestStrcmp ();
	TestStrcpy ();
	TestStrcasecmp();
	TestStrchr();
	TestStrdup();
	TestStrcat();
	TestStrspn();
	TestIsPalindrome();
	
	return 0;
}


void TestStrlen ()
{
	char str1[] = "Hello World!";
	if (strlen(str1) == Strlen(str1))
	{
		printf ("Strlen Work\n");
	
	}
	else 
	{
		printf ("Strlen fail\n");
	}

	if (strlen("Hello Worl0d!") == Strlen("Hello Worl0d!"))
        {

		printf ("Strlen Work\n");
	
		}
	else 
	{
		printf ("Strlen fail\n");
	}


}

void TestStrcmp ()
{
	char str1[] = "abcd";
	char str2[] = "ABCD";

	
	if (strcmp(str1, str2) == Strcmp(str1, str2))
	{
		printf ("Strcmp Work\n");
	
	}
	else 
	{
		printf ("Strcmp fail\n");
	}


}

void TestStrcpy ()
{
	char str1[50];
	char str2[50];
	size_t test =strcmp(strcpy(str1,"qaqa"), Strcpy(str2,"qaqa"));
	if (test == 0)
	{
		printf ("Strcpy Work\n");
	
	}
	else 
	{
		printf ("Strcpy fail\n");
	}

}

void TestStrcasecmp ()
{
	char str1[] = "abcd";
	char str2[] = "ABCD";

	
	if (strcasecmp(str1, str2) == Strcasecmp(str1, str2))
	{
		printf ("Strcmp Work\n");
	
	}
	else 
	{
		printf ("Strcmp fail\n");
	}



}

void TestStrchr()
{
	int c= 'q';
	char str1[] = "geqlsl";
	
	
	if (strchr(str1, c) == Strchr(str1, c))
	{
		printf ("Strchr Work\n");
	
	}
	else 
	{
		printf ("Strchr fail\n");
	}
}

void TestStrdup()
{
	char *str1 = "hi :)";
	char *test1 = strdup(str1); 
	char *test2 = Strdup(str1);
	if (strcmp(test1,test2) == 0)
	{
		printf ("Strdup Work\n");
	
	}
	else 
	{
		printf ("Strdup fail\n");
	}


}

void TestStrcat()
{
	char str1[30] = "geqlsl";
	char str2[30] = "geqlsl";
	if (strcmp(strcat(str1,"qaqa"), Strcat(str2,"qaqa")) == 0)
	{
		printf ("Strcat Work\n");
	
	}
	else 
	{
		printf ("Strcat fail\n");
	}	

}



void TestStrspn()
{
	char str1[] = "geqlsl";
	if (strspn(str1, "gleq") == Strspn(str1, "gleq"))
	{
		printf ("Strspn Work\n");
	
	}
	else 
	{
		printf ("Strspn fail\n");
	}	

}


void TestIsPalindrome()
{
	if (IsPalindrome("mabam") == 1)	
{
		printf ("IsPalindrome Work\n");
	
	}
	else 
	{
		printf ("IsPalindrome fail\n");
	}	
}
