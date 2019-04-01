/**
 * @file posix_timer.c
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief File for registering, starting an stoping Posix Timer to log Sensor Data
 * @version 0.1
 * @date 2019-03-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "posix_timer.h"

int create_posixtimer(timer_t * timerID, void (*timer_callback)())
{
    int ret_value = 0;
    struct sigevent se;

    if(timerID == NULL)
        {
            return -1;
            printf("NULL Pointer \n");
        }

    se.sigev_notify = SIGEV_THREAD;
    se.sigev_notify_function = timer_callback;
    se.sigev_notify_attributes = NULL;

    ret_value = timer_create(CLOCK_REALTIME, &se, timerID);

    return ret_value;
}

int start_posixtimer(timer_t timerID, uint64_t sec)
{
    int retval = 0;
    struct itimerspec ts;

    ts.it_value.tv_sec = sec;    
    ts.it_value.tv_nsec = 0;    

    ts.it_interval.tv_sec = ts.it_value.tv_sec;
	ts.it_interval.tv_nsec = ts.it_value.tv_nsec;

    retval = timer_settime(timerID,0,&ts,NULL);
    return (retval);
}


int stop_posixtimer(timer_t timerID)
{
    int retval = 0;
    struct itimerspec ts;

    ts.it_value.tv_sec = 0;
	ts.it_value.tv_sec = 0;
	ts.it_interval.tv_sec = 0;
	ts.it_interval.tv_sec = 0;

    return (timer_settime(timerID,0,&ts,NULL));
}

int delete_posixtimer(timer_t timerID)
{
    return(timer_delete(timerID));
}