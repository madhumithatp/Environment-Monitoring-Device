/*
@File Name	: myI2C.h
@Description: Main task spawning multiple threads
@Author		: Deepesh Sonigra 
@Author		: Madhumitha Tolakanahalli
@Date		: 03/22/2019
@citation	: https://elinux.org/Interfacing_with_I2C_Devices
*/

#include"main.h"

pthread_t threads1, threads2, threads3;

typedef struct
{
	char *FileName;
}StructThread;

int main(int argc, char **argv)
{
	StructThread MyThreads[3];
	printf("Main task created\n");	
	FILE *fptr;
	int status;
	if(argc < 2 )
	printf("Enter the Filename for logging data \n");
	status= pthread_create(&threads3,NULL,logger_task,(void *)&(MyThreads[2]));
	if(status)
	{
	perror("Log Task not created Error code :");
	return 0;
	}

	status= pthread_create(&threads1,NULL,temperature_task,(void *)&(MyThreads[0]));
	if(status)
	{
	perror("Temp Task not created Error code ");
	return 0;
	}
	status= pthread_create(&threads2,NULL,light_task,(void *)&(MyThreads[1]));
	if(status)
	{
	perror("Light Task not created Error code :");
	return 0;
	}
	status= pthread_join(threads3,NULL);
	if(status)
	{
	perror("log Task join error Error code");
	return 0;
	}
	status= pthread_join(threads1,NULL);
	if(status)
	{
	perror("Temp Task join error Error code :");
	return 0;
	}
	status= pthread_join(threads2,NULL);
	if(status)
	{
	perror("Light Task join error Error code");
	return 0;
	}

}
