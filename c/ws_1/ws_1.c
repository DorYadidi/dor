#include <stdio.h>

int Flip(int num)
/* function that recieive an int and flips it
*int num can be any number (int)
*Return int 
*/
{
	int flipped_num=0;

	while (num != 0)
    {
		flipped_num = flipped_num * 10;
        flipped_num  = flipped_num + (num % 10);
        num = num / 10;    
    }
    return flipped_num;
}

/*
--------------------------------------------------------------------------
*/
int Ubs (int num)
/* function that recieive an int and rertun the ubs
*int num can be any number (int)
*/
{
	if (num<0)
	{	
	return -1*num;
	}
else
	{
		return num;
	}
}
double Power10 (int num)
/* function that recieive an int and rertun 10^number
*int num can be any number (int)
*/
	{
		int ubs_number = Ubs(num);
		int i;
		int sum =1;
		for (i=1;i<=ubs_number;i++)
		{
			sum = sum*10;
		}	
		if (num<0)
		{
			return 1/sum;
		}
		return sum;
	}

