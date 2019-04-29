/*******************************************************************************
* NAME: uniqe id                                                               *
*                                                                              *
* PURPOSE:                                                                     *
*                                                                              *
* AUTHOR: dor yadidi                                                           *
* DATE UPDATED:  14.11.18                                                      *
*******************************************************************************/
#include <stdio.h>
#include <assert.h> /*assert*/
#include <time.h>
#include <stdlib.h>
#include "uid.h"

#define SYS_CALL_PASS(sys_call_function)      \
	if (-1 == sys_call_function)         \
	{                                    \
		exit(1);                         \
	}

#define ERROR -1
pthread_mutex_t sequence_mutex = PTHREAD_MUTEX_INITIALIZER;

unique_id_t UIDCreate()
{
	static int sequence;
	unique_id_t u_id;
	u_id.time = time(NULL);
	u_id.thread_id = pthread_self();
	u_id.sequence = sequence;
	++sequence;

	return (u_id);
}

bool UIDIsSame(const unique_id_t uid1, const unique_id_t uid2)
{
	if(uid1.time == uid2.time && uid1.thread_id == uid2.thread_id &&
	   uid1.sequence && uid2.sequence)
	{
		return (TRUE);
	}

	return (FALSE);
}

bool UIDIsBad(const unique_id_t uid)
{
	if(uid.time == ERROR)
	{
		return (TRUE);
	}

	return (FALSE);
}

unique_id_t UIDGetBad()
{
	unique_id_t u_id;
	u_id.time = ERROR;
	u_id.sequence = ERROR;

	return (u_id);
}
