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

pid_t pid_pong;

void HandlerPong(int sig, siginfo_t *act, void *param)
{
	(void)param;
	(void)sig;
	pid_pong = act->si_pid;
}

int main()
{
	struct sigaction handler_pong;
	handler_pong.sa_flags = SA_SIGINFO;
	handler_pong.sa_sigaction = HandlerPong;
	printf("This is a Pid: %d\n",(int)getpid());
	sigaction(SIGUSR2, &handler_pong, NULL);

	while (1)
    {
		pause();
		printf("\033[1m\033[33m Ping!!!\n \033[0m");
		usleep(100);
		kill(pid_pong, SIGUSR1);
	}

	return (0);
}
