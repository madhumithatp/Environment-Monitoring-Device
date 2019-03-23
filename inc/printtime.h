/*
@File Name	: printtime.h
@Description: time functions to get time  
@Author		: Deepesh Sonigra 
@Author		: Madhumitha Tolakanahalli
@Date		: 03/22/2019
*/

#ifndef PRINTTIME_H_
#define PRINTTIME_H_`

#include <sys/time.h>
#include<stddef.h>

#define USEC_TO_MSEC(x) 	(x /= (1000000))


double getTime();
	/*
@description: prints current time in secs 
@return 	: double , current time 
*/


#endif /* PRINTTIME_H_ */
