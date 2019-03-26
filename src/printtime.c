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

void getTime(FILE * ptr)
{	
	struct timeval t;
	unsigned long  tsec = 0;
	gettimeofday(&t,NULL);
	fprintf(ptr, "[%lu : %lu]",t.tv_sec,t.tv_usec); 
}
