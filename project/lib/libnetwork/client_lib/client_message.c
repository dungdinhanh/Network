#include "client_message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig/message.h>


MessageClient setLogIn(char *userName, char *password)
{
	MessageClient messageClient = newMessageClient();
	setMethodClient(messageClient, LOG_IN);
	setUserClient(messageClient, userName);
	setPasswordClient(messageClient, password);
	return messageClient;
}


MessageClient setLogOut(char *userName)
{
	MessageClient messageClient = newMessageClient();
	setMethodClient(messageClient, LOG_OUT);
	return messageClient;
}


MessageClient setRegister(char *userName, char *password)
{
	MessageClient messageClient = newMessageClient();
	setMethodClient(messageClient, REGISTER);
	setUserClient(messageClient, userName);
	setPasswordClient(messageClient, password);
	return messageClient;
}


MessageClient setSendMessage(char *message, int senderID, int receiverID)
{
	MessageClient messageClient = newMessageClient();
	setMethodClient(messageClient, SEND_MESSAGE);
	setMessageClient(messageClient, message);
	setSenderClient(messageClient, senderID);
	setReceiverClient(messageClient, receiverID);
	return messageClient;
}



MessageClient setCreateGroup(char *groupName, int senderID)
{
	MessageClient messageClient = newMessageClient();
	setMethodClient(messageClient, CREATE_GROUP);
	setSenderClient(messageClient, senderID);
	return messageClient;
}


MessageClient setAddPersonToGroup(int senderID, int groupID)
{
	MessageClient messageClient = newMessageClient();
	setMethodClient(messageClient, ADD_PERSON_GROUP);
	setSenderClient(messageClient, senderID);
	setGroupClient(messageClient, groupID);
	return messageClient;
}
