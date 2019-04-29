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
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <semaphore.h>

#define SEM_NAME "/semaphore"
sem_t *sem_ping;

static void HandlerPing(int sig)
{
	(void)sig;
}

int main()
{
	pid_t pong_pid;
	char *filename = "./pong4.out";
	struct sigaction handler_pong;
	handler_pong.sa_handler = HandlerPing;
	
	sem_ping = sem_open(SEM_NAME, O_CREAT, 0644, 0);
	if (SEM_FAILED == sem_ping)
	{
		perror("sem_open: fail");
		exit (1);
	}

	pong_pid = fork();

	if (0 == pong_pid)
	{
		execlp(filename, filename, (char *)NULL);
		exit(1);
	}
	else
	{
		sleep(2);
		sigaction(SIGUSR2, &handler_pong, NULL);

		if (-1 == sem_post(sem_ping))
		{
			perror ("sem_post: fail");
			exit(1);
		}

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
