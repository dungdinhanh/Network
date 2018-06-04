#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libent/group.h>
#include <libent/user.h>
#include <libclient/client_message.h>
#include <libparse/parser.h>
#include <libsocket/socket_api.h>
#include "group_client.h"




void createGroupClient(int socketID, int sender, char *groupName)
{
    MessageClient messageClient = setCreateGroup(groupName, sender);
    char *message = clientStructToJson(messageClient);
    sendMessage(socketID, message);
}

void joinGroup(int socketID, int sender, int groupID)
{
    MessageClient messageClient = setAddPersonToGroup(sender, groupID);
    char *message = clientStructToJson(messageClient);
    sendMessage(socketID, message);
}

Group * getListGroup(int socketID, int sender)
{
    // MessageClient messageclient = setListAllUsers()
    MessageClient messageClient = setListGroups(sender);
    char *message = clientStructToJson(messageClient);
    sendMessage(socketID, message);

    Group * group = (Group *)malloc(sizeof(Group) * MAX_CLIENT_MESS);
    char *response = receiveMessage(socketID);
    if(response == NULL)return NULL;
    MessageServer messageServer = serverJsonToStruct(response);
    int count = 0;
    while(1)
    {
        group[count] = newGroup();
        group[count].groupID = messageServer.object[count].id;
        strcpy(group[count].groupName, messageServer.object[count].user);
        if(group[count].groupID == -1)break;
        count++;
    }
    return group;
}

Group * getListGroupIn(int socketID, int sender)
{
    MessageClient messageClient = setListGroupsIn(sender);
    char *message = clientStructToJson(messageClient);
    sendMessage(socketID, message);
    Group * group = (Group *)malloc(sizeof(Group) * MAX_CLIENT_MESS);
    char *response = receiveMessage(socketID);
    if(response == NULL)return NULL;
    MessageServer messageServer = serverJsonToStruct(response);
    int count = 0;
    while(1)
    {
        group[count] = newGroup();
        group[count].groupID = messageServer.object[count].id;
        strcpy(group[count].groupName, messageServer.object[count].user);
        if(group[count].groupID == -1)break;
        count++;
    }
    return group;
}


void requestGroupChatRoom(int sender, int groupID, int socketID)
{
    MessageClient messageClient = setGroupChatRoom(sender, groupID);
    char *message = clientStructToJson(messageClient);
    sendMessage(socketID, message);
}

void sendMessageGroupClient(int sender, int groupID, char *userName ,char *message ,int socketID)
{
    MessageClient messageClient = setSendMessageGroup(message, sender, groupID);
    strcpy(messageClient.user, userName);
    char *messageJSON = clientStructToJson(messageClient);
    sendMessage(socketID, messageJSON);
}
