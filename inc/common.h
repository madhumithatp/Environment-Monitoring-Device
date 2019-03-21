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

#include <mqueue.h>

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
    MSGTYPE_SENSOR_DATA,
    MSGTYPE_SENSOR_STATUS,
    MSGTYPE_EXIT,

}MsgType_t;

typedef union
{
    LightPacket_t lightpacket;
    TemperaturePacket_t temperaturepacket;
}Packet;
