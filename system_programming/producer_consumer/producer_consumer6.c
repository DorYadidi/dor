/*******************************************************************************
* NAME: Producer Consumer Problem single producers / multiple consumers        *
*       condition variable, mutex, semaphore                                   *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  14.01.19                                                      *
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CAPACITY 10
#define PRINT_IN_THREAD 10
#define NUMBER_OF_CONSUMERS  5
#define SYS_CALL_SUCCESS 0

static volatile int is_empty = 1;
static volatile int counter_cons = 0;
static pthread_mutex_t lock;
static sem_t sem_producer;
static pthread_cond_t cv;

typedef struct args_s
{
	int *message;
	int index;
} args_t;

void UnlockMutex(void *lock)
{
    pthread_mutex_unlock((pthread_mutex_t *)lock);
}

void *Consumer(void *args)
{
    pthread_cleanup_push(UnlockMutex, (void *)(&lock));

    while (1)
	{
    	pthread_mutex_lock(&lock);

	    while (counter_cons != ((args_t *)args)->index + 1)
	    {
	        pthread_cond_wait(&cv, &lock);
	    }

	    printf("THREAD ID %d: Print Number %d\n",
		       ((args_t *)args)->index,*((args_t *)args)->message);

	    --counter_cons;
		pthread_cond_broadcast(&cv);

	    if (0 == counter_cons)
	    {
	        sem_post(&sem_producer);
	    }

	    pthread_mutex_unlock(&lock);
    }

    pthread_cleanup_pop(1);
    return (NULL);
}

void *Producer(void *args)
{
    int i = 0;

    for (i = 0; i < PRINT_IN_THREAD ; ++i)
    {
        sem_wait(&sem_producer);
		pthread_mutex_lock(&lock);
		*((args_t *)args)->message = i;

        counter_cons = NUMBER_OF_CONSUMERS;
        pthread_cond_broadcast(&cv);
		pthread_mutex_unlock(&lock);
    }

    return (NULL);
}

int main()
{
    int i = 0;
    int message = 0;

    pthread_t producer;
	pthread_t consumer_threads[NUMBER_OF_CONSUMERS];
	args_t consumer_args[NUMBER_OF_CONSUMERS];
	args_t producer_args;

    if (SYS_CALL_SUCCESS != pthread_mutex_init(&lock, NULL))
    {
        exit(1);
    }

    if (SYS_CALL_SUCCESS != sem_init(&sem_producer, 0, 1))
    {
        exit(1);
    }

    if (SYS_CALL_SUCCESS != pthread_cond_init(&cv, 0))
    {
        exit(1);
    }

    for (i = 0; i < NUMBER_OF_CONSUMERS ; ++i)
    {
		consumer_args[i].message = &message;
		consumer_args[i].index = i;
        if (SYS_CALL_SUCCESS !=
			pthread_create(&consumer_threads[i], NULL, Consumer, &consumer_args[i]))
        {
            exit(1);
        }
    }

	producer_args.message = &message;
	producer_args.index = i;

    if (SYS_CALL_SUCCESS != pthread_create(&producer, NULL, Producer, &producer_args))
    {
        exit(1);
    }

    pthread_join(producer, NULL);

    for (i = 0; i < NUMBER_OF_CONSUMERS ; ++i)
    {
        pthread_cancel(consumer_threads[i]);
    }

    for (i = 0; i < NUMBER_OF_CONSUMERS ; ++i)
    {
        pthread_join(consumer_threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    sem_destroy(&sem_producer);
    pthread_cond_destroy(&cv);

    return (0);
}
