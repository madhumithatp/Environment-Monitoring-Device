/**
 * @file temperature_task.c
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief  temperature task function for logging temp..
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include"temperature_task.h"

mqd_t temperature_task_mq_init()
{
    mqd_t ret_mq;
    struct mq_attr temperature_mqattr;
    temperature_mqattr.mq_msgsize = sizeof(TemperaturePacket_t);
    temperature_mqattr.mq_maxmsg = 128;
    temperature_mqattr.mq_flags = 0;

    mq_unlink(MQ_TEMPERATURE);
    ret_mq = mq_open(MQ_TEMPERATURE, O_CREAT | O_RDWR, 0666, &temperature_mqattr);
    return ret_mq;
}

Packet temperature_task_packet_create(MsgType_t msgtype, float temp)
{
    Packet packet_c;
    packet_c.msg_type                      = msgtype;
    packet_c.ID                            = TID_TEMPERATURE;
    packet_c.temperaturepacket.temperature = temp;
    return packet_c;
}

void temperature_task_timer_handler()
{

    float temperature;
    temperature = getTemperature(CELCIUS);
    Packet packet_c;
    packet_c = temperature_task_packet_create(MSGTYPE_STATUS,temperature);
    char msg[20];
    sprintf(msg,"Current Temperature : %f",temperature);
    log_message(MSGTYPE_DATA,TID_TEMPERATURE,msg);
}

void* temperature_task()
{
    Packet LogTermperatureData;
    Packet *packet_temp = &LogTermperatureData;
	int count = 0;
	printf("Temp Task Entered\n");
    mq_temperature=temperature_task_mq_init();
	float temperature;
     
	 while(count < 10)
	 {
         temperature_task_timer_handler();
         usleep(500);
	 	count++;
	 }

}