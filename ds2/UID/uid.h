#ifndef __DS_UID_H__
#define __DS_UID_H__

#include <time.h> /* time_t*/
#include <sys/types.h>/* pid_t */
#include <unistd.h> /*getpid*/
#include <pthread.h>
#include "enum_rd58.h"


/*******************************************************************************
* NAME: unique id                                                               *
*                                                                              *
* PURPOSE:                                                                     *
*                                                                              *
* AUTHOR: Dor yadidi                                                           *
* DATE UPDATED:  14.11.18                                                      *
*******************************************************************************/

typedef struct uid_s
{
	time_t time;
	pthread_t thread_id;
	int sequence;

} unique_id_t;


/******************************************************************************/

unique_id_t UIDCreate();
/*******************************************************************************
* Creates uid                                                                  *
*                                                                              *
*                                                                              *
* Returns:                                                                     *
*  pointer to memory address of uid                                            *
*******************************************************************************/


bool UIDIsSame(const unique_id_t uid1, const unique_id_t uid2);
/*******************************************************************************
* Returns boolean value of if uid1 and uid2 are the same iterator              *
*                                                                              *
* Parameters:                                                                  *
*  uid1 - unique id                                                             *
*  uid2 - unique id                                                             *
*                                                                              *
* Returns:                                                                     *
*  TRUE - if iterators are the same                                            *
*  FALSE - if iteratos are not the same                                        *
*******************************************************************************/

bool UIDIsBad(const unique_id_t uid);
/*******************************************************************************
* Returns boolean value of if uid contains wrong id                            *
*                                                                              *
* Parameters:                                                                  *
*  uid - unique id                                                             *
*                                                                              *
* Returns:                                                                     *
*  TRUE - if iterators are the same                                            *
*  FALSE - if iteratos are not the same                                        *
*******************************************************************************/

unique_id_t UIDGetBad();
/*******************************************************************************
* Returns bad uid                                                              *
*******************************************************************************/



#endif
