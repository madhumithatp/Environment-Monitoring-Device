/*
@File Name	: myI2C.h
@Description: Main task spawning multiple threads
@Author		: Deepesh Sonigra 
@Author		: Madhumitha Tolakanahalli
@Date		: 03/22/2019
@citation	: https://elinux.org/Interfacing_with_I2C_Devices
*/

#include"main.h"




int main(int argc, char **argv)
{

	mq_main = main_task_init();
	printf("Main task created\n");	
	int status;
	if(argc < 2 )
	printf("Enter the Filename for logging data \n");
	
	if(create_threads() == ERROR)
	{
		perror("Error Creating Threads\n");
	}

		if(join_threads() == ERROR)
	{
		perror("Error joining Threads\n");
	}



}
