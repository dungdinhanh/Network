#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <libauth/auth_server.h>
#include <libio/database_api.h>
#include <libmessage/message_server.h>

typedef struct SenderReceiverSocket{
    int sender;
    int receiver;
    int socketID;
    int groupID;
    char *senderUserName;
}SenderReceiverSocket;



// char *popMessage(MessageQueue messageQueue)
// {
//     if(dll_empty(messageQueue))return NULL;
//     MessageQueue node = dll_first(messageQueue);
//     Jval data = dll_val(node);
//     dll_delete_node(node);
//     return jval_s(data);
// }
SenderReceiverSocket srsInit()
{
    SenderReceiverSocket srsObject;
    srsObject.groupID = -1;
    srsObject.receiver = -1;
    srsObject.sender = -1;
    srsObject.senderUserName = (char *)malloc(sizeof(char) * MAX_CLIENT_MESS);
    return srsObject;
}

void *continuousLoadMessage(void *senderReceiverSocket)
{
    SenderReceiverSocket *srsObject = (SenderReceiverSocket *) senderReceiverSocket;
    int senderID = srsObject->sender;
    int receiverID = srsObject->receiver;
    int socketID = srsObject->socketID;
    char *senderName = (char *)malloc(sizeof(char) * 100);
    strcpy(senderName, srsObject->senderUserName);
    while(1)
    {
        //printf("inside loops\n");
        char *message = readMessageFromSource(receiverID, senderID);
        if(message == NULL)continue;
        printf("%s\n", message);
        sendMessageBackToClient(socketID, message, senderName ,senderID, receiverID);
    }
}




void mainServer(int listenID);

void *clientHandle(void *connectID);

int main()
{
    startConnection();
    setUpEnvironment();
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
    int logInResult = -1;
    char *clientName = (char *)malloc(sizeof(char) * MAX_CLIENT_MESS);
    pthread_t listenMessageID;
    while(1)
    {
        char * message = receiveMessage(connectionID);
        if(message == NULL)
        {
            if(logInResult != -1)
            {
                deleteOnline(logInResult);
                pthread_cancel(&listenMessageID); //new not test
            }
            break;
        }
        printf("%s\n", message);
        MessageClient messageClient = clientJsonToStruct(message);
        if(messageClient.method == 0)
        {
            logInResult = logInServer(connectionID, messageClient.user, messageClient.password);
            if(logInResult == -1)return NULL;
            else
            {
                strcpy(clientName, messageClient.user);
                newOnline(logInResult);
                continue;
            }
        }

        if(messageClient.method == 2)
        {
            int registerResult = registerServer(connectionID, messageClient.user, messageClient.password);
            continue;
        }

        if(messageClient.method == 3)
        {
            addMessageToSource(messageClient.sender, messageClient.receiver, messageClient.message);
        }

        if(messageClient.method == 6)
        {
            sendAllUsers(connectionID, messageClient.sender);
        }

        if(messageClient.method == 11)
        {
            SenderReceiverSocket *senderReceiverSocket = (SenderReceiverSocket *)
            malloc(sizeof(SenderReceiverSocket));
            *senderReceiverSocket = srsInit();
            senderReceiverSocket->sender = messageClient.sender;
            senderReceiverSocket->receiver = messageClient.receiver;
            senderReceiverSocket->socketID = connectionID;
            strcpy(senderReceiverSocket->senderUserName, clientName);

            int lResult = pthread_create(&listenMessageID, NULL, continuousLoadMessage, 
            senderReceiverSocket);
            if(lResult)
            {
                printf("Error: Return Code from pthread_create() is %d\n", lResult);
            }
        }
    }   
}
