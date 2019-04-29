#include <stdio.h>

int main()
{
    int a = 5;
    int b = 7;
    int *p_a = &a;
/*    ++b;*/
    printf("%d %p\n", *p_a, (void *)p_a);

	++p_a;
/*    printf("%d %p\n", b, (void *)&b);*/
    printf("%d %p\n", *p_a, (void *)p_a);
/*	printf("%p, %p, %s\n", (void *)&b, (void *)p_a, (void *)&b == (void *)p_a ? "YES\n" : "NO\n");*/
    
    return 0;
}

