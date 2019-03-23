/**
 * @file light_task.h
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Light Task Header File
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef LIGHT_TASK_H_
#define LIGHT_TASK_H_

#include "common.h"
#include "apds9301.h"

#define MQ_LIGHT        "/msgqueue_light"

/**
 * @brief Function to initialize Light Message Queue
 * 
 * @return mqd_t 
 */
mqd_t light_task_mq_init();


/**
 * @brief 
 * Function to populate packets
 * @param packet_pc 
 * @param msg_type 
 * @param lux 
 */
void light_task_packet_create(Packet **packet_pc, MsgType_t msg_type, float lux);

/**
 * @brief Timer Handler for light task
 * 
 * @param packet_tm 
 */
void light_task_timer_handler(Packet **packet_tm);

/**
 * @brief Callback for light task thread
 * 
 * @return void* 
 */
void* light_task();

#endif /* LIGHT_TASK_H_ */
