#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig/message.h>
#include <libclient/client_message.h>
#include <libserver/server_message.h>
#include <libparse/parser.h>
#include <libsocket/socket_api.h>
#include <libent/user.h>
#include <libio/database_api.h>
#include <libfdr/dllist.h>
#include <libfdr/jrb.h>
#include <libfdr/dllist.h>
#include <libfdr/jval.h>
#include <pthread.h>
#include "message_server.h"


Source source = NULL;
OnlineList onlineList = NULL;

void setUpEnvironment()
{
    source = make_jrb();
    onlineList = new_dllist();
}


void printDll(Dllist aList)
{
    OnlineList on;
    dll_traverse(on, aList)
    {
        printf("%d - ", jval_i(on->val));
    }
    printf("\n");
}

void printJRB()
{
    Source temp;
    Source temp2;
    jrb_traverse(temp, source)
    {
        printf("%d : ", jval_i(temp->key));
        Source inNode = (Source) jval_v(jrb_val(temp));
        jrb_traverse(temp2, inNode)
        {
            printf("%d - ", jval_i(temp2->key));
            printf("| queue: ");
            printDll((Dllist) jval_v(temp2->val));
            printf("|");
        }
        printf("\n");
    }
}




void printDllString(Dllist aList)
{
    OnlineList on;
    dll_traverse(on, aList)
    {
        printf("%s - ", jval_s(on->val));
    }
    printf("\n");
}


void newOnline(int userID)
{
    if(checkOnline(userID))return;
    dll_append(onlineList, new_jval_i(userID));
    Source temp;
    jrb_insert_int(source, userID, new_jval_v(make_jrb()));
    //printf("haha\n");
    temp = jrb_find_int(source, userID);
    temp = (Source)jval_v(jrb_val(temp));
    OnlineList node;
    //printf("after first \n");
    dll_traverse(node, onlineList)
    {
        if(jval_i(dll_val(node)) == userID) continue;
        jrb_insert_int(temp, jval_i(dll_val(node)), new_jval_v(new_dllist()));
        // printf("over there\n");
        Source innerTree = jrb_find_int(source, jval_i(dll_val(node)));
        innerTree = (Source)jval_v(jrb_val(innerTree));
        jrb_insert_int(innerTree, userID, new_jval_v(new_dllist()));
    }   
    printJRB();
    // printDll(source); 
}

void deleteOnline(int userID)
{
    if(!checkOnline(userID))return;
    OnlineList userOnline = getNodeOnline(userID);
    if (userOnline == NULL)return;
    dll_delete_node(userOnline);
    Source onlineNode = jrb_find_int(source, userID);
    if(onlineNode == NULL)return;
    jrb_delete_node(onlineNode);
    
    Source temp;
    jrb_traverse(temp, source)
    {
        Source innerTree = (Source) jval_v(jrb_val(temp));
        Source delNode = jrb_find_int(innerTree, userID);
        if(delNode != NULL)jrb_delete_node(delNode);
    }
}


OnlineList getNodeOnline(int userID)
{
    OnlineList temp;
    dll_traverse(temp, onlineList)
    {
        if(jval_i(dll_val(temp)) == userID)
        {
            return temp;
        }
    }
    return NULL;
}

int checkOnline(int userID)
{
    OnlineList temp;
    //int re;
    dll_traverse(temp, onlineList)
    {
        if(jval_i(dll_val(temp)) == userID)return 1;
    }
    return 0;
}

MessageQueue getMessageQueue(int sender, int receiver)
{
    Source inTree = jrb_find_int(source, receiver);
    if(inTree == NULL)
    {
        printf("no receiver found\n");
        return NULL;
    }
    inTree = (Source) jval_v(jrb_val(inTree));
    Source inNode = jrb_find_int(inTree, sender);
    if(inNode == NULL)
    {
        printf("no sender found\n");
        return NULL;
    };
    MessageQueue messageQueue = (MessageQueue) jval_v(jrb_val(inNode));
    return messageQueue;
}

void addMessageToSource(int sender, int receiver, char *message) // just add to source not print out or wirte log
{
    MessageQueue messageQueue = getMessageQueue(sender, receiver);
    if(messageQueue == NULL)return;
    dll_append(messageQueue, new_jval_s(message));
    //printDllString(messageQueue);
}

char *dequeueMessage(MessageQueue messageQueue)
{
    if(dll_empty(messageQueue))return NULL;
    MessageQueue first = dll_first(messageQueue);
    Jval val = dll_val(first);
    dll_delete_node(first);
    return jval_s(val);
}

char *readMessageFromSource(int sender, int receiver)
{
    MessageQueue messageQueue = getMessageQueue(sender, receiver);
    if(messageQueue == NULL){
        printf("no queue found\n");
        pthread_exit(3);
        return NULL;
    }
    if(dll_empty(messageQueue))return NULL;
    else return dequeueMessage(messageQueue);
}

// void addMessageToSource(int sender, int receiver, char * message) //add to source - need more action about write into history or print out
// {
//     Source senderNode = jrb_find_int(sender);
//     if(senderNode == NULL)return;
//     Source receiverNode = (Source) jval_v(jrb_val(senderNode));
//     if(receiverNode == NULL)return;
//     MessageQueue messageQueue = (MessageQueue) jval_v(jrb_val(receiverNode));
//     dll_
// }

//action for server ====-==========================================
void sendAllUsers(int socketID, int sender)
{
    MessageServer messageServer = setList();
    User *user = getAllUsers();
    int count = 0;
    while(1)
    {
        if(user[count].id == -1)break;
        Object object = initObject();
        strcpy(object.user, user[count].userName);
        object.id = user[count].id;
        addObject(&messageServer, object);
        count++;
    }
    char *message = serverStructToJson(messageServer);
    sendMessage(socketID, message);
}


void sendMessageBackToClient(int socketID,char *message, char *senderName, int sender, int receiver)
{
    MessageServer messageServer = setSendMessageToClient(message, senderName, sender, receiver, -1);
    char *messageJSON = serverStructToJson(messageServer);
    sendMessage(socketID, messageJSON);
}

// void receiveMessageStringFromClient(int sender, int )

// void getAllGroups(int socketID, int sender)
// {
//     MessageServer messageServer = setList();
    
// }