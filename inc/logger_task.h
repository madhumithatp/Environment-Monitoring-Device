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

#define MQ_LOG  "/msgqueue_log"

#define Filename "log.txt"

mqd_t mq_log;


#endif /* LOGGER_TASK_H_ */
