/*
@File Name	: printtime.c
@Description: time functions to get time  
@Author		: Deepesh Sonigra 
@Author		: Madhumitha Tolakanahalli
@Date		: 03/22/2019
*/

#include"printtime.h" 

void getTime(FILE * ptr)
{	
	struct timeval t;
	unsigned long  tsec = 0;
	gettimeofday(&t,NULL);
	fprintf(ptr, "[%lu : %lu]",t.tv_sec,t.tv_usec); 
	// unsigned long sec = t.tv_sec;
	
	// unsigned long usec = t.tv_usec;
	// tsec = sec*1000000;
	// printf("[%lu]", tsec);
	// tsec += usec;
	// printf("[%lu]", tsec);
	// //USEC_TO_MSEC(tsec);
	// return tsec; 
}
