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
sem_t *sem_pong;

static void HandlerPong(int sig)
{
	(void)sig;
}

int main()
{
	pid_t parent = getppid();
	struct sigaction handler_ping;
	handler_ping.sa_handler = HandlerPong;
	sigaction(SIGUSR1, &handler_ping, NULL);

	sem_pong = sem_open(SEM_NAME, O_CREAT);
	if (SEM_FAILED == sem_pong)
	{
		perror ("sem_open: fail");
		exit (1);
	}

	if (-1 == sem_unlink(SEM_NAME))
	{
		perror ("sem_unlink : fail");
		exit (1);
	}

	if (-1 == sem_wait(sem_pong))
	{
		perror ("sem_wait: fail");
		exit (1);
	}


	kill(parent, SIGUSR2);

	while (1)
	{
		pause();
		printf("\033[1m\033[32m Pong!!!!\n \033[0m");
		usleep(10000);
		kill(parent, SIGUSR2);
	}

 	return (0);
}
