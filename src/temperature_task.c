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
    recent_temperature = getTemperature(CELCIUS);
    log_message(TYPE_DATA,TID_TEMPERATURE,"Current Temperature : %f",recent_temperature);
    
}
float latest_temperature(unit_temp unit)
{
    float temperature = recent_temperature;
    switch(unit)
	{
		case CELCIUS:
			return temperature;
		case FARENHEIT:
			return TMP_C_TO_F(temperature);
		case KELVIN:
			return TMP_C_TO_K(temperature);
		default:
			return temperature;
	}
}
void temperature_task_response()
{
    float temperature;
    Packet response;

    while(kill_signal_temperature == 0)
    {
            memset(&response,0,sizeof(response));

        
        if(receive_packet(mq_temperature, &response)== ERROR)
        {
            perror("Error Receive Packet Temperature");
            continue;
        }
        
       
            // printf("Temp message type =%d",response.msg_type);
            switch(response.msg_type)
            {
                case TYPE_HEARTBEAT:
                send_packet(TYPE_HEARTBEAT,response.ID,TID_TEMPERATURE,"Sending HeartBeat\n");
            
                break;

                case TYPE_DATA:
                {
                    temperature = getTemperature(CELCIUS);
                    if(strcmp((response.messagepacket.message_str),"Celcius") == 0)
                    {
                        printf("Sending Celcius\n");
                        send_packet(TYPE_INFO,response.ID,TID_TEMPERATURE,"Temperature is %f",temperature);
                    }

                    else if(strcmp((response.messagepacket.message_str),"Farenheit")== 0)
                    {
                       
                        TMP_C_TO_F(temperature);
                         printf("Sending Farenheit %f\n",temperature);
                        send_packet(TYPE_INFO,response.ID,TID_TEMPERATURE,"Temperature is %f",temperature);
                    }   
                    
                    else if(strcmp((response.messagepacket.message_str),"Kelvin") == 0)
                    {
                       
                        TMP_C_TO_K(temperature);
                         printf("Sending kelvin %f\n",temperature);
                        send_packet(TYPE_INFO,response.ID,TID_TEMPERATURE,"Temperature is %f",temperature);
                    }
                    else 
                    {
                        printf("sendind default in celcius");
                        send_packet(TYPE_INFO,response.ID,TID_TEMPERATURE,"Temperature is %f",temperature);  
                    }
                }
                break;

                case TYPE_INFO:
              
                break;

                case TYPE_ERROR:
                break;
                
                case TYPE_EXIT:
              
                printf("Exit received Temp\n");
                kill_signal_temperature =1;
                break;

            }
        


    }
     printf("Exiting Temperature Task\n");
}


void* temperature_task()
{
	int count = 0;
    timer_t temperature_timerID;
	printf("Temp Task Entered\n");
	float temperature;
      

    if(create_posixtimer(&temperature_timerID,&temperature_task_timer_handler) == -1)
        printf("Temperature Timer Create Error \n");
    else 
        printf("Temperature Timer Created \n");
    
    if(start_posixtimer(temperature_timerID,2) == -1)
        printf("Temperature Timer Start Error \n");
    else 
        printf("Temperature Timer Started \n");
    
    temperature_task_response();
    if (stop_posixtimer(temperature_timerID) == -1 );

    delete_posixtimer(temperature_timerID);
    mq_close(mq_temperature);


}