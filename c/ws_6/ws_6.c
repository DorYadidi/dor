/*Dor yadidi ws_6*/

#include <stdio.h> /*fclose, fopen, fgets, fseek*/

double Pow2 (unsigned int x, int y);
/*************************************************************************
 *Return x*(2^y)	                                                 *
 *************************************************************************/

int PowOf2Loop (unsigned int n);
/*************************************************************************
 *Return 1 if n is power of 2 and 0 otherwish - Using a loop             *
 *************************************************************************/

int PowOf2 (unsigned int n);
/*************************************************************************
 *Return 1 if n is power of 2 and 0 otherwish                            *
 *************************************************************************/

int AddOne(unsigned int number);
/*************************************************************************
 *Return n+1 witout arithmetic operators                                 *
 *************************************************************************/

void Arry3BitOn (unsigned int *arr, int size_arr);
/*************************************************************************
 *receives an arry with the size_arr and print only if have 3 bits on    *
 *************************************************************************/

int ByteMirrorLoop(unsigned int n);
/*************************************************************************
 *byte mirorr using a loop                                               *
 *************************************************************************/

int ByteMirror(int n);
/*************************************************************************
 *byte mirorr                                                            *
 *************************************************************************/
int F1(unsigned char n);
/*************************************************************************
 *if the bits 2,6 on return 1 else return 0                              *
 *************************************************************************/

int F2(unsigned char n);
/*************************************************************************
 *if the bits 2 or 6 on return 1 else return 0                           *
 *************************************************************************/

int F3(unsigned char n);
/*************************************************************************
 *swap between bit 3 and 5 and return the new number                     *
 *************************************************************************/

unsigned int ClosestNum(unsigned int n);
/*************************************************************************
 *Return the closest number from n that divided by 16 witout remainder   *
 *************************************************************************/

void Swap( int *x,int *y);
/*************************************************************************
 *swap between 2 bariables witout using in a third variable              *
 *************************************************************************/

int BitsOnLoop(unsigned int n);
/*************************************************************************
 *counts the number of set bits in an integer                            *
 *************************************************************************/

int BitsOn(unsigned int n);
/*************************************************************************
 *counts the number of set bits in an integer                            *
 *************************************************************************/

void FloatBits(float num);
/*************************************************************************
 *receives a float number and prints its bits                            *
 *************************************************************************/


double Pow2(unsigned int x, int y)
{
	double result = 0;
	if(y < 0)
	{
		result = (1 / (x*(1 << y)));
		return result;
	}

	result = (x*(1 << y));
	return result;

}

int PowOf2Loop (unsigned int n)
{
	int i=0;
	for (i=0; i <= (int)n; ++i)
	{
		if ((1 << i) == (int)n)
		{
			return 1;
		}

	}

	return 0;
}

int PowOf2 (unsigned int n)
{
	if( (n != 0) && (n & (n - 1)) == 0)
	{
		return 1;
	}

	return 0;

}

int AddOne(unsigned int num)
{
	int m = 1;

    while((num & m) != 0)
    {
        num = num ^ m;
        m = m << 1;
    }

    num = num ^ m;

    return num;

}

void Arry3BitOn (unsigned int *arr, int size_arr)
{
	int check = 0;
	int i = 0, j = 0;

	for (i = 0; i < size_arr; ++i)
	{
		check = 0;

		for (j = 0; j <= 31; ++j)
		{

			check = check + ((arr[i] & (1 << j)) >> j);
			if (4 == check)
			{
				break;
			}
		}

		if (3 == check)
		{
		printf("%d ", arr[i]);

		}
	}

	printf("\n");
}

void Arry3BitOn2 (unsigned int *arr, int size_arr)
{
	int check = 0;
	int i = 0, j = 0;

	for (i = 0; (i < size_arr) ; ++i)
	{
		check = 0;

		for (j = 0; (j < sizeof(int*8)) && (count > 4); ++j)
		{
			check = check + ((arr[i] & (1 << j)) >> j);
		}

		if (3 == check)
		{
		printf("%d ", arr[i]);

		}
	}

	printf("\n");
}

int ByteMirrorLoop(unsigned int n)
{
	int new_n = 0;
	int i=0;
	for (i = 0; i < 32; ++i)
	{
		new_n = new_n << 1;

		if (n & 1)
		{
			new_n = new_n | 1;
		}

		n = n >> 1;
	}

	return new_n;
}

int ByteMirror(int x)
{

 x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
 x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
 x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
 x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));

return((x >> 16) | (x << 16));
}


int F1(unsigned char n)
{
	if ((n & 34) == 34)
	{
		return 1;

	}

	return 0;
}

int F2(unsigned char n)
{
	if ((n & 34) == 34 || (n & 2) == 2 || (n & 32) == 32)
	{
		return 1;
	}

	return 0;
}


int F3(unsigned char n)
{


	int bit3 = ((n >> 2) & 1);
	int bit5 = ((n >> 4) & 1);
	n = (bit3 << 4) | (n & 239);
	n = (bit5 << 2) | (n & 251);

	return n;

}

unsigned int ClosestNum(unsigned int n)
{
	return n - (n & 15);

}


void Swap(int *x,int *y)
{

	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;

}

int BitsOnLoop(unsigned int n)
{
	int i = 0;
	int count = 0;
	for (i = 0; i <= 31; ++i)
	{
		count = count + ((n & (1 << i)) >> i);
	}

	return count;
}

int BitsOn(unsigned int n)
{
  /*put count of each 2 bits into those 2 bits*/
    n = n - ((n >> 1) & 0x55555555);
     /*put count of each 4 bits into those 4 bits */
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    /*put count of each 8 bits into those 8 bits */
    n = ((n + (n >> 4) )& 0xF0F0F0F);
   /*returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24)
      + ...*/
    return ((n* 0x1010101) >> 24);

}

void FloatBits(float num)
{
	 int *p_num = NULL;
	 int i = 32;
	 int buf= 0;
	 p_num =(int *)&num;

	 for (i=31; i >= 0; --i)
	 {
	 	buf = (*p_num & (1 << i)) >> i;
	 	printf ("%d", buf);
	 }

	 printf("\n");

}
