#include <stdio.h>
#include <pthread.h>

#define COUNT 0x80000000L

size_t fixed_count;

void *Count(void *counter)
{
	size_t i = 0;

	for (i = 0; i < fixed_count; ++i)
	{
		*(size_t *)counter += 1;
	}

	return (NULL);
}

int main(int argc, char **argv)
{
	size_t i = 0;
	size_t n_threads = argv[1] - '0';
	size_t sum_of_counters = 0;
	pthread_t threads[1000];
	size_t counter[1000];
	(void)argc;

	fixed_count = COUNT / n_threads;

	for (i = 0; i < n_threads; ++i)
	{
		pthread_create(&threads[i * 15], NULL, Count, &counter[i * 15]);
	}

	for (i = 0; i < n_threads; ++i)
	{
		pthread_join(threads[i * 15], NULL);
	}

	for (i = 0; i < n_threads; ++i)
	{
		sum_of_counters += counter[i * 15];
	}
	printf("sum of all counters: %lu\n", sum_of_counters);

	return (0);
}
