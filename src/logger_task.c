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
    fprintf(logfptr, "Logger Task Begin \n");
    fclose(logfptr);

    Packet LogData;
    printf("Logger Task Entered \n");

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
            {
                printf(" [%lu] Temperature : %0.3f C \n", getTime(), LogData.temperaturepacket.temperature);
                fprintf(logfptr, " [%lf] Temperature : %0.3f C \n", getTime(), LogData.temperaturepacket.temperature);
            } break;
            case TID_LIGHT:
            {
                printf(" [%lu] Luminosity : %0.3f \n", getTime(), LogData.lightpacket.lux);
                fprintf(logfptr, " [%lf] Luminosity : %0.3f \n", getTime(), LogData.lightpacket.lux);
            } break;
            default:
            {
                printf(" [%lf] Luminosity : %0.3f \n", getTime(), LogData.lightpacket.lux);
                fprintf(logfptr, " [%lf] Luminosity : %0.3f \n", getTime(), LogData.lightpacket.lux);
            } break;
        }
        fclose(logfptr);
    }
    
    mq_close(mq_log);

}