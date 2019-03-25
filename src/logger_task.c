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

mqd_t log_task_mq_init()
{   
    printf("Logger Task Init \n");
    mqd_t ret_mq;
    struct mq_attr log_mqattr;
    log_mqattr.mq_msgsize = sizeof(Packet);
    log_mqattr.mq_maxmsg = 128;
    log_mqattr.mq_flags = 0;

    mq_unlink(MQ_LOG);
    ret_mq = mq_open(MQ_LOG,O_CREAT | O_RDWR, 0666, &log_mqattr);

    return ret_mq;
}

void * logger_task()
{
    FILE * logfptr = fopen(Filename, "w");
    fprintf(logfptr, "[%lf]\t[Status]\tLogger Task Created Successfully\n",getTime());
    fclose(logfptr);

    Packet LogData;
    mq_log = log_task_mq_init();

    memset(&LogData, 0, sizeof(Packet));
    while(1)
    {
        logfptr = fopen(Filename, "a");
        if(mq_receive(mq_log,(char * )&LogData,sizeof(LogData),NULL) == -1)
        {
            perror("Logger Queue Receive Error \n");
        }
        printf("Logger ID %d \n",LogData.ID);
        switch(LogData.ID)
        {
            case TID_TEMPERATURE:
            
                if(LogData.msg_type == MSGTYPE_DATA)
                    fprintf(logfptr, " [%lf]\t[%s]\t[Temperature]\tCurrent Temperature : %0.3f DegC \n", getTime(), LogData.msg_type, LogData.temperaturepacket.temperature);
                else
                    fprintf(logfptr,"[%lf]\t[%s]\t %s",getTime(),LogData.msg_type,LogData.messagepacket.message_str);
            break;

            case TID_LIGHT:

                if(LogData.msg_type == MSGTYPE_DATA)
                    fprintf(logfptr, " [%lf]\t[%s]\t[Light]\tLuminosity : %0.3f \n", getTime(), LogData.msg_type,LogData.lightpacket.lux);
                else
                    fprintf(logfptr,"[%lf]\t[%s]\t %s",getTime(),LogData.msg_type,LogData.messagepacket.message_str);
            break;

            case TID_MAIN:    
                fprintf(logfptr,"[%lf]\t[%s]\t [Main] \t %s",getTime(),LogData.msg_type,LogData.messagepacket.message_str);
            break;

            case TID_SOCKET:
                fprintf(logfptr,"[%lf]\t[%s]\t [Main] \t %s",getTime(),LogData.msg_type,LogData.messagepacket.message_str);
            break;
        }
        fclose(logfptr);
    }
    
    mq_close(mq_log);

}