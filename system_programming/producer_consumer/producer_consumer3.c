/*******************************************************************************
* NAME: producer_consumer  - multiple producer Mutex +                         *
*        and consumer with Semaphores                                          *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  09.01.19                                                      *
*******************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include "queue.h"

#define MAX_STRING 100
#define NUMBER_OF_THREADS 100
#define PRINT_IN_THREAD 5
#define RETURN_ERROR 1
#define SYS_CALL_SUCCESS 0

typedef struct
{
	queue_t *queue;
	int index;

} args_t;

static sem_t semaphore;
static pthread_mutex_t lock;
static volatile int semaphore_flag;


void *Consumer(void *queue)
{
	while (0 != semaphore_flag)
	{
		void *message = NULL;
		sem_wait(&semaphore);

		if (0 == semaphore_flag)
		{
			return (NULL);
		}

		pthread_mutex_lock(&lock);
		message = QueueDequeue(queue);
		pthread_mutex_unlock(&lock);
		printf("Consumer ID: %d -> %s\n" , (int)pthread_self(), (char *)message);
		free(message);
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
		sem_post(&semaphore);
		sleep(1);
	}

	return (NULL);
}

int main()
{
	queue_t *queue = NULL;
	int i;
	pthread_t consumer_thread[NUMBER_OF_THREADS];
	pthread_t produser_thread[NUMBER_OF_THREADS];
	args_t queue_mutex[NUMBER_OF_THREADS];
	semaphore_flag = 1;

	queue = QueueCreate();
	if (NULL == queue)
	{
		return (RETURN_ERROR);
	}

	if (sem_init(&semaphore, 0, 0) != SYS_CALL_SUCCESS)
	{
		exit(1);
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

	for (i = 0; i < NUMBER_OF_THREADS; ++i)
	{
		if (pthread_create(&consumer_thread[i], NULL, Consumer, queue) !=
	        SYS_CALL_SUCCESS)
		{
			exit(1);
		}
	}

	for (i = 0; i < NUMBER_OF_THREADS; ++i)
	{
		if (pthread_join(produser_thread[i], NULL) != SYS_CALL_SUCCESS)
		{
			exit(1);
		}
	}

	semaphore_flag = 0;

	for (i = 0; i < NUMBER_OF_THREADS; ++i)
	{
		sem_post(&semaphore);
	}

	for (i = 0; i < NUMBER_OF_THREADS; ++i)
	{
		if (pthread_join(consumer_thread[i], NULL) != SYS_CALL_SUCCESS)
		{
			exit(1);
		}
	}

	pthread_mutex_destroy(&lock);
	sem_destroy(&semaphore);
	QueueDestroy(&queue);

	return (0);
}
