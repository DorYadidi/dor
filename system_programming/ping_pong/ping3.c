/*******************************************************************************
* NAME: Ping Pong - parent child                                               *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  20.01.19                                                      *
*******************************************************************************/

#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <stdio.h> /*printf, PID*/
#include <signal.h> /*signal*/
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static void HandlerPing(int sig)
{
	(void)sig;
}

int main()
{
	pid_t pong_pid;
	char *filename = "./pong3.out";
	struct sigaction handler_pong;
	handler_pong.sa_handler = HandlerPing;
	sigaction(SIGUSR2, &handler_pong, NULL);

	pong_pid = fork();
	if (0 == pong_pid)
	{
		execlp(filename, filename, (char *)NULL);
		exit(1);
	}
	else
	{
		while (1)
		{
			pause();
			printf("\033[1m\033[34mPing!\n \033[0m");
			usleep(10000);
			kill(pong_pid, SIGUSR1);
		}
	}

 	return (0);
}
