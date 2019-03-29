#ifndef MAIN_TASK_H
#define MAIN_TASK_H


#include <pthread.h>
#include <time.h>
#include "printtime.h"
#include "light_task.h"
#include "temperature_task.h"
#include "logger_task.h"
#include "common.h"
#include "timer.h"
#define MQ_MAIN "/msgqueue_main"
static mqd_t mq_main;


typedef struct
{
	char *FileName;
}StructThread;
StructThread MyThreads[3];

pthread_t threads1, threads2, threads3;
timer_t hb_timerID;

#endif