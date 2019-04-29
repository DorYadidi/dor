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

static void HandlerPong(int sig)
{
	(void)sig;
}

int main()
{
	struct sigaction handler_ping;
	handler_ping.sa_handler = HandlerPong;
	sigaction(SIGUSR1, &handler_ping, NULL);
	kill(getppid(), SIGUSR2);

	while (1)
	{
		pause();
		printf("\033[1m\033[32m Pong!!!!\n \033[0m");
		usleep(10000);
		kill(getppid(), SIGUSR2);
	}

 	return (0);
}
