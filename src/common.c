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

int log_packet(Packet ** packet_log)
{
    Packet *packet_log_c = malloc(sizeof(Packet));
    packet_log_c = *packet_log;

    if(packet_log_c->ID == TID_TEMPERATURE)
    { 
        if((mq_send(mq_log,(const char*)&packet_log_c->temperaturepacket,sizeof(packet_log_c->temperaturepacket),0))== -1)
        {
           // log_error("Error Sending Temperature PAcket\n");
            perror("Error Sending Temperature Packet");

        }
    }
    if(packet_log_c->ID == TID_LIGHT)
    { 
        if((mq_send(mq_log,(const char*)&packet_log_c->lightpacket,sizeof(packet_log_c->lightpacket),0))== -1)
        {
            perror("Error Sending Light Packet");
            //log_error("Error Sending Light PAcket\n");
        }
    }


}