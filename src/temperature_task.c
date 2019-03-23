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

void temperature_task_packet_create(Packet** packet_pc, MsgType_t msgtype, float temp)
{
    Packet *packet_c = malloc(sizeof(Packet));
    packet_c->temperaturepacket.msg_type    = msgtype;
    packet_c->ID                            = TID_TEMPERATURE;
    packet_c->temperaturepacket.temperature = temp;
    *packet_pc = packet_c;
}




void temperature_task_timer_handler(Packet** packet_data)
{

    float temperature;
    temperature = getTemperature(CELCIUS);
    Packet *packet_c = malloc(sizeof(Packet));
    temperature_task_packet_create(&packet_c,MSGTYPE_SENSOR_DATA,temperature);
    *packet_data = packet_c;
    log_packet(&packet_data);

}

void* temperature_task()
{
    Packet LogTermperatureData;
    Packet *packet_temp = &LogTermperatureData;
	int count = 0;
	printf("Temp Task Entered\n");
    mq_temperature=temperature_task_mq_init();
	// float temperature;
     
	// while(count < 10)
	// {
    //     temperature_task_timer_handler(&packet_temp);
    //     usleep(500);
	// 	count++;
	// }

}