/*******************************************************************************
* NAME: producer_consumer  - fixed size queue (cbuffer) -> 1 mutex +           *
*      2 semaphore                                                             *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  09.01.19                                                      *
*******************************************************************************/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "c_buffer.h"
#include "enum_rd58.h"

#define MAX_STRING 100
#define NUMBER_OF_PRODUCERS 10
#define NUMBER_OF_CONSUMERS 10
#define CBUFFER_CAPACITY 64
#define PRINT_IN_THREAD 10
#define RETURN_ERROR 1
#define SYS_CALL_SUCCESS 0

typedef struct
{
	c_buffer_t *buffer;
	int thread_index;
} args_t;

static pthread_mutex_t lock_cons;
static pthread_mutex_t lock_prod;
static sem_t semaphore_cons;
static sem_t semaphore_prod;
static volatile int semaphore_flag;

void *Consumer(void *buffer)
{
	char **print_message = malloc(sizeof(char *));

	if (NULL == print_message)
	{
		return (NULL);
	}

	while (TRUE)
	{
		sem_wait(&semaphore_cons);

		if (0 == semaphore_flag)
		{
			free(print_message);
			print_message = NULL;
			return (NULL);
		}

		pthread_mutex_lock(&lock_cons);

		CBufferRead(buffer, print_message, sizeof(char *));
		printf("Consumer ID: %d -> %s\n", (int)pthread_self(), *print_message);

		free(*print_message);
		*print_message = NULL;
		sem_post(&semaphore_prod);
		pthread_mutex_unlock(&lock_cons);
	}

	free(print_message);
	print_message = NULL;
	return (NULL);
}

void *Producer(void *CBuffer_index_void)
{
	int i = 0;
	args_t *temp_buffer = CBuffer_index_void;
	c_buffer_t *buffer = temp_buffer->buffer;
	int thread_index = temp_buffer->thread_index;

	for (i = 0; i < PRINT_IN_THREAD; ++i)
	{
		char *message = malloc(MAX_STRING);

		if (NULL == message)
		{
			return (NULL);
		}

		sprintf(message, "Thread %d : %d", thread_index, i);
		sem_wait(&semaphore_prod);
		pthread_mutex_lock(&lock_prod);

		CBufferWrite(buffer, &message, sizeof(char *));
		sem_post(&semaphore_cons);
		pthread_mutex_unlock(&lock_prod);
		sleep(1);
	}

	return (NULL);
}

int main()
{
	c_buffer_t *buffer = NULL;
	int i;
	int counter_semaphore;
	pthread_t consumer_threads[NUMBER_OF_CONSUMERS];
	pthread_t producers_thread[NUMBER_OF_PRODUCERS];
	args_t buffer_index[NUMBER_OF_PRODUCERS];

	semaphore_flag = 1;

	buffer = CBufferCreate(CBUFFER_CAPACITY * sizeof(char *));
	if (NULL == buffer)
	{
		return (RETURN_ERROR);
	}

	if (sem_init(&semaphore_cons, 0, 0) != SYS_CALL_SUCCESS)
	{
		exit(1);
	}

	if (sem_init(&semaphore_prod, 0, CBUFFER_CAPACITY) != SYS_CALL_SUCCESS)
	{
		exit(1);
	}

	if (pthread_mutex_init(&lock_prod, NULL) != SYS_CALL_SUCCESS)
	{
		exit(1);
	}

	if (pthread_mutex_init(&lock_cons, NULL) != SYS_CALL_SUCCESS)
	{
		exit(1);
	}

	for (i = 0; i < NUMBER_OF_PRODUCERS; ++i)
	{
		buffer_index[i].buffer = buffer;
		buffer_index[i].thread_index = i;

		if (pthread_create(&producers_thread[i], NULL, Producer, &buffer_index[i])
	        != SYS_CALL_SUCCESS)
		{
			exit(1);
		}
	}

	for (i = 0; i < NUMBER_OF_CONSUMERS; ++i)
	{
		if (pthread_create(&consumer_threads[i], NULL, Consumer, buffer)
	        != SYS_CALL_SUCCESS)
		{
			exit(1);
		}
	}

	for (i = 0; i < NUMBER_OF_PRODUCERS; ++i)
	{
		if (pthread_join(producers_thread[i], NULL) != SYS_CALL_SUCCESS)
		{
			exit(1);
		}
	}

	sem_getvalue(&semaphore_cons, &counter_semaphore);

	while (counter_semaphore != 0)
	{
		sem_getvalue(&semaphore_cons, &counter_semaphore);
	}

	semaphore_flag = 0;

	for (i = 0; i < NUMBER_OF_CONSUMERS; ++i)
	{
		if (sem_post(&semaphore_cons) != SYS_CALL_SUCCESS)
		{
			exit(1);
		}
	}

	for (i = 0; i < NUMBER_OF_CONSUMERS; ++i)
	{
		if (pthread_join(consumer_threads[i], NULL) != SYS_CALL_SUCCESS)
		{
			exit(1);
		}
	}

	sem_destroy(&semaphore_cons);
	sem_destroy(&semaphore_prod);
	pthread_mutex_destroy(&lock_cons);
	pthread_mutex_destroy(&lock_prod);
	CBufferDestroy(&buffer);

	return (0);
}
