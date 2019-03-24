/**
 * @file light_task.c
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Light Task functions for logging, heartbeat...
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "light_task.h"

volatile float light_state;
mqd_t mq_light;


mqd_t light_task_mq_init()
{   
    mqd_t ret_mq;
    struct mq_attr light_mqattr;
    light_mqattr.mq_msgsize = sizeof(LightPacket_t);
    light_mqattr.mq_maxmsg = 128;
    light_mqattr.mq_flags = 0;

    mq_unlink(MQ_LIGHT);
    ret_mq = mq_open(MQ_LIGHT,O_CREAT | O_RDWR, 0666, light_mqattr);

    return ret_mq;
}

Packet light_task_packet_create(MsgType_t msg_type, float lux)
{
    Packet packet_c;
    packet_c.lightpacket.msg_type = msg_type;
    packet_c.ID                   = 3;
    packet_c.lightpacket.lux      = lux;
    printf("Light Task Create : Structure polluted \n");
    return packet_c;
}

void light_task_timer_handler()
{
    float lux;
    lux = getLuminosity();
    Packet packet_temp;
    packet_temp= light_task_packet_create(MSGTYPE_SENSOR_DATA,lux);
    printf("packet_create ID : %d \t lux : %f \t \n",packet_temp.ID,packet_temp.lightpacket.lux);
    log_packet(packet_temp);
    usleep(5000);
}

void* light_task()
{
    Packet LogLightData;
    Packet *ptr_light = &LogLightData;
	int count = 0;
	//light res;
	printf("Light Task Entered\n");
	float light2;
    mq_light = light_task_mq_init();
	if(apds9301_power_on()!= ERROR)
	{
		if(apds9301_setup() != ERROR)
		{
			while(count < 10)
			{
				light_task_timer_handler(&ptr_light);
                //	printf("Light is %f\n",light2);
				count++;
			}
			// res = is_Day_or_Night();	
			// if(res == NIGHT)
			// 	printf("Night\n");
			// else
			// 	printf("Day\n");
		}	
	}


}