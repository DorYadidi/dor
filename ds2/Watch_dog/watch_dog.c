/*******************************************************************************
* NAME: Watch Dog                                                              *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  22.01.19                                                      *
*******************************************************************************/
#include <stdio.h> /*perror*/
#include <pthread.h> /*thread*/
#include "watch_dog_inf.h"

extern pthread_t wd_thread;

int main (int argc, char *argv[])
{
	(void)argc;
	printf("I am WATCH_DOG\n");
	KeepMeAlive(argv);

	if (0 != pthread_join(wd_thread, NULL))
	{
		perror("pthread join error: wd \n");
	}


	return (0);
}


/*gc -I../include watch_dog.c watch_dog_inf.c ../Task_Scheduler/task.c ../Task_Scheduler/task_scheduler.c ../Doubly_linked_list/d_linked_list.c ../Sorted_List/sorted_list.c ../UID/uid.c ../Priority_Queue/priority_queue.c -l pthread -o watch_dog.out
*/
