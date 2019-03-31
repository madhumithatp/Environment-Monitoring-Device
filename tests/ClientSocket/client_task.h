/**
 * @file client_task.h
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Header Files for Client Socket Task 
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef CLIENT_TASK_H_
#define CLIENT_TASK_H_

#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>

#define PORT_CLIENT             4444
#define CLIENT_MAXCONN          5
#define IP_CLIENT               "127.0.0.1"

typedef enum
{
    REQUEST_TEMPERATURE_C = 1,
    REQUEST_TEMPERATURE_K = 2,
    REQUEST_TEMPERATURE_F = 3,
    REQUEST_LUMINOSITY = 4,
    REQUEST_DAY_OR_NIGHT = 5,
    REQUEST_EXIT = 6,
} RequestType_t;

typedef struct 
{
    char rxdata[50];

} RxPacket;

typedef struct
{
    RequestType_t RequestID;

} TxPacket;

/**
 * @brief Get option input from user
 * 
 * @return int 
 */
int print_options();

/**
 * @brief Decode user-entered option
 * 
 * @param option 
 * @return RequestType_t 
 */
RequestType_t decode_user_option(int option);

/**
 * @brief Read all bytes of received socket packet
 * 
 * @param fd 
 * @param len 
 * @param buffer 
 */
void read_socket_packet(int fd, unsigned int len, void * buffer);

#endif /* CLIENT_TASK_H_ */
