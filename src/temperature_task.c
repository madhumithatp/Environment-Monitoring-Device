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
    temperature_mqattr.mq_msgsize = sizeof(Packet);
    temperature_mqattr.mq_maxmsg = 128;
    temperature_mqattr.mq_flags = 0;
    mq_unlink(MQ_TEMPERATURE);
    ret_mq = mq_open(MQ_TEMPERATURE, O_CREAT | O_RDWR, 0666, &temperature_mqattr);
    return ret_mq;
}

void temperature_task_timer_handler()
{
    static int count = 0;
    float temperature;
    temperature = getTemperature(CELCIUS);
    log_message(TYPE_DATA,TID_TEMPERATURE,"Current Temperature : %f",temperature);
    printf("Temperature Task Timer Handler Count : %d \t Temperature : %f\n",count++,temperature);
}

void* temperature_task()
{
	int count = 0;
    timer_t temperature_timerID;
	printf("Temp Task Entered\n");
    mq_temperature=temperature_task_mq_init();
	float temperature;
      
	//  while(count < 10)
	//  {
    //      temperature_task_timer_handler();
    //      usleep(500);
	//  	count++;
	//  }

    if(create_posixtimer(&temperature_timerID,&temperature_task_timer_handler) == -1)
        printf("Temperature Timer Create Error \n");
    else printf("Temperature Timer Created \n");
    if(start_posixtimer(temperature_timerID,1) == -1)
        printf("Temperature Timer Start Error \n");
    else printf("Temperature Timer Started \n");

}