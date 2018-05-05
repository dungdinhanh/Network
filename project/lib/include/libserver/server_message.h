#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libconfig/message.h>
#define SUCCESS 0
#define FAILS 1
#define SEND_MESSAGE 2
#define LIST 3



MessageServer setSuccessfulResponse(int code)
{
	MessageServer messageServer = newMessageServer();
	setMethodServer(messageServer, SUCCESS);
	setCodeServer(messageServer, code);
	return messageServer;
}

MessageServer setFailResponse(int code)
{
	MessageServer messageServer = newMessageServer();
	setCodeServer(messageServer, code);
	setMethodServer(messageServer, FAILS);
	return messageServer;
}

MessageServer setSendMessageToClient(char *message, char*senderName, int sender_id, int receiver_id, int group_id)
{
	MessageServer messageServer = newMessageServer();
	setMethodServer(messageServer, SEND_MESSAGE);
	setMessageServer(messageServer, message);
	setSenderNameServer(messageServer, senderName);
	setSenderServer(messageServer, sender_id);
	setReceiverServer(messageServer, receiver_id);
	return messageServer;
}


