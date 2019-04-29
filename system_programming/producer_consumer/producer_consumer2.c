/*******************************************************************************
* NAME: producer_consumer  - multiple producer Mutex +                         *
*        and consumer with Busy Wait                                           *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  09.01.19                                                      *
*******************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "queue.h"

#define MAX_STRING 100
#define NUMBER_OF_THREADS 10
#define PRINT_IN_THREAD 5
#define RETURN_ERROR 1
#define SYS_CALL_SUCCESS 0

typedef struct
{
	queue_t *queue;
	int index;

} args_t;

static pthread_mutex_t lock;
static volatile int busy_wait_flag;

void *Consumer(void *queue)
{
	while (busy_wait_flag != 0)
	{
		void *message = NULL;
		if (FALSE == QueueIsEmpty(queue))
		{
			pthread_mutex_lock(&lock);
			message = QueueDequeue(queue);
			pthread_mutex_unlock(&lock);
			printf("%s\n", (char *)message);
			free(message);
			message = NULL;
		}
	}

	return (NULL);
}

void *Producer(void *queue_mutex)
{
	int i = 0;
	args_t *queue_index = queue_mutex;
	queue_t *queue = queue_index->queue;
	int index = queue_index->index;

	for (i = 0; i < PRINT_IN_THREAD; ++i)
	{
		char *message = (char *)malloc(MAX_STRING);
		if (NULL == message)
		{
			exit (1);
		}

		sprintf(message, "Thread %d : %d", index, i);
		pthread_mutex_lock(&lock);

		if (SUCCESS != QueueEnqueue(queue, message))
		{
			pthread_mutex_unlock(&lock);
			return (NULL);
		}

		pthread_mutex_unlock(&lock);
		sleep(1);
	}

	return (NULL);
}

int main()
{
	queue_t *queue = NULL;
	int i;
	pthread_t consumer_thread;
	pthread_t produser_thread[NUMBER_OF_THREADS];
	args_t queue_mutex[NUMBER_OF_THREADS];
	busy_wait_flag = 1;

	queue = QueueCreate();
	if (NULL == queue)
	{
		return (RETURN_ERROR);
	}

	if (pthread_mutex_init(&lock, NULL) != SYS_CALL_SUCCESS)
	{
		exit(1);
	}

	for (i = 0; i < NUMBER_OF_THREADS; ++i)
	{
		queue_mutex[i].queue = queue;
		queue_mutex[i].index = i;

		if (pthread_create(&produser_thread[i], NULL, Producer, &queue_mutex[i]) !=
	        SYS_CALL_SUCCESS)
		{
			exit(1);
		}
	}

	if (pthread_create(&consumer_thread, NULL, Consumer, queue) !=
	    SYS_CALL_SUCCESS)
	{
		exit(1);
	}

	for (i = 0; i < NUMBER_OF_THREADS; ++i)
	{
		if (pthread_join(produser_thread[i], NULL) != SYS_CALL_SUCCESS)
		{
			exit(1);
		}
	}

	busy_wait_flag = 0;

	if (pthread_join(consumer_thread, NULL) != SYS_CALL_SUCCESS)
	{
		exit(1);
	}

	pthread_mutex_destroy(&lock);
	QueueDestroy(&queue);

	return (0);
}
