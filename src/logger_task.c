/**
 * @file logger_task.c
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief 
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "logger_task.h"
#include "common.h"



mqd_t log_task_mq_init()
{   
   
    mqd_t ret_mq;
    struct mq_attr log_mqattr;
    log_mqattr.mq_msgsize = sizeof(Packet);
    log_mqattr.mq_maxmsg = 128;
    log_mqattr.mq_flags = 0;

    mq_unlink(MQ_LOG);
    ret_mq = mq_open(MQ_LOG,O_CREAT | O_RDWR, 0666, &log_mqattr);
    printf("Logger Task Init \n");
    return ret_mq;
}

void * logger_task(void *arg)
{
    static int exit_bit;
    char * MsgType_label[5]= {"DATA", "INFO","EXIT","ERROR, HEARTBEAT"};
    StructThread *Thread2ptr = (StructThread*)(arg);
    FILE * logfptr = fopen(Thread2ptr->FileName, "w");
    char* Filename = Thread2ptr->FileName;
    getTime(logfptr);fprintf(logfptr, " [STATUS]\tLogger Task Entered \n");
    int8_t _msgtype = 0;
    char* type;
    fclose(logfptr);
    Packet LogData;

    memset(&LogData, 0, sizeof(Packet));

    while(kill_signal_logger == 0)
    {
        if(mq_receive(mq_log,(char * )&LogData,sizeof(LogData),NULL) == -1)
        {
            perror("Logger Queue Receive Error \n");
        }
        
        switch(LogData.ID)
        {
            case TID_TEMPERATURE:
                logfptr = fopen(Filename, "a");
              
                getTime(logfptr);
                fprintf(logfptr,"[%s]\t[Temperature]\t %s\n",MsgType_label[LogData.msg_type],LogData.messagepacket.message_str);
                fclose(logfptr);
            break;

            case TID_LIGHT:   
               
                logfptr = fopen(Filename, "a"); 
                getTime(logfptr);fprintf(logfptr,"[%s]\t[Light]\t \t  %s \n",MsgType_label[LogData.msg_type],LogData.messagepacket.message_str);
                fclose(logfptr);
            break;

            case TID_MAIN:  
                {
                    
                    logfptr = fopen(Filename, "a"); 
                    switch(LogData.msg_type)
                    {
                        case TYPE_HEARTBEAT:
                            send_packet(TYPE_HEARTBEAT,TID_MAIN,TID_LOGGER,"Logger:Sending HeartBeat ");
                        break;
                        case TYPE_INFO:
                            getTime(logfptr); fprintf(logfptr,"[%s]\t[Main]\t\t%s \n",MsgType_label[LogData.msg_type],LogData.messagepacket.message_str); 
                        break;
                        case TYPE_EXIT:
                        send_packet(TYPE_EXIT,TID_MAIN,TID_LOGGER,"Exit");
                        kill_signal_logger = 1;
                        default:
                            getTime(logfptr);fprintf(logfptr,"[%s]\t [Main]\t\t%s\n ",MsgType_label[LogData.msg_type],LogData.messagepacket.message_str);
                        break;  
                    }
                    fclose(logfptr);
                }
            break;

            case TID_SOCKET:
                logfptr = fopen(Filename, "a"); 
                getTime(logfptr);fprintf(logfptr,"[%s]\t [Socket] \t %s",MsgType_label[LogData.msg_type],LogData.messagepacket.message_str);
                fclose(logfptr);
            break;
        }
        //fclose(logfptr);
    }
     printf("Exiting logger Task\n");
    
    mq_close(mq_log);

}