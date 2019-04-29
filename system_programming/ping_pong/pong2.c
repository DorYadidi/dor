/*******************************************************************************
* NAME: Ping Pong - parent child                                               *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  20.01.19                                                      *
*******************************************************************************/

#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <stdio.h> /*printf, PID*/
#include <wait.h> /*wait*/
#include <signal.h> /*signal*/
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void HandlerPing(int sig)
{
	(void)sig;
}

int main(int argc, char **argv)
{
	pid_t ping_pid = atoi(argv[1]);
	struct sigaction handler_ping;
	(void)argc;

	handler_ping.sa_handler = HandlerPing;
	sigaction(SIGUSR1, &handler_ping, NULL);

	kill(ping_pid, SIGUSR2);

	while (1)
    {
		pause();
		printf("\033[1m\033[32m Pong!!!!\n \033[0m");
		usleep(100);
		kill(ping_pid, SIGUSR2);
	}

	return (0);
}
