#include <stdio.h>
#include "ws_1.c" 


void TestPower10 ();
void TestFlip ();

int main ()

{
	TestPower10();
	TestFlip ();
	
	return 0;
}


void TestPower10 ()
{

	if(Power10(5)==100000)
	{
		printf("Work for input 5\n");
	}
	else 
	{
		printf("error for input 5\n");
	}

	
	if(Power10(-5)==1/100000)
	{
		printf("Work for input -5\n");
	}
	else 
	{
		printf("error for input -5\n");
	}
	
	if(Power10(1)==10)
	{
		printf("Work for input 1\n");
	}
	else 
	{
		printf("error for input 1\n");
	}
	
	if(Power10(0)==1)
	{
		printf("Work for input 0\n");
	}
	else 
	{
		printf("error for input 0\n");
	}

}

void TestFlip ()
{
	if (Flip(12340)==4321)
	{
		printf("Work for input 12340\n");
	}
	else 
	{
		printf("error for input 12340\n");
	}
	
	if (Flip(-123)==-321)
    {
		printf("%dWork for input -123\n", Flip(-123));
	}
	else 
	{
		printf("error for input -123\n");
	}
	
	if (Flip(1)==1)
	{
		printf("Work for input 1\n");
	}
	else 
	{
		printf("error for input 1\n");
	}
}
