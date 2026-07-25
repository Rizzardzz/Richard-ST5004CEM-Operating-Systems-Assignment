/*
====================================================
ST5004CEM Operating Systems and Security

Task 4: Network Programming and IPC

Server Application

Features:
- Socket communication
- Multiple client handling
- Authentication
- Data validation
- Error handling

====================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>


#define PORT 8080
#define BUFFER_SIZE 1024


char username[] = "admin";
char password[] = "12345";



/*
----------------------------------------------------
Function: clientHandler()

Purpose:
Handles communication with each connected client.
----------------------------------------------------
*/
void *clientHandler(void *socketDesc)
{
    int clientSocket = *(int *)socketDesc;

    char buffer[BUFFER_SIZE];


    send(clientSocket,
         "Username: ",
         strlen("Username: "),
         0);


    memset(buffer,0,BUFFER_SIZE);

    recv(clientSocket,
         buffer,
         BUFFER_SIZE,
         0);


    char user[50];

    strcpy(user,buffer);



    send(clientSocket,
         "Password: ",
         strlen("Password: "),
         0);


    memset(buffer,0,BUFFER_SIZE);

    recv(clientSocket,
         buffer,
         BUFFER_SIZE,
         0);



    if(strcmp(user,username)==0 &&
       strcmp(buffer,password)==0)
    {
        send(clientSocket,
             "Authentication Successful\n",
             27,
             0);
    }
    else
    {
        send(clientSocket,
             "Authentication Failed\n",
             23,
             0);

        close(clientSocket);

        return NULL;
    }


    while(1)
    {
        memset(buffer,0,BUFFER_SIZE);


        int read = recv(clientSocket,
                        buffer,
                        BUFFER_SIZE,
                        0);


        if(read <=0)
        {
            printf("Client disconnected.\n");
            break;
        }


        printf("Client Message: %s\n",buffer);


        if(strcmp(buffer,"exit")==0)
        {
            break;
        }


        char reply[] =
        "Server received your message";


        send(clientSocket,
             reply,
             strlen(reply),
             0);
    }


    close(clientSocket);

    return NULL;
}
/*
----------------------------------------------------
Main Function

Creates server socket, accepts multiple clients,
and creates a thread for each client.
----------------------------------------------------
*/
int main()
{
    int serverSocket;
    int clientSocket;

    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;

    socklen_t clientLength;


    /*
    Create socket
    */
    serverSocket = socket(AF_INET,
                          SOCK_STREAM,
                          0);


    if(serverSocket < 0)
    {
        printf("Socket creation failed.\n");
        return 1;
    }



    /*
    Configure server address
    */
    serverAddress.sin_family = AF_INET;

    serverAddress.sin_addr.s_addr = INADDR_ANY;

    serverAddress.sin_port = htons(PORT);



    /*
    Bind socket to port
    */
    if(bind(serverSocket,
            (struct sockaddr *)&serverAddress,
            sizeof(serverAddress)) < 0)
    {
        printf("Binding failed.\n");
        return 1;
    }



    /*
    Start listening for clients
    */
    listen(serverSocket,5);



    printf("====================================\n");
    printf(" Server Started\n");
    printf(" Waiting for clients...\n");
    printf(" Port: %d\n",PORT);
    printf("====================================\n");



    while(1)
    {
        clientLength = sizeof(clientAddress);


        /*
        Accept client connection
        */
        clientSocket = accept(serverSocket,
                              (struct sockaddr *)&clientAddress,
                              &clientLength);



        if(clientSocket < 0)
        {
            printf("Client connection failed.\n");
            continue;
        }



        printf("New client connected.\n");



        /*
        Create a thread for each client
        */
        pthread_t thread;


        pthread_create(&thread,
                       NULL,
                       clientHandler,
                       (void *)&clientSocket);



        pthread_detach(thread);
    }



    close(serverSocket);


    return 0;
}
