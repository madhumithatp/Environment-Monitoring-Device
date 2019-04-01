/**
 * @file socket_task.c
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief 
 * @version 0.1
 * @date 2019-03-29
 * 
 * @copyright Copyright (c) 2019
 * @citation https:tackoverflow.com/questions/666601/what-is-the-correct-way-of-reading-from-a-tcp-socket-in-c-c
 * 
 */

#include "socket_task.h"

TxPacket socket_task_request_handler(RequestType_t request)
{ 
    TxPacket ret_packet;
    Packet response;
    float temperature = 0;
    float Socket = 0;
    switch(request)
    {
        case REQUEST_TEMPERATURE_C :
           temperature = latest_temperature(CELCIUS);
            sprintf(ret_packet.txdata, "Temperature is %f\n",temperature);
            
            break;
        case REQUEST_TEMPERATURE_K :
             temperature = latest_temperature(KELVIN);
            sprintf(ret_packet.txdata, "Temperature is %f\n",temperature);
           
            break;
        case REQUEST_TEMPERATURE_F :
             temperature = latest_temperature(FARENHEIT);
            sprintf(ret_packet.txdata, "Temperature is %f\n",temperature);
            
            break;
        case REQUEST_LUMINOSITY :
            Socket = latest_lux();
            sprintf(ret_packet.txdata, "Lux is is %f\n",Socket);
            
          
            break;
        case REQUEST_DAY_OR_NIGHT :
            Socket = latest_lux();
            if(is_Day_or_Night(Socket) == NIGHT)
            {
                 sprintf(ret_packet.txdata, "Night Time\n");
                
            }
            else
            {
                sprintf(ret_packet.txdata, "Day Time\n");
                
            }
           
        break;
        case REQUEST_EXIT :
            printf("End Connection");

        break;
        default :
          
        break;
    }
    return ret_packet;
     
}    
void socket_task_timer_handler()
{
    send_packet(TYPE_HEARTBEAT,TID_MAIN,TID_SOCKET,"Sending HeartBeat\n");
}

void socket_response()
{
        timer_t socket_timerID;
        Packet response;
        memset(&response,0,sizeof(response));

          
        if(mq_receive(mq_socket,(char * )&response,sizeof(response),NULL) == ERROR)
        {   
            perror("Error Receiving socket\n");
        }
       
            switch(response.msg_type)
            {
                
                case TYPE_HEARTBEAT:
                {
                send_packet(TYPE_HEARTBEAT,response.ID,TID_SOCKET,"Sending HeartBeat\n");
               
                  if(create_posixtimer(&socket_timerID,&socket_task_timer_handler) == -1)
                    printf("Socket Timer Create Error \n");
                 else
                 printf("Socket Timer created \n");
                if(start_posixtimer(socket_timerID,5) == -1)
                printf("Socket Timer Start Error \n");
                else printf("Socket Timer Started \n");
                memset(&response,0,sizeof(response));
                }
                break;

                case TYPE_DATA:
                  
                break;

                case TYPE_INFO: 
                  
                break;

                case TYPE_ERROR:
                break;
                
                case TYPE_EXIT:
                kill_signal_socket = 1;
                delete_posixtimer(socket_timerID);
                                                                        
                break;

            }
     
        

}

mqd_t socket_task_mq_init()
{   
    mqd_t ret_mq;
    struct mq_attr socket_mqattr;
    socket_mqattr.mq_msgsize = sizeof(Packet);
    socket_mqattr.mq_maxmsg = 128;
    socket_mqattr.mq_flags = 0;
    mq_unlink(MQ_SOCKET);
    ret_mq = mq_open(MQ_SOCKET,O_CREAT | O_RDWR , 0666, &socket_mqattr);

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
    else 
    {   printf("Server Socket created successfully \n");
        log_message(TYPE_INFO,TID_SOCKET,"Socket Created \n");
    }

    if (setsockopt(fd_serversoc, SOL_SOCKET, SO_REUSEPORT | SO_REUSEADDR, &(options), sizeof(options)) == -1)
    {
        perror("ERROR : Server Socket Option Set failed \n");
    }
   

    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = INADDR_ANY;
    ser_addr.sin_port = htons(PORT_SERVER);

    if(bind(fd_serversoc,(struct sockddr * )&ser_addr,sizeof(struct sockaddr_in)) == -1)
    {
        perror("ERROR : Server Socket Binding failed \n");
        log_message(TYPE_INFO,TID_SOCKET,"Binding\n");
    }
  
    // printf("Server Socket Binding successful \n");

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
    socket_response();
    while(kill_signal_socket == 0)
    {
        fd_serversoc = socket_task_init(fd_serversoc);

   
        if(listen(fd_serversoc,SOCKET_MAXCONN) == -1)
        {
            printf("ERROR : Server Socket Listening failed\n");
        }
        else 
        {
            printf("Server Socket Listening \n");
            log_message(TYPE_INFO,TID_SOCKET,"Listening\n");
        }
        fd_clientsoc = accept(fd_serversoc,(struct sockaddr *)&cl_addr,(socklen_t*)&cl_addr_len); 
        if(fd_clientsoc == -1)
        {
            printf("ERROR: Server Socket Accept failed ERROR No. : %s\n",strerror(errno));
        }
        else 
        {      
            printf("Server Socket Accept successful \n");
            log_message(TYPE_INFO,TID_SOCKET,"Client Accepted Connection \n");
        }
        
        inet_ntop(AF_INET, &cl_addr.sin_addr, IPaddr_client, sizeof(IPaddr_client));
        printf("[Server] Client Address : %s \n",IPaddr_client);
        log_message(TYPE_INFO,TID_SOCKET,"Client IP %s \n",IPaddr_client);

       while(kill_signal_socket == 0)
        {   
            memset(&packet_rx,0,sizeof(packet_rx));
            bytesRead = recv(fd_clientsoc,(&packet_rx), sizeof(packet_rx),0);  
           
            if(packet_rx.RequestID == REQUEST_EXIT)
            {
                memset(&packet_rx,0,sizeof(packet_rx));
               fd_clientsoc = 0;
                break;
            }
            packet_tx = socket_task_request_handler(packet_rx.RequestID);
            if(send (fd_clientsoc,(char *)&packet_tx,sizeof(packet_tx),0))
                perror("Sending Response to Client failed");
           // else printf("Server Data: %s sent \n ",packet_tx.txdata);
       }
     

    }

    printf("Exiting socket \n");
    close(fd_clientsoc);
    mq_close(mq_socket);

}

