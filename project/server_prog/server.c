#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libauth/auth_server.h>
#include <libio/database_api.h>

void mainServer(int listenID);

void *clientHandle(void *connectID);

int main()
{
    startConnection();
    int listenID = getListen();
    // int connectID = getAccept(listenID);
    mainServer(listenID);
    // // logInServer(connectID);
    // registerServer(connectID);
    // //close(connectID);
    // //close(listenID);
    // // close(connectID);
    // // close(listenID);
    closeConnection();
    return 0;
}


void mainServer(int listenID)
{
    while(1)
    {
        pthread_t clientThread;
        int connectID = getAccept(listenID);
        int tResult = pthread_create(&clientThread, NULL, clientHandle, (void *)connectID);
        if(tResult)
        {
            printf("Error: Return Code from pthread_create() is %d\n", tResult);
            continue;
        }
    }
}


void *clientHandle(void *connectID)
{
    int connectionID = (int)connectID;
    while(1)
    {
        char * message = receiveMessage(connectionID);
        printf("%s\n", message);
        MessageClient messageClient = clientJsonToStruct(message);
        if(messageClient.method == 0)
        {
            int logInResult = logInServer(connectionID, messageClient.user, messageClient.password);
            if(logInResult == 0)return NULL;
            else continue;
        }

        if(messageClient.method == 2)
        {
            int registerResult = registerServer(connectionID, messageClient.user, messageClient.password);
            continue;
        }
    }   
}