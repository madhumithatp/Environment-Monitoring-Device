/**
 * @file temperature_task.h
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief 
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef TEMPERATURE_TASK_H
#define TEMPERATURE_TASK_H

#include "tmp102.h"
#include "common.h"
#include "posix_timer.h"
#define MQ_TEMPERATURE          "/msgqueue_temperature"


volatile float temperature;

/*
 * @brief initialize the queue
 * 
 * @return mqt_t 
 */
mqd_t temperature_task_mq_init();

/**
 * @brief Timer Handler for Temperature Sensor
 * 
 */
void temperature_task_timer_handler();

/**
 * @brief Thread Callback Function
 * 
 * @return void* 
 */
void* temperature_task();




#endif