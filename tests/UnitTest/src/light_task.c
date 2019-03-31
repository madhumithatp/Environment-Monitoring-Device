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


mqd_t light_task_mq_init()
{   
    mqd_t ret_mq;
    struct mq_attr light_mqattr;
    light_mqattr.mq_msgsize = sizeof(Packet);
    light_mqattr.mq_maxmsg = 128;
    light_mqattr.mq_flags = 0;
    mq_unlink(MQ_LIGHT);
    ret_mq = mq_open(MQ_LIGHT,O_CREAT | O_RDWR, 0666, &light_mqattr);

    return ret_mq;
}

void light_task_timer_handler()
{
    static int count = 0;
    float lux;
    lux = getLuminosity();
    log_message(TYPE_DATA,TID_LIGHT,"Current Luminance : %f \t",lux);
   // printf("Light Task Timer Handler Count : %d \t Lux : %f\n",count++,lux);
}

void light_task_response()
{
    
    float LIGHT;
    Packet response;
    memset(&response,0,sizeof(response));
    while(kill_signal == 0)
    {
      
            memset(&response,0,sizeof(response));

        
        if(receive_packet(mq_light, &response)== ERROR)
        {
            perror("Error Receive Packet LIGHT");
            continue;
        }
        
        
            switch(response.msg_type)
            {
                case TYPE_HEARTBEAT:
                send_packet(TYPE_HEARTBEAT,response.ID,TID_LIGHT,"Sending HeartBeat\n");
               
                break;

                case TYPE_DATA:
                LIGHT = getLuminosity();
                send_packet(TYPE_DATA,response.ID,TID_LIGHT,"Current LIGHT is %f",LIGHT);
                break;

                case TYPE_INFO:
                break;

                case TYPE_ERROR:
                break;
                
                case TYPE_EXIT:
              //  send_packet(TYPE_EXIT,response.ID,TID_LIGHT,"Exiting LIGHT sensor\n");
                log_message(TYPE_EXIT,TID_LIGHT,"Task Exit request from ID = %d",response.ID);
                break;

            }
        

       
    }
}

void* light_task()
{
	int count = 0;
	timer_t light_timerID;
	printf("Light Task Entered\n");
    mq_light = light_task_mq_init();
	if(apds9301_power_on()!= ERROR)
	{
		if(apds9301_setup() != ERROR)
		{
            // while(count<10)
            // {
            //     light_task_timer_handler();
            //     usleep(500);
            // }

            if(create_posixtimer(&light_timerID,&light_task_timer_handler) == -1)
                printf("Light Timer Create Error \n");
            else
                 printf("Light Timer created \n");
            if(start_posixtimer(light_timerID,2) == -1)
                printf("Light Timer Start Error \n");
            else printf("Light Timer Started \n");
		}	

        else 
            printf("Light Setup failed \n");
	 }
     else
         printf("Light PowerOn Failed  \n");
     
     light_task_response();

     stop_posixtimer(light_timerID);
     delete_posixtimer(light_timerID);
      mq_close(mq_light);

}