
#include "main_task.h"



int main_task_init()
{
    mqd_t ret_mq;
    struct mq_attr main_mqattr;
    main_mqattr.mq_msgsize = sizeof(Packet);
    main_mqattr.mq_maxmsg = 128;
    main_mqattr.mq_flags = 0;

    mq_unlink(MQ_LIGHT);
    ret_mq = mq_open(MQ_LIGHT,O_CREAT | O_RDWR, 0666, main_mqattr);

    return ret_mq; 
}

return_status create_threads()
{
    int status;
    status= pthread_create(&threads3,NULL,logger_task,(void *)&(MyThreads[2]));
	if(status)
	{
	perror("Log Task not created Error code :");
	return ERROR;
	}
	status= pthread_create(&threads1,NULL,temperature_task,(void *)&(MyThreads[0]));
	if(status)
	{
	perror("Temp Task not created Error code ");
	return ERROR;
	}
	status= pthread_create(&threads2,NULL,light_task,(void *)&(MyThreads[1]));
	if(status)
	{
	perror("Light Task not created Error code :");
	return ERROR;
	}
    return SUCCESS;
}