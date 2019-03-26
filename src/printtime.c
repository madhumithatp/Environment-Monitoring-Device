/*
@File Name	: myI2C.h
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

double getTime()
{	
	struct timeval t;
	double tsec;
	gettimeofday(&t,NULL);
	tsec = (t.tv_sec*1000000) + t.tv_usec;
	USEC_TO_MSEC(tsec);
	return tsec; 

}
