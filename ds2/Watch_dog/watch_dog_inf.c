/*******************************************************************************
* NAME: Watch Dog                                                              *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  22.01.19                                                      *
*******************************************************************************/

#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE

#include <stdlib.h> /* getenv, putenv */
#include <pthread.h> /*thread*/
#include <stdio.h> /*perror*/
#include <time.h> /*time_t*/
#include <sys/types.h> /*kill*/
#include <signal.h> /*signal*/
#include <unistd.h>
#include <string.h> /*strcmp*/
#include <fcntl.h> /*sem_t*/
#include <sys/stat.h> /*sem_t*/
#include <semaphore.h> /*sem_t*/
#include <sys/wait.h> /*wait pid*/
#include "watch_dog_inf.h"
#include "task_scheduler.h"

#define SEM_NAME "/semaphore"
#define WD_EXEC "./watch_dog.out"
#define SYS_CALL_SUCCESS 0
#define FREQUENCY_CHECK_ALIVE 5
#define FREQUENCY_SEND_SIGNAL 2
#define ALLOWED_MISSES 3
#define FREQUENCY_CHECK_DNR 1

static sem_t *sem_wd;
static int conter;
static pid_t wd_pid;
pthread_t wd_thread;
bool dnr_flag = FALSE;

static status ForkExec(char *argv[]);
static void *WDThread(void *pid_wd);
static status SendSignal(void *param);
static void HandlerWD(int sig);
static status CheckAlive(void *argv);
static void DestroyTask(void *param);
static void DNRChangeFlag(int sig);
static status CheckDNRflag(void *param);

status KeepMeAlive(char *argv[])
{
	struct sigaction handler_act = {0};
	struct sigaction handler_dnr = {0};
	handler_act.sa_handler = HandlerWD;
	handler_dnr.sa_handler = DNRChangeFlag;
	sigaction(SIGUSR1, &handler_act, NULL);
	sigaction(SIGUSR2, &handler_dnr, NULL);

	if (SUCCESS != ForkExec(argv))
	{
		perror("Fork Exec: FAIL");
		return (FAIL);
	}

	if (SYS_CALL_SUCCESS != pthread_create(&wd_thread, NULL, WDThread, argv))
	{
		return(FAIL);
	}

	return (SUCCESS);
}

/****************************Init Thread and fork******************************/

static status ForkExec(char *argv[])
{
	char *check_env = NULL;

	sem_wd = sem_open(SEM_NAME, O_CREAT | O_RDWR, 0644, 0);
	if (SEM_FAILED == sem_wd)
	{
		perror("sem_open: fail");
		return (FAIL);
	}

	check_env = getenv("WATCH_DOG");
	if (NULL == check_env)
	{
		putenv("WATCH_DOG=WD");
		wd_pid = fork();
		if (0 == wd_pid)
		{
			execvp(WD_EXEC, argv);
			exit(1);
		}

		unsetenv("WATCH_DOG");
	}
	else
	{
		wd_pid = getppid();
	}

	return (SUCCESS);
}

static void *WDThread(void *argv)
{
	char *check_env = NULL;

	task_scheduler_t *scheduler = TaskSchedulerCreate();
	if (NULL == scheduler)
	{
		perror("INIT TASK SCHEDULER FAIL");
		return (NULL);
	}

	if (TRUE == UIDIsBad(TaskSchedulerAddTask(scheduler, time(NULL),
	    FREQUENCY_SEND_SIGNAL, SendSignal, DestroyTask, NULL)))
	{
		TaskSchedulerDestroy(scheduler);
		scheduler = NULL;
		perror("ADD TASK FAIL");
		return (NULL);
	}

	if (TRUE == UIDIsBad(TaskSchedulerAddTask(scheduler,
		time(NULL) + FREQUENCY_CHECK_ALIVE,
		FREQUENCY_CHECK_ALIVE, CheckAlive, DestroyTask, argv)))
	{
		TaskSchedulerDestroy(scheduler);
		scheduler = NULL;
		perror("ADD TASK FAIL");
		return (NULL);
	}

	if (TRUE == UIDIsBad(TaskSchedulerAddTask(scheduler, time(NULL),
	    FREQUENCY_CHECK_DNR, CheckDNRflag, DestroyTask, NULL)))
	{
		TaskSchedulerDestroy(scheduler);
		scheduler = NULL;
		perror("ADD TASK FAIL");
		return (NULL);
	}

	check_env = getenv("WATCH_DOG");
	if (NULL == check_env)
	{
		putenv("WATCH_DOG=24/7");
		if (SYS_CALL_SUCCESS != sem_wait(sem_wd))
		{
			perror("sem_wait: fail");
			exit (1);
		}
	}
	else
	{
		if (SYS_CALL_SUCCESS != sem_post(sem_wd))
		{
			perror ("sem_post: fail");
			exit (1);
		}
	}

	TaskSchedulerStart(scheduler);
	TaskSchedulerDestroy(scheduler);
	scheduler = NULL;
	return (NULL);
}

/********************************Send Signal***********************************/

static status SendSignal(void *param)
{
	(void)param;
	if (SYS_CALL_SUCCESS != kill(wd_pid, SIGUSR1))
	{
		perror("Send Signal fail");
	}

	printf("PID: %d Send Signal\n", getpid());
	return (SUCCESS);
}

static void DestroyTask(void *param)
{
	(void)param;
}

static void HandlerWD(int sig)
{
	(void)sig;
	++conter;
}

/****************************Check Alive***************************************/

static status CheckAlive(void *argv)
{
	char *check_env = NULL;
	(void)argv;

	if ((FREQUENCY_CHECK_ALIVE - ALLOWED_MISSES) > conter)
	{
		printf("PID: %d check fail\n", getpid());

		check_env = getenv("WATCH_DOG");
		wd_pid = fork();
		if (0 == wd_pid)
		{
			if (0 == strcmp(check_env, "24/7"))
			{
				putenv("WATCH_DOG=WD");
				execvp(WD_EXEC, argv);
				exit(1);
			}

			putenv("WATCH_DOG=24/7");
			execvp(*(char **)argv, argv);
			exit(1);
		}
	}
	else
	{
		printf("PID: %d check pass\n", getpid());
	}

	conter = 0;

	return (SUCCESS);
}

/************************************DNR**************************************/
void DNR()
{
	if (SYS_CALL_SUCCESS != kill(wd_pid, SIGUSR2))
		{
			perror("failed to send DNR signal \n");
			return;
		}

		dnr_flag = TRUE;

		if (SYS_CALL_SUCCESS != pthread_join(wd_thread, NULL))
		{
			perror("pthread join error: wd \n");
		}

		if (SYS_CALL_SUCCESS != sem_unlink(SEM_NAME))
		{
			perror ("sem_unlink: fail");
		}

		if (SYS_CALL_SUCCESS != sem_close(sem_wd))
		{
			perror ("sem_destroy: fail");
		}
}

static void DNRChangeFlag(int sig)
{
	(void)sig;
	dnr_flag = TRUE;
}

static status CheckDNRflag(void *param)
{
	(void)param;

	if (TRUE == dnr_flag)
	{
		return (FAIL);
	}

	return (SUCCESS);
}
