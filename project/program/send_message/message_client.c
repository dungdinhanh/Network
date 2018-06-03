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

void requestSetTwoChatRoom(int socketID, int sender, int receiver)
{
     MessageClient messageClient = setTwoChatRoom(sender, receiver);
     char *messageJSON = clientStructToJson(messageClient);
     sendMessage(socketID, messageJSON);
}


User *allUsersInSystemClient(int socketID, int sender)
{
    MessageClient messageClient = setListAllUsers(sender, -1);
    char *messageJSON = clientStructToJson(messageClient);
    sendMessage(socketID, messageJSON);
    char *response = receiveMessage(socketID);
    // printf("%s\n", response);
    MessageServer messageServer = serverJsonToStruct(response);
    // printf("after parsing \n");
    if(messageServer.method == 1)return NULL;
    User *user = (User *)malloc(sizeof(User) * MAX_USERS_IN);
    int count = 0;
    while(1)
    {
        // printf("into loops %d\n", count);
        
        user[count] = newUser();
        // printf("error here 1 \n");
        user[count].id = messageServer.object[count].id;
        // printf("error here 2\n");
        strcpy(user[count].userName, messageServer.object[count].user);
        // printf("error here 3\n");
        // printf("user name : %s - %d - %d\n", user[count].userName, user[count].id, count);;
        strcpy(user[count].password, "");  
        if(messageServer.object[count].id == -1)break; 
        count++;
    }
    count = 0;
    // while(1)
    // {
    //     if(user[count].id == -1)break;
    //     printf("%d. %s\n", user[count].id, user[count].userName);
    //     count++;
    // }
    return user;
}  


