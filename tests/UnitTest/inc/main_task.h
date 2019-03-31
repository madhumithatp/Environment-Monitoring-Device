#ifndef MAIN_TASK_H
#define MAIN_TASK_H


#include <pthread.h>
#include <time.h>
#include "printtime.h"
#include "light_task.h"
#include "temperature_task.h"
#include "logger_task.h"
#include "socket_task.h"
#include "common.h"
#include "posix_timer.h"

#define MQ_MAIN "/msgqueue_main"
#define HB_LIMIT 	(10)

#define NUM_OF_THREADS 4


typedef struct
{
	char *FileName;
}StructThread;
StructThread MyThreads[NUM_OF_THREADS];

pthread_t threadID[NUM_OF_THREADS];
timer_t hb_timerID;
pthread_mutex_t hb_status;
int heartbeat_count[NUM_OF_THREADS];



/**
 * @brief  initialize main task attributes
 * 
 * @return int 
 */


int main_task_init();
/**
 * @brief 
 * 
 */
return_status create_threads();
/**
 * @brief 
 * 
 */
return_status join_threads();
/**
 * @brief handler for heartbeat
 * 
 */
void heartbeat_handler();
/**
 * @brief hb check 
 * 
 */
void main_task_response();

/**
 * @brief logging exits for all threads
 * 
 */
void log_exit_all();

#endif