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
	Led_init(LED1);
	UserLed(LED1,OFF);
	printf("Main task created\n");	
	int status;
	memset(&heartbeat_count,0,sizeof(heartbeat_count));
	if(argc < 2 )
		printf("No user input for logfile, using log.txt \n");
	
	pthread_mutex_init(&hb_status, NULL);

	 /*Create Threads */
	 if(built_in_startup_tests()!=SUCCESS)
	{
		printf("BIST Failed. Exiting");
		exit(1);
	}
    if(create_threads() == ERROR)
	{
		perror("Error Creating Threads, Exiting Program\n");
        exit(1);
	}
    else printf("Threads created uccessfully \n");
		
	master_mqueue_init();

	signalhandlerInit(0X0F);

	if(create_posixtimer(&hb_timerID,heartbeat_handler) == ERROR)
	{
		perror("Error Creating Timer");
	}
	start_posixtimer(hb_timerID, 5);

	sleep(6);
	main_task_response();
	//delete_posixtimer(hb_timerID);
	//mq_close(mq_main);

	pthread_mutex_destroy(&hb_status);
	delete_threads();
	if(join_threads() == ERROR)
	{
		perror("Error joining Threads\n");
	}
	printf("EXITING PROGRAM\n");
	exit(0);

}
