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
#include "driver_i2c.h"

mqd_t mq_log;           //Definitation of Mqueue descriptor

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

void * logger_task()
{
    char * MsgType_label[4]= {"DATA", "STATUS","EXIT","ERROR"};
    FILE * logfptr = fopen(Filename, "w");
    fprintf(logfptr, " [STATUS]\tLogger Task Entered \n");
    int8_t _msgtype = 0;
    char* type;

    Packet LogData;
    mq_log = log_task_mq_init();

    memset(&LogData, 0, sizeof(Packet));
    memset(&LogData, 0, sizeof(Packet));
    while(1)
    {
        logfptr = fopen(Filename, "a");
        if(mq_receive(mq_log,(char * )&LogData,sizeof(LogData),NULL) == -1)
        {
            perror("Logger Queue Receive Error \n");
        }
        switch(LogData.ID)
        {
            case TID_TEMPERATURE:
                getTime(logfptr);fprintf(logfptr,"[%s]\t[Temperature]\t %s\n",MsgType_label[LogData.msg_type],LogData.messagepacket.message_str);
            break;

            case TID_LIGHT:    
                getTime(logfptr);fprintf(logfptr,"[%s]\t[Light]\t \t  %s \n",MsgType_label[LogData.msg_type],LogData.messagepacket.message_str);
            break;

            case TID_MAIN:   
                getTime(logfptr);fprintf(logfptr,"[%s]\t [Main] \t %s",MsgType_label[LogData.msg_type],LogData.messagepacket.message_str);
            break;

            case TID_SOCKET:
                getTime(logfptr);fprintf(logfptr,"[%s]\t [Socket] \t %s",MsgType_label[LogData.msg_type],LogData.messagepacket.message_str);
            break;
        }
        fclose(logfptr);
    }
    
    mq_close(mq_log);

}