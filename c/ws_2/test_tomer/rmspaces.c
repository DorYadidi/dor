#include<stdio.h>
#include<stdlib.h>
#include <string.h>


static void strDeleteChar (char* p)
/* deletes the first char from string  */
{
	while (*p)
	{
		*p = *(p + 1);
		p++;
	}
}

int IsWhiteSpace (char ch)
/* A function that return 1 if the current value is a tab or space           */
{
	return ((ch == ' ') || (ch == '\t')) ? 1 : 0;
}

void RmSpaces(char * str)
/* A function that cleans white spaces from the start, end, and middle       */
{
	char* p = str;

	/* remove white space from the start of the string */
	while (*p != '\0')
	{
		if (IsWhiteSpace(*p))
		{
			p++;
		}

		else
		{
			break;
		}
	}
	strcpy(str, (const char *)p);

	/* remove white spaces from end of the string */
	if (strlen(str) > 0)
	{
		p = str + strlen(str) - 1;

		while (IsWhiteSpace(*p))
		{
			p--;
		}
		*(p + 1) = '\0';
	}

	/* remove duplicate white spaces from middle of the string */
	p = str;
	while (*p != '\0')
	{
		if (*p == '\t')
		{
			*p = ' ';
		}

		p++;
	}

	p = str;
	while (*p != '\0')
	{
		if ((*p == ' ') && (*(p + 1) == ' '))
		{
			strDeleteChar(p);
		}

		else
		{
			p++;
		}
	}
}

int main ()
{
	char *str = " gdf  sda  		.ss  ";
	printf("%s", str);

return 0;

}
