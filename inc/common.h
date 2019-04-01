/**
 * @file common.h
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Contains common functions and variables used by other files
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <mqueue.h>
#include "driver_i2c.h"
#include "signalhandler.h"
#include "userled.h"
#include "light_task.h"
#include "temperature_task.h"
#include "logger_task.h"
#include "socket_task.h"
#include "common.h"
#include "posix_timer.h"
#include "main.h"

#define MAX_MSG_SIZE    (30)

volatile mqd_t mq_log;           //Definitation of Mqueue descriptor
volatile mqd_t mq_temperature;
volatile mqd_t mq_light;
volatile mqd_t mq_socket;
volatile mqd_t mq_main;

volatile sig_atomic_t kill_signal;

typedef enum 
{
    TYPE_DATA = 0,
    TYPE_INFO = 1,
    TYPE_EXIT = 2,
    TYPE_ERROR = 3,
    TYPE_HEARTBEAT = 4
    

}MsgType_t;

/**
 * @brief
 * 
 */
typedef enum 
{
    
    TID_LOGGER = 0,
    TID_LIGHT = 1,
    TID_TEMPERATURE = 2,
    TID_SOCKET = 3,
    TID_MAIN = 4,
}TID_t;

typedef struct 
{
    char message_str[MAX_MSG_SIZE];
}MessagePacket_t;

typedef struct 
{
    MsgType_t msg_type;
    TID_t ID;
    MessagePacket_t messagepacket;
}Packet;

/**
 * @brief  Function to log packets
 * 
 * @param packet_log 
 * @return int 
 */
int log_packet(Packet packet_log);

/**
 * @brief logs messages to the logger task
 * reference http://www.cplusplus.com/reference/cstdio/vsprintf/
 * @param type 
 * @param ID 
 * @param format 
 * @param ... 
 * @return return_status 
 */
return_status log_message(MsgType_t type,TID_t ID,char * format, ...);
/**
 * @brief sending heartbeat
 * 
 */
return_status send_packet( MsgType_t type,TID_t ID_to,TID_t ID_from,char* format, ...);

/**
 * 
 * @brief receive heartbeat
 * 
 * @param mq_type 
 * @param heartbeat 
 * @return return_status 
 */
return_status receive_packet(mqd_t mq_type, Packet *Received);

/**
 * @brief Inits all queues
 * 
 */
void master_mqueue_init();

#endif /* COMMON_H_ */
