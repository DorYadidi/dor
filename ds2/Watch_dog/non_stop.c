/*******************************************************************************
* NAME: Watch Dog                                                              *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  22.01.19                                                      *
*******************************************************************************/
#include <stdio.h> /*perror*/
#include <unistd.h> /*sleep*/
#include "watch_dog_inf.h"

#define DNR_TIMER 10

int main (int argc, char *argv[])
{
	int sleep_timer = DNR_TIMER;
	(void)argc;
	printf("I am 24/7\n");
	KeepMeAlive(argv);

	while (sleep_timer != 0)
	{
		sleep_timer = sleep(sleep_timer);
	}

	DNR();

	return (0);
}
