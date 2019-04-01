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

volatile sig_atomic_t kill_signal_temperature;
volatile float recent_temperature;

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

/**
 * @brief 
 * 
 */

float latest_temperature(unit_temp unit);


#endif