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
	Led_Init();
	
	printf("Main task created\n");	
	int status;
	memset(&heartbeat_count,0,sizeof(heartbeat_count));
	if(argc < 2 )
		{
			printf("ERROR Invalid Arguments : Please Enter File name\n");
			exit(1);
		}
	
	pthread_mutex_init(&hb_status, NULL);

	 /*Create Threads */
	 if(built_in_startup_tests()!=SUCCESS)
	{
		printf("BIST Failed. Exiting");
		//userled(LED1,ON);
		gpio_fd_write_on(54);
		exit(1);
	}
	for(int i =0; i<NUM_OF_THREADS;i++)
		MyThreads[i].FileName = argv[1];
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
