#include <stdio.h>

float Power10(int num)
/*             int nun = numbre of pow                                        *
 *             funcs check power of 10                                        */
{
	float sum = 1;
	int b = 10;
	int i;    
	if (0 > num)
        { 
           num =-num;
           b = 1 / b;
        } 
          
    for(i = 1; i <= num; i++)
    {
        sum = b * sum;
    }
    
    
    return sum;
}

void Swap(int *n_1 , int *n_2)
/*             int *n1  = pointer to number 1                                 *
 *             int *n2  = pointer to number 2                                 *
 *             funcs swap two numbers                                         */
{
	int temp;
	temp=*n_1;
    *n_1=*n_2;
    *n_2=temp;
}

int Flip(int number)
/*             int *n1  = pointer to number 1                                 *
 *             int *n2  = pointer to number 2                                 *
 *             function flip number                                           */
{
	int newnumber=0;
    while(number!=0)
    {
    	newnumber*=10;
        newnumber+=(number%10);
        number /=10;
          
    }
    return newnumber;
}



