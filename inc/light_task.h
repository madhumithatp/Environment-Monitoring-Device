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



#define MQ_LIGHT        "/msgqueue_light"

typedef struct 
{
    MsgType_t msg_type;
    TID_t ID;
    float lux;

} LightPacket_t;

/**
 * @brief Function to initialize Light Message Queue
 * 
 * @return mqd_t 
 */
mqd_t light_task_mq_init();

/**
 * @brief Populate Light Message Queue Packets 
 * 
 * @param packet 
 * @param msg_type 
 * @param lux 
 */
void light_task_packet_create(LightPacket_t * packet,MsgType_t msg_type, float lux);


