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
	messageClient.method = SEND_MESSAGE;
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