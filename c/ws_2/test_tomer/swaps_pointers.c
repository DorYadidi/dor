#include <stdio.h>

void SwapPointers(int **a, int **b)
/*Swaps between 2 addresses in the memory*/ 
{

    int* z;
    z = *a;
    *a = *b;
    *b = z;

}
