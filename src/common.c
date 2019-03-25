/**
 * @file common.c
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Contains common functions and variables used by other files
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdarg.h>
#include "common.h"


int log_packet(Packet packet_log)
{
    printf("log_packet() \n");
   
   // printf(" Logging Task ID : %d \t lux : %f \t \n",packet_log.ID,packet_log.lightpacket.lux);
    if(packet_log.ID == TID_TEMPERATURE)
    { 
        if((mq_send(mq_log,(char*)&packet_log,sizeof(packet_log),0))== -1)
        {
           // log_error("Error Sending Temperature PAcket\n");
            perror("Error Sending Temperature Packet");
            return -1;

        }
    }
    if(packet_log.ID == TID_LIGHT)
    { 
        printf("mq_send(light) \n");
        if((mq_send(mq_log,(const char*)&packet_log,sizeof(packet_log),0))== -1)
        {
            perror("Error Sending Light Packet");
            //log_error("Error Sending Light PAcket\n");
            return -1;
        }
    }


}

return_status log_message(MsgType_t type,TID_t ID, char *s)
{
    Packet packet_log;
     snprintf(packet_log.messagepacket.message_str, sizeof(packet_log.messagepacket.message_str),s);
    packet_log.msg_type = type; 
    packet_log.ID       = ID;
    if((mq_send(mq_log,(const char*)&packet_log,sizeof(packet_log),0))== -1)
        {
            perror("Error Sending Message Packet");
            //log_error("Error Sending Light PAcket\n");
            return ERROR;
        }
    return SUCCESS;
}

