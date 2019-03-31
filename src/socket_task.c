/**
 * @file socket_task.c
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief 
 * @version 0.1
 * @date 2019-03-29
 * 
 * @copyright Copyright (c) 2019
 * @citation https://stackoverflow.com/questions/666601/what-is-the-correct-way-of-reading-from-a-tcp-socket-in-c-c
 * 
 */

#include "socket_task.h"

TxPacket socket_task_request_handler(RequestType_t request)
{ 
    TxPacket ret_packet;
    Packet response;
    switch(request)
    {
        case REQUEST_TEMPERATURE_C :
            send_packet(TYPE_DATA,TID_TEMPERATURE,TID_SOCKET,"Celcius");
            
            break;
        case REQUEST_TEMPERATURE_K :
            send_packet(TYPE_DATA,TID_TEMPERATURE,TID_SOCKET,"Farenheit");
            break;
        case REQUEST_TEMPERATURE_F :
                send_packet(TYPE_DATA,TID_TEMPERATURE,TID_SOCKET,"Kelvin");
            break;
        case REQUEST_LUMINOSITY :
            send_packet(TYPE_DATA,TID_LIGHT,TID_SOCKET,"Lux");
            break;
        case REQUEST_DAY_OR_NIGHT :
            send_packet(TYPE_DATA,TID_LIGHT,TID_SOCKET,"isday");
        break;
        case REQUEST_EXIT :
            printf("End Connection");

        break;
        default :
            printf("Socket Case : Invalid REequestID \n");
        break;
    }
            
        if(receive_packet(mq_socket, &response)== ERROR)
        {
            perror("Error Receive Packet Temperature");
        }
        else 
        printf("Packet Received on Socket Side TYPE : %d\t  ID:%d \n message: %s\n",response.msg_type,response.ID,response.messagepacket.message_str);
            switch(response.msg_type)
            {
                /*
                case TYPE_HEARTBEAT:
                send_packet(TYPE_HEARTBEAT,response.ID,TID_SOCKET,"Sending HeartBeat\n");
                printf("sending heartbeat socket \n");
                break;
*/
                case TYPE_DATA:
                   // strcpy(ret_packet.txdata,response.messagepacket.message_str);
                break;

                case TYPE_INFO: 
                    strcpy(ret_packet.txdata,response.messagepacket.message_str);
                break;
                case TYPE_ERROR:
                break;
                
                case TYPE_EXIT:
                log_message(TYPE_EXIT,TID_SOCKET,"Task Exit request from ID = %d",response.ID);
                break;

            }


    return ret_packet;

}

mqd_t socket_task_mq_init()
{   
    mqd_t ret_mq;
    struct mq_attr socket_mqattr;
    socket_mqattr.mq_msgsize = sizeof(Packet);
    socket_mqattr.mq_maxmsg = 128;
    socket_mqattr.mq_flags = 0;
    mq_unlink(MQ_SOCKET);
    ret_mq = mq_open(MQ_SOCKET,O_CREAT | O_RDWR, 0666, &socket_mqattr);

    return ret_mq;
}

int socket_task_init(int fd_serversoc)
{
    int options = 1;
    struct sockaddr_in ser_addr;

    fd_serversoc = socket(AF_INET,SOCK_STREAM,0);
    if(fd_serversoc == -1)
    {
        perror("ERROR : Server Socket Creation failed \n");
    }
    else printf("Server Socket created successfully \n");

    if (setsockopt(fd_serversoc, SOL_SOCKET, SO_REUSEPORT | SO_REUSEADDR, &(options), sizeof(options)) == -1)
    {
        perror("ERROR : Server Socket Option Set failed \n");
    }
    else printf("Server Socket Options Set successfully \n");

    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = INADDR_ANY;
    ser_addr.sin_port = htons(PORT_SERVER);

    if(bind(fd_serversoc,(struct sockddr * )&ser_addr,sizeof(struct sockaddr_in)) == -1)
    {
        perror("ERROR : Server Socket Binding failed \n");
    }
    else printf("Server Socket Binding successful \n");

    return fd_serversoc;
}

void * socket_task()
{
    int fd_serversoc, fd_clientsoc, options = 1;
    char IPaddr_client[25];
    struct sockaddr_in cl_addr;
    int cl_addr_len = sizeof(cl_addr);
   
    int bytesRead = 0, totalBytes = 0;

    int rxdata;
   
    RxPacket packet_rx;
    TxPacket packet_tx;

    size_t len = sizeof(packet_rx);

    printf("Socket Task Entered \n");
      mq_socket = socket_task_mq_init();
     while(kill_signal == 0)
    {
  
    
    fd_serversoc = socket_task_init(fd_serversoc);

   
        printf("Socket Listeing\n");
        if(listen(fd_serversoc,SOCKET_MAXCONN) == -1)
        {
            perror("ERROR : Server Socket Listening failed\n");
        }
        else printf("Server Socket Listening \n");

        fd_clientsoc = accept(fd_serversoc,(struct sockaddr *)&cl_addr,(socklen_t*)&cl_addr_len); 
        if(fd_clientsoc == -1)
        {
            printf("ERROR: Server Socket Accept failed ERROR No. : %s\n",strerror(errno));
        }
        else printf("Server Socket Accept successful \n");

        inet_ntop(AF_INET, &cl_addr.sin_addr, IPaddr_client, sizeof(IPaddr_client));
        printf("[Server] Client Address : %s",IPaddr_client);

       while(kill_signal == 0)
        {   
            memset(&packet_rx,0,sizeof(packet_rx));
            bytesRead = recv(fd_clientsoc,(&packet_rx), sizeof(packet_rx),0);  
            printf("Server Socket : Packet Received with ID %d\n",packet_rx.RequestID);
            
            if(packet_rx.RequestID == REQUEST_EXIT)
            {
                memset(&packet_rx,0,sizeof(packet_rx));
               // fd_clientsoc = 0;
                break;
            }
            packet_tx = socket_task_request_handler(packet_rx.RequestID);
            if(send (fd_clientsoc,(char *)&packet_tx,sizeof(packet_tx),0))
                perror("Sending Response to Client failed");
            else printf("Server Data: %s sent \n ",packet_tx.txdata);
       }
       printf("Exited While of send rec\n");

    }

    printf("Exited second while\n");
    close(fd_clientsoc);
    mq_close(mq_socket);

}
