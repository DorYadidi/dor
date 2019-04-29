/*******************************************************************************
* NAME: producer_consumer  - single  producer and consumer with Busy Wait      *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  09.01.19                                                      *
*******************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_STRING 100
#define PRINT_MESSAGE 1
#define NUM_OF_PRINTS 5

static volatile int empty;
static volatile int busy_wait_flag;

void *ConsumerBWait(void *message)
{
	while (busy_wait_flag)
	{
		if (PRINT_MESSAGE == empty)
		{
			printf("%s", (char *)message);
			empty = 0;
		}
	}

	return (NULL);
}

int main()
{
	char *message = NULL;
	int i = 0;
	pthread_t thread_id;

	message =(char *)malloc(MAX_STRING);
	if (NULL == message)
	{
		return (1);
	}

	empty = 0;
	busy_wait_flag = 1;

	if (pthread_create(&thread_id, NULL, ConsumerBWait, message) != 0)
	{
		exit(1);
	}

	for (i = 0; i < NUM_OF_PRINTS; ++i)
	{
		sprintf(message, "Message: %d\n", i);
		empty = PRINT_MESSAGE;
		sleep(1);
	}

	free(message);
	message = NULL;
	busy_wait_flag = 0;

	if (pthread_join(thread_id, NULL))
	{
		exit(1);
	}

	return (0);
}
