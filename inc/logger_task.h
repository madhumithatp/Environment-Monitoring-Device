/**
 * @file logger_task.h
 * @author author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief 
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef LOGGER_TASK_H_
#define LOGGER_TASK_H_

#include "common.h"
#include "driver_i2c.h"
#include"printtime.h"

#define MQ_LOG  "/msgqueue_log"

#define Filename "log.txt"
volatile sig_atomic_t kill_signal_logger;


/**
 * @brief Initilaize arrtibutes for message queue
 * 
 * @return mqd_t 
 */
mqd_t log_task_mq_init();

/**
 * @brief Callback for logger thread
 * 
 * @return void* 
 */
void * logger_task();
#endif /* LOGGER_TASK_H_ */
