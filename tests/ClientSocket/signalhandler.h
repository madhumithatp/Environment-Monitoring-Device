#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include<signal.h>
#include<stdint.h>
#include<stddef.h>
#include<sys/types.h>


typedef enum
{
    USR1 = 0x01,
    USR2 = 0x02,
    INT  = 0x04,
    KILL = 0x08,
    ALL  = 0x0F 
}signal_type;

 void signalhandlerInit(signal_type mask);

 void signal_handler(int signal);

 void signal_handler_pipe(int signal);


#endif