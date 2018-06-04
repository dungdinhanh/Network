#ifndef _CLIENT_MESSAGE_H_
#define _CLIENT_MESSAGE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig/message.h>
#define MAX_CLIENT_MESS 1000
#define LOG_IN 0
#define LOG_OUT 1
#define REGISTER 2
#define SEND_MESSAGE_C 3
#define CREATE_GROUP 4
#define ADD_PERSON_GROUP 5
#define LIST_USERS 6
#define SEND_FILE 7
#define LIST_GROUPS 8
#define LIST_GROUPS_IN 9
#define TWO_CHAT 11


MessageClient setLogIn(char *userName, char *password);

MessageClient setLogOut(char *userName);

MessageClient setRegister(char *userName, char *password);

MessageClient setSendMessage(char *message, int senderID, int receiverID);

MessageClient setSendMessageGroup(char *message, int sender, int groupID);


MessageClient setCreateGroup(char *groupName, int senderID);

MessageClient setAddPersonToGroup(int senderID, int groupID);

MessageClient setListAllUsers(int senderID, int groupID);//senderID and groupID can be -1 if there is no data for this field

MessageClient setTwoChatRoom(int sender, int receiver);


MessageClient setGroupChatRoom(int sender, int groupID);

MessageClient setListGroups(int sender);

MessageClient setListGroupsIn(int sender);



#endif