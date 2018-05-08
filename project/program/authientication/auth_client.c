#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig/message.h>
#include <libclient/client_message.h>
#include <libsocket/socket_api.h>
#include <libparse/parser.h>
#include "auth_client.h"
#define MAX_LOGIN 1000

int logInClient(int socketID)
{
    char *userName = (char *)malloc(sizeof(char) * MAX_LOGIN);
    char *password = (char *)malloc(sizeof(char) * MAX_LOGIN);

    printf("Input user name: ");
    gets(userName);
    printf("Input password: ");
    gets(password);

    MessageClient messageClient = setLogIn(userName, password);
    char *message = clientStructToJson(messageClient);
    // printf("%s\n", message);
    sendMessage(socketID, message);
    char *response = (char *)malloc(sizeof(char) * MAX_LOGIN);
    MessageServer messageServer = serverJsonToStruct(response);
    if(messageServer.method == 1)return 0;
    else return 1;    
}


int registerClient(int socketID)
{
    char *userName = (char *)malloc(sizeof(char) * MAX_LOGIN);
    char *password = (char *)malloc(sizeof(char) * MAX_LOGIN);
    printf("Input user name: ");
    gets(userName);
    printf("Input password : ");
    gets(password);

    MessageClient messageClient = setRegister(userName, password);
    char *message = clientStructToJson(messageClient);
    sendMessage(socketID, message);
    char *response = (char *)malloc(sizeof(char) * MAX_CLIENT_MESS);
    MessageServer messageServer = serverJsonToStruct(response);
    if(messageServer.method == 1) return 0;
    else return 1;
}







