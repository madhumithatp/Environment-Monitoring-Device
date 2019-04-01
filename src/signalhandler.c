/**
 * @file signalhandler.c
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief  handler for signals
 * @version 0.1
 * @date 2019-03-27 
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include<signalhandler.h>

 void signalhandlerInit(struct sigaction *sa, void(*handlerFunc)(int),signal_type mask)
{
sa->sa_sigaction = handlerFunc;
sa->sa_flags = SA_SIGINFO;

if(mask & USR1)
{
    if (sigaction(SIGUSR1,sa,NULL)
        log_error("Error SIGUSR1 init");
        // send message to log task
}
if(mask & USR2)
{
    if (sigaction(SIGUSR2,sa,NULL)
        log_error("Error SIGUSR2 init");
        // send message to log task
}
if(mask & INT)
{
    if (sigaction(SIGINT,sa,NULL)
        log_error("Error SIGINT init");
        // send message to log task
}
if(mask & KILL)
{
    if (sigaction(SIGKILL,sa,NULL)
        log_error("Error SIG init");
        // send message to log task
}


}

