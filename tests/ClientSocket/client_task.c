/**
 * @file client_task.c
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief 
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "client_task.h"

int print_options()
{   
    int option = 0;
    do
    {
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    printf("Enter the request to be serviced \n");
    printf("\t(1) Get Temperature in Celcius\n");
    printf("\t(2) Get Temperature in Kelvin\n");
    printf("\t(3) Get Temperature in Farenheit\n");
    printf("\t(4) Get Luminosity\n");
    printf("\t(5) Is it Day or Night?\n");
    printf("\t(6) Exit \n");

    scanf("%d", &option);

    if((option >= 1) && (option < 7))
        return option;
    else
        printf("Wrong option entered! Please try again... \n");   

    }while(1);
}

RequestType_t decode_user_option(int option)
{
    switch(option)
    {
        case 1: { return REQUEST_TEMPERATURE_C;} break;
        case 2: { return REQUEST_TEMPERATURE_K;} break;
        case 3: { return REQUEST_TEMPERATURE_F;} break;
        case 4: { return REQUEST_LUMINOSITY;} break;
        case 5: { return REQUEST_DAY_OR_NIGHT;} break;
        case 6: { return REQUEST_EXIT;} break;
        default : break;
    }
}
void read_socket_packet(int fd, unsigned int len, void * buffer)
{
    int bytesRead = 0;
    int totalBytes;

    while(bytesRead < len)
    {
        totalBytes = read(fd,buffer + bytesRead, len);  
        if(totalBytes == -1)
            printf("Read Error in Client \n");  
        bytesRead += totalBytes;
    }
}


int main()
{
    int bytes = 0,option = 0;
   
    struct sockaddr_in ser_addr,cl_addr;
    int fd_clientsoc = socket(AF_INET, SOCK_STREAM, 0);

    TxPacket packet_tx;
    RxPacket packet_rx;
    char buffer[50];

    int flag = 1;

    if(fd_clientsoc == -1)
    {
        perror("ERROR : Client Socket Creation failed \n");
    }
    else printf("Client Socket created successfully \n");

    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons (PORT_CLIENT);

    if(inet_pton(AF_INET,IP_CLIENT,&ser_addr.sin_addr) == -1)
    {
        perror("[Client Socket] inet failed \n");
    }
    while(flag)
    {
        if(connect(fd_clientsoc,(struct sockaddr * )&ser_addr,sizeof(ser_addr)) == -1)
            perror("ERROR: Client Socket Connect Failed \n");
    
        while(flag)
        {
            /* Get user request,  create a packet and set to Server */
            option = print_options();

            if(option == 6)
            {
                flag = 0;
                printf("Exiting Client Application");
                close(fd_clientsoc);
                break;
            }
            memset(&buffer,0,sizeof(buffer));
            packet_tx.RequestID = decode_user_option(option);

            bytes = write(fd_clientsoc, (char *)&packet_tx,sizeof(packet_tx));

            if(bytes < sizeof(packet_tx))
                perror(" ERROR : Client Socket : Complete data not sent \n");

            /* Get response from server */
            if(recv(fd_clientsoc,(char *) &packet_rx, sizeof(RxPacket),0) == -1)
                perror("Client Receive error \n");
            else 
            {   
                strcpy(buffer,packet_rx.rxdata);
                printf("CLient Received Value : %s",buffer);    
            }
        }
    }

    return 0;

}
