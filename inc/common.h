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
#include "driver_i2c.h"
#define MAX_MSG_SIZE    (50)

typedef enum 
{
    MSGTYPE_DATA = 1,
    MSGTYPE_STATUS = 2,
    MSGTYPE_EXIT = 0,
    MSGTYPE_ERROR = -1,

}MsgType_t;


typedef enum 
{
    TID_MAIN = 1,
    TID_LOGGER = 2,
    TID_LIGHT = 3,
    TID_TEMPERATURE = 4,
    TID_SOCKET = 5,

}TID_t;



typedef struct 
{
    TID_t ID;
    float temperature;

}TemperaturePacket_t;

typedef struct 
{
    TID_t ID;
    float lux;

} LightPacket_t;

typedef struct 
{
    char message_str[MAX_MSG_SIZE];

}MessagePacket_t;

typedef struct 
{
    MsgType_t msg_type;
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
return_status log_message(MsgType_t type,TID_t ID, char *s);

#endif /* COMMON_H_ */
