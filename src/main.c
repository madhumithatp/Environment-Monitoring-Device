/*
@File Name	: myI2C.h
@Description: Main task spawning multiple threads
@Author		: Deepesh Sonigra 
@Author		: Madhumitha Tolakanahalli
@Date		: 03/22/2019
@citation	: https://elinux.org/Interfacing_with_I2C_Devices
*/

#include"main.h"

pthread_t threads1, threads2;

typedef struct
{
	char *FileName;
}StructThread;

void* temp_task(void *arg)
{
	int count = 0;
	printf("Temp Task Entered\n");
	
	float temperature;
	while(count < 10)
	{
		temperature = getTemperature(CELCIUS);
		printf("Temperature is %f\n",temperature);
		count++;
	}

}
void* light_task(void *arg)
{
		
	
	int count = 0;
	light res;
	printf("Light Task Entered\n");
	float light2;
	if(apds9301_power_on()!= ERROR)
	{
		if(apds9301_setup() != ERROR)
		{
			while(count < 10)
			{
				light2 = getLuminosity();
			//	printf("Light is %f\n",light2);
				count++;
			}
			res = is_Day_or_Night();	
			if(res == NIGHT)
				printf("Night\n");
			else
				printf("Day\n");
		}	
	}


}

int main(int argc, char **argv)
{
	StructThread MyThreads[2];
	printf("Main task created\n");	
	FILE *fptr;
	int status;
	if(argc < 2 )
		printf("Enter the Filename for logging data \n");

	for(int i =0; i<2;i++)
		MyThreads[i].FileName = argv[1];

	 status= pthread_create(&threads1,NULL,temp_task,(void *)&(MyThreads[0]));
	 if(status)
	 {
	 	perror("Temp Task not created Error code ");
	 	return 0;
	 }
	status= pthread_create(&threads2,NULL,light_task,(void *)&(MyThreads[1]));
	 	 if(status)
	 {
	 	perror("Temp Task not created Error code :");
	 	return 0;
	 }
	 fptr = fopen(Filename,"w");
	 if(fptr == NULL)
	 {
	 	perror("file NULL pointer");
	 	return 0;
	 }
	 fprintf(fptr,"Main Task Entered\n"); 
	 fclose(fptr);
	 status= pthread_join(threads1,NULL);
	 if(status)
	 {
	 	perror("Temp Task join error Error code :");
	 	return 0;
	}
	 status= pthread_join(threads2,NULL);
	 if(status)
	 {
	 	perror("log Task join error Error code");
	 	return 0;
	 }
}
