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

void light_task_timer_handler()
{
    float lux;
    lux = getLuminosity();
    Packet packet_temp;
    char msg[20];
    sprintf(msg,"Current Luminosity : %f",lux);
    log_message(MSGTYPE_DATA,TID_LIGHT,msg);
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
				light_task_timer_handler();
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