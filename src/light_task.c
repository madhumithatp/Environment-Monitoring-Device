/**
 * @file light_task.c
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Light Task functions for logging, heartbeat...
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "light_task.h"

volatile float light;
mqd_t mq_light;


mqd_t light_task_mq_init()
{   
    mqd_t ret_mq;
    struct mq_attr light_mqattr;
    light_mqattr.mq_msgsize = sizeof(LightPacket_t);
    light_mqattr.mq_maxmsg = 128;
    light_mqattr.mq_flags = 0;

    mq_unlink(MQ_LIGHT);
    ret_mq = mq_open(MQ_LIGHT,O_CREAT | O_RDWR, 0666, light_mqattr);

    return ret_mq;

}

void light_task_packet_create(LightPacket_t * packet,MsgType_t msg_type, float lux)
{
    packet -> msg_type = msg_type;
    packet -> ID       = TID_LIGHT;
    packet -> lux      = lux;
}

void light_task_timer_handler(LightPacket_t * packet)
{
    float lux;
    lux = getLuminosity();
    light_task_packet_create(&packet,MSGTYPE_SENSOR_DATA,lux);

}


