#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig/message.h>
#include <libserver/server_message.h>
#include <libsocket/socket_api.h>
#include <libparse/parser.h>
#include <libio/database_api.h>
#include <libconfig/code.h>
#include "auth_server.h"
#define MAX_LOGIN 1000


int logInServer(int connID, char *userName, char *password)
{
    // char *message = receiveMessage (connID);
    // MessageClient messageClient = clientJsonToStruct(message);
    // printf("user name: %s\npassword: %s\n", messageClient.user, messageClient.password);
    User user = getUser(userName, password);
    char *response;
    if(user.id == -1)
    {   
        printf("fail\n");
        //wait for complete function
        MessageServer messageServer = setFailResponse(FAIL_LOGIN);
        response = serverStructToJson(messageServer);
        sendMessage(connID, response);
        return 0;
    }
    else{
        printf("success\n");
        //wait for complete function
        MessageServer messageServer = setSuccessfulResponse(SUCCESS_LOGIN, user.id);
        response = serverStructToJson(messageServer);
        sendMessage (connID, response);
        return 1;
    }
}

int registerServer(int connID, char *userName, char *password)
{
    // char *message = receiveMessage(connID);
    // MessageClient messageClient = clientJsonToStruct(message);
    int insert = insertUser(userName, password);
    User user = getUser(userName, password);
    MessageServer messageServer = setSuccessfulResponse(SUCCESS_ADD_USER, user.id);
    char *message = serverStructToJson(messageServer);
    sendMessage(connID, message);
    // printf("Resutl : %d\n", insert); // not true return 0 still successful
    return insert;
}