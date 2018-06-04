#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libent/group.h>
#include <libent/user.h>
#include <libparse/parser.h>
#include <libserver/server_message.h>
#include <libio/database_api.h>
#include <libsocket/socket_api.h>
#include <libfdr/dllist.h>
#include <libfdr/jrb.h>
#include <libfdr/jval.h>
#include <pthread.h>
#include "group_action.h"


GroupSource gSource;
GroupList gList;



void setUpGroupSource()
{
    gSource = make_jrb();
    gList = new_dllist();
    Group * group = getAllGroups();
    int count = 0;
    while(1)
    {
        if(group[count].groupID == -1)break;
        jrb_insert_int(gSource, group[count].groupID, new_jval_v(make_jrb()));
        GroupSource innerNode = jrb_find_int(gSource, group[count].groupID);
        innerNode = (GroupSource) jval_v(jrb_val(innerNode));
        int countUser = 0;
        while(1)
        {
            if(group[count].user[countUser] == -1)break;
            jrb_insert_int(innerNode, group[count].user[countUser], new_jval_v(new_dllist()));
            countUser++;
        }
        dll_append(gList, new_jval_v(&group[count]));
        count++;
    }
}

Dllist getGroupList()
{
    return gList;
}

Dllist getMessageGroupQueue(int groupID, int receiver)
{
    GroupSource groupNode = jrb_find_int(gSource, groupID);
    if(groupNode == NULL)return NULL;
    groupNode = (GroupSource) jval_v(jrb_val(groupNode));
    GroupSource innerNode = jrb_find_int(groupNode, receiver);
    if(innerNode == NULL)
    {
        // pthread_exit(4);
        return NULL;
    }
    Dllist messageQueue = (Dllist) jval_v(jrb_val(innerNode));
    return messageQueue;
}

void addMessageToGroupSource(int groupID, int receiver ,char *senderName ,char *message)
{
    char *messageIntoSource = (char *)malloc(sizeof(char) * MAX_LINE);
    sprintf(messageIntoSource, "%s: %s", senderName ,message);
    Dllist messageQueue = getMessageGroupQueue(groupID, receiver);
    if(messageQueue == NULL)
    {
        return;
    }
    dll_append(messageQueue, new_jval_s(messageIntoSource));
}

void addMessageToGroupSourceAll(int groupID, int sender, char *senderName, char *message)
{
    char *messageIntoSource = (char *)malloc(sizeof(char) * MAX_LINE);
    sprintf(messageIntoSource, "%s : %s", senderName, message);
    GroupSource node = jrb_find_int(gSource, groupID);
    node = (GroupSource) jval_v(jrb_val(node));
    GroupSource temp;
    jrb_traverse(temp, node)
    {
        if(jval_i(temp->key) == sender)continue;
        Dllist listMessage = (Dllist) jval_v(temp->val);
        dll_append(listMessage, new_jval_s(messageIntoSource));
    }
}

char *getMessageFromQueue(Dllist messageQueue)
{
    if(dll_empty(messageQueue))return NULL;
    Dllist node = dll_first(messageQueue);
    Jval data = dll_val(node);
    dll_delete_node(node);
    return jval_s(data);
}



char * readMessageFromGroupSource(int groupID, int receiver)
{
    Dllist messageQueue = getMessageGroupQueue(groupID, receiver);
    if(messageQueue == NULL)
    {
        return NULL;
    }
    return getMessageFromQueue(messageQueue);    
}


void sendSussesfulResponse(int connectionID)
{
    MessageServer messageServer = setSuccessfulResponse(0, connectionID);
    char *message = serverStructToJson(messageServer);
    sendMessage(connectionID, message);
}


void sendFailResponse(int connectionID)
{
    MessageServer messageServer = setSuccessfulResponse(0, connectionID);
    char *message = serverStructToJson(messageServer);
    sendMessage(connectionID, message);
}


void createGroup(char *groupName, int creator, int connectionID)
{
    int result = insertGroup(groupName, creator);
    if(result == 1)sendSussesfulResponse(connectionID);
    // MessageServer messageServer = setSuccessfulResponse(0, creator);
    // char *message = serverStructToJson(messageServer);
    // sendMessage(connectionID, message);
    setUpGroupSource();
}


void insertUserToGroup(int sender, int group, int connectionID)
{
    int result = addUserToGroup(sender, group);
    if(result == 1)sendSussesfulResponse(connectionID);
    setUpGroupSource();
}


void sendListGroups(int sender, int connectionID)
{
    MessageServer messageServer = setList();
    Dllist node;
    if(gList == NULL)return;
    dll_traverse(node, gList)
    {   
        Object object = initObject();
        Group * currentGroup = (Group *) jval_v(dll_val(node));
        object.id = currentGroup->groupID;
        strcpy(object.user, currentGroup->groupName);
        addObject(&messageServer, object);
    }
    char *messageJSON = serverStructToJson(messageServer);
    sendMessage(connectionID, messageJSON);
}


void sendListGroupsIn(int sender, int connectionID)
{
    MessageServer messageServer = setList();
    messageServer.receiver = sender;
    Dllist node;
    int *groupIDList = getGroupsForUsers(sender);
    dll_traverse(node, gList)
    {
        int count = 0;
        Group *temp = (Group *)jval_v(dll_val(node));
        while(1)
        {
            if(groupIDList[count] == -1)break;
            if(groupIDList[count] == temp->groupID)
            {
                Object object = initObject();
                object.id = groupIDList[count];
                printf("%d\n", object.id);
                strcpy(object.user, temp->groupName);
                addObject(&messageServer, object);
            }
            count++;
        }
    }
    char *messageJSON = serverStructToJson(messageServer);
    sendMessage(connectionID, messageJSON);
}

