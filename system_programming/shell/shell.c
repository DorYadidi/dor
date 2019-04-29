/*******************************************************************************
* NAME: Shell Command line                                                     *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  07.01.19                                                      *
*******************************************************************************/

#include <stdlib.h> /*malloc, free*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h> /*strcmp*/

#define MAX_INPUT 80

void SystemShell()
{
	char *command = (char *)malloc(MAX_INPUT);
	if (NULL == command)
	{
		printf("MEMORY_ALLOCATION_FAIL");
		return;
	}

	while(1)
	{
		if (-1 == system("pwd"))
		{
			free(command);
			command = NULL;
			return;
		}

		printf(">");

		if (-1 > scanf("%s", command))
		{
			free(command);
			command = NULL;
			return;
		}

		if (strcmp(command, "exit") == 0)
		{
			free(command);
			command = NULL;
			break;
		}

		if (-1 == system(command))
		{
			free(command);
			command = NULL;
			return;
		}
	}

	free(command);
	command = NULL;
}

/*****************************************************************************/

static void InsertArgv(char **agrv, char *command)
{
    char *delim = " ";
    char *token = NULL;

    token = strtok(command, delim);

    while (token != NULL)
    {
        *agrv = token;
		++agrv;
        token = strtok(NULL, delim);
    }
}


void ForkShell()
{
	char *command = NULL;
	char **argv = (char **)calloc(sizeof(char*), MAX_INPUT);

	pid_t pid;
	if (NULL == argv)
	{
		free(argv);
		argv = NULL;
		printf("MEMORY_ALLOCATION_FAIL");
		return;
	}

	command = (char *)calloc(sizeof(char), MAX_INPUT);
	if (NULL == command)
	{
		printf("MEMORY_ALLOCATION_FAIL");
		return;
	}

	while(1)
	{
		if (-1 == system("pwd"))
		{
			break;
		}

		printf(">");

		if (NULL == gets(command))
		{
			break;
		}

		if (strncmp(command, "exit", 4) == 0)
		{
			break;
		}

		pid = fork();
		if(0 == pid)
		{
			InsertArgv(argv ,command);
			execvp(command, argv);
			exit(0);
		}
		else if (NULL == strchr(command, '&'))
		{
			wait(NULL);
		}
	}

	free(command);
	command = NULL;
	free(argv);
	argv = NULL;
}

int main()
{
	ForkShell();

	return (0);
}
