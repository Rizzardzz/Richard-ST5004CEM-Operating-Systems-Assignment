/*
====================================================
ST5004CEM Operating Systems and Security

Task 4: Network Programming and IPC

Client Application

Features:
- Socket connection
- User authentication
- Data exchange
- Error handling

====================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


#define PORT 8080
#define BUFFER_SIZE 1024



/*
----------------------------------------------------
Main Function

Connects to server and exchanges messages.
----------------------------------------------------
*/
int main()
{
    int clientSocket;

    struct sockaddr_in serverAddress;

    char buffer[BUFFER_SIZE];



    /*
    Create socket
    */
    clientSocket = socket(AF_INET,
                          SOCK_STREAM,
                          0);



    if(clientSocket < 0)
    {
        printf("Socket creation failed.\n");
        return 1;
    }



    /*
    Configure server address
    */

    serverAddress.sin_family = AF_INET;

    serverAddress.sin_port = htons(PORT);



    serverAddress.sin_addr.s_addr =
        inet_addr("127.0.0.1");



    /*
    Connect to server
    */
    if(connect(clientSocket,
               (struct sockaddr *)&serverAddress,
               sizeof(serverAddress)) < 0)
    {
        printf("Connection failed.\n");
        return 1;
    }



    printf("Connected to server.\n");



    /*
    Receive username request
    */

    memset(buffer,0,BUFFER_SIZE);

    recv(clientSocket,
         buffer,
         BUFFER_SIZE,
         0);


    printf("%s",buffer);



    scanf("%s",buffer);


    send(clientSocket,
         buffer,
         strlen(buffer),
         0);



    /*
    Receive password request
    */

    memset(buffer,0,BUFFER_SIZE);


    recv(clientSocket,
         buffer,
         BUFFER_SIZE,
         0);



    printf("%s",buffer);



    scanf("%s",buffer);


    send(clientSocket,
         buffer,
         strlen(buffer),
         0);



    /*
    Authentication response
    */

    memset(buffer,0,BUFFER_SIZE);


    recv(clientSocket,
         buffer,
         BUFFER_SIZE,
         0);



    printf("%s\n",buffer);



    if(strstr(buffer,"Failed"))
    {
        close(clientSocket);
        return 0;
    }



    /*
    Message communication
    */
    getchar();

    while(1)
    {
        printf("Enter message: ");

        fgets(buffer,
              BUFFER_SIZE,
              stdin);



        buffer[strcspn(buffer,"\n")] = 0;



        send(clientSocket,
             buffer,
             strlen(buffer),
             0);



        if(strcmp(buffer,"exit")==0)
            break;



        memset(buffer,0,BUFFER_SIZE);



        recv(clientSocket,
             buffer,
             BUFFER_SIZE,
             0);



        printf("Server: %s\n",buffer);
    }



    close(clientSocket);


    return 0;
}
