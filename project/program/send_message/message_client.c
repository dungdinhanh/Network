#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig/message.h>
#include <libclient/client_message.h>
#include <libserver/server_message.h>
#include <libparse/parser.h>
#include <libsocket/socket_api.h>
#include <libent/user.h>
#include "message_client.h"


void sendMessageClient(int socketID, char *message, int sender, int receiver)
{
    MessageClient messageClient = setSendMessage(message, sender, receiver);
    char *messageJSON = clientStructToJson(messageClient);
    sendMessage(socketID, messageJSON);
    //return 1;
}


User *allUsersInSystemClient(int socketID, int sender)
{
    MessageClient messageClient = setListAllUsers(sender, -1);
    char *messageJSON = clientStructToJson(messageClient);
    sendMessage(socketID, messageJSON);
    char *response = receiveMessage(socketID);
    printf("%s\n", response);
    MessageServer messageServer = serverJsonToStruct(response);
    if(messageServer.method == 1)return NULL;
    User *user = (User *)malloc(sizeof(User) * MAX_USERS_IN);
    int count = 0;
    while(1)
    {
        if(messageServer.object[count].id == -1)break;
        user[count].id = messageServer.object[count].id;
        setUserName(user[count], messageServer.object[count].user);
        printf("user name : %s\n", user[count].userName);
        strcpy(user[count].password, "");   
        count++;
    }
    return user;
}  


