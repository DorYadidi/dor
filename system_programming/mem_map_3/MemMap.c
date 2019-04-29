#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include "header.h"

void MyFunc()
{
	printf("I am MyFunc\n");
}

int main()
{
	void *handler = NULL;
	void (*func_bar2)(void);
	MyFunc();
	printf("Address MyFunc: %p\n", MyFunc);
	Foo();
	printf("Address Foo: %p\n", Foo);
	printf("Address Global in Foo: global_bss %p, global_data %p\n", &global_bss, &global_data);
	Bar1();
	printf("Address Bar1: %p\n", Bar1);

	handler = dlopen("./libso2.so", RTLD_LAZY);
	if (NULL == handler)
	{
		printf("Error dlopen\n");
	}

	*(void **)&func_bar2 = dlsym(handler, "Bar2");
	/*pause();*/

	printf("Address Foo1: %p\n", Foo1);
	printf("Address Foo2: %p\n", Foo2);
	printf("Address Bar2: %p\n", *func_bar2);
	func_bar2();


	dlclose(handler);

	return (0);
}
