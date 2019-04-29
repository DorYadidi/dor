/*******************************************************************************
* NAME: Ping Pong - parent child                                               *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  20.01.19                                                      *
*******************************************************************************/

#define _DEFAULT_SOURCE
#define _XOPEN_SOURCE

#include <stdio.h> /*printf, PID*/
#include <wait.h> /*wait*/
#include <signal.h> /*signal*/
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

pid_t pid_child;

void HandlerParnt(int sig)
{
	(void)sig;
}

void HandlerChild(int sig)
{
	(void)sig;
}

int main()
{
	struct sigaction child;
	struct sigaction parent;
	child.sa_handler = HandlerChild;
	parent.sa_handler = HandlerParnt;
	pid_child = fork();

	while (0 == pid_child)
    {
  		sigaction(SIGUSR2, &child, NULL);
  		printf("\033[1m\033[33mI am the child in this process\n \033[0m");
		usleep(100);
		kill(getppid(), SIGUSR1);
		pause();
	}

	while (0 != pid_child)
	{
		sigaction(SIGUSR1, &parent, NULL);
		pause();
		printf("\033[1m\033[32mI am the Parent in this process\n\033[0m");
		usleep(100);
		kill(pid_child, SIGUSR2);
	}

	return (0);
}
