/**
 * @file socket_task.h
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Header file for Server Socket Task
 * @version 0.1
 * @date 2019-03-29
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef SOCKET_TASK_H_
#define SOCKET_TASK_H_

#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>

#include "common.h"

#define PORT_SERVER             4444
#define SOCKET_MAXCONN          5

#define MQ_SOCKET               "/msgqueue_socket"

typedef enum
{
    REQUEST_TEMPERATURE_C = 1,
    REQUEST_TEMPERATURE_F = 2,
    REQUEST_TEMPERATURE_K = 3,
    REQUEST_LUMINOSITY = 4,
    REQUEST_DAY_OR_NIGHT = 5,
    REQUEST_EXIT = 6,
} RequestType_t;

typedef struct 
{
    char txdata[50];

} TxPacket;

typedef struct
{
    RequestType_t RequestID;

} RxPacket;

/**
 * @brief Server Socket init
 * 
 * @param fd_serversoc 
 * @return int 
 */
int socket_task_init(int fd_serversoc);

/**
 * @brief Callback function
 * 
 * @return void* 
 */
void * socket_task();
#endif /* SOCKET_TASK_H_ */
