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

#include "common.h"

int log_packet(Packet packet_log)
{
    printf("log_packet() \n");
   
    printf(" Logging Task ID : %d \t lux : %f \t \n",packet_log.ID,packet_log.lightpacket.lux);
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