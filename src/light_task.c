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
    light_mqattr.mq_msgsize = sizeof(Packet);
    light_mqattr.mq_maxmsg = 128;
    light_mqattr.mq_flags = 0;
    mq_unlink(MQ_LIGHT);
    ret_mq = mq_open(MQ_LIGHT,O_CREAT | O_RDWR, 0666, light_mqattr);

    return ret_mq;
}

void light_task_timer_handler()
{
    float lux;
    unsigned long time;
    lux = getLuminosity();
    log_message(TYPE_DATA,TID_LIGHT,"Current Luminance : %f \t",lux);
    usleep(5000);
}

void* light_task()
{
    timer_t light_timerID;
	int count = 0;
	
	printf("Light Task Entered\n");
    mq_light = light_task_mq_init();
	if(apds9301_power_on()!= ERROR)
	{
		if(apds9301_setup() != ERROR)
		{
            while(count<10)
            {
                light_task_timer_handler();
                count++;
            }
            // if(create_posixtimer(light_timerID,light_task_timer_handler) == -1)
            //     printf("Light Timer Create Error \n");
            // if(start_posixtimer(light_timerID,2) == -1)
            //     printf("Light Timer Start Error \n");
		}	
	}


}