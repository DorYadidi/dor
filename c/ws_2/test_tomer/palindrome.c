#include <stdio.h>
#include <string.h>

char *_strrev(char *str)
{
      char z;
      char *p1, *p2;

      if (! str || ! *str)
      {
            return str;
      }

      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            z = *p1;
            *p1 = *p2;
            *p2 = z;
      }

      return str;
}

int IsPalindrom(const char *str)
{

	int i;
	int isPalindrome = 1;
	char string[200] = "";
	char string_rev[200] = "";

	strcpy(string, str);

	strcpy(string_rev, string);

	i = strcmp ( _strrev(string_rev) ,string);

	if( i != 0 )
	{
		isPalindrome = 0;
	}

	if(isPalindrome)
	{
		printf("Yes, it is Palindrome!\n");
	}

	else
	{
		printf("No, not a Palindrome\n");
	}

	return 0;
}

