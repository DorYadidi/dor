#include <stdio.h>
#include <string.h>
#include <assert.h>

int CheckSeven(int num)
/* A function that checks if a number has 7 or divide by 7                    */
{
	int temp = num;
	
	if(( num % 7) == 0)
	{
		printf("BOOM\n");
		return 0;
	}

	while( num != 0 )
	{
		if( (num % 10) == 7)
		{
			printf("BOOM\n");
			return 0;
		}
		num /= 10;
	}

	printf("%d\n", temp);
	return 0;
}

void SevenBoom(int from, int to)
/*              A function receives a range                                   */
{
	int i;

	assert( from < to );
	
	for (i = from ; i <= to; i ++ )
	{
		CheckSeven(i);
	}
}
	

