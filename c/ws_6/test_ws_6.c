#include <stdio.h>
#include "ws_6.c"


int main()
{

	unsigned int arr[8] = {1,7,100000,4,5,146,13};
	int a= 3;
	int b= 5;
	int *p_a = &a;
	int *p_b = &b;
	float num = -118.625;
	
	
	printf("pow2: work %f \n", Pow2(5,0));
	
	printf("pow2: work %f \n", Pow2(5,-1));
	/*if(Pow2(5,0) != 5)
	{
		printf("pow2: error1 \n");
	}

	if(Pow2(5,-1) == 1/10)
	{
		printf("pow2: work %f \n", Pow2(5,-1));
	}
	*/
	if (PowOf2Loop(0) == 0)
	{
		printf ("PowOf2Loop Work %d\n", PowOf2Loop(0));	
	}
	else 
	{
		printf ("PowOf2Loop Dont Work");
	}

	if (PowOf2(8) == 1)
	{
		printf ("PowOf2 Work %d\n", PowOf2(8));	
	}
	else 
	{
		printf ("PowOf2 Dont Work");
	}

	
	if (AddOne(12) == 13)
	{
		printf ("AddOne Work %d\n", AddOne(12));
	}
	else 
	{
		printf ("AddOne Dont Work");
	}

	if (ByteMirrorLoop(1000) == 398458880)
	{
	printf ("ByteMirrorLoop Work %d\n", ByteMirrorLoop(1000));	
	}
	else 
	{
		printf ("ByteMirrorLoop Dont Work\n");
	}	
	
	if (ByteMirror(1000) == 398458880)
	{
	printf ("ByteMirror Work %d\n", ByteMirror(1000));	
	}
	else 
	{
		printf ("ByteMirror Dont Work\n");
	}
	

	Arry3BitOn(arr, 8);
	
	if (F1(35) == 1)
	{
		printf ("F1 Work %d\n", F1(35));	
	}
	else 
	{
		printf ("F1 Dont Work");
	}	

	
	if (F2(6) == 1)
	{
		printf ("F2 Work %d\n", F2(6));	
	}
	else 
	{
		printf ("F2 Dont Work");
	}	

	if (ClosestNum(849) == 848)
	{
		printf ("ClosestNum Work %d\n", ClosestNum(849));	
	}
	else 
	{
		printf ("ClosestNum Dont Work");
	}
	
	Swap(p_a, p_b);
	if (a == 5 && b == 3)
	{
		printf ("Swap Work\n");	
	}	
	else 
	{
		printf ("Swap dont Work\n");	
	}
	
	if (BitsOnLoop(100000) == 6)
	{
		printf ("BitsOnLoop Work %d\n", BitsOnLoop(100000));	
	}
	else
	{
	printf ("BitsOnLoop dont Work\n");	
	}

	if (BitsOn(100000) == 6)
	{
		printf ("BitsOn Work %d\n", BitsOn(100000));	
	}
	
	else
	{
		printf ("BitsOn dont Work\n");	
	}

	
	FloatBits(num);
	
	return 0;
}	
