/*
@File Name	: printtime.c
@Description: time functions to get time  
@Author		: Deepesh Sonigra 
@Author		: Madhumitha Tolakanahalli
@Date		: 03/22/2019
*/

#include"printtime.h" 
/*
@description: prints current time in secs 
@return 	: double , current time 
*/

unsigned long  getTime()
{	
	struct timeval t;
	unsigned long  tsec = 0;
	gettimeofday(&t,NULL);
	printf("[%lu ,%lu]",t.tv_sec,t.tv_usec);
	unsigned long sec = t.tv_sec;
	
	unsigned long usec = t.tv_usec;
	tsec = sec*1000000;
	printf("[%lu]", tsec);
	tsec += usec;
	printf("[%lu]", tsec);
	//USEC_TO_MSEC(tsec);
	return tsec; 

}
