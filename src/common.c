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

extern mqd_t mq_log;

int log_packet(Packet packet_log)
{
    //printf("log_packet() \n");
   
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
        if((mq_send(mq_log,(char*)&packet_log,sizeof(packet_log),0))== -1)
        {
            perror("Error Sending Light Packet");
            //log_error("Error 
           // Sending Light PAcket\n");
            return -1;
        }
    }


}

return_status log_message(MsgType_t type,TID_t ID,char* format, ...)
{
    Packet packet_log;
    va_list args;
    va_start(args,format);
    vsprintf(packet_log.messagepacket.message_str,format,args);
    va_end(args);
    packet_log.msg_type = type; 
    packet_log.ID       = ID;
    if((mq_send(mq_log,(char*)&packet_log,sizeof(packet_log),0))== -1)
        {
            perror("Error Sending Message Packet");
            //log_error("Error Sending Light PAcket\n");  
            return ERROR;
        }
    
    return SUCCESS;
}

return_status send_packet( MsgType_t type,TID_t ID_to, TID_t ID_from,char* format, ...)
{
     Packet packet_log;
     va_list args;
     va_start(args,format);
     vsprintf(packet_log.messagepacket.message_str,format,args);
     va_end(args);
     packet_log.msg_type = type;
     packet_log.ID       = ID_from;
     switch(ID_to)
     {
        case TID_MAIN:
             if((mq_send(mq_main,(char*)&packet_log,sizeof(packet_log),0))== -1)
             {
                 perror("Error Sending Message Packet");
                 return ERROR;
            }
        break;
        
        case TID_TEMPERATURE:
             if((mq_send(mq_temperature,(char*)&packet_log,sizeof(packet_log),0))== -1)
             {
                 perror("Error Sending Message Packet");
                 return ERROR;
            }
        break;
        case TID_LIGHT:
             if((mq_send(mq_light,(char*)&packet_log,sizeof(packet_log),0))== -1)
             {
                 perror("Error Sending Message Packet");
                 return ERROR;
             }
        break;
                case TID_LOGGER:
             if((mq_send(mq_log,(char*)&packet_log,sizeof(packet_log),0))== -1)
             {
                 perror("Error Sending Message Packet");
                 return ERROR;
             }
        break;
         case TID_SOCKET:
           // printf("Message Type to socket %d ID: %d",packet_log.msg_type,packet_log.ID);
             if((mq_send(mq_socket,(char*)&packet_log,sizeof(packet_log),0))== -1)
             {
                 perror("Error Sending Message Packet");
                 return ERROR;
             }
        break;
        

     } 
     return SUCCESS;
}

return_status receive_packet(mqd_t mq_type, Packet *Received)
{
    int status;
    
   if(mq_receive(mq_type,(char * )Received,sizeof(Packet),NULL) == ERROR)
    {   
        return ERROR;
    }
    return SUCCESS;        
    
}

