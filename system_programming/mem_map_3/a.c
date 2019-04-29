#include <stdio.h>
#include "header.h"

int global_bss;
int global_data = 1;

void Foo()
{
	printf("I am Foo\n");
}
