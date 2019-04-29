
/******************************************************************************
 * Bitwise operations                                                         *
 * creator: chen mardix                                                       *
 * date: 22.10.18                                                             *
 ******************************************************************************/

#include <stdio.h> /* printf */

double Pow2(unsigned int x, int y);
/******************************************************************************
 * returns x*(2^y)                                                            *
 ******************************************************************************/

int PowOf2Loop (unsigned int n);
/******************************************************************************
 * checking if a number is a power of 2 by loop                               *
 ******************************************************************************/	

int PowOf2 (unsigned int n);
/******************************************************************************
 * checking if a number is a power of 2 without loop                          *
 ******************************************************************************/
	
int AddOne(unsigned int num);
/******************************************************************************
 * adding one to number without arithmetic operator                           *
 ******************************************************************************/

void Array3BitOn(unsigned int arr[],int size);
/******************************************************************************
 * printing the numbers in array that has 3 bits on                           *
 ******************************************************************************/
	
int ByteMirrorLoop(unsigned int n);
/******************************************************************************
 * reversing the bits in a number by loop                                     *
 ******************************************************************************/
	
int ByteMirror (int num);
/******************************************************************************
 * reversing the bits in a number without loop                                *
 ******************************************************************************/

int F1(unsigned int n);	
/******************************************************************************
 * checking if the 2 and 6 bits are on                                        *
 ******************************************************************************/

int F2(unsigned int n);	
/******************************************************************************
 * checking if the 2 or 6 bits are on                                        *
 ******************************************************************************/

int F3(unsigned int n);
/******************************************************************************
 * swaping the 3 and 5 bits                                                   *
 ******************************************************************************/	

int ClosestNum(int n);
/******************************************************************************
 * returns the closest number to n that divded by 16 without reminder         *
 ******************************************************************************/

void Swap(int *x,int *y);	
/******************************************************************************
 * swaps x and y without pointers                                             *
 ******************************************************************************/

int BitsOnLoop(int n);
/******************************************************************************
 * checking how many bits are on by loop                                      *
 ******************************************************************************/

int BitsOn(int n);
/******************************************************************************
 * checking how many bits are on without loop                                 *
 ******************************************************************************/

void FloatBits (float num);	
/******************************************************************************
 * print float number bits                                                    *
 ******************************************************************************/


double Pow2(unsigned int x, int y)
{
	if(y < 0)
	{
		return 1 / (x *= (1 << y)); 
	}

	return x *= (1 << y);
    
}

int PowOf2Loop(unsigned int n)
{
    unsigned int i = 1;
    for ( i = 1; i <= n; i = i * 2)
    {
        if(i == n)
        {
            return 1;
        }
    }
    return 0;
}

int PowOf2(unsigned int n)
{
    if( (n != 1) && ((n & (n - 1)) == 0))
    {
        return 1;
    }
    return 0;
}

int AddOne(unsigned int num)
{
    int temp = 1;
	if(num & 1)
	{
		num ^= temp;
		temp <<= temp;
	}
	num ^= temp;
	return num;
}

void Array3BitOn(unsigned int arr[],int size)
{
	int digcounter = 0;
	int i=0, j = 0;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < 32; ++j)
		{
			digcounter += (arr[i] & (1 << j)) >> j;
		}
		if (3 == digcounter)
		{
			printf("%d,",arr[i]);
		}
		digcounter = 0;
	}
	printf("\n");
}
    

int ByteMirrorLoop(unsigned int n)
{
    int i = 1;
    unsigned int new_num = 0;
    
    for (i = 0; i < 32; i++) 
    {
        new_num = new_num << 1;
        if (n & 1)
        {
            new_num = new_num | 1;
        }
        n = n >> 1;
    }
	return new_num;
}

int ByteMirror(int num)
{
 	num = (((num & 0xaaaaaaaa) >> 1) | ((num & 0x55555555) << 1));
 	num = (((num & 0xcccccccc) >> 2) | ((num & 0x33333333) << 2));
 	num = (((num & 0xf0f0f0f0) >> 4) | ((num & 0x0f0f0f0f) << 4));
 	num = (((num & 0xff00ff00) >> 8) | ((num & 0x00ff00ff) << 8));

	return (((num >> 16) | (num << 16))) ;
}

int F1(unsigned int n)
{
    unsigned int bit2 = 2;
    unsigned int bit6 = 32;
    bit2 = (bit2 & n) >> 1; 
    bit6 = (bit6 & n) >> 5;
    return (bit2 & bit6);
}

int F2(unsigned int n)
{
    unsigned int bit2 = 2;
    unsigned int bit6 = 32;
    bit2 = (bit2 & n) >> 1; 
    bit6 = (bit6 & n) >> 5;
    return (bit2 | bit6);
}

int F3(unsigned int n)
{
    unsigned int bit1 =  (n >> 2) & 1; 
    unsigned int bit2 =  (n >> 4) & 1; 
    unsigned int x = (bit1 ^ bit2); 
    x = (x << 2) | (x << 4); 
    return (n ^ x); 
}

int ClosestNum(int n)
{
    return (n & ~15);
}
void Swap(int *x,int *y)
{
	*x = *x ^ *y;
	*y = *y ^ *x;
	*x = *x ^ *y;
}
int BitsOnLoop(int n)
{
	int digcounter = 0;
	int j = 0;
	for (j = 0; j < 8; j++)
	{
		digcounter += (n & (1 << j)) >> j;
	}
	return digcounter;
}

int BitsOn(int n)
{ 
	/* hamming wight*/
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

void FloatBits(float f)
{
	int *n = (int *)&f;
	int current_dig = 0;
	int i = 31;
	for(i = 31; i >= 0; i--)
	{		
		current_dig = (*n &(1 << i)) >> i;
		printf("%d",(unsigned int)current_dig);
	}
	printf("\n");
}


