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
#include"common.h"


mqt_t temperature_task_mq_init(Packet *packet_init)
{
    mqd_t ret_mq
    struct mq_attr temperature_mqattr;
    temperature_mqattr.mq_msgsize = sizeof(TemperaturePacket_t);
    temperature_mqattr.mq_maxmsg = 128;
    temperature_mqattr.flags = 0;

    mq_unlink(MQ_TEMPERATURE);
    ret_mq = mq_open(MQ_TEMPERATURE, O_CREAT | O_RDWR, 0666, &temperature_mqattr);
    return ret_mq;
}

void temperature_task_packet_create( Packet *packet_pc, MsgType_t msgtype, float temp)
{
    packet_pc->PacketType.temperaturepacket.msg_type = msgtype;
    packet_pc->ID = TID_TEMPERATURE;
    packet_pc->PacketType.temperaturepacket.temperature = temp;
}




void temperature_task_timer_handler( Packet* packet_data)
{

    float temperature;
    temperature = getTemperature(CELCIUS);
    temperature_task_packet_create(packet_data,MSGTYPE_SENSOR_DATA,temperature);
    log_packet( packet_data, TID_TEMPERA);

}

void* temperature_task()
{
    
	int count = 0;
	printf("Temp Task Entered\n");
	float temperature;
     Packet LogTemperatureData;
    temperature_task_mq_init()
    Packet LogTemperatureData;
	while(count < 10)
	{
        temperature_task_timer_handler(&LogTemperatureData);
        usleep(500);
		count++;
	}
    mq_close 

}