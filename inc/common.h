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
#include"logger_task.h"

#define MAX_MSG_SIZE  (50)

typedef enum 
{
    MSGTYPE_SENSOR_DATA = 1,
    MSGTYPE_SENSOR_STATUS = 2,
    MSGTYPE_EXIT = 3,

}MsgType_t;


typedef enum 
{
    TID_MAIN = 1,
    TID_LOGGER = 2,
    TID_LIGHT = 3,
    TID_TEMPERATURE = 4,
    TID_SOCKET = 5,

}TID_t;

typedef enum
{
    HEARTBEAT,
    ERROR,
    STATUS,
}LogType_t;

typedef struct 
{
    MsgType_t msg_type;
    TID_t ID;
    float temperature;

}TemperaturePacket_t;

typedef struct 
{
    MsgType_t msg_type;
    TID_t ID;
    float lux;

} LightPacket_t;

typedef struct 
{
    LogType_t msg;
    char message_str[MAX_MSG_SIZE];

}MessagePacket_t;

typedef struct 
{
    TID_t ID;
    union
    {
        LightPacket_t lightpacket;
        TemperaturePacket_t temperaturepacket;
        MessagePacket_t messagepacket;

    };
    
}Packet;

/**
 * @brief  Function to log packets
 * 
 * @param packet_log 
 * @return int 
 */
int log_packet(Packet packet_log);

/**
 * @brief Send messages string to logger task 
 * 
 */

int log_message(packet message, fmt, ...);

#endif /* COMMON_H_ */
