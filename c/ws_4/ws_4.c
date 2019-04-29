#include <stdio.h>

void ClickByIf();
void ClickBySwitch();
void ClickByLut();
int flag=1;
void AClick();
void TClick();
void EscClick();

int main()
{

	ClickByIf();

	ClickBySwitch();
	
	ClickByLut();
	
	return 0;
}



void ClickByIf()
{
	int io = 0;
	
	while (1)
	{
		system("stty -icanon -echo");	
		printf("(if) Enter character: \n");
		io = getchar();
		if (io == 'T')
		{
			printf("T pressed\n");
		}
		else if (io == 'A')
		{
			printf("A pressed\n");	
		}
		else if (io == 27)
		{
			  printf("exit\n");
			  system("stty icanon echo");	
			  break;
		}
		else 
		{
			printf("no A and T\n");	
	
		}
		
	}

}

void ClickBySwitch()
{
		int io = 0;
		while (1)
	{
		system("stty -icanon -echo");	
		printf("(switch) Enter character: \n");
		io = getchar();
		switch(io) 
		{
			case ('T'):
				printf("T pressed\n");
				break;
			
			case ('A'):
				printf("A pressed\n");
				break;
			
			case 27:
				  printf("exit\n");
				  break;
		
			default: 
			{
				printf("no A and T\n");	
	
			}
		}
		if (io == 27)
		{
			  system("stty icanon echo");	
			  break;
		}
		
	}

}


void ClickByLut()
{
	int io=0;
	void (*look_up_table[256])() = {0};
	look_up_table[65] = &AClick;
	look_up_table[84] = &TClick;
	look_up_table[27] = &EscClick;
	system("stty -icanon -echo");
	
	while(flag != 0)
	{
		printf("(LUT) Enter character: \n");
		io=getchar();
		if (65 == io || 84 == io || 27 == io)
		{
			(look_up_table[io]());
		
		}
		else 
		{
		
			printf("no A and T\n");	
		
		}
	
	
	}	
	
	
}

void AClick()
{
	printf("A pressed\n");

}

void TClick()
{
	printf("T pressed\n");

}

void EscClick()
{

	printf("exit\n");
	system("stty icanon echo");	
	flag = 0;
}

