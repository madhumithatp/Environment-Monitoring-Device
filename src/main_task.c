
#include "main_task.h"



int main_task_init()
{
    mqd_t ret_mq;
    struct mq_attr main_mqattr;
    main_mqattr.mq_msgsize = sizeof(Packet);
    main_mqattr.mq_maxmsg = 128;
    main_mqattr.mq_flags = 0;

    mq_unlink(MQ_MAIN);
    ret_mq = mq_open(MQ_MAIN,O_CREAT | O_RDWR, 0666, &main_mqattr);

    return ret_mq; 
}

return_status create_threads()
{
    int status;
    status= pthread_create(&threadID[2],NULL,logger_task,(void *)&(MyThreads[2]));
	if(status)
	{
	perror("Log Task not created Error code :");
	return ERROR;
	}
	status= pthread_create(&threadID[0],NULL,temperature_task,(void *)&(MyThreads[0]));
	if(status)
	{
	perror("Temp Task not created Error code ");
	return ERROR;
	}
	status= pthread_create(&threadID[1],NULL,light_task,(void *)&(MyThreads[1]));
	if(status)
	{
	perror("Light Task not created Error code :");
	return ERROR;
	}
	status= pthread_create(&threadID[3],NULL,socket_task,(void *)&(MyThreads[3]));
	if(status)
	{
	perror("Light Task not created Error code :");
	return ERROR;
	}
    return SUCCESS;

}

return_status join_threads()
{
	for(int i = 0; i < NUM_OF_THREADS; i++)
	{
		int status;
		status = pthread_join(threadID[i],NULL);
		if(status!= 0)
			return ERROR;
		
	return SUCCESS;

	}

}
return_status delete_threads()
{
	for (int i = 0; i<NUM_OF_THREADS;i++)
if (pthread_cancel(threadID[i]))
	{
		perror("ERROR:Cannot Destroy threads");
	}	
}


void heartbeat_handler()
{
	if(heartbeat_count[TID_LIGHT]<= HB_LIMIT && heartbeat_count[TID_TEMPERATURE]<=HB_LIMIT && heartbeat_count[TID_LOGGER]<=HB_LIMIT )
	{
		
		
		pthread_mutex_lock(&hb_status);
		heartbeat_count[TID_LOGGER]++;
		pthread_mutex_unlock(&hb_status);
		if(send_packet(TYPE_HEARTBEAT,TID_LOGGER,TID_MAIN,"Heartbeat")== ERROR)
		{
			perror("Error Sending Logger heartbeat");
		}
		pthread_mutex_lock(&hb_status);
		heartbeat_count[TID_TEMPERATURE]++;
		pthread_mutex_unlock(&hb_status);
		
		if(send_packet(TYPE_HEARTBEAT,TID_TEMPERATURE,TID_MAIN, "Heartbeat")== ERROR)
		{
			perror("Error Sending Temperature heartbeat");
		}		
		pthread_mutex_lock(&hb_status);
		heartbeat_count[TID_LIGHT]++;
		pthread_mutex_unlock(&hb_status);
		
		if(send_packet(TYPE_HEARTBEAT,TID_LIGHT,TID_MAIN, "Heartbeat")== ERROR)
		{
			perror("Error Sending Light heartbeat");
		}
		//heartbeat_count[TID_SOCKET]++;
		// if(send_packet(TYPE_HEARTBEAT,TID_SOCKET,TID_MAIN, "Heartbeat Count : %d",heartbeat_count[TID_SOCKET])== ERROR)
		// {
		// 	perror("Error Sending Temperature heartbeat");
		// }

	}
	else
	{
		printf("Heartbeat failed\n");
		if(heartbeat_count[TID_LIGHT] > HB_LIMIT)
		{
			perror("Error Heartbeat Limit of light crossed ");
			log_message(TYPE_HEARTBEAT,TID_LIGHT,"Light task inactive: Heartbeat Count over Limit\n");
		}
		if(heartbeat_count[TID_LOGGER] > HB_LIMIT)
		{
			perror("Error Heartbeat Limit of Logger crossed ");
		}
		if(heartbeat_count[TID_TEMPERATURE] > HB_LIMIT)
		{
			perror("Error Heartbeat Limit of temperature crossed ");
			log_message(TYPE_HEARTBEAT,TID_TEMPERATURE,"Temperature task inactive: Heartbeat Count over Limit\n");
		}
		// if(heartbeat_count[TID_SOCKET] > HB_LIMIT)
		// {
		// 	perror("Error Heartbeat Limit of Socket crossed ");
		//	log_message(TYPE_HEARTBEAT,TID_SOCKET,"SOCKET task inactive: Heartbeat Count over Limit\n");
		// }
		 stop_posixtimer(hb_timerID);
		
		 kill_signal = 1;

	}	

}

void main_task_response()
{
	 char * ID_TASK[5] = {"LOGGER", "LIGHT","TEMPERATURE","SOCKET", "MAIN"};
	//int ret,prio,id;
	Packet Heartbeat;
	int id;
	// struct timespec recv_timeout = {0};
	int status;
	while(kill_signal == 0)
	{
		memset(&Heartbeat,0,sizeof(Heartbeat));
		//  clock_gettime(CLOCK_REALTIME, &recv_timeout);
        // recv_timeout.tv_sec += 2;
        // ret = mq_timedreceive(mq_main,(char*)&(Heartbeat),sizeof(Heartbeat),&prio,&recv_timeout);
		if( receive_packet(mq_main,&Heartbeat) == ERROR)
		{
			perror("Error Receiving Heartbeat");
			continue;
		}
		id= (int)Heartbeat.ID;
		// if(ERROR == ret && ETIMEDOUT == errno)
        // {
		// 	perror("ERROR receiving in main");
        //     continue;
        // }
        // if(ERROR == ret)
        // {
        //     perror("Error main task queue ");
        //     continue;
        // }
		  switch(Heartbeat.msg_type)
            {
                case TYPE_HEARTBEAT:
				{
					// /printf("heartbeat received from %d\n",id);
					send_packet(TYPE_INFO,TID_LOGGER, TID_MAIN,"Heartbeat Received Task ID :%d \n",id);
					pthread_mutex_lock(&hb_status);
					heartbeat_count[Heartbeat.ID] = 0;
					pthread_mutex_unlock(&hb_status);
				}
                break;

                case TYPE_DATA:
                break;

                case TYPE_INFO:
                break;

                case TYPE_ERROR:
                break;
                
                case TYPE_EXIT:
              	  	log_message(TYPE_EXIT,TID_MAIN,"Task Exit request from ID = %d",id);
					kill_signal = 1;
                break;

            }
    	}
	 
}

void log_exit_all()
{
	 char * ID_TASK[5] = {"LOGGER", "LIGHT","TEMPERATURE","SOCKET", "MAIN"};
	for(int i =1; i<4;i++)
	{
	printf("Exiting Tasks no %d\n",i);
	log_message(TYPE_EXIT,TID_MAIN,"Exiting the Task ID:  %d\n",i);
	}
}

