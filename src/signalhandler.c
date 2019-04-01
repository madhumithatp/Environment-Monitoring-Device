// /**
//  * @file signalhandler.c
//  * @author Deepesh Sonigra
//  *         Madhumitha Tolakanahalli
//  * @brief  handler for signals
//  * @version 0.1
//  * @date 2019-03-27 
//  * 
//  * @copyright Copyright (c) 2019
//  * 
//  */

#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include "signalhandler.h"
#include "common.h"

 void signalhandlerInit(signal_type mask)
{
    struct sigaction sa;
    sa.sa_sigaction = &signal_handler;
    sa.sa_flags = SA_SIGINFO;

    struct sigaction sa1;
    sa1.sa_sigaction = &signal_handler_pipe;
    sa1.sa_flags = SA_SIGINFO;

    if(mask & USR1)
    {
        if (sigaction(SIGUSR1,&sa,NULL))
         perror("Error SIGUSR1 init");
        // send message to log task
    }
    if(mask & USR2)
    {
        if (sigaction(SIGUSR2,&sa,NULL))
            perror("Error SIGUSR2 init");
            // send message to log task
    }
    if(mask & INT)
    {
        if (sigaction(SIGINT,&sa,NULL))
            perror("Error SIGINT init");
            // send message to log task
    }
    if(mask & KILL)
    {
        if (sigaction(SIGTERM,&sa,NULL))
            perror("Error SIG init");
            // send message to log task
    }
    
    if (sigaction(SIGPIPE,&sa1,NULL))
        perror("Error SIG init");
        // send message to log task

}

void signal_handler_pipe(int signal)
{

}
void signal_handler(int signal)
{
	switch (signal)
	{

		case SIGUSR1:
			printf("SIGUSR1 signal.\n");
			break;
		case SIGUSR2:
			printf("SIGUSR2 signal.\n");
			break;
		case SIGINT:
			printf("SIGINT signal.\n");
			break;
		case SIGTERM:
			printf("SIGTERM signal.\n");
			break;
		case SIGKILL:
			printf("SIGTSTP signal.\n");
			break;
		default:
			printf("Invalid signal.\n");
			break;
	}
    log_exit_all();
    
}

#endif