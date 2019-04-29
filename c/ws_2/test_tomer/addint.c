#include<stdio.h>
#include<stdlib.h>
#include <string.h>

char *strrev(char *str)
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


char* AddInt (char *a, char *b)
/* A function that returns a result of 2 numbers represented as strings       *
 *                                                                            *
 * pa - pointer that receives the first string, starts from the end           *
 * pb - pointer that receives the second string, starts from the end          *
 * a1 and b1 - calculates the digit from ascii value                          *
 * *pres - stores the addition of the 2 digits, back to ascii value           */

{
	static char str_res[100] = "";
	char* pa = a + strlen(a) - 1;
	char* pb = b + strlen(b) - 1;
	char* pres = str_res;

	int a1, b1, c1, sum;
	c1 = 0;

	while ((pa >= a) || (pb >= b)) /*runs untill the start of the strings */
	{
		a1 = 0;
		b1 = 0;

		/* add one digit */
		if (pa >= a)
		{
			a1 = *pa - '0';
			pa--;
		}

		if (pb >= b)
		{
			b1 = *pb - '0';
			pb--;
		}

		sum = a1 + b1 + c1;

		if (sum < 10)
		{
			*pres = sum + '0';
			c1 = 0; /* carry */
		}

		else
		{
			*pres = (sum - 10) + '0';
			c1 = 1;
		}

		pres++;

	}

	if (c1 == 1)
	{
		*pres = '1';
		pres++;
		*pres = '\0';
	}

	if (strlen(str_res) > 0)
	{
		strrev(str_res);
	}
	return str_res;
}

