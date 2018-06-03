#include "client_message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig/message.h>


MessageClient setLogIn(char *userName, char *password)
{
	MessageClient messageClient = newMessageClient();
	messageClient.method = LOG_IN;
	setUserClient(messageClient, userName);
	setPasswordClient(messageClient, password);
	return messageClient;
}


MessageClient setLogOut(char *userName)
{
	MessageClient messageClient = newMessageClient();
	messageClient.method = LOG_OUT;
	return messageClient;
}


MessageClient setRegister(char *userName, char *password)
{
	MessageClient messageClient = newMessageClient();
	messageClient.method = REGISTER;
	setUserClient(messageClient, userName);
	setPasswordClient(messageClient, password);
	return messageClient;
}


MessageClient setSendMessage(char *message, int senderID, int receiverID)
{
	MessageClient messageClient = newMessageClient();
	messageClient.method = SEND_MESSAGE_C;
	setMessageClient(messageClient, message);
	messageClient.sender = senderID;
	messageClient.receiver = receiverID;
	return messageClient;
}



MessageClient setCreateGroup(char *groupName, int senderID)
{
	MessageClient messageClient = newMessageClient();
	messageClient.method = CREATE_GROUP;
	messageClient.sender = senderID;
	return messageClient;
}


MessageClient setAddPersonToGroup(int senderID, int groupID)
{
	MessageClient messageClient = newMessageClient();
	messageClient.method = ADD_PERSON_GROUP;
	messageClient.sender = senderID;
	messageClient.group = groupID;
	return messageClient;
}

MessageClient setListAllUsers(int sender, int groupID)//senderID and groupID can be -1 if there is no data for this field
{
	MessageClient messageClient = newMessageClient();
	messageClient.method = 6;
	messageClient.group = groupID;
	messageClient.sender = sender;
	return messageClient;
}

MessageClient setTwoChatRoom(int sender, int receiver)
{
	MessageClient messageClient = newMessageClient();
	messageClient.method = 11;
	messageClient.sender = sender;
	messageClient.receiver = receiver;
	return messageClient;
}
