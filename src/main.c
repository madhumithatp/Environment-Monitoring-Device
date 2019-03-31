/*
@File Name	: myI2C.h
@Description: Main task spawning multiple threads
@Author		: Deepesh Sonigra 
@Author		: Madhumitha Tolakanahalli
@Date		: 03/22/2019
@citation	: https://elinux.org/Interfacing_with_I2C_Devices
*/

#include "main.h"
#include "userled.h"

int main(int argc, char **argv)
{
	
	UserLed(LED1,OFF);
	mq_main = main_task_init();
	printf("Main task created\n");	
	int status;
	memset(&heartbeat_count,0,sizeof(heartbeat_count));
	if(argc < 2 )
	printf("Enter the Filename for logging data \n");
	pthread_mutex_init(&hb_status, NULL);

	if(create_threads() == ERROR)
	{
		perror("Error Creating Threads\n");
	}
	signalhandlerInit(0X0F);
	if(create_posixtimer(&hb_timerID,heartbeat_handler) == ERROR)
	{
		perror("Error Creating Timer");
	}
	start_posixtimer(hb_timerID, 5);
	UserLed(LED1,ON);
	printf("Led On\n");
	sleep(6);
	main_task_response();

	delete_posixtimer(hb_timerID);
	log_exit_all();
	mq_close(mq_main);
	pthread_mutex_destroy(&hb_status);
	delete_threads();
	if(join_threads() == ERROR)
	{
		perror("Error joining Threads\n");
	}
	printf("EXITING PROGRAM\n");

}
