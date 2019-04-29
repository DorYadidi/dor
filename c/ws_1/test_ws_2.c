#include <stdio.h>
#include <string.h>
#include "ws_2.c"

void TestStrlen ();
void TestStrcmp ();

int main ()
{
	TestStrlen ();
	TestStrcmp ();

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
