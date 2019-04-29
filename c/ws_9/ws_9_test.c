#include "ws_9.h"

void TestMemset();
void TestMemcpy();
void TestMemmove();
void TestIsLittleEndian();
void TestAtoi36();
void TestItoa36();
void TestOnlyTwice();


int main ()
{
     
     TestMemset();
     TestMemcpy();
     TestMemmove();
     TestAtoi36();
     TestItoa36();
     TestOnlyTwice();
     TestIsLittleEndian();



    return 0;
}




void TestMemset()
{
	char str[50];
	char str2[50];
	strcpy(str,"This is string.h library function");
	strcpy(str2,"This is string.h library function");
	if (strcmp(Memset(str,'A',11), memset(str2,'A',11)) == 0)
	{
		printf("Memset work!\n");
	}
	else
	{
		printf("Memset dont work!\n");
	}

}

void TestMemcpy()
{
   const char src[50] = "heelo rd58 gg weqeq";
   char dest[50];
   char dest2[50];
   strcpy(dest, "sdsdaadaa");
   if (strcmp(Memcpy(dest, src, strlen(src)+1), memcpy(dest2, src, strlen(src)+1)) == 0)
	{
		printf("Memcpy work!\n");
	}
	else
	{
		printf("Memcpy dont work!\n");
	}
   
}

void TestMemmove()
{
	char src[50] = "heelo rd58 gg weqeq";
	char src2[50] = "heelo rd58 gg weqeq";
	if (strcmp(Memmove(src+5, src, 17), memmove(src2+5, src2, 17)) == 0)
	{
		printf("Memmove work!\n");
	}
	else
	{
		printf("Memmove dont work!\n");
	}

}


void TestAtoi36()
{
	char test[4]="11A"; 
	int i = Atoi36(test, 16);
	if (282 == i)
	{
		printf("Atoi36 work!\n");
	}
	else
	{
		printf("Atoi36 dont work!\n");
	}

}





void TestIsLittleEndian()
{
	int i = IsLittleEndian();
	if (1 == i)
	{
		printf("IsLittleEndian work!\n");
	}
	else
	{
		printf("IsLittleEndian dont work!\n");
	}

}



void TestItoa36()
{
	char charArray[50];
	Itoa36(1234, charArray, 16); 
	if (strcmp(charArray, "4D2") == 0)
	{
		printf("Itoa36 work!\n");
	}
	else
	{
		printf("Itoa36 dont work!\n");
	}


}

void TestOnlyTwice()
{
	char a[] = "1AAA2345612abc";
	char b[] = "2348A9789999aba";
	char c[] = "2avA";
	OnlyTwice(a, 14, b, 15, c, 4);
	printf ("if 34b OnlyTwice Work!\n");
	

}














